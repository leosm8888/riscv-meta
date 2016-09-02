//
//  riscv-test-mult.cc
//

#undef NDEBUG

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <type_traits>

#include "riscv-endian.h"
#include "riscv-types.h"
#include "riscv-bits.h"

using namespace riscv;

struct _u16
{
	typedef u8 utype;

	union {
		u8                          b[2];
	#if _BYTE_ORDER == _LITTLE_ENDIAN
		struct { u8 lo;  u8 hi; }   p;
	#else
		struct { u8 hi;  u8 lo; }   p;
	#endif
	} val;

	inline _u16() : val{ .b = { 0 } } {}
	inline _u16(const _u16 &o) : val{ .p = o.val.p } {}

	#if _BYTE_ORDER == _LITTLE_ENDIAN
	inline _u16(u8 hi, u8 lo) : val{ .p = { .lo = lo, .hi = hi } } {}
	#else
	inline _u16(u8 hi, u8 lo) : val{ .p = { .hi = hi, .lo = lo } } {}
	#endif
};

struct _s16
{
	typedef u8 utype;
	typedef s8 stype;

	union {
		u8                          b[2];
	#if _BYTE_ORDER == _LITTLE_ENDIAN
		struct { u8 lo;  s8 hi; }   p;
	#else
		struct { s8 hi;  u8 lo; }   p;
	#endif
	} val;

	inline _s16() : val{ .b = { 0 } } {}
	inline _s16(const _s16 &o) : val{ .p = o.val.p } {}

	#if _BYTE_ORDER == _LITTLE_ENDIAN
	inline _s16(s8 hi, u8 lo) : val{ .p = { .lo = lo, .hi = hi } } {}
	#else
	inline _s16(s8 hi, u8 lo) : val{ .p = { .hi = hi, .lo = lo } } {}
	#endif
};

struct _u32
{
	typedef u16 utype;

	union {
		u8                          b[4];
	#if _BYTE_ORDER == _LITTLE_ENDIAN
		struct { u16 lo; u16 hi; }  p;
	#else
		struct { u16 hi; u16 lo; }  p;
	#endif
	} val;

	inline _u32() : val{ .b = { 0 } } {}
	inline _u32(const _u32 &o) : val{ .p = o.val.p } {}

	#if _BYTE_ORDER == _LITTLE_ENDIAN
	inline _u32(u16 hi, u16 lo) : val{ .p = { .lo = lo, .hi = hi } } {}
	#else
	inline _u32(u16 hi, u16 lo) : val{ .p = { .hi = hi, .lo = lo } } {}
	#endif
};

struct _s32
{
	typedef u16 utype;
	typedef s16 stype;

	union {
		u8                          b[4];
	#if _BYTE_ORDER == _LITTLE_ENDIAN
		struct { u16 lo; s16 hi; }  p;
	#else
		struct { s16 hi; u16 lo; }  p;
	#endif
	} val;

	inline _s32() : val{ .b = { 0 } } {}
	inline _s32(const _s32 &o) : val{ .p = o.val.p } {}

	#if _BYTE_ORDER == _LITTLE_ENDIAN
	inline _s32(s16 hi, u16 lo) : val{ .p = { .lo = lo, .hi = hi } } {}
	#else
	inline _s32(s16 hi, u16 lo) : val{ .p = { .hi = hi, .lo = lo } } {}
	#endif
};

struct _u64
{
	typedef u32 utype;

	union {
		u8                          b[8];
	#if _BYTE_ORDER == _LITTLE_ENDIAN
		struct { u32 lo; u32 hi; }  p;
	#else
		struct { u32 hi; u32 lo; }  p;
	#endif
	} val;

	inline _u64() : val{ .b = { 0 } } {}
	inline _u64(const _u64 &o) : val{ .p = o.val.p } {}

	#if _BYTE_ORDER == _LITTLE_ENDIAN
	inline _u64(u32 hi, u32 lo) : val{ .p = { .lo = lo, .hi = hi } } {}
	#else
	inline _u64(u32 hi, u32 lo) : val{ .p = { .hi = hi, .lo = lo } } {}
	#endif
};

struct _s64
{
	typedef u32 utype;
	typedef s32 stype;

	union {
		u8                          b[8];
	#if _BYTE_ORDER == _LITTLE_ENDIAN
		struct { u32 lo; s32 hi; }  p;
	#else
		struct { s32 hi; u32 lo; }  p;
	#endif
	} val;

	inline _s64() : val{ .b = { 0 } } {}
	inline _s64(const _s64 &o) : val{ .p = o.val.p } {}

	#if _BYTE_ORDER == _LITTLE_ENDIAN
	inline _s64(s32 hi, u32 lo) : val{ .p = { .lo = lo, .hi = hi } } {}
	#else
	inline _s64(s32 hi, u32 lo) : val{ .p = { .hi = hi, .lo = lo } } {}
	#endif
};

struct _u128
{
	typedef u64 utype;

	union {
		u8                          b[16];
	#if _BYTE_ORDER == _LITTLE_ENDIAN
		struct { u64 lo; u64 hi; }  p;
	#else
		struct { u64 hi; u64 lo; }  p;
	#endif
	} val;

	inline _u128() : val{ .b = { 0 } } {}
	inline _u128(const _u128 &o) : val{ .p = o.val.p } {}

	#if _BYTE_ORDER == _LITTLE_ENDIAN
	inline _u128(u64 hi, u64 lo) : val{ .p = { .lo = lo, .hi = hi } } {}
	#else
	inline _u128(u64 hi, u64 lo) : val{ .p = { .hi = hi, .lo = lo } } {}
	#endif
};

struct _s128
{
	typedef u64 utype;
	typedef s64 stype;

	union {
		u8                          b[16];
	#if _BYTE_ORDER == _LITTLE_ENDIAN
		struct { u64 lo; s64 hi; }  p;
	#else
		struct { s64 hi; u64 lo; }  p;
	#endif
	} val;

	inline _s128() : val{ .b = { 0 } } {}
	inline _s128(const _s128 &o) : val{ .p = o.val.p } {}

	#if _BYTE_ORDER == _LITTLE_ENDIAN
	inline _s128(s64 hi, u64 lo) : val{ .p = { .lo = lo, .hi = hi } } {}
	#else
	inline _s128(s64 hi, u64 lo) : val{ .p = { .hi = hi, .lo = lo } } {}
	#endif
};


/*
 *  Babbage multiplication, Passages from the Life of
 *  a Philosopher, Larger numbers treated, page 125
 *
 *                               |       x0 * y0       |
 *      +             |       x1 * y0       |
 *      +             |       x0 * y1       |
 *      +  |       x1 * y1       |
 *      +  |         C|         C|
 *
 *  z0  =  x0 * y0
 *  z1  =  x1 * y0
 *  z2  =  x0 * y1
 *  z3  =  x1 * y1
 *
 *  r   =  z0 + ((z1 + z2) << qb) + (z3 << hb)
 */


/* multiply unsigned unsigned */

template <typename R>
R mulu(typename R::utype x, typename R::utype y)
{
	typedef typename R::utype U;

	const int qb = sizeof(U) << 2;
	const U   mask = (U(1) << qb) - 1;

	U x0 =    x       & mask;
	U x1 =    x >> qb & mask;
	U y0 =    y       & mask;
	U y1 =    y >> qb & mask;
	U z0 =    x0 * y0;
	U z1 =    x1 * y0;
	U z2 =    x0 * y1;
	U z3 =    x1 * y1;
	U z4 =    z1 + z2;
	U c1 =    z4 < z1;
	U lo =    z0 + (z4 << qb);
	U c2 =    lo < z0;
	U hi =    z3 + (z4 >> qb) + (c1 << qb) + c2;

	return R(hi, lo);
}


/* multiply signed signed */

template <typename R>
R muls(typename R::stype x, typename R::stype y)
{
	typedef typename R::utype U;

	const int qb = sizeof(U) << 2;
	const U   mask = (U(1) << qb) - 1;
	const int sshift = (sizeof(U) << 3) - 1;

	U xs =    U(x) >> sshift;
	U ys =    U(y) >> sshift;
	U xu =    (xs ? -x : x);
	U x0 =    xu       & mask;
	U x1 =    xu >> qb & mask;
	U yu =    (ys ? -y : y);
	U y0 =    yu       & mask;
	U y1 =    yu >> qb & mask;
	U z0 =    x0 * y0;
	U z1 =    x1 * y0;
	U z2 =    x0 * y1;
	U z3 =    x1 * y1;
	U z4 =    z1 + z2;
	U c1 =    z4 < z1;
	U lo1 =   z0 + (z4 << qb);
	U c2 =    lo1 < z0;
	U rs =    xs ^ ys;
	U hi1 =   z3 + (z4 >> qb) + (c1 << qb) + c2;
	U lo2 =   rs ? lo1 - 1 : lo1;
	U hib =   lo2 > lo1;
	U hi2 =   hib ? hi1 - 1 : hi1;
	U hi =    rs ? ~hi2 : hi2;
	U lo =    rs ? ~lo2 : lo2;

	return R(hi, lo);
}


/* multiply signed unsigned */

template <typename R>
R mulsu(typename R::stype x, typename R::utype y)
{
	typedef typename R::utype U;

	const int qb = sizeof(U) << 2;
	const U   mask = (U(1) << qb) - 1;
	const int sshift = (sizeof(U) << 3) - 1;

	U xs =    U(x) >> sshift;
	U xu =    (xs ? -x : x);
	U x0 =    xu       & mask;
	U x1 =    xu >> qb & mask;
	U y0 =    y       & mask;
	U y1 =    y >> qb & mask;
	U z0 =    x0 * y0;
	U z1 =    x1 * y0;
	U z2 =    x0 * y1;
	U z3 =    x1 * y1;
	U z4 =    z1 + z2;
	U c1 =    z4 < z1;
	U lo1 =   z0 + (z4 << qb);
	U c2 =    lo1 < z0;
	U hi1 =   z3 + (z4 >> qb) + (c1 << qb) + c2;
	U lo2 =   xs ? lo1 - 1 : lo1;
	U hib =   lo2 > lo1;
	U hi2 =   hib ? hi1 - 1 : hi1;
	U hi =    xs ? ~hi2 : hi2;
	U lo =    xs ? ~lo2 : lo2;

	return R(hi, lo);
}

/* multiply high unsigned unsigned */

template <typename U>
U mulhu(U x, U y)
{
	const int qb = sizeof(U) << 2;
	const U   mask = (U(1) << qb) - 1;

	U x0 =    x       & mask;
	U x1 =    x >> qb & mask;
	U y0 =    y       & mask;
	U y1 =    y >> qb & mask;
	U z0 =    x0 * y0;
	U z1 =    x1 * y0;
	U z2 =    x0 * y1;
	U z3 =    x1 * y1;
	U z4 =    z1 + z2;
	U c1 =    z4 < z1;
	U lo =    z0 + (z4 << qb);
	U c2 =    lo < z0;
	U hi =    z3 + (z4 >> qb) + (c1 << qb) + c2;

	return hi;
}


/* multiply high signed signed */

template <typename S>
S mulhs(S x, S y)
{
	typedef typename std::make_unsigned<S>::type U;

	const int qb = sizeof(U) << 2;
	const U   mask = (U(1) << qb) - 1;
	const int sshift = (sizeof(U) << 3) - 1;

	U xs =    U(x) >> sshift;
	U ys =    U(y) >> sshift;
	U xu =    (xs ? -x : x);
	U x0 =    xu       & mask;
	U x1 =    xu >> qb & mask;
	U yu =    (ys ? -y : y);
	U y0 =    yu       & mask;
	U y1 =    yu >> qb & mask;
	U z0 =    x0 * y0;
	U z1 =    x1 * y0;
	U z2 =    x0 * y1;
	U z3 =    x1 * y1;
	U z4 =    z1 + z2;
	U c1 =    z4 < z1;
	U lo1 =   z0 + (z4 << qb);
	U c2 =    lo1 < z0;
	U rs =    xs ^ ys;
	U hi1 =   z3 + (z4 >> qb) + (c1 << qb) + c2;
	U lo2 =   rs ? lo1 - 1 : lo1;
	U hib =   lo2 > lo1;
	U hi2 =   hib ? hi1 - 1 : hi1;
	U hi =    rs ? ~hi2 : hi2;

	return hi;
}


/* multiply high signed unsigned */

template <typename S, typename U>
S mulhsu(S x, U y)
{
	const int qb = sizeof(U) << 2;
	const U   mask = (U(1) << qb) - 1;
	const int sshift = (sizeof(U) << 3) - 1;

	U xs =    U(x) >> sshift;
	U xu =    (xs ? -x : x);
	U x0 =    xu       & mask;
	U x1 =    xu >> qb & mask;
	U y0 =    y       & mask;
	U y1 =    y >> qb & mask;
	U z0 =    x0 * y0;
	U z1 =    x1 * y0;
	U z2 =    x0 * y1;
	U z3 =    x1 * y1;
	U z4 =    z1 + z2;
	U c1 =    z4 < z1;
	U lo1 =   z0 + (z4 << qb);
	U c2 =    lo1 < z0;
	U hi1 =   z3 + (z4 >> qb) + (c1 << qb) + c2;
	U lo2 =   xs ? lo1 - 1 : lo1;
	U hib =   lo2 > lo1;
	U hi2 =   hib ? hi1 - 1 : hi1;
	U hi =    xs ? ~hi2 : hi2;

	return hi;
}


/* test wrappers */

template <typename L, typename R>
void test_muls(typename R::stype x, typename R::stype y)
{
	R xy = muls<R>(x, y);
	L xya = (L(xy.val.p.hi) << (sizeof(L) << 2)) | L(xy.val.p.lo);
	L xyc = L(x) * L(y);
	bool pass = (xya == xyc);
	char fmt[256];
	const int hw = sizeof(L);
	snprintf(fmt, sizeof(fmt), "%%s "
		"%%-11sx=%%-20lld (0x%%0%ullx)\n"
		"%%16sy=%%-20lld (0x%%0%ullx)\n"
		"%%12sxy.hi=%%-20lld (0x%%0%ullx)\n"
		"%%12sxy.lo=%%-20llu (0x%%0%ullx)\n"
		"%%9sxy.check=%%-20lld (0x%%0%ullx)\n",
		hw,hw,hw,hw,hw<<1);
	printf(fmt, pass ? "PASS" : "FAIL", __func__,
		(s64)x, (u64)x, "",
		(s64)y, (u64)y, "",
		(s64)xy.val.p.hi, (u64)xy.val.p.hi, "",
		(u64)xy.val.p.lo, (u64)xy.val.p.lo, "",
		(s64)xyc, (u64)xyc);
}

template <typename L, typename R>
void test_mulu(typename R::utype x, typename R::utype y)
{
	R xy = mulu<R>(x, y);
	L xya = (L(xy.val.p.hi) << (sizeof(L) << 2)) | L(xy.val.p.lo);
	L xyc = L(x) * L(y);
	bool pass = (xya == xyc);
	char fmt[256];
	const int hw = sizeof(L);
	snprintf(fmt, sizeof(fmt), "%%s "
		"%%-11sx=%%-20llu (0x%%0%ullx)\n"
		"%%16sy=%%-20llu (0x%%0%ullx)\n"
		"%%12sxy.hi=%%-20llu (0x%%0%ullx)\n"
		"%%12sxy.lo=%%-20llu (0x%%0%ullx)\n"
		"%%9sxy.check=%%-20llu (0x%%0%ullx)\n",
		hw,hw,hw,hw,hw<<1);
	printf(fmt, pass ? "PASS" : "FAIL", __func__,
		(u64)x, (u64)x, "",
		(u64)y, (u64)y, "",
		(u64)xy.val.p.hi, (u64)xy.val.p.hi, "",
		(u64)xy.val.p.lo, (u64)xy.val.p.lo, "",
		(u64)xyc, (u64)xyc);
}

template <typename L, typename R>
void test_mulsu(typename R::stype x, typename R::utype y)
{
	R xy = mulsu<R>(x, y);
	L xya = (L(xy.val.p.hi) << (sizeof(L) << 2)) | L(xy.val.p.lo);
	L xyc = L(x) * L(y);
	bool pass = (xya == xyc);
	char fmt[256];
	const int hw = sizeof(L);
	snprintf(fmt, sizeof(fmt), "%%s "
		"%%-11sx=%%-20lld (0x%%0%ullx)\n"
		"%%16sy=%%-20llu (0x%%0%ullx)\n"
		"%%12sxy.hi=%%-20lld (0x%%0%ullx)\n"
		"%%12sxy.lo=%%-20llu (0x%%0%ullx)\n"
		"%%9sxy.check=%%-20lld (0x%%0%ullx)\n",
		hw,hw,hw,hw,hw<<1);
	printf(fmt, pass ? "PASS" : "FAIL", __func__,
		(s64)x, (u64)x, "",
		(u64)y, (u64)y, "",
		(s64)xy.val.p.hi, (u64)xy.val.p.hi, "",
		(u64)xy.val.p.lo, (u64)xy.val.p.lo, "",
		(s64)xyc, (u64)xyc);
}


/* test program */

int main()
{
	// test muls (signed signed)
	test_muls<s16,_s16>(0, 127);
	test_muls<s16,_s16>(77, 127);
	test_muls<s16,_s16>(127, 127);
	test_muls<s16,_s16>(-77, 127);
	test_muls<s16,_s16>(-127, 127);
	test_muls<s16,_s16>(-128, 127);
	test_muls<s16,_s16>(-77, -77);
	test_muls<s16,_s16>(-127, -127);
	test_muls<s16,_s16>(-128, -128);
	test_muls<s32,_s32>(0, 32767);
	test_muls<s32,_s32>(77, 32767);
	test_muls<s32,_s32>(32767, 32767);
	test_muls<s32,_s32>(-77, 32767);
	test_muls<s32,_s32>(-32767, 32767);
	test_muls<s32,_s32>(-32768, 32767);
	test_muls<s32,_s32>(-77, -77);
	test_muls<s32,_s32>(-32767, -32767);
	test_muls<s32,_s32>(-32768, -32768);
	test_muls<s64,_s64>(0, 2147483647);
	test_muls<s64,_s64>(77, 2147483647);
	test_muls<s64,_s64>(2147483647, 2147483647);
	test_muls<s64,_s64>(-77, 2147483647);
	test_muls<s64,_s64>(-2147483647, 2147483647);
	test_muls<s64,_s64>(-2147483648, 2147483647);
	test_muls<s64,_s64>(-77, -77);
	test_muls<s64,_s64>(-2147483647, -2147483647);
	test_muls<s64,_s64>(-2147483648, -2147483648);

	// test mulsu (signed unsigned)
	test_mulsu<s16,_s16>(0, 127);
	test_mulsu<s16,_s16>(127, 1);
	test_mulsu<s16,_s16>(77, 127);
	test_mulsu<s16,_s16>(127, 127);
	test_mulsu<s16,_s16>(127, 254);
	test_mulsu<s16,_s16>(-127, 254);
	test_mulsu<s16,_s16>(-128, 254);
	test_mulsu<s16,_s16>(-77, 254);
	test_mulsu<s32,_s32>(0, 32767);
	test_mulsu<s32,_s32>(32767, 1);
	test_mulsu<s32,_s32>(77, 32767);
	test_mulsu<s32,_s32>(32767, 32767);
	test_mulsu<s32,_s32>(32767, 65535);
	test_mulsu<s32,_s32>(-32767, 65535);
	test_mulsu<s32,_s32>(-32768, 65535);
	test_mulsu<s32,_s32>(-77, 65535);
	test_mulsu<s64,_s64>(0, 2147483647);
	test_mulsu<s64,_s64>(2147483647, 1);
	test_mulsu<s64,_s64>(77, 2147483647);
	test_mulsu<s64,_s64>(2147483647, 2147483647);
	test_mulsu<s64,_s64>(2147483647, 4294967295);
	test_mulsu<s64,_s64>(-2147483647, 4294967295);
	test_mulsu<s64,_s64>(-2147483648, 4294967295);
	test_mulsu<s64,_s64>(-77, 4294967295);

	// test mulu (unsigned unsigned)
	test_mulu<u16,_u16>(53, 63);
	test_mulu<u16,_u16>(53, 67);
	test_mulu<u16,_u16>(63, 191);
	test_mulu<u16,_u16>(254, 254);
	test_mulu<u32,_u32>(12345, 999);
	test_mulu<u32,_u32>(12345, 63000);
	test_mulu<u32,_u32>(65533, 65533);
	test_mulu<u64,_u64>(123450, 9990);
	test_mulu<u64,_u64>(123450, 630000);
	test_mulu<u64,_u64>(87652393, 87652393);
	test_mulu<u64,_u64>(613566756, 613566756);
	test_mulu<u64,_u64>(4294967295, 630000);
	test_mulu<u64,_u64>(4294967295, 87652393);
	test_mulu<u64,_u64>(4294967295, 613566756);
	test_mulu<u64,_u64>(4294967295, 4294967295);
	test_mulu<unsigned __int128,_u128>(18446744073709551615ULL,18446744073709551615ULL);

	// test mulhs (signed signed) high bits
	assert(mulhs(s8(0), s8(127)) == s8(0));
	assert(mulhs(s8(77), s8(127)) == s8(38));
	assert(mulhs(s8(127), s8(127)) == s8(63));
	assert(mulhs(s8(-77), s8(127)) == s8(-39));
	assert(mulhs(s8(-127), s8(127)) == s8(-64));
	assert(mulhs(s8(-128), s8(127)) == s8(-64));
	assert(mulhs(s8(-77), s8(-77)) == s8(23));
	assert(mulhs(s8(-127), s8(-127)) == s8(63));
	assert(mulhs(s8(-128), s8(-128)) == s8(64));
	assert(mulhs(s16(0), s16(32767)) == s16(0));
	assert(mulhs(s16(77), s16(32767)) == s16(38));
	assert(mulhs(s16(32767), s16(32767)) == s16(16383));
	assert(mulhs(s16(-77), s16(32767)) == s16(-39));
	assert(mulhs(s16(-32767), s16(32767)) == s16(-16384));
	assert(mulhs(s16(-32768), s16(32767)) == s16(-16384));
	assert(mulhs(s16(-77), s16(-77)) == s16(0));
	assert(mulhs(s16(-32767), s16(-32767)) == s16(16383));
	assert(mulhs(s16(-32768), s16(-32768)) == s16(16384));
	assert(mulhs(s32(0), s32(2147483647)) == s32(0));
	assert(mulhs(s32(77), s32(2147483647)) == s32(38));
	assert(mulhs(s32(2147483647), s32(2147483647)) == s32(1073741823));
	assert(mulhs(s32(-77), s32(2147483647)) == s32(-39));
	assert(mulhs(s32(-2147483647), s32(2147483647)) == s32(-1073741824));
	assert(mulhs(s32(-2147483648), s32(2147483647)) == s32(-1073741824));
	assert(mulhs(s32(-77), s32(-77)) == s32(0));
	assert(mulhs(s32(-2147483647), s32(-2147483647)) == s32(1073741823));
	assert(mulhs(s32(-2147483648), s32(-2147483648)) == s32(1073741824));

	// test mulhsu (signed unsigned) high bits
	assert(mulhsu(s8(0), u8(127)) == s8(0));
	assert(mulhsu(s8(127), u8(1)) == s8(0));
	assert(mulhsu(s8(77), u8(127)) == s8(38));
	assert(mulhsu(s8(127), u8(127)) == s8(63));
	assert(mulhsu(s8(127), u8(254)) == s8(126));
	assert(mulhsu(s8(-127), u8(254)) == s8(-127));
	assert(mulhsu(s8(-128), u8(254)) == s8(-127));
	assert(mulhsu(s8(-77), u8(254)) == s8(-77));
	assert(mulhsu(s16(0), u16(32767)) == s16(0));
	assert(mulhsu(s16(32767), u16(1)) == s16(0));
	assert(mulhsu(s16(77), u16(32767)) == s16(38));
	assert(mulhsu(s16(32767), u16(32767)) == s16(16383));
	assert(mulhsu(s16(32767), u16(65535)) == s16(32766));
	assert(mulhsu(s16(-32767), u16(65535)) == s16(-32767));
	assert(mulhsu(s16(-32768), u16(65535)) == s16(-32768));
	assert(mulhsu(s16(-77), u16(65535)) == s16(-77));
	assert(mulhsu(s32(0), u32(2147483647)) == s32(0));
	assert(mulhsu(s32(2147483647), u32(1)) == s32(0));
	assert(mulhsu(s32(77), u32(2147483647)) == s32(38));
	assert(mulhsu(s32(2147483647), u32(2147483647)) == s32(1073741823));
	assert(mulhsu(s32(2147483647), u32(4294967295)) == s32(2147483646));
	assert(mulhsu(s32(-2147483647), u32(4294967295)) == s32(-2147483647));
	assert(mulhsu(s32(-2147483648), u32(4294967295)) == s32(-2147483648));
	assert(mulhsu(s32(-77), u32(4294967295)) == s32(-77));

	// test mulhu (unsigned unsigned) high bits
	assert(mulhu(u8(53), u8(63)) == u8(13));
	assert(mulhu(u8(53), u8(67)) == u8(13));
	assert(mulhu(u8(63), u8(191)) == u8(47));
	assert(mulhu(u8(254), u8(254)) == u8(252));
	assert(mulhu(u16(12345), u16(999)) == u16(188));
	assert(mulhu(u16(12345), u16(63000)) == u16(11867));
	assert(mulhu(u16(65533), u16(65533)) == u16(65530));
	assert(mulhu(u32(123450), u32(9990)) == u32(0));
	assert(mulhu(u32(123450), u32(630000)) == u32(18));
	assert(mulhu(u32(87652393), u32(87652393)) == u32(1788824));
	assert(mulhu(u32(613566756), u32(613566756)) == u32(87652393));
	assert(mulhu(u32(4294967295), u32(630000)) == u32(629999));
	assert(mulhu(u32(4294967295), u32(87652393)) == u32(87652392));
	assert(mulhu(u32(4294967295), u32(613566756)) == u32(613566755));
	assert(mulhu(u32(4294967295), u32(4294967295)) == u32(4294967294));
	assert(mulhu(u64(18446744073709551615ULL), u64(18446744073709551615ULL)) == u64(18446744073709551614ULL));

	return 0;
}