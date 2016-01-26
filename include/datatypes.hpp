/**
 * @file datatypes.hpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 24, 2016
 *
 */

/*
 * Change Log:
 *
 * Jan 24, 2016: 
 * - datatypes.hpp created
 */
#ifndef INCLUDE_DATATYPES_HPP_
#define INCLUDE_DATATYPES_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <climits>

#if (UCHAR_MAX == 0xff)
	typedef signed char   s8;  /* signed byte   */
	typedef unsigned char u8; /* unsigned byte */
#else
	#error "No 8-bit sized type available."
#endif

#if (USHRT_MAX == 0xffff)
	typedef signed short   s16;  /* signed 16 bit integer   */
	typedef unsigned short u16;  /* unsigned 16 bit integer */
#elif (UINT_MAX == 0xffff)
	typedef signed int     s16;  /* signed 16 bit integer   */
	typedef unsigned int   u16;  /* unsigned 16 bit integer */
#endif

#if (UINT_MAX == 0xffffffffL)
	typedef signed int    s32;  /* signed 32 bit integer   */
	typedef unsigned int  u32;  /* unsigned 32 bit integer */
#elif (ULONG_MAX == 0xffffffffL)
	typedef signed long   s32;  /* signed 32 bit integer   */
	typedef unsigned long u32;  /* unsigned 32 bit integer */
#endif

#if (ULONG_MAX == 0xffffffffffffffffL)
	typedef signed long        s64;
	typedef unsigned long      u64;
#elif (ULLONG_MAX == 0xffffffffffffffffLL) || (ULONG_LONG_MAX == 0xffffffffffffffffLL)
	typedef signed long long   s64;
	typedef unsigned long long u64;
#else
	// handle no 64-bit
#endif

	//--------------------------------------------------------------------------
	// System-Specific Lexical Types
	//--------------------------------------------------------------------------

	typedef signed char    byte;       ///< Signed 1-byte primitive
	typedef unsigned char  ubyte;      ///< Unsigned 1-byte primitive
	typedef int            word;       ///< Signed instruction-sized integer (Word)
	typedef unsigned int   uword;      ///< Unsigned instruction-sized integer (Word)

	//---------------------------------------------------------------------------

	typedef unsigned char  uchar;      ///< Unsigned char type
	typedef unsigned short ushort;     ///< Unsigned short type
	typedef unsigned int   uint;       ///< Unsigned int type
	typedef unsigned long  ulong;      ///< Unsigned long type

	typedef float  f32;
	typedef double f64;
	typedef long double highp;

	// 64-bit long word
	union Word64{
		u64 u;
		s64 s;
		f64	f;
	};
	// 32-bit Word
	union Word32{
		u32 u;
		s32 s;
		f32 f;
	};
	// 16-bit Word
	union Word16{
		u16 u;
		s16 s;
	};



#endif /* INCLUDE_DATATYPES_HPP_ */
