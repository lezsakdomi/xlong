template <uint8_t BITS>
struct TypeBySize {
	typedef void type;
};

template<> struct TypeBySize<1> { typedef uint8_t  type; };
template<> struct TypeBySize<2> { typedef uint16_t type; };
template<> struct TypeBySize<4> { typedef uint32_t type; };
template<> struct TypeBySize<8> { typedef uint64_t type; };

template<> struct TypeBySize<16>  { typedef __int128  type; }; // GCC required
