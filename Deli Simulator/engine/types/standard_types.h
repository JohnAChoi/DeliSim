
#ifndef _C_STANDARD_TYPES_H_
#define _C_STANDARD_TYPES_H_

// Include NULL define (with C++11)
#ifdef _WIN32
	#if _MSC_VER > 1500
		#ifndef NULL
			#define NULL (nullptr)
		#else
			#undef NULL
			#define NULL (nullptr)
		#endif
	#else
		#ifndef NULL
		#define NULL (0)
		#endif
	#endif
#else
	#if __cplusplus > 199711L
		#ifndef NULL
			#define NULL (nullptr)
		#else
			#undef NULL
			#define NULL (nullptr)
		#endif
	#else
		#ifndef NULL
		#define NULL (0)
		#endif
	#endif
#endif
// Include NIL define
#ifndef NIL
	#define NIL (0)
#endif

// Include the fixed-size integer types
#if __cplusplus > 199711L
	// Only include it if it's in the current version
	#include <stdint.h>
	//#include <inttypes.h> //this one if it doesn't work
#else
	// Define 32bit number if not defined
	#ifdef _WIN32
		#if _MSC_VER > 1500
			#include <stdint.h>
		#else
			typedef unsigned __int8  uint8_t;
			typedef unsigned __int16 uint16_t;
			typedef unsigned __int32 uint32_t;
			typedef unsigned __int64 uint64_t;

			typedef __int8  int8_t;
			typedef __int16 int16_t;
			typedef __int32 int32_t;
			typedef __int64 int64_t;
		#endif
	#endif
#endif

typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned int	uint;

#include "floattype.h"

// Define the FORCE_INLINE macro
#ifdef __GNUC__
	#define FORCE_INLINE inline
#else
	#ifndef __INTEL_COMPILER
		#define FORCE_INLINE __forceinline
	#else
		#define FORCE_INLINE inline
	#endif
#endif

#define VALID_FLOAT(a) (( (a)==(a) )&&( ((a) <= FLT_MAX) && ((a) >= -FLT_MAX) ))
#ifdef _WIN32
	#ifdef _ENGINE_DEBUG
#include "windows.h"
		// Special assert definition for engine debug
		extern "C" {
			_CRTIMP void __cdecl _wassert(_In_z_ const wchar_t * _Message, _In_z_ const wchar_t *_File, _In_ unsigned _Line);
		}
		#define fnl_assert(_Expression) (void)( (!!(_Expression)) || (_wassert(_CRT_WIDE(#_Expression), _CRT_WIDE(__FILE__), __LINE__), 0) )
	#else
		// Not debug mode
		#define fnl_assert(_Expression)     ((void)0)
	#endif
#endif

#include "floattype_fn.h"

#endif