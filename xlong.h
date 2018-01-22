#ifndef xlong_h
#define xlong_h

#include <istream>
#include <ostream>

#include <vector>
#include <limits>

template <typename T> class Xlong;

template<typename T> std::istream& operator>>(std::istream& stream, Xlong<T> xlong);
template<typename T> std::ostream& operator<<(std::ostream& stream, Xlong<T> xlong);

template <typename T>
class Xlong {
protected:
	std::vector<T> value; // big-endian, base std::numeric_limits<T>::max()-std::numeric_limits<T>::min()+1
	bool sign; // true means +, false means -
public:
	Xlong() {}
	Xlong(const Xlong<T>& o): value(o.value), sign(o.sign) {}
	Xlong(const T& value, bool sign=true): value(1, value), sign(sign) {}
	Xlong(const T& value, signed sign): Xlong(value*sign, sign>0) {}

	bool operator<(const T& o) const;
	bool operator<(const Xlong<T>& o) const;
	bool operator>(const T& o) const { return (Xlong<T>)o < *this; }
	bool operator>(const Xlong<T>& o) const { return o < *this; }
	bool operator!=(const T& o) { return *this < o || *this > o; }
	bool operator!=(const Xlong<T>& o) { return *this < o || *this > o; }
	bool operator==(const T& o) { return !( *this != o ); }
	bool operator==(const Xlong<T>& o) { return !( *this != o ); }

	Xlong<T>& negate();
	Xlong<T>& operator+=(const Xlong<T>& o);
	Xlong<T>& operator-=(const Xlong<T>& o) { return *this += -o; };
	Xlong<T>& operator*=(const Xlong<T>& o);
	Xlong<T>& operator/=(const Xlong<T>& o);
	Xlong<T>& operator%=(const Xlong<T>& o);
	
	Xlong<T> operator-() const { Xlong<T> copy(*this); return copy.negate(); };
	Xlong<T> operator+(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy += o; }
	Xlong<T> operator-(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy -= o; }
	Xlong<T> operator*(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy *= o; }
	Xlong<T> operator/(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy /= o; }
	template<typename T2> T2 operator%(const T2& o) const;
	Xlong<T> operator%(const Xlong<T>& o) const { Xlong<T> copy(*this); return copy %= o; }

	/*
	template<typename T_> friend std::istream& operator<<(std::istream& stream, const Xlong<T_>& xlong);
	template<typename T_> friend std::ostream& operator>>(std::ostream& stream, const Xlong<T_>& xlong);
	*/
};

#endif // xlong_h
