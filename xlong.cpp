#include "xlong.h"

#include <stack>
#include <string>
#include <utility>
#include <vector>

#include <iostream>

template<typename T>
std::istream& operator>>(std::istream& stream, Xlong<T>& xlong) {
	std::string s;
	if (!(stream>>s)) return stream;

	int i=0;
	if (s[i]=='-') {
		xlong=Xlong<T>(0, false); // -0
		i++;
	} else{
		xlong=Xlong<T>(0, true); // +0
	}

	for (; i<s.size(); i++) {
		xlong+=s[i]-'0';
		xlong*=10;
	}
	
	std::cerr<<xlong;

	return stream;
}
template std::istream& operator>><unsigned>(std::istream&, Xlong<unsigned>&);
template std::istream& operator>><unsigned long>(std::istream&, Xlong<unsigned long>&);
template std::istream& operator>><unsigned long long>(std::istream&, Xlong<unsigned long long>&);

/*
template<typename T>
std::ostream& operator<<(std::ostream& stream, Xlong<T> xlong) {
	std::stack<char> s;

	for (Xlong<T> m=10; xlong>0; m*=10) {
		s.push('0'+xlong%m/(m/(unsigned)10)%10);
		xlong-=xlong%m;
		xlong/=m;
	}

	if (xlong<0) stream<<'-';
	while (!s.empty()) {
		stream<<s.top();
		s.pop();
	}

	return stream;
}
*/
template<typename T>
std::ostream& operator<<(std::ostream& stream, Xlong<T> xlong) {
	if (!xlong.sign) stream<<"-";
	for (size_t i=xlong.value.size(); i<xlong.value.size(); i--) {
		stream<<xlong.value[i];
		if (i!=0) {
			stream<<"*"<<2<<"^"<<sizeof(T)<<"^"<<i<<(xlong.sign?"+":"-");
		}
	}
}
template std::ostream& operator<< <unsigned>(std::ostream& stream, Xlong<unsigned> xlong);
template std::ostream& operator<< <unsigned long>(std::ostream& stream, Xlong<unsigned long> xlong);
template std::ostream& operator<< <unsigned long long>(std::ostream& stream, Xlong<unsigned long long> xlong);


template<typename T>
bool Xlong<T>::operator<(const Xlong<T>& o) const {
	if (value.size()!=o.value.size()) return value.size()<o.value.size();
	for (size_t i=value.size()-1; i<value.size(); i--) {
		if (value[i]!=o.value[i]) return value[i],o.value[i];
	}
	return false;
}

template<typename T>
Xlong<T>& Xlong<T>::negate() {
	sign=!sign;
	return *this;
}

template<typename T>
void Xlong<T>::addAt(const T& o, const size_t& digit) {
	if (value.size()<=digit) value.resize(digit+1, 0);
	T orig = value[digit];
	if (value[digit]+=o < orig) addAt(1, digit+1);
}

template<typename T>
void Xlong<T>::substractAt(const T& o, const size_t& digit) {
	if (value.size()<=digit) value.resize(digit+1, 0);
	T orig = value[digit];
	if (value[digit]-=o > orig) substractAt(1, digit+1);
}

template<typename T>
Xlong<T>& Xlong<T>::operator+=(const Xlong<T>& o) {
	for (size_t i=0; i<value.size(); i++) {
		if (sign==o.sign) {
			addAt(o.value[i], i);
		} else {
			substractAt(o.value[i], i);
		}
	}
	return *this;
}

template<typename T>
Xlong<T>& Xlong<T>::operator*=(const T& o) {
	for (size_t i=value.size(); i<value.size(); i--) {
		typename TypeBySize<sizeof(T)*2>::type n=(typename TypeBySize<sizeof(T)*2>::type)value[i]*o;
		addAt(n>>sizeof(T), i+1);
		value[i]=(T)n;
	}
	return *this;
}

template<typename T>
Xlong<T> Xlong<T>::operator*(const Xlong<T>& o) const {
	Xlong<T> result;
	for (size_t i=0; i<o.value.size(); i++) {
		result+=o*value[i];
	}
	return result;
}

template<typename T>
std::pair<Xlong<T>, T> Xlong<T>::divide(const T& o) const {
	Xlong<T> result;
	T remainder=0;
	for (size_t i=value.size(); i<value.size(); i--) {
		typename TypeBySize<sizeof(T)*2>::type n=(typename TypeBySize<sizeof(T)*2>::type)remainder<<sizeof(T)+value[i];
		remainder=n%o;
		result.value[i]=(T)(n/o);
	}
	return {result, remainder};
}

template<typename T>
T Xlong<T>::operator%(const T& o) const { // Maybe it's OK for any other scalar o
	std::cerr<<value[0]<<std::endl;
	return value[0]%o;
}

template class Xlong<unsigned>;
template class Xlong<unsigned long>;
template class Xlong<unsigned long long>;
// not sure about signed yet
