#include "xlong.h"

#include <stack>
#include <string>
#include <vector>

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
	
	return stream;
}
template std::istream& operator>><unsigned>(std::istream&, Xlong<unsigned>&);
template std::istream& operator>><unsigned long>(std::istream&, Xlong<unsigned long>&);
template std::istream& operator>><unsigned long long>(std::istream&, Xlong<unsigned long long>&);

template<typename T>
std::ostream& operator<<(std::ostream& stream, Xlong<T> xlong) {
	std::stack<char> s;

	for (Xlong<T> m=10; xlong>0; m*=10) {
		s.push('0'+xlong%m/(m/10)%10);
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
template std::ostream& operator<< <unsigned>(std::ostream& stream, Xlong<unsigned> xlong);
template std::ostream& operator<< <unsigned long>(std::ostream& stream, Xlong<unsigned long> xlong);
template std::ostream& operator<< <unsigned long long>(std::ostream& stream, Xlong<unsigned long long> xlong);

template class Xlong<unsigned>;
template class Xlong<unsigned long>;
template class Xlong<unsigned long long>;
// not sure about signed yet
