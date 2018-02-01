#ifndef xlong_h
#define xlong_h

#include <iostream>
#include <utility>
#include <vector>

#include <limits>
#include "typebysize.h"

template<typename T> class Xlong;

template<typename T> std::istream& operator>>(std::istream& stream, Xlong<T>& xlong);
template<typename T> std::ostream& operator<<(std::ostream& stream, Xlong<T> xlong);

template <typename T>
class Xlong {
protected:
	std::vector<T> value; // big-endian, base std::numeric_limits<T>::max()-std::numeric_limits<T>::min()+1
	bool sign; // true means +, false means -
public:
	friend std::istream& operator>> <T>(std::istream& stream, Xlong<T>& xlong);
	friend std::ostream& operator<< <T>(std::ostream& stream, Xlong<T> xlong);

	Xlong() {}
	Xlong(const Xlong<T>& o): value(o.value), sign(o.sign) {}
	Xlong(const T& value, bool sign=true, size_t size=1): value(size, value), sign(sign) {}
	Xlong(const T& value, signed sign): Xlong(value*sign, sign>0) {}
	Xlong<T>& operator=(const Xlong<T>& o) { value=o.value; sign=o.sign; }

	bool operator<(const Xlong<T>& o) const;
	bool operator>(const Xlong<T>& o) const { return o < *this; }
	bool operator!=(const Xlong<T>& o) { return *this < o || *this > o; }
	bool operator==(const Xlong<T>& o) { return !( *this != o ); }

	Xlong<T>& negate();
	Xlong<T> operator-() const { Xlong<T> copy(*this); return copy.negate(); };

	void addAt(const T& o, const size_t& digit);
	void substractAt(const T& o, const size_t& digit);
	Xlong<T>& operator+=(const Xlong<T>& o);
	Xlong<T>& operator-=(const Xlong<T>& o) { return *this += -o; };
	Xlong<T> operator+(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy += o; }
	Xlong<T> operator-(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy -= o; }

	Xlong<T>& operator*=(const T& o);
	Xlong<T> operator*(const Xlong<T>& o) const;
	template<typename T2> Xlong<T>& operator*=(const T2& o) { operator=(operator*(o)); }
	template<typename T2> Xlong<T> operator*(const T2& o) { Xlong<T> copy(*this); return copy*=o; }

	T operator%(const T& o) const;
	std::pair<Xlong<T>, T> divide(const T& o) const;
	template<typename T2> Xlong<T> operator/(const T2& o) const { return divide(o).first; }
	//template<typename T2> T operator%(const T2& o) const { return divide(o).second; } // T2 operator%(const T2& o) const is faster
	//Xlong<T>& operator/=(const Xlong<T>& o);
	
	//Xlong<T> operator/(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy /= o; }
	template<typename T2> T2 operator%(const T2& o) const;
	//Xlong<T> operator%(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy %= o; }
	//Xlong<T>& operator%=(const Xlong<T>& o);
};

#endif // xlong_h
