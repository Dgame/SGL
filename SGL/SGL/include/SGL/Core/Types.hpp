#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>

#if 0

using int8  = signed char;
using uint8 = unsigned char;

using int16  = signed short;
using uint16 = unsigned short;

using int32  = signed int;
using uint32 = unsigned int;

using int64  = signed long;
using uint64 = unsigned long;

#else

using int8 = std::int8_t;
using uint8 = std::uint8_t;

using int16 = std::int16_t;
using uint16 = std::uint16_t;

using int32 = std::int32_t;
using uint32 = std::uint32_t;

using int64 = std::int64_t;
using uint64 = std::uint64_t;

#endif

using float32 = float;
using float64 = double;
using float80 = long double;

#endif