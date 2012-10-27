/*
===========================================================================

Daemon GPL Source Code
Copyright (C) 1999-2010 id Software LLC, a ZeniMax Media company.

This file is part of the Daemon GPL Source Code (Daemon Source Code).

Daemon Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Daemon Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Daemon Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Daemon Source Code is also subject to certain additional terms.
You should have received a copy of these additional terms immediately following the
terms and conditions of the GNU General Public License which accompanied the Daemon
Source Code.  If not, please request a copy in writing from id Software at the address
below.

If you have questions concerning this license or the applicable additional terms, you
may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville,
Maryland 20850 USA.

===========================================================================
*/

#ifndef __Q_SHARED_H
#define __Q_SHARED_H

#if defined( __cplusplus )
extern "C" {
#endif

// q_shared.h -- included first by ALL program modules.
// A user mod should never modify this file

#define PRODUCT_NAME            "Unvanquished"
#define PRODUCT_NAME_UPPER      "UNVANQUISHED" // Case, No spaces
#define PRODUCT_NAME_LOWER      "unvanquished" // No case, No spaces
#define PRODUCT_VERSION         "0.8.0"

#define ENGINE_NAME             "Daemon Engine"
#define ENGINE_VERSION          "0.8.0"

#ifdef REVISION
# define Q3_VERSION             PRODUCT_NAME " " PRODUCT_VERSION " " REVISION
#else
# define Q3_VERSION             PRODUCT_NAME " " PRODUCT_VERSION
#endif

#define Q3_ENGINE               ENGINE_NAME " " ENGINE_VERSION
#define Q3_ENGINE_DATE          __DATE__

#define CLIENT_WINDOW_TITLE     PRODUCT_NAME
#define CLIENT_WINDOW_MIN_TITLE PRODUCT_NAME_LOWER
#define GAMENAME_FOR_MASTER     PRODUCT_NAME_UPPER

#ifndef DEDICATED
#define CONFIG_NAME             "autogen.cfg"
#else
#define CONFIG_NAME             "autogen_server.cfg"
#endif

#if 1
#if !defined( COMPAT_Q3A )
#define COMPAT_Q3A 1
#endif
#endif

#if 1
#if !defined( COMPAT_ET )
#define COMPAT_ET 1
#endif
#endif

#define UNNAMED_PLAYER "UnnamedPlayer"

#if defined _WIN32 && !defined __GNUC__

#pragma warning(disable : 4018) // signed/unsigned mismatch
#pragma warning(disable : 4032)
#pragma warning(disable : 4051)
#pragma warning(disable : 4057) // slightly different base types
#pragma warning(disable : 4100) // unreferenced formal parameter
#pragma warning(disable : 4115)
#pragma warning(disable : 4125) // decimal digit terminates octal escape sequence
#pragma warning(disable : 4127) // conditional expression is constant
#pragma warning(disable : 4136)
#pragma warning(disable : 4152) // nonstandard extension, function/data pointer conversion in expression
#pragma warning(disable : 4201)
#pragma warning(disable : 4214)
#pragma warning(disable : 4244)
//#pragma warning(disable : 4142)   // benign redefinition
#pragma warning(disable : 4305) // truncation from const double to float
//#pragma warning(disable : 4310)   // cast truncates constant value
//#pragma warning(disable : 4505)   // unreferenced local function has been removed
#pragma warning(disable : 4514)
#pragma warning(disable : 4702) // unreachable code
#pragma warning(disable : 4711) // selected for automatic inline expansion
#pragma warning(disable : 4220) // varargs matches remaining parameters
#pragma warning(disable : 4706) // assignment within conditional expression // cs: probably should correct all of these at some point
#pragma warning(disable : 4005) // macro redefinition
#pragma warning(disable : 4996) // This function or variable may be unsafe. Consider using 'function_s' instead
#pragma warning(disable : 4075) // initializers put in unrecognized initialization area
#pragma warning(disable : 4355) // 'this': used in member initializer list
#pragma warning(disable : 4305) // signed unsigned mismatch
#pragma warning(disable : 4554) // qualifier applied to reference type; ignored
#pragma warning(disable : 4800) // forcing bool variable to one or zero, possible performance loss
#pragma warning(disable : 4090) // 'function' : different 'const' qualifiers
#pragma warning(disable : 4267) // 'initializing' : conversion from 'size_t' to 'int', possible loss of data
#pragma warning(disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
#pragma warning(disable : 4133) // 'function' : incompatible types - from 'unsigned long *' to 'const time_t *'
#pragma warning(disable : 4127) // conditional expression is constant
#pragma warning(disable : 4389) // '==' : signed/unsigned mismatch
#endif

#if defined( ppc ) || defined( __ppc ) || defined( __ppc__ ) || defined( __POWERPC__ )
#define idppc 1
#endif

	/**********************************************************************
	  VM Considerations

	  The VM can not use the standard system headers because we aren't really
	  using the compiler they were meant for.  We use bg_lib.h which contains
	  prototypes for the functions we define for our own use in bg_lib.c.

	  When writing mods, please add needed headers HERE, do not start including
	  stuff like <stdio.h> in the various .c files that make up each of the VMs
	  since you will be including system headers files can will have issues.

	  Remember, if you use a C library function that is not defined in bg_lib.c,
	  you will have to add your own version for support in the VM.

	 **********************************************************************/

#ifdef Q3_VM

#include "../../gamelogic/game/bg_lib.h"

	typedef int intptr_t;

#include "../../engine/qcommon/q_platform.h"

#define STATIC_INLINE

#ifdef Q3_VM_INSTANTIATE
#define IFDECLARE
#else
#define IFDECLARE ;
#endif

#ifdef USE_LLVM
extern int memcmp( void *, void *, size_t );
#endif

#else

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <sys/stat.h> // rain
#include <float.h>

// vsnprintf is ISO/IEC 9899:1999
// abstracting this to make it portable
#ifdef _WIN32
#define Q_vsnprintf _vsnprintf
#define Q_snprintf  _snprintf
#else
#define Q_vsnprintf vsnprintf
#define Q_snprintf  snprintf
#endif

#ifdef _MSC_VER
#include <io.h>

	typedef signed __int64   int64_t;
	typedef signed __int32   int32_t;
	typedef signed __int16   int16_t;
	typedef signed __int8    int8_t;
	typedef unsigned __int64 uint64_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int8  uint8_t;
#else
#include <stdint.h>
#endif

#include "q_platform.h"

// not VM - we can have static inline
#define STATIC_INLINE static INLINE ALWAYS_INLINE
#define IFDECLARE
#define Q3_VM_INSTANTIATE
#endif

#if defined __GNUC__ || defined __clang__
#define NORETURN __attribute__((__noreturn__))
#define UNUSED __attribute__((__unused__))
#define PRINTF_ARGS(f, a) __attribute__((__format__(__printf__, (f), (a))))
#define PRINTF_LIKE(n) PRINTF_ARGS((n), (n) + 1)
#define VPRINTF_LIKE(n) PRINTF_ARGS((n), 0)
#define ALIGNED(a) __attribute__((__aligned__(a)))
#define ALWAYS_INLINE __attribute__((__always_inline__))
#else
#define NORETURN
#define UNUSED
#define PRINTF_ARGS(f, a)
#define PRINTF_LIKE(n)
#define VPRINTF_LIKE(n)
#define ALIGNED(a)
#define ALWAYS_INLINE
#define __attribute__(x)
#define __func__ __FUNCTION__
#endif

//bani
//======================= GNUC DEFINES ==================================
#if ( defined _MSC_VER )
#define Q_EXPORT __declspec(dllexport)
#elif ( defined __SUNPRO_C )
#define Q_EXPORT __global
#elif (( __GNUC__ >= 3 ) && ( !__EMX__ ) && ( !sun ))
#define Q_EXPORT __attribute__((__visibility__("default")))
#else
#define Q_EXPORT
#endif
//=============================================================

	typedef unsigned char        byte;
	typedef unsigned int         uint;

	typedef enum {qfalse, qtrue} qboolean;

	typedef union
	{
		float        f;
		int          i;
		unsigned int ui;
	} floatint_t;

	typedef int qhandle_t;
	typedef int sfxHandle_t;
	typedef int fileHandle_t;
	typedef int clipHandle_t;

#define PAD(x,y)                ((( x ) + ( y ) - 1 ) & ~(( y ) - 1 ))
#define PADLEN(base, alignment) ( PAD(( base ), ( alignment )) - ( base ))
#define PADP(base, alignment)   ((void *) PAD((intptr_t) ( base ), ( alignment )))

#ifndef NULL
#ifdef __cplusplus
#define NULL ( 0L )
#else
#define NULL ( (void *)0 )
#endif
#endif

#define STRING(s)  #s
// expand constants before stringifying them
#define XSTRING(s) STRING(s)

#define MAX_QINT 0x7fffffff
#define MIN_QINT ( -MAX_QINT - 1 )

#ifndef BIT
#define BIT(x) ( 1 << ( x ) )
#endif

// the game guarantees that no string from the network will ever
// exceed MAX_STRING_CHARS
#define MAX_STRING_CHARS  1024 // max length of a string passed to Cmd_TokenizeString
#define MAX_STRING_TOKENS 256 // max tokens resulting from Cmd_TokenizeString
#define MAX_TOKEN_CHARS   1024 // max length of an individual token

#define MAX_INFO_STRING   1024
#define MAX_INFO_KEY      1024
#define MAX_INFO_VALUE    1024

#define BIG_INFO_STRING   8192 // used for system info key only
#define BIG_INFO_KEY      8192
#define BIG_INFO_VALUE    8192

#define MAX_QPATH         64 // max length of a quake game pathname
#define MAX_OSPATH        256 // max length of a filesystem pathname
#define MAX_CMD           1024 // max length of a command line

// rain - increased to 36 to match MAX_NETNAME, fixes #13 - UI stuff breaks
// with very long names
#define MAX_NAME_LENGTH    36 // max length of a client name

#define MAX_SAY_TEXT       400

#define MAX_BINARY_MESSAGE 32768 // max length of binary message

	typedef enum
	{
	  MESSAGE_EMPTY = 0,
	  MESSAGE_WAITING, // rate/packet limited
	  MESSAGE_WAITING_OVERFLOW, // packet too large with message
	} messageStatus_t;

// paramters for command buffer stuffing
	typedef enum
	{
	  EXEC_NOW, // don't return until completed, a VM should NEVER use this,
	  // because some commands might cause the VM to be unloaded...
	  EXEC_INSERT, // insert at current position, but don't run yet
	  EXEC_APPEND // add to end of the command buffer
	} cbufExec_t;

//
// these aren't needed by any of the VMs.  put in another header?
//
#define MAX_MAP_AREA_BYTES 32 // bit vector of area visibility

// print levels from renderer (FIXME: set up for game / cgame?)
	typedef enum
	{
	  PRINT_ALL,
	  PRINT_DEVELOPER, // only print when "developer 1"
	  PRINT_WARNING,
	  PRINT_ERROR
	} printParm_t;

#ifdef ERR_FATAL
#undef ERR_FATAL // this is possibly defined in malloc.h
#endif

// parameters to the main Error routine
	typedef enum
	{
	  ERR_FATAL, // exit the entire game with a popup window
	  ERR_VID_FATAL, // exit the entire game with a popup window and doesn't delete profile.pid
	  ERR_DROP, // print to console and disconnect from game
	  ERR_SERVERDISCONNECT, // don't kill server
	  ERR_DISCONNECT // client disconnected from the server
	} errorParm_t;

// font rendering values used by ui and cgame

#define BLINK_DIVISOR         200
#define PULSE_DIVISOR         75

#if !defined( NDEBUG ) && !defined( BSPC )
#define HUNK_DEBUG
#endif

	typedef enum
	{
	  h_high,
	  h_low,
	  h_dontcare
	} ha_pref;

#ifdef HUNK_DEBUG
#define Hunk_Alloc( size, preference ) Hunk_AllocDebug( size, preference, # size, __FILE__, __LINE__ )
	void *Hunk_AllocDebug( int size, ha_pref preference, const char *label, const char *file, int line );

#else
	void *Hunk_Alloc( int size, ha_pref preference );

#endif

#define Com_Memset   memset
#define Com_Memcpy   memcpy

#define Com_Allocate malloc
#define Com_Dealloc  free

#define CIN_system   1
#define CIN_loop     2
#define CIN_hold     4
#define CIN_silent   8
#define CIN_shader   16

	/*
	==============================================================

	MATHLIB

	==============================================================
	*/

	typedef float  vec_t;
	typedef vec_t  vec2_t[ 2 ];

#if defined( SSEVEC3_T )
	typedef vec_t  vec3_t[ 4 ]; // ALIGN(16);
	typedef vec3_t vec4_t;
#else
	typedef vec_t  vec3_t[ 3 ];
	typedef vec_t  vec4_t[ 4 ];
#endif

	typedef vec_t  vec5_t[ 5 ];

	typedef vec3_t axis_t[ 3 ];
	typedef vec_t  matrix3x3_t[ 9 ];
	typedef vec_t  matrix_t[ 16 ];
	typedef vec_t  quat_t[ 4 ];

	typedef int    fixed4_t;
	typedef int    fixed8_t;
	typedef int    fixed16_t;

#ifndef M_PI
#define M_PI 3.14159265358979323846f // matches value in gcc v2 math.h
#endif

#ifndef M_SQRT2
#define M_SQRT2 1.414213562f
#endif

#ifndef M_ROOT3
#define M_ROOT3 1.732050808f
#endif

#define ARRAY_LEN(x) ( sizeof( x ) / sizeof( *( x ) ) )

// angle indexes
#define PITCH 0 // up / down
#define YAW   1 // left / right
#define ROLL  2 // fall over

// plane sides
	typedef enum
	{
	  SIDE_FRONT = 0,
	  SIDE_BACK = 1,
	  SIDE_ON = 2,
	  SIDE_CROSS = 3
	} planeSide_t;

#define NUMVERTEXNORMALS 162
	extern vec3_t bytedirs[ NUMVERTEXNORMALS ];

// all drawing is done to a 640*480 virtual screen size
// and will be automatically scaled to the real resolution
#define SCREEN_WIDTH     640
#define SCREEN_HEIGHT    480

#define TINYCHAR_WIDTH   ( SMALLCHAR_WIDTH )
#define TINYCHAR_HEIGHT  ( SMALLCHAR_HEIGHT )

#define MINICHAR_WIDTH   8
#define MINICHAR_HEIGHT  12

#define SMALLCHAR_WIDTH  8
#define SMALLCHAR_HEIGHT 16

#define BIGCHAR_WIDTH    16
#define BIGCHAR_HEIGHT   16

#define GIANTCHAR_WIDTH  32
#define GIANTCHAR_HEIGHT 48

	extern vec4_t colorBlack;
	extern vec4_t colorRed;
	extern vec4_t colorGreen;
	extern vec4_t colorBlue;
	extern vec4_t colorYellow;
	extern vec4_t colorOrange;
	extern vec4_t colorMagenta;
	extern vec4_t colorCyan;
	extern vec4_t colorWhite;
	extern vec4_t colorLtGrey;
	extern vec4_t colorMdGrey;
	extern vec4_t colorDkGrey;
	extern vec4_t colorMdRed;
	extern vec4_t colorMdGreen;
	extern vec4_t colorDkGreen;
	extern vec4_t colorMdCyan;
	extern vec4_t colorMdYellow;
	extern vec4_t colorMdOrange;
	extern vec4_t colorMdBlue;

	extern vec4_t clrBrown;
	extern vec4_t clrBrownDk;
	extern vec4_t clrBrownLine;
	extern vec4_t clrBrownText;
	extern vec4_t clrBrownTextDk;
	extern vec4_t clrBrownTextDk2;
	extern vec4_t clrBrownTextLt;
	extern vec4_t clrBrownTextLt2;
	extern vec4_t clrBrownLineFull;

#define GAME_INIT_FRAMES 6
#define FRAMETIME        100 // msec

#define Q_COLOR_ESCAPE   '^'

#define COLOR_BLACK      '0'
#define COLOR_RED        '1'
#define COLOR_GREEN      '2'
#define COLOR_YELLOW     '3'
#define COLOR_BLUE       '4'
#define COLOR_CYAN       '5'
#define COLOR_MAGENTA    '6'
#define COLOR_WHITE      '7'
#define COLOR_ORANGE     '8'
#define COLOR_MDGREY     '9'
#define COLOR_LTGREY     ':'
//#define COLOR_LTGREY  ';'
#define COLOR_MDGREEN    '<'
#define COLOR_MDYELLOW   '='
#define COLOR_MDBLUE     '>'
#define COLOR_MDRED      '?'
#define COLOR_LTORANGE   'A'
#define COLOR_MDCYAN     'B'
#define COLOR_MDPURPLE   'C'
#define COLOR_NULL       '*'

#define COLOR_BITS       31
#define ColorIndex( c ) ( ( ( c ) - '0' ) & COLOR_BITS )

#define S_COLOR_BLACK    "^0"
#define S_COLOR_RED      "^1"
#define S_COLOR_GREEN    "^2"
#define S_COLOR_YELLOW   "^3"
#define S_COLOR_BLUE     "^4"
#define S_COLOR_CYAN     "^5"
#define S_COLOR_MAGENTA  "^6"
#define S_COLOR_WHITE    "^7"
#define S_COLOR_ORANGE   "^8"
#define S_COLOR_MDGREY   "^9"
#define S_COLOR_LTGREY   "^:"
//#define S_COLOR_LTGREY    "^;"
#define S_COLOR_MDGREEN  "^<"
#define S_COLOR_MDYELLOW "^="
#define S_COLOR_MDBLUE   "^>"
#define S_COLOR_MDRED    "^?"
#define S_COLOR_LTORANGE "^A"
#define S_COLOR_MDCYAN   "^B"
#define S_COLOR_MDPURPLE "^C"
#define S_COLOR_NULL     "^*"

STATIC_INLINE qboolean Q_IsColorString( const char *p ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
{
	return ( p[0] == Q_COLOR_ESCAPE &&
	         ( p[1] == COLOR_NULL || ( p[1] >= '0' && p[1] != Q_COLOR_ESCAPE && p[1] < 'p' ) )
	       ) ? qtrue : qfalse;
}
#endif

#define INDENT_MARKER    '\v'

	extern vec4_t g_color_table[ 32 ];

#define MAKERGB( v, r, g, b )         v[ 0 ] = r; v[ 1 ] = g; v[ 2 ] = b
#define MAKERGBA( v, r, g, b, a )     v[ 0 ] = r; v[ 1 ] = g; v[ 2 ] = b; v[ 3 ] = a

// Hex Color string support
#define gethex( ch )                  ( ( ch ) > '9' ? ( ( ch ) >= 'a' ? ( ( ch ) - 'a' + 10 ) : ( ( ch ) - '7' ) ) : ( ( ch ) - '0' ) )
#define ishex( ch )                   ( ( ch ) && ( ( ( ch ) >= '0' && ( ch ) <= '9' ) || ( ( ch ) >= 'A' && ( ch ) <= 'F' ) || ( ( ch ) >= 'a' && ( ch ) <= 'f' ) ) )
// check whether in the rrggbb format, r,g,b e {0,...,9} U {A,...,F}
#define Q_IsHexColorString( p )       ( ishex( *( p ) ) && ishex( *( ( p ) + 1 ) ) && ishex( *( ( p ) + 2 ) ) && ishex( *( ( p ) + 3 ) ) && ishex( *( ( p ) + 4 ) ) && ishex( *( ( p ) + 5 ) ) )
#define Q_HexColorStringHasAlpha( p ) ( ishex( *( ( p ) + 6 ) ) && ishex( *( ( p ) + 7 ) ) )

#define DEG2RAD( a )                  ( ( ( a ) * M_PI ) / 180.0F )
#define RAD2DEG( a )                  ( ( ( a ) * 180.0f ) / M_PI )

#define Q_max(a, b)                   (( a ) > ( b ) ? ( a ) : ( b ))
#define Q_min(a, b)                   (( a ) < ( b ) ? ( a ) : ( b ))
#define Q_bound(a, b, c)              ( Q_max(a, Q_min(b, c)))
#define Q_clamp(a, b, c)              (( b ) >= ( c ) ? ( a ) = ( b ) : ( a ) < ( b ) ? ( a ) = ( b ) : ( a ) > ( c ) ? ( a ) = ( c ) : ( a ))
#define Q_lerp(from, to, frac)        ( from + (( to - from ) * frac ))

	struct cplane_s;

	extern vec3_t   vec3_origin;
	extern vec3_t   axisDefault[ 3 ];
	extern matrix_t matrixIdentity;
	extern quat_t   quatIdentity;

#define nanmask ( 255 << 23 )

#define IS_NAN( x ) ( ( ( *(int *)&( x ) ) & nanmask ) == nanmask )

#if idx64
	extern long qftolsse( float f );
	extern int  qvmftolsse( void );
	extern void qsnapvectorsse( vec3_t vec );

#define Q_ftol       qftolsse
#define Q_SnapVector qsnapvectorsse

	extern int ( *Q_VMftol )( void );
#elif id386
	extern long QDECL qftolx87( float f );
	extern long QDECL qftolsse( float f );
	extern int QDECL  qvmftolx87( void );
	extern int QDECL  qvmftolsse( void );
	extern void QDECL qsnapvectorx87( vec3_t vec );
	extern void QDECL qsnapvectorsse( vec3_t vec );

	extern long( QDECL *Q_ftol )( float f );
	extern int ( QDECL *Q_VMftol )( void );
	extern void ( QDECL *Q_SnapVector )( vec3_t vec );
#else
#define Q_ftol lrintf
#define Q_SnapVector(vec) \
        do \
  { \
    vec3_t *temp = ( vec ); \
                \
    ( *temp )[ 0 ] = round(( *temp )[ 0 ]); \
    ( *temp )[ 1 ] = round(( *temp )[ 1 ]); \
    ( *temp )[ 2 ] = round(( *temp )[ 2 ]); \
  } while(0)
#endif

	/*
	// if your system does not have lrintf() and round() you can try this block. Please also open a bug report at bugzilla.icculus.org
	// or write a mail to the ioq3 mailing list.
	#else
	  #define Q_ftol(v) ((long) (v))
	  #define Q_round(v) do { if((v) < 0) (v) -= 0.5f; else (v) += 0.5f; (v) = Q_ftol((v)); } while(0)
	  #define Q_SnapVector(vec) \
	        do\
	        {\
	                vec3_t *temp = (vec);\
	                \
	                Q_round((*temp)[0]);\
	                Q_round((*temp)[1]);\
	                Q_round((*temp)[2]);\
	        } while(0)
	#endif
	*/

	STATIC_INLINE long XreaL_Q_ftol( float f ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
#if id386_sse && defined( _MSC_VER )
		static int tmp;
		__asm fld f
		__asm fistp tmp
		__asm mov  eax, tmp
#else
		return ( long ) f;
#endif
	}
#endif

	STATIC_INLINE float Q_rsqrt( float number ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		float y;

#if idppc
		float x = 0.5f * number;

#ifdef __GNUC__
		asm( "frsqrte %0, %1" : "=f"( y ) : "f"( number ) );
#else
		y = __frsqrte( number );
#endif
		return y * ( 1.5f - ( x * y * y ) );

#elif id386_3dnow && defined __GNUC__
//#error Q_rqsrt
		asm volatile
		(
		  // lo                                   | hi
		  "femms                               \n"
		  "movd           (%%eax),        %%mm0\n" // in                                   |       -
		  "pfrsqrt        %%mm0,          %%mm1\n" // 1/sqrt(in)                           | 1/sqrt(in)    (approx)
		  "movq           %%mm1,          %%mm2\n" // 1/sqrt(in)                           | 1/sqrt(in)    (approx)
		  "pfmul          %%mm1,          %%mm1\n" // (1/sqrt(in))?                        | (1/sqrt(in))?         step 1
		  "pfrsqit1       %%mm0,          %%mm1\n" // intermediate                                                 step 2
		  "pfrcpit2       %%mm2,          %%mm1\n" // 1/sqrt(in) (full 24-bit precision)                           step 3
		  "movd           %%mm1,        (%%edx)\n"
		  "femms                               \n"
		  :
		  : "a"( &number ), "d"( &y ) : "memory"
		);
#elif id386_sse && defined __GNUC__
		asm volatile( "rsqrtss %0, %1" : "=x"( y ) : "x"( number ) );
#elif id386_sse && defined _MSC_VER
		__asm
		{
			rsqrtss xmm0, number
			movss y, xmm0
		}
#else
		union
		{
			float f;
			int   i;
		} t;

		float       x2;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		t.f = number;
		t.i = 0x5f3759df - ( t.i >> 1 ); // what the fuck?
		y = t.f;
		y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
#endif
		return y;
	}
#endif

	STATIC_INLINE float Q_fabs( float x ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
#if idppc && defined __GNUC__
		float abs_x;

		asm( "fabs %0, %1" : "=f"( abs_x ) : "f"( x ) );
		return abs_x;
#else
		floatint_t tmp;

		tmp.f = x;
		tmp.i &= 0x7FFFFFFF;
		return tmp.f;
#endif
	}
#endif

#define SQRTFAST( x ) ( 1.0f / Q_rsqrt( x ) )

// fast float to int conversion
#if id386 && !( ( defined __linux__ || defined __FreeBSD__ || defined __GNUC__ ) && ( defined __i386__ ) ) // rb010123
	long myftol( float f );

#elif defined( __MACOS__ )
#define myftol( x ) (long)( x )
#else
	extern long int lrintf( float x );

#define myftol( x ) lrintf( x )
#endif

#ifdef _MSC_VER
	STATIC_INLINE long lrintf( float f )
	{
#ifdef _M_X64
		return ( long )( ( f > 0.0f ) ? ( f + 0.5f ) : ( f - 0.5f ) );
#else
		int i;

		_asm
		{
			fld f
			fistp i
		};

		return i;
#endif
	}

#endif

#if id386_3dnow && defined __GNUC__ && 0
	STATIC_INLINE float Q_recip( float in )
	{
		vec_t out;

		femms();
		asm volatile( "movd		(%%eax),	%%mm0\n""pfrcp		%%mm0,		%%mm1\n"                    // (approx)
		              "pfrcpit1	%%mm1,		%%mm0\n"// (intermediate)
		              "pfrcpit2	%%mm1,		%%mm0\n"// (full 24-bit)
		              // out = mm0[low]
		              "movd		%%mm0,		(%%edx)\n"::"a"( &in ), "d"( &out ) : "memory" );

		femms();
		return out;
	}
#else
	#define Q_recip(x) ( 1.0f / (x) )
#endif

	byte         ClampByte( int i );
	signed char  ClampChar( int i );
	signed short ClampShort( int i );

// this isn't a real cheap function to call!
	int          DirToByte( vec3_t dir );
	void         ByteToDir( int b, vec3_t dir );

#if 1

#define DotProduct( x,y )            ( ( x )[ 0 ] * ( y )[ 0 ] + ( x )[ 1 ] * ( y )[ 1 ] + ( x )[ 2 ] * ( y )[ 2 ] )
#define VectorSubtract( a,b,c )      ( ( c )[ 0 ] = ( a )[ 0 ] - ( b )[ 0 ],( c )[ 1 ] = ( a )[ 1 ] - ( b )[ 1 ],( c )[ 2 ] = ( a )[ 2 ] - ( b )[ 2 ] )
#define VectorAdd( a,b,c )           ( ( c )[ 0 ] = ( a )[ 0 ] + ( b )[ 0 ],( c )[ 1 ] = ( a )[ 1 ] + ( b )[ 1 ],( c )[ 2 ] = ( a )[ 2 ] + ( b )[ 2 ] )
#define VectorCopy( a,b )            ( ( b )[ 0 ] = ( a )[ 0 ],( b )[ 1 ] = ( a )[ 1 ],( b )[ 2 ] = ( a )[ 2 ] )
#define VectorScale( v, s, o )       ( ( o )[ 0 ] = ( v )[ 0 ] * ( s ),( o )[ 1 ] = ( v )[ 1 ] * ( s ),( o )[ 2 ] = ( v )[ 2 ] * ( s ) )
#define VectorMA( v, s, b, o )       ( ( o )[ 0 ] = ( v )[ 0 ] + ( b )[ 0 ] * ( s ),( o )[ 1 ] = ( v )[ 1 ] + ( b )[ 1 ] * ( s ),( o )[ 2 ] = ( v )[ 2 ] + ( b )[ 2 ] * ( s ) )
#define VectorLerpTrem( f, s, e, r ) (( r )[ 0 ] = ( s )[ 0 ] + ( f ) * (( e )[ 0 ] - ( s )[ 0 ] ), \
                                      ( r )[ 1 ] = ( s )[ 1 ] + ( f ) * (( e )[ 1 ] - ( s )[ 1 ] ), \
                                      ( r )[ 2 ] = ( s )[ 2 ] + ( f ) * (( e )[ 2 ] - ( s )[ 2 ] ))

#else

#define DotProduct( x,y )       _DotProduct( x,y )
#define VectorSubtract( a,b,c ) _VectorSubtract( a,b,c )
#define VectorAdd( a,b,c )      _VectorAdd( a,b,c )
#define VectorCopy( a,b )       _VectorCopy( a,b )
#define VectorScale( v, s, o )  _VectorScale( v,s,o )
#define VectorMA( v, s, b, o )  _VectorMA( v,s,b,o )

#endif

#ifdef Q3_VM
#ifdef VectorCopy
#undef VectorCopy
// this is a little hack to get more efficient copies in our interpreter
	typedef struct
	{
		float v[ 3 ];
	} vec3struct_t;
#define VectorCopy( a,b ) ( *(vec3struct_t *)( b ) = *(vec3struct_t *)( a ) )
#endif
#endif

#define VectorClear( a )             ( ( a )[ 0 ] = ( a )[ 1 ] = ( a )[ 2 ] = 0 )
#define VectorNegate( a,b )          ( ( b )[ 0 ] = -( a )[ 0 ],( b )[ 1 ] = -( a )[ 1 ],( b )[ 2 ] = -( a )[ 2 ] )
#define VectorSet( v, x, y, z )      ( ( v )[ 0 ] = ( x ), ( v )[ 1 ] = ( y ), ( v )[ 2 ] = ( z ) )

#define Vector2Set( v, x, y )        ( ( v )[ 0 ] = ( x ),( v )[ 1 ] = ( y ) )
#define Vector2Copy( a,b )           ( ( b )[ 0 ] = ( a )[ 0 ],( b )[ 1 ] = ( a )[ 1 ] )
#define Vector2Subtract( a,b,c )     ( ( c )[ 0 ] = ( a )[ 0 ] - ( b )[ 0 ],( c )[ 1 ] = ( a )[ 1 ] - ( b )[ 1 ] )

#define Vector4Set( v, x, y, z, n )  ( ( v )[ 0 ] = ( x ),( v )[ 1 ] = ( y ),( v )[ 2 ] = ( z ),( v )[ 3 ] = ( n ) )
#define Vector4Copy( a,b )           ( ( b )[ 0 ] = ( a )[ 0 ],( b )[ 1 ] = ( a )[ 1 ],( b )[ 2 ] = ( a )[ 2 ],( b )[ 3 ] = ( a )[ 3 ] )
#define Vector4MA( v, s, b, o )      ( ( o )[ 0 ] = ( v )[ 0 ] + ( b )[ 0 ] * ( s ),( o )[ 1 ] = ( v )[ 1 ] + ( b )[ 1 ] * ( s ),( o )[ 2 ] = ( v )[ 2 ] + ( b )[ 2 ] * ( s ),( o )[ 3 ] = ( v )[ 3 ] + ( b )[ 3 ] * ( s ) )
#define Vector4Average( v, b, s, o ) ( ( o )[ 0 ] = ( ( v )[ 0 ] * ( 1 - ( s ) ) ) + ( ( b )[ 0 ] * ( s ) ),( o )[ 1 ] = ( ( v )[ 1 ] * ( 1 - ( s ) ) ) + ( ( b )[ 1 ] * ( s ) ),( o )[ 2 ] = ( ( v )[ 2 ] * ( 1 - ( s ) ) ) + ( ( b )[ 2 ] * ( s ) ),( o )[ 3 ] = ( ( v )[ 3 ] * ( 1 - ( s ) ) ) + ( ( b )[ 3 ] * ( s ) ) )
#define Vector4Lerp( f, s, e, r )    (( r )[ 0 ] = ( s )[ 0 ] + ( f ) * (( e )[ 0 ] - ( s )[ 0 ] ), \
                                      ( r )[ 1 ] = ( s )[ 1 ] + ( f ) * (( e )[ 1 ] - ( s )[ 1 ] ), \
                                      ( r )[ 2 ] = ( s )[ 2 ] + ( f ) * (( e )[ 2 ] - ( s )[ 2 ] ), \
                                      ( r )[ 3 ] = ( s )[ 3 ] + ( f ) * (( e )[ 3 ] - ( s )[ 3 ] ))

#define DotProduct4(x, y)            (( x )[ 0 ] * ( y )[ 0 ] + ( x )[ 1 ] * ( y )[ 1 ] + ( x )[ 2 ] * ( y )[ 2 ] + ( x )[ 3 ] * ( y )[ 3 ] )

#define SnapVector( v )              do { v[ 0 ] = ( (int)( v[ 0 ] ) ); v[ 1 ] = ( (int)( v[ 1 ] ) ); v[ 2 ] = ( (int)( v[ 2 ] ) ); } while ( 0 )

// just in case you don't want to use the macros
	vec_t    _DotProduct( const vec3_t v1, const vec3_t v2 );
	void     _VectorSubtract( const vec3_t veca, const vec3_t vecb, vec3_t out );
	void     _VectorAdd( const vec3_t veca, const vec3_t vecb, vec3_t out );
	void     _VectorCopy( const vec3_t in, vec3_t out );
	void     _VectorScale( const vec3_t in, float scale, vec3_t out );
	void     _VectorMA( const vec3_t veca, float scale, const vec3_t vecb, vec3_t vecc );

	unsigned ColorBytes3( float r, float g, float b );
	unsigned ColorBytes4( float r, float g, float b, float a );

	float    NormalizeColor( const vec3_t in, vec3_t out );
	void     ClampColor( vec4_t color );

	float    RadiusFromBounds( const vec3_t mins, const vec3_t maxs );
	void     ZeroBounds( vec3_t mins, vec3_t maxs );
	void     ClearBounds( vec3_t mins, vec3_t maxs );
	void     AddPointToBounds( const vec3_t v, vec3_t mins, vec3_t maxs );

// RB: same as BoundsIntersectPoint but kept for compatibility
	qboolean PointInBounds( const vec3_t v, const vec3_t mins, const vec3_t maxs );

	void     BoundsAdd( vec3_t mins, vec3_t maxs, const vec3_t mins2, const vec3_t maxs2 );
	qboolean BoundsIntersect( const vec3_t mins, const vec3_t maxs, const vec3_t mins2, const vec3_t maxs2 );
	qboolean BoundsIntersectSphere( const vec3_t mins, const vec3_t maxs, const vec3_t origin, vec_t radius );
	qboolean BoundsIntersectPoint( const vec3_t mins, const vec3_t maxs, const vec3_t origin );

	STATIC_INLINE void BoundsToCorners( const vec3_t mins, const vec3_t maxs, vec3_t corners[ 8 ] ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		VectorSet( corners[ 0 ], mins[ 0 ], maxs[ 1 ], maxs[ 2 ] );
		VectorSet( corners[ 1 ], maxs[ 0 ], maxs[ 1 ], maxs[ 2 ] );
		VectorSet( corners[ 2 ], maxs[ 0 ], mins[ 1 ], maxs[ 2 ] );
		VectorSet( corners[ 3 ], mins[ 0 ], mins[ 1 ], maxs[ 2 ] );
		VectorSet( corners[ 4 ], mins[ 0 ], maxs[ 1 ], mins[ 2 ] );
		VectorSet( corners[ 5 ], maxs[ 0 ], maxs[ 1 ], mins[ 2 ] );
		VectorSet( corners[ 6 ], maxs[ 0 ], mins[ 1 ], mins[ 2 ] );
		VectorSet( corners[ 7 ], mins[ 0 ], mins[ 1 ], mins[ 2 ] );
	}
#endif

	int VectorCompare( const vec3_t v1, const vec3_t v2 );

	STATIC_INLINE int Vector4Compare( const vec4_t v1, const vec4_t v2 ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		if ( v1[ 0 ] != v2[ 0 ] || v1[ 1 ] != v2[ 1 ] || v1[ 2 ] != v2[ 2 ] || v1[ 3 ] != v2[ 3 ] )
		{
			return 0;
		}

		return 1;
	}
#endif

	STATIC_INLINE void VectorLerp( const vec3_t from, const vec3_t to, float frac, vec3_t out ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		out[ 0 ] = from[ 0 ] + ( ( to[ 0 ] - from[ 0 ] ) * frac );
		out[ 1 ] = from[ 1 ] + ( ( to[ 1 ] - from[ 1 ] ) * frac );
		out[ 2 ] = from[ 2 ] + ( ( to[ 2 ] - from[ 2 ] ) * frac );
	}
#endif

#define VectorLerp4( f, s, e, r ) (( r )[ 0 ] = ( s )[ 0 ] + ( f ) * (( e )[ 0 ] - ( s )[ 0 ] ), \
                                   ( r )[ 1 ] = ( s )[ 1 ] + ( f ) * (( e )[ 1 ] - ( s )[ 1 ] ), \
                                   ( r )[ 2 ] = ( s )[ 2 ] + ( f ) * (( e )[ 2 ] - ( s )[ 2 ] ))

	STATIC_INLINE int VectorCompareEpsilon( const vec3_t v1, const vec3_t v2, float epsilon ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		vec3_t d;

		VectorSubtract( v1, v2, d );
		d[ 0 ] = fabs( d[ 0 ] );
		d[ 1 ] = fabs( d[ 1 ] );
		d[ 2 ] = fabs( d[ 2 ] );

		if ( d[ 0 ] > epsilon || d[ 1 ] > epsilon || d[ 2 ] > epsilon )
		{
			return 0;
		}

		return 1;
	}
#endif

	vec_t VectorLength( const vec3_t v );
	vec_t VectorLengthSquared( const vec3_t v );
	vec_t Distance( const vec3_t p1, const vec3_t p2 );
	vec_t DistanceSquared( const vec3_t p1, const vec3_t p2 );
	void  CrossProduct( const vec3_t v1, const vec3_t v2, vec3_t cross );
	vec_t VectorNormalize( vec3_t v );  // returns vector length
	void  VectorNormalizeFast( vec3_t v );  // does NOT return vector length, uses rsqrt approximation
	vec_t VectorNormalize2( const vec3_t v, vec3_t out );
	void  VectorInverse( vec3_t v );
	void  Vector4Scale( const vec4_t in, vec_t scale, vec4_t out );

	void  VectorRotate( vec3_t in, vec3_t matrix[ 3 ], vec3_t out );

	int   NearestPowerOfTwo( int val );
	int   Q_log2( int val );
#ifdef Q3_VM
#define Q_acos(c) acos(c)
#else
	float Q_acos( float c );
#endif
	int   Q_isnan( float x );

	int   Q_rand( int *seed );
	float Q_random( int *seed );
	float Q_crandom( int *seed );

#define random()  ( ( rand() & 0x7fff ) / ( (float)0x7fff ) )
#define crandom() ( 2.0 * ( random() - 0.5 ) )

	void vectoangles( const vec3_t value1, vec3_t angles );

#define VectorToAngles(value1, angles) vectoangles( (value1), (angles) )

	float vectoyaw( const vec3_t vec );

	void  AnglesToAxis( const vec3_t angles, vec3_t axis[ 3 ] );
// TTimo: const vec_t ** would require explicit casts for ANSI C conformance
// see unix/const-arg.c
	void  AxisToAngles( /*const*/ vec3_t axis[ 3 ], vec3_t angles );
//void AxisToAngles ( const vec3_t axis[3], vec3_t angles );
	float VectorDistance( vec3_t v1, vec3_t v2 );
	float VectorDistanceSquared( vec3_t v1, vec3_t v2 );

	float VectorMinComponent( vec3_t v );
	float VectorMaxComponent( vec3_t v );

	void  AxisClear( vec3_t axis[ 3 ] );
	void  AxisCopy( vec3_t in[ 3 ], vec3_t out[ 3 ] );

	void  SetPlaneSignbits( struct cplane_s *out );
	int   BoxOnPlaneSide( vec3_t emins, vec3_t emaxs, struct cplane_s *plane );

	float AngleMod( float a );
	float LerpAngle( float from, float to, float frac );
	void  LerpPosition( vec3_t start, vec3_t end, float frac, vec3_t out );
	float AngleSubtract( float a1, float a2 );
	void  AnglesSubtract( vec3_t v1, vec3_t v2, vec3_t v3 );

	float AngleNormalize2Pi( float angle );
	float AngleNormalize360( float angle );
	float AngleNormalize180( float angle );
	float AngleDelta( float angle1, float angle2 );
	float AngleBetweenVectors( const vec3_t a, const vec3_t b );
	void  AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up );

#define AnglesToVector(angles, out) AngleVectors( (angles), (out), NULL, NULL )

	vec_t PlaneNormalize( vec4_t plane );  // returns normal length

	/* greebo: This calculates the intersection point of three planes.
	 * Returns <0,0,0> if no intersection point could be found, otherwise returns the coordinates of the intersection point
	 * (this may also be 0,0,0) */
	qboolean PlanesGetIntersectionPoint( const vec4_t plane1, const vec4_t plane2, const vec4_t plane3, vec3_t out );
	void     PlaneIntersectRay( const vec3_t rayPos, const vec3_t rayDir, const vec4_t plane, vec3_t res );

	qboolean PlaneFromPoints( vec4_t plane, const vec3_t a, const vec3_t b, const vec3_t c );
	qboolean PlaneFromPointsOrder( vec4_t plane, const vec3_t a, const vec3_t b, const vec3_t c, qboolean cw );
	void     ProjectPointOnPlane( vec3_t dst, const vec3_t point, const vec3_t normal );
	void     RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point, float degrees );
	void     RotatePointAroundVertex( vec3_t pnt, float rot_x, float rot_y, float rot_z, const vec3_t origin );

	void     RotateAroundDirection( vec3_t axis[ 3 ], float yaw );
	void     MakeNormalVectors( const vec3_t forward, vec3_t right, vec3_t up );

// perpendicular vector could be replaced by this

//int       PlaneTypeForNormal( vec3_t normal );

	void VectorMatrixMultiply( const vec3_t p, vec3_t m[ 3 ], vec3_t out );

// RB: NOTE renamed MatrixMultiply to AxisMultiply because it conflicts with most new matrix functions
// It is important for mod developers to do this change as well or they risk a memory corruption by using
// the other MatrixMultiply function.
	void  AxisMultiply( float in1[ 3 ][ 3 ], float in2[ 3 ][ 3 ], float out[ 3 ][ 3 ] );
	void  AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up );
	void  PerpendicularVector( vec3_t dst, const vec3_t src );

// Ridah
	void  GetPerpendicularViewVector( const vec3_t point, const vec3_t p1, const vec3_t p2, vec3_t up );
	void  ProjectPointOntoVector( vec3_t point, vec3_t vStart, vec3_t vEnd, vec3_t vProj );
	void  ProjectPointOntoVectorBounded( vec3_t point, vec3_t vStart, vec3_t vEnd, vec3_t vProj );
	float DistanceFromLineSquared( vec3_t p, vec3_t lp1, vec3_t lp2 );
	float DistanceFromVectorSquared( vec3_t p, vec3_t lp1, vec3_t lp2 );

// done.

	vec_t DistanceBetweenLineSegmentsSquared( const vec3_t sP0, const vec3_t sP1,
	    const vec3_t tP0, const vec3_t tP1, float *s, float *t );
	vec_t DistanceBetweenLineSegments( const vec3_t sP0, const vec3_t sP1,
	                                   const vec3_t tP0, const vec3_t tP1, float *s, float *t );

//=============================================

// RB: XreaL matrix math functions required by the renderer

	void     MatrixIdentity( matrix_t m );
	void     MatrixClear( matrix_t m );
	void     MatrixCopy( const matrix_t in, matrix_t out );
	qboolean MatrixCompare( const matrix_t a, const matrix_t b );
	void     MatrixTransposeIntoXMM( const matrix_t m );
	void     MatrixTranspose( const matrix_t in, matrix_t out );

// invert any m4x4 using Kramer's rule.. return qtrue if matrix is singular, else return qfalse
	qboolean MatrixInverse( matrix_t m );
	void     MatrixSetupXRotation( matrix_t m, vec_t degrees );
	void     MatrixSetupYRotation( matrix_t m, vec_t degrees );
	void     MatrixSetupZRotation( matrix_t m, vec_t degrees );
	void     MatrixSetupTranslation( matrix_t m, vec_t x, vec_t y, vec_t z );
	void     MatrixSetupScale( matrix_t m, vec_t x, vec_t y, vec_t z );
	void     MatrixSetupShear( matrix_t m, vec_t x, vec_t y );
	void     MatrixMultiply( const matrix_t a, const matrix_t b, matrix_t out );
	void     MatrixMultiply2( matrix_t m, const matrix_t m2 );
	void     MatrixMultiplyRotation( matrix_t m, vec_t pitch, vec_t yaw, vec_t roll );
	void     MatrixMultiplyZRotation( matrix_t m, vec_t degrees );
	void     MatrixMultiplyTranslation( matrix_t m, vec_t x, vec_t y, vec_t z );
	void     MatrixMultiplyScale( matrix_t m, vec_t x, vec_t y, vec_t z );
	void     MatrixMultiplyShear( matrix_t m, vec_t x, vec_t y );
	void     MatrixToAngles( const matrix_t m, vec3_t angles );
	void     MatrixFromAngles( matrix_t m, vec_t pitch, vec_t yaw, vec_t roll );
	void     MatrixFromVectorsFLU( matrix_t m, const vec3_t forward, const vec3_t left, const vec3_t up );
	void     MatrixFromVectorsFRU( matrix_t m, const vec3_t forward, const vec3_t right, const vec3_t up );
	void     MatrixFromQuat( matrix_t m, const quat_t q );
	void     MatrixFromPlanes( matrix_t m, const vec4_t left, const vec4_t right, const vec4_t bottom, const vec4_t top,
	                           const vec4_t near, const vec4_t far );
	void     MatrixToVectorsFLU( const matrix_t m, vec3_t forward, vec3_t left, vec3_t up );
	void     MatrixToVectorsFRU( const matrix_t m, vec3_t forward, vec3_t right, vec3_t up );
	void     MatrixSetupTransformFromVectorsFLU( matrix_t m, const vec3_t forward, const vec3_t left, const vec3_t up, const vec3_t origin );
	void     MatrixSetupTransformFromVectorsFRU( matrix_t m, const vec3_t forward, const vec3_t right, const vec3_t up, const vec3_t origin );
	void     MatrixSetupTransformFromRotation( matrix_t m, const matrix_t rot, const vec3_t origin );
	void     MatrixSetupTransformFromQuat( matrix_t m, const quat_t quat, const vec3_t origin );
	void     MatrixAffineInverse( const matrix_t in, matrix_t out );
	void     MatrixTransformNormal( const matrix_t m, const vec3_t in, vec3_t out );
	void     MatrixTransformNormal2( const matrix_t m, vec3_t inout );
	void     MatrixTransformPoint( const matrix_t m, const vec3_t in, vec3_t out );
	void     MatrixTransformPoint2( const matrix_t m, vec3_t inout );
	void     MatrixTransform4( const matrix_t m, const vec4_t in, vec4_t out );
	void     MatrixTransformPlane( const matrix_t m, const vec4_t in, vec4_t out );
	void     MatrixTransformPlane2( const matrix_t m, vec3_t inout );
	void     MatrixPerspectiveProjection( matrix_t m, vec_t left, vec_t right, vec_t bottom, vec_t top, vec_t near, vec_t far );
	void     MatrixPerspectiveProjectionLH( matrix_t m, vec_t left, vec_t right, vec_t bottom, vec_t top, vec_t near, vec_t far );
	void     MatrixPerspectiveProjectionRH( matrix_t m, vec_t left, vec_t right, vec_t bottom, vec_t top, vec_t near, vec_t far );
	void     MatrixPerspectiveProjectionFovYAspectLH( matrix_t m, vec_t fov, vec_t aspect, vec_t near, vec_t far );
	void     MatrixPerspectiveProjectionFovXYLH( matrix_t m, vec_t fovX, vec_t fovY, vec_t near, vec_t far );
	void     MatrixPerspectiveProjectionFovXYRH( matrix_t m, vec_t fovX, vec_t fovY, vec_t near, vec_t far );
	void     MatrixPerspectiveProjectionFovXYInfiniteRH( matrix_t m, vec_t fovX, vec_t fovY, vec_t near );
	void     MatrixOrthogonalProjection( matrix_t m, vec_t left, vec_t right, vec_t bottom, vec_t top, vec_t near, vec_t far );

	void     MatrixOrthogonalProjectionLH( matrix_t m, vec_t left, vec_t right, vec_t bottom, vec_t top, vec_t near, vec_t far );
	void     MatrixOrthogonalProjectionRH( matrix_t m, vec_t left, vec_t right, vec_t bottom, vec_t top, vec_t near, vec_t far );

	void     MatrixPlaneReflection( matrix_t m, const vec4_t plane );

	void     MatrixLookAtLH( matrix_t output, const vec3_t pos, const vec3_t dir, const vec3_t up );
	void     MatrixLookAtRH( matrix_t m, const vec3_t eye, const vec3_t dir, const vec3_t up );
	void     MatrixScaleTranslateToUnitCube( matrix_t m, const vec3_t mins, const vec3_t maxs );
	void     MatrixCrop( matrix_t m, const vec3_t mins, const vec3_t maxs );

	STATIC_INLINE void AnglesToMatrix( const vec3_t angles, matrix_t m ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		MatrixFromAngles( m, angles[ PITCH ], angles[ YAW ], angles[ ROLL ] );
	}
#endif

//=============================================

// RB: XreaL quaternion math functions required by the renderer

#define QuatSet(q,x,y,z,w) (( q )[ 0 ] = ( x ),( q )[ 1 ] = ( y ),( q )[ 2 ] = ( z ),( q )[ 3 ] = ( w ))
#define QuatCopy(a,b)      (( b )[ 0 ] = ( a )[ 0 ],( b )[ 1 ] = ( a )[ 1 ],( b )[ 2 ] = ( a )[ 2 ],( b )[ 3 ] = ( a )[ 3 ] )

#define QuatCompare(a,b)   (( a )[ 0 ] == ( b )[ 0 ] && ( a )[ 1 ] == ( b )[ 1 ] && ( a )[ 2 ] == ( b )[ 2 ] && ( a )[ 3 ] == ( b )[ 3 ] )

	STATIC_INLINE void QuatClear( quat_t q ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		q[ 0 ] = 0;
		q[ 1 ] = 0;
		q[ 2 ] = 0;
		q[ 3 ] = 1;
	}
#endif

	/*
	STATIC_INLINE int QuatCompare(const quat_t a, const quat_t b)
	{
	        if(a[0] != b[0] || a[1] != b[1] || a[2] != b[2] || a[3] != b[3])
	        {
	                return 0;
	        }
	        return 1;
	}
	*/

	STATIC_INLINE void QuatCalcW( quat_t q ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
#if 1
		vec_t term = 1.0f - ( q[ 0 ] * q[ 0 ] + q[ 1 ] * q[ 1 ] + q[ 2 ] * q[ 2 ] );

		if ( term < 0.0 )
		{
			q[ 3 ] = 0.0;
		}
		else
		{
			q[ 3 ] = -sqrt( term );
		}

#else
		q[ 3 ] = sqrt( fabs( 1.0f - ( q[ 0 ] * q[ 0 ] + q[ 1 ] * q[ 1 ] + q[ 2 ] * q[ 2 ] ) ) );
#endif
	}
#endif

	STATIC_INLINE void QuatInverse( quat_t q ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		q[ 0 ] = -q[ 0 ];
		q[ 1 ] = -q[ 1 ];
		q[ 2 ] = -q[ 2 ];
	}
#endif

	STATIC_INLINE void QuatAntipodal( quat_t q ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		q[ 0 ] = -q[ 0 ];
		q[ 1 ] = -q[ 1 ];
		q[ 2 ] = -q[ 2 ];
		q[ 3 ] = -q[ 3 ];
	}
#endif

	STATIC_INLINE vec_t QuatLength( const quat_t q ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		return ( vec_t ) sqrt( q[ 0 ] * q[ 0 ] + q[ 1 ] * q[ 1 ] + q[ 2 ] * q[ 2 ] + q[ 3 ] * q[ 3 ] );
	}
#endif

	vec_t QuatNormalize( quat_t q );

	void  QuatFromAngles( quat_t q, vec_t pitch, vec_t yaw, vec_t roll );

	STATIC_INLINE void AnglesToQuat( const vec3_t angles, quat_t q ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		QuatFromAngles( q, angles[ PITCH ], angles[ YAW ], angles[ ROLL ] );
	}
#endif

	void QuatFromMatrix( quat_t q, const matrix_t m );
	void QuatToVectorsFLU( const quat_t quat, vec3_t forward, vec3_t left, vec3_t up );
	void QuatToVectorsFRU( const quat_t quat, vec3_t forward, vec3_t right, vec3_t up );

	void QuatToAxis( const quat_t q, vec3_t axis[ 3 ] );
	void QuatToAngles( const quat_t q, vec3_t angles );

// Quaternion multiplication, analogous to the matrix multiplication routines.

// qa = rotate by qa, then qb
	void QuatMultiply0( quat_t qa, const quat_t qb );

// qc = rotate by qa, then qb
	void QuatMultiply1( const quat_t qa, const quat_t qb, quat_t qc );

// qc = rotate by qa, then by inverse of qb
	void QuatMultiply2( const quat_t qa, const quat_t qb, quat_t qc );

// qc = rotate by inverse of qa, then by qb
	void QuatMultiply3( const quat_t qa, const quat_t qb, quat_t qc );

// qc = rotate by inverse of qa, then by inverse of qb
	void QuatMultiply4( const quat_t qa, const quat_t qb, quat_t qc );

	void QuatSlerp( const quat_t from, const quat_t to, float frac, quat_t out );
	void QuatTransformVector( const quat_t q, const vec3_t in, vec3_t out );

//=============================================

	typedef struct
	{
		qboolean frameMemory;
		int      currentElements;
		int      maxElements; // will reallocate and move when exceeded
		void     **elements;
	} growList_t;

// you don't need to init the growlist if you don't mind it growing and moving
// the list as it expands
	void Com_InitGrowList( growList_t *list, int maxElements );
	void Com_DestroyGrowList( growList_t *list );
	int  Com_AddToGrowList( growList_t *list, void *data );
	void *Com_GrowListElement( const growList_t *list, int index );
	int  Com_IndexForGrowListElement( const growList_t *list, const void *element );

//=============================================================================

	enum
	{
	  MEMSTREAM_SEEK_SET,
	  MEMSTREAM_SEEK_CUR,
	  MEMSTREAM_SEEK_END
	};

	enum
	{
	  MEMSTREAM_FLAGS_EOF = BIT( 0 ),
	  MEMSTREAM_FLAGS_ERR = BIT( 1 ),
	};

// helper struct for reading binary file formats
	typedef struct memStream_s
	{
		byte *buffer;
		int  bufSize;
		byte *curPos;
		int  flags;
	}

	memStream_t;

	memStream_t *AllocMemStream( byte *buffer, int bufSize );
	void        FreeMemStream( memStream_t *s );
	int         MemStreamRead( memStream_t *s, void *buffer, int len );
	int         MemStreamGetC( memStream_t *s );
	int         MemStreamGetLong( memStream_t *s );
	int         MemStreamGetShort( memStream_t *s );
	float       MemStreamGetFloat( memStream_t *s );

//=============================================

#ifndef MAX
#define MAX(x,y) (( x ) > ( y ) ? ( x ) : ( y ))
#endif

#ifndef MIN
#define MIN(x,y) (( x ) < ( y ) ? ( x ) : ( y ))
#endif

#if defined( _MSC_VER ) || defined( Q3_VM )
	float rintf( float v );
#endif

//=============================================

	float      Com_Clamp( float min, float max, float value );

	char       *COM_SkipPath( char *pathname );
	char       *Com_SkipTokens( char *s, int numTokens, char *sep );
	char       *Com_SkipCharset( char *s, char *sep );
	void       COM_FixPath( char *pathname );
	const char *COM_GetExtension( const char *name );
	void       COM_StripExtension( const char *in, char *out );
	void       COM_StripExtension2( const char *in, char *out, int destsize );
	void       COM_StripExtension3( const char *src, char *dest, int destsize );
	void       COM_StripFilename( char *in, char *out );
	void       COM_DefaultExtension( char *path, int maxSize, const char *extension );

	void       COM_BeginParseSession( const char *name );
	void       COM_RestoreParseSession( char **data_p );
	void       COM_SetCurrentParseLine( int line );
	int        COM_GetCurrentParseLine( void );
	char       *COM_Parse( char **data_p );

// RB: added COM_Parse2 for having a Doom 3 style tokenizer.
	char       *COM_Parse2( char **data_p );
	char       *COM_ParseExt2( char **data_p, qboolean allowLineBreak );

	char       *COM_ParseExt( char **data_p, qboolean allowLineBreak );
	int        COM_Compress( char *data_p );
	void       COM_ParseError( char *format, ... ) PRINTF_LIKE(1);
	void       COM_ParseWarning( char *format, ... ) PRINTF_LIKE(1);

	int        Com_ParseInfos( char *buf, int max, char infos[][ MAX_INFO_STRING ] );

	qboolean   COM_BitCheck( const int array[], int bitNum );

	void       COM_BitSet( int array[], int bitNum );
	void       COM_BitClear( int array[], int bitNum );

	int        Com_HashKey( char *string, int maxlen );

#define MAX_TOKENLENGTH 1024

#ifndef TT_STRING
//token types
#define TT_STRING      1 // string
#define TT_LITERAL     2 // literal
#define TT_NUMBER      3 // number
#define TT_NAME        4 // name
#define TT_PUNCTUATION 5 // punctuation
#endif

	typedef struct pc_token_s
	{
		int   type;
		int   subtype;
		int   intvalue;
		float floatvalue;
		char  string[ MAX_TOKENLENGTH ];
		int   line;
		int   linescrossed;
	} pc_token_t;

// data is an in/out parm, returns a parsed out token

	void      COM_MatchToken( char **buf_p, char *match );

	void      Com_Parse1DMatrix( char **buf_p, int x, float *m, qboolean checkBrackets );
	void      Com_Parse2DMatrix( char **buf_p, int y, int x, float *m );
	void      Com_Parse3DMatrix( char **buf_p, int z, int y, int x, float *m );

	qboolean  SkipBracedSection( char **program );
	qboolean  SkipBracedSection_Depth( char **program, int depth );  // start at given depth if already
	void      SkipRestOfLine( char **data );

	void      Parse1DMatrix( char **buf_p, int x, float *m );
	void      Parse2DMatrix( char **buf_p, int y, int x, float *m );
	void      Parse3DMatrix( char **buf_p, int z, int y, int x, float *m );

	int QDECL Com_sprintf( char *dest, int size, const char *fmt, ... ) PRINTF_LIKE(3);

// mode parm for FS_FOpenFile
	typedef enum
	{
	  FS_READ,
	  FS_WRITE,
	  FS_APPEND,
	  FS_APPEND_SYNC,
	  FS_READ_DIRECT,
	  FS_UPDATE
	} fsMode_t;

	typedef enum
	{
	  FS_SEEK_CUR,
	  FS_SEEK_END,
	  FS_SEEK_SET
	} fsOrigin_t;

	int        Com_HexStrToInt( const char *str );

	const char *Com_ClearForeignCharacters( const char *str );

//=============================================

	int        Q_isprint( int c );
	int        Q_islower( int c );
	int        Q_isupper( int c );
	int        Q_isalpha( int c );
	int        Q_isnumeric( int c );
	int        Q_isalphanumeric( int c );
	int        Q_isforfilename( int c );

	qboolean   Q_strtol( const char *s, long *out );
	qboolean   Q_strtoi( const char *s, int *out );

// portable case insensitive compare
	int        Q_stricmp( const char *s1, const char *s2 );
	int        Q_strncmp( const char *s1, const char *s2, int n );
	int        Q_stricmpn( const char *s1, const char *s2, int n );
	char       *Q_strlwr( char *s1 );
	char       *Q_strupr( char *s1 );
	char       *Q_strrchr( const char *string, int c );
	const char *Q_stristr( const char *s, const char *find );

#if defined(_WIN32) && !defined(__MINGW32__)
double rint( double x );
#endif

// buffer size safe library replacements
// NOTE : had problem with loading QVM modules
#ifdef NDEBUG
	void Q_strncpyz( char *dest, const char *src, int destsize );

#else
#define         Q_strncpyz(string1,string2,length) Q_strncpyzDebug( string1, string2, length, __FILE__, __LINE__ )
	void     Q_strncpyzDebug( char *dest, const char *src, size_t destsize, const char *file, int line ) __attribute__((__nonnull__));

#endif
	void     Q_strcat( char *dest, int destsize, const char *src );
	int      Q_strnicmp( const char *string1, const char *string2, int n );
	void     Q_strncpyz2( char *dst, const char *src, int dstSize );
	int      Q_strcasecmp( const char *s1, const char *s2 );
	int      Q_strncasecmp( const char *s1, const char *s2, int n );
	qboolean Q_strreplace( char *dest, int destsize, const char *find, const char *replace );

// strlen that discounts Quake color sequences
	int      Q_PrintStrlen( const char *string );

// removes color sequences from string
	char     *Q_CleanStr( char *string );

// parse "\n" into '\n'
	void     Q_ParseNewlines( char *dest, const char *src, int destsize );

// Count the number of char tocount encountered in string
	int      Q_CountChar( const char *string, char tocount );

// removes whitespaces and other bad directory characters
	char     *Q_CleanDirName( char *dirname );

//=============================================

int Q_UTF8Width( const char *str );
int Q_UTF8WidthCP( int ch );
int Q_UTF8Strlen( const char *str );
int Q_UTF8PrintStrlen( const char *str );
qboolean Q_UTF8ContByte( char c );
unsigned long Q_UTF8CodePoint( const char *str );
char *Q_UTF8Encode( unsigned long codepoint );
int Q_UTF8Store( const char *s );
char *Q_UTF8Unstore( int e );

//=============================================

// 64-bit integers for global rankings interface
// implemented as a struct for QVM compatibility
	typedef struct
	{
		byte b0;
		byte b1;
		byte b2;
		byte b3;
		byte b4;
		byte b5;
		byte b6;
		byte b7;
	} qint64;

	/*
	short           LittleShort(short l);
	int             LittleLong(int l);
	qint64          LittleLong64(qint64 l);
	float           LittleFloat(float l);

	short           BigShort(short l);
	int             BigLong(int l);
	qint64          BigLong64(qint64 l);
	float           BigFloat(float l);

	void            Swap_Init(void);
	*/

	char     *QDECL va( const char *format, ... ) PRINTF_LIKE(1);

//=============================================

//
// key / value info strings
//
	char       *Info_ValueForKey( const char *s, const char *key );
	void       Info_RemoveKey( char *s, const char *key );
	void       Info_RemoveKey_big( char *s, const char *key );
	void       Info_SetValueForKey( char *s, const char *key, const char *value );
	void       Info_SetValueForKey_Big( char *s, const char *key, const char *value );
	qboolean   Info_Validate( const char *s );
	void       Info_NextPair( const char **s, char *key, char *value );

// this is only here so the functions in q_shared.c and bg_*.c can link
	void QDECL Com_Error( int level, const char *error, ... ) PRINTF_LIKE(2) NORETURN;
	void QDECL Com_Printf( const char *msg, ... ) PRINTF_LIKE(1);
	void QDECL Com_DPrintf( const char *msg, ... ) PRINTF_LIKE(1);

	/*
	==========================================================

	CVARS (console variables)

	Many variables can be used for cheating purposes, so when
	cheats is zero, force all unspecified variables to their
	default values.
	==========================================================
	*/

#define CVAR_ARCHIVE    1 // set to cause it to be saved to vars.rc
// used for system variables, not for player
// specific configurations
#define CVAR_USERINFO   2 // sent to server on connect or change
#define CVAR_SERVERINFO 4 // sent in response to front end requests
#define CVAR_SYSTEMINFO 8 // these cvars will be duplicated on all clients
#define CVAR_INIT       16 // don't allow change from console at all,
// but can be set from the command line
#define CVAR_LATCH      32 // will only change when C code next does
// a Cvar_Get(), so it can't be changed
// without proper initialization.  modified
// will be set, even though the value hasn't
// changed yet
#define CVAR_ROM                 64 // display only, cannot be set by user at all
#define CVAR_USER_CREATED        128 // created by a set command
#define CVAR_TEMP                256 // can be set even when cheats are disabled, but is not archived
#define CVAR_CHEAT               512 // can not be changed if cheats are disabled
#define CVAR_NORESTART           1024 // do not clear when a cvar_restart is issued
#define CVAR_SHADER              2048 // tell renderer to recompile shaders.

#define CVAR_UNSAFE              4096 // ydnar: unsafe system cvars (renderer, sound settings, anything that might cause a crash)
#define CVAR_SERVERINFO_NOUPDATE 8192 // gordon: won't automatically send this to clients, but server browsers will see it
#define CVAR_NONEXISTENT         0xFFFFFFFF // Cvar doesn't exist.

// nothing outside the Cvar_*() functions should modify these fields!
	typedef struct cvar_s
	{
		char          *name;
		char          *string;
		char          *resetString; // cvar_restart will reset to this value
		char          *latchedString; // for CVAR_LATCH vars
		int           flags;
		qboolean      modified; // set each time the cvar is changed
		int           modificationCount; // incremented each time the cvar is changed
		float         value; // atof( string )
		int           integer; // atoi( string )
		qboolean      validate;
		qboolean      integral;
		float         min;
		float         max;

		struct cvar_s *next;

		struct cvar_s *hashNext;
	} cvar_t;

#define MAX_CVAR_VALUE_STRING 256

	typedef int cvarHandle_t;

// the modules that run in the virtual machine can't access the cvar_t directly,
// so they must ask for structured updates
	typedef struct
	{
		cvarHandle_t handle;
		int          modificationCount;
		float        value;
		int          integer;
		char         string[ MAX_CVAR_VALUE_STRING ];
	} vmCvar_t;

	/*
	==============================================================

	VoIP

	==============================================================
	*/

// if you change the count of flags be sure to also change VOIP_FLAGNUM
#define VOIP_SPATIAL 0x01 // spatialized voip message
#define VOIP_DIRECT  0x02 // non-spatialized voip message

// number of flags voip knows. You will have to bump protocol version number if you
// change this.
#define VOIP_FLAGCNT 2

	/*
	==============================================================

	COLLISION DETECTION

	==============================================================
	*/

#ifdef Q3_VM
#include "../../engine/qcommon/surfaceflags.h"
#else
#include "surfaceflags.h" // shared with the q3map utility
#endif

// plane types are used to speed some tests
// 0-2 are axial planes
#define PLANE_X          0
#define PLANE_Y          1
#define PLANE_Z          2
#define PLANE_NON_AXIAL  3
#define PLANE_NON_PLANAR 4

	/*
	=================
	PlaneTypeForNormal
	=================
	*/

//#define PlaneTypeForNormal(x) (x[0] == 1.0 ? PLANE_X : (x[1] == 1.0 ? PLANE_Y : (x[2] == 1.0 ? PLANE_Z : PLANE_NON_AXIAL) ) )
#define PlaneTypeForNormal( x ) ( x[ 0 ] == 1.0 ? PLANE_X : ( x[ 1 ] == 1.0 ? PLANE_Y : ( x[ 2 ] == 1.0 ? PLANE_Z : ( x[ 0 ] == 0.f && x[ 1 ] == 0.f && x[ 2 ] == 0.f ? PLANE_NON_PLANAR : PLANE_NON_AXIAL ) ) ) )

	/*
	STATIC_INLINE int PlaneTypeForNormal(vec3_t normal)
	{
	        if(normal[0] == 1.0)
	                return PLANE_X;

	        if(normal[1] == 1.0)
	                return PLANE_Y;

	        if(normal[2] == 1.0)
	                return PLANE_Z;

	        return PLANE_NON_AXIAL;
	}
	*/

// plane_t structure
// !!! if this is changed, it must be changed in asm code too !!!
	typedef struct cplane_s
	{
		vec3_t normal;
		float  dist;
		byte   type; // for fast side tests: 0,1,2 = axial, 3 = nonaxial
		byte   signbits; // signx + (signy<<1) + (signz<<2), used as lookup during collision
		byte   pad[ 2 ];
	} cplane_t;

	typedef enum
	{
	  TT_NONE,

	  TT_AABB,
	  TT_CAPSULE,
	  TT_BISPHERE,

	  TT_NUM_TRACE_TYPES
	} traceType_t;

#define CPLANE

// a trace is returned when a box is swept through the world
	typedef struct
	{
		qboolean allsolid; // if true, plane is not valid
		qboolean startsolid; // if true, the initial point was in a solid area
		float    fraction; // time completed, 1.0 = didn't hit anything
		vec3_t   endpos; // final position
		cplane_t plane; // surface normal at impact, transformed to world space
		int      surfaceFlags; // surface hit
		int      contents; // contents on other side of surface hit
		int      entityNum; // entity the contacted sirface is a part of
		float    lateralFraction; // fraction of collision tangetially to the trace direction
	} trace_t;

// trace->entityNum can also be 0 to (MAX_GENTITIES-1)
// or ENTITYNUM_NONE, ENTITYNUM_WORLD

// markfragments are returned by CM_MarkFragments()
	typedef struct
	{
		int firstPoint;
		int numPoints;
	} markFragment_t;

	typedef struct
	{
		vec3_t origin;
		vec3_t axis[ 3 ];
	} orientation_t;

//=====================================================================

// in order from highest priority to lowest
// if none of the catchers are active, bound key strings will be executed
#define KEYCATCH_CONSOLE 0x0001
#define KEYCATCH_UI      0x0002
#define KEYCATCH_MESSAGE 0x0004
#define KEYCATCH_CGAME   0x0008

#define KEYEVSTATE_DOWN 0
#define KEYEVSTATE_CHAR 1
#define KEYEVSTATE_BIT  2
#define KEYEVSTATE_SUP  3

// sound channels
// channel 0 never willingly overrides
// other channels will always override a playing sound on that channel
	typedef enum
	{
	  CHAN_AUTO,
	  CHAN_LOCAL, // menu sounds, etc
	  CHAN_WEAPON,
	  CHAN_VOICE,
	  CHAN_ITEM,
	  CHAN_BODY,
	  CHAN_LOCAL_SOUND, // chat messages, etc
	  CHAN_ANNOUNCER, // announcer voices, etc
	  CHAN_VOICE_BG, // xkan - background sound for voice (radio static, etc.)
	} soundChannel_t;

	/*
	========================================================================

	  ELEMENTS COMMUNICATED ACROSS THE NET

	========================================================================
	*/
#define ANIM_BITS 10

#define ANGLE2SHORT( x ) ( (int)( ( x ) * 65536 / 360 ) & 65535 )
#define SHORT2ANGLE( x ) ( ( x ) * ( 360.0 / 65536 ) )

#define SNAPFLAG_RATE_DELAYED 1
#define SNAPFLAG_NOT_ACTIVE   2 // snapshot used during connection and for zombies
#define SNAPFLAG_SERVERCOUNT  4 // toggled every map_restart so transitions can be detected

//
// per-level limits
//
#define MAX_CLIENTS         64 // JPW NERVE back to q3ta default was 128    // absolute limit

#define GENTITYNUM_BITS     10 // JPW NERVE put q3ta default back for testing // don't need to send any more

#define MAX_GENTITIES       ( 1 << GENTITYNUM_BITS )

// tjw: used for limiting weapons that may overflow gentities[]
#define MIN_SPARE_GENTITIES 64

// entitynums are communicated with GENTITY_BITS, so any reserved
// values thatare going to be communcated over the net need to
// also be in this range
#define ENTITYNUM_NONE           ( MAX_GENTITIES - 1 )
#define ENTITYNUM_WORLD          ( MAX_GENTITIES - 2 )
#define ENTITYNUM_MAX_NORMAL     ( MAX_GENTITIES - 2 )

#define MAX_MODELS               256 // these are sent over the net as 8 bits (Gordon: upped to 9 bits, erm actually it was already at 9 bits, wtf? NEVAR TRUST GAMECODE COMMENTS, comments are evil :E, let's hope it doesn't horribly break anything....)
#define MAX_SOUNDS               256 // so they cannot be blindly increased
#define MAX_CS_SKINS             64
#define MAX_CSSTRINGS            32

#define MAX_CS_SHADERS           32
#define MAX_SERVER_TAGS          256
#define MAX_TAG_FILES            64

#define MAX_CONFIGSTRINGS        1024

// these are the only configstrings that the system reserves, all the
// other ones are strictly for servergame to clientgame communication
#define CS_SERVERINFO          0 // an info string with all the serverinfo cvars
#define CS_SYSTEMINFO          1 // an info string for server system to client system configuration (timescale, etc)

#define RESERVED_CONFIGSTRINGS 2 // game can't modify below this, only the system can

#define MAX_GAMESTATE_CHARS    16000
	typedef struct
	{
		int  stringOffsets[ MAX_CONFIGSTRINGS ];
		char stringData[ MAX_GAMESTATE_CHARS ];
		int  dataCount;
	} gameState_t;

#define REF_FORCE_DLIGHT       ( 1 << 31 ) // RF, passed in through overdraw parameter, force this dlight under all conditions
#define REF_JUNIOR_DLIGHT      ( 1 << 30 ) // (SA) this dlight does not light surfaces.  it only affects dynamic light grid
#define REF_DIRECTED_DLIGHT    ( 1 << 29 ) // ydnar: global directional light, origin should be interpreted as a normal vector

// bit field limits
#define MAX_STATS              16
#define MAX_PERSISTANT         16
#define MAX_MISC               16

#define MAX_EVENTS             4 // max events per frame before we drop events

#define PS_PMOVEFRAMECOUNTBITS 6

// playerState_t is the information needed by both the client and server
// to predict player motion and actions
// nothing outside of pmove should modify these, or some degree of prediction error
// will occur

// you can't add anything to this without modifying the code in msg.c
// (Gordon: unless it doesn't need transmission over the network, in which case it should probably go into the new pmext struct anyway)

// playerState_t is a full superset of entityState_t as it is used by players,
// so if a playerState_t is transmitted, the entityState_t can be fully derived
// from it.
//
// NOTE: all fields in here must be 32 bits (or those within sub-structures)
	typedef struct playerState_s
	{
		int    commandTime; // cmd->serverTime of last executed command
		int    pm_type;
		int    bobCycle; // for view bobbing and footstep generation
		int    pm_flags; // ducked, jump_held, etc
		int    pm_time;

		vec3_t origin;
		vec3_t velocity;
		int    weaponTime;
		int    gravity;

		int   speed;
		int   delta_angles[ 3 ]; // add to command angles to get view direction
		// changed by spawns, rotating objects, and teleporters

		int groundEntityNum; // ENTITYNUM_NONE = in air

		int legsTimer; // don't change low priority animations until this runs out
		int legsAnim; // mask off ANIM_TOGGLEBIT

		int torsoTimer; // don't change low priority animations until this runs out
		int torsoAnim; // mask off ANIM_TOGGLEBIT

		int movementDir; // a number 0 to 7 that represents the relative angle
		// of movement to the view angle (axial and diagonals)
		// when at rest, the value will remain unchanged
		// used to twist the legs during strafing

		int eFlags; // copied to entityState_t->eFlags

		int eventSequence; // pmove generated events
		int events[ MAX_EVENTS ];
		int eventParms[ MAX_EVENTS ];
		int oldEventSequence; // so we can see which events have been added since we last converted to entityState_t

		int externalEvent; // events set on player from another source
		int externalEventParm;
		int externalEventTime;

		int clientNum; // ranges from 0 to MAX_CLIENTS-1

		// weapon info
		int weapon; // copied to entityState_t->weapon
		int weaponstate;

		vec3_t viewangles; // for fixed views
		int    viewheight;

		// damage feedback
		int damageEvent; // when it changes, latch the other parms
		int damageYaw;
		int damagePitch;
		int damageCount;

		int stats[ MAX_STATS ];
		int persistant[ MAX_PERSISTANT ]; // stats that aren't cleared on death

		// ----------------------------------------------------------------------
		// So to use persistent variables here, which don't need to come from the server,
		// we could use a marker variable, and use that to store everything after it
		// before we read in the new values for the predictedPlayerState, then restore them
		// after copying the structure received from the server.

		// Arnout: use the pmoveExt_t structure in bg_public.h to store this kind of data now (presistant on client, not network transmitted)

		int ping; // server to game info for scoreboard
		int pmove_framecount;
		int entityEventSequence;

		int           generic1;
		int           loopSound;
		int           otherEntityNum;
		vec3_t        grapplePoint; // location of grapple to pull towards if PMF_GRAPPLE_PULL
		int           weaponAnim; // mask off ANIM_TOGGLEBIT
		int           Ammo;
		int           clips; // clips held
		int           tauntTimer; // don't allow another taunt until this runs out
		int           misc[ MAX_MISC ]; // misc data
	} playerState_t;

//====================================================================

//
// usercmd_t->button bits, many of which are generated by the client system,
// so they aren't game/cgame only definitions
//

#define USERCMD_BUTTONS     16 // bits allocated for buttons (multiple of 8)

#define BUTTON_ATTACK       0
#define BUTTON_TALK         1  // disables actions
#define BUTTON_USE_HOLDABLE 2
#define BUTTON_GESTURE      3
#define BUTTON_WALKING      4  // walking can't just be inferred from MOVE_RUN
                               // because a key pressed late in the frame will
                               // only generate a small move value for that
                               // frame; walking will use different animations
                               // and won't generate footsteps
#define BUTTON_SPRINT       5
#define BUTTON_ACTIVATE     6
#define BUTTON_ANY          7  // if any key is pressed
#define BUTTON_ATTACK2      8
//                          9
//                          10
//                          11
//                          12
//                          13
//                          14
#define BUTTON_DODGE        15

#define MOVE_RUN          120 // if forwardmove or rightmove are >= MOVE_RUN,
// then BUTTON_WALKING should be set

// Arnout: doubleTap buttons - DT_NUM can be max 8
	typedef enum
	{
	  DT_NONE,
	  DT_MOVELEFT,
	  DT_MOVERIGHT,
	  DT_FORWARD,
	  DT_BACK,
	  DT_UP,
	  DT_NUM
	} dtType_t;

// usercmd_t is sent to the server each client frame
	typedef struct usercmd_s
	{
		int         serverTime;
		int         angles[ 3 ];

		signed char forwardmove, rightmove, upmove;
		byte        doubleTap; // Arnout: only 3 bits used

		// rain - in ET, this can be any entity, and it's used as an array
		// index, so make sure it's unsigned
		// But Unv doesn't use it.
		byte identClient; // NERVE - SMF

		byte        weapon;
		byte        flags;

		byte        buttons[ USERCMD_BUTTONS / 8 ];
	} usercmd_t;

// Some functions for buttons manipulation & testing
	STATIC_INLINE void usercmdPressButton( byte *buttons, int bit ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		buttons[bit / 8] |= 1 << ( bit & 7 );
	}
#endif

	STATIC_INLINE void usercmdReleaseButton( byte *buttons, int bit ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		buttons[bit / 8] &= ~( 1 << ( bit & 7 ) );
	}
#endif

	STATIC_INLINE void usercmdClearButtons( byte *buttons ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		memset( buttons, 0, USERCMD_BUTTONS / 8 );
	}
#endif

	STATIC_INLINE void usercmdCopyButtons( byte *dest, const byte *source ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		memcpy( dest, source, USERCMD_BUTTONS / 8 );
	}
#endif

	STATIC_INLINE void usercmdLatchButtons( byte *dest, const byte *srcNew, const byte *srcOld ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		int i;
		for ( i = 0; i < USERCMD_BUTTONS / 8; ++i )
		{
			 dest[i] |= srcNew[i] & ~srcOld[i];
		}
	}
#endif

	STATIC_INLINE qboolean usercmdButtonPressed( const byte *buttons, int bit ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		return ( buttons[bit / 8] & ( 1 << ( bit & 7 ) ) ) ? qtrue : qfalse;
	}
#endif

	STATIC_INLINE qboolean usercmdButtonsDiffer( const byte *a, const byte *b ) IFDECLARE
#ifdef Q3_VM_INSTANTIATE
	{
		return memcmp( a, b, USERCMD_BUTTONS / 8 ) ? qtrue : qfalse;
	}
#endif

//===================================================================

// if entityState->solid == SOLID_BMODEL, modelindex is an inline model number
#define SOLID_BMODEL 0xffffff

	typedef enum
	{
	  TR_STATIONARY,
	  TR_INTERPOLATE, // non-parametric, but interpolate between snapshots
	  TR_LINEAR,
	  TR_LINEAR_STOP,
	  TR_LINEAR_STOP_BACK, //----(SA)  added.  so reverse movement can be different than forward
	  TR_SINE, // value = base + sin( time / duration ) * delta
	  TR_GRAVITY,
	  // Ridah
	  TR_GRAVITY_LOW,
	  TR_GRAVITY_FLOAT, // super low grav with no gravity acceleration (floating feathers/fabric/leaves/...)
	  TR_GRAVITY_PAUSED, //----(SA)  has stopped, but will still do a short trace to see if it should be switched back to TR_GRAVITY
	  TR_ACCELERATE,
	  TR_DECELERATE,
	  TR_BUOYANCY,
	  // Gordon
	  TR_SPLINE,
	  TR_LINEAR_PATH
	} trType_t;

	typedef struct
	{
		trType_t trType;
		int      trTime;
		int      trDuration; // if non 0, trTime + trDuration = stop time
//----(SA)  removed
		vec3_t   trBase;
		vec3_t   trDelta; // velocity, etc
//----(SA)  removed
	} trajectory_t;

// entityState_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way
// Different eTypes may use the information in different ways
// The messages are delta compressed, so it doesn't really matter if
// the structure size is fairly large
//
// NOTE: all fields in here must be 32 bits (or those within sub-structures)

	typedef enum
	{
		ET_GENERAL,
		ET_PLAYER,
		ET_ITEM,

		ET_RANGE_MARKER,
		ET_BUILDABLE,       // buildable type

		ET_LOCATION,

		ET_MISSILE,
		ET_MOVER,
		ET_BEAM,
		ET_PORTAL,
		ET_SPEAKER,
		ET_PUSH_TRIGGER,
		ET_TELEPORT_TRIGGER,
		ET_INVISIBLE,
		ET_GRAPPLE,       // grapple hooked on wall

		ET_CORPSE,
		ET_PARTICLE_SYSTEM,
		ET_ANIMMAPOBJ,
		ET_MODELDOOR,
		ET_LIGHTFLARE,
		ET_LEV2_ZAP_CHAIN,

		ET_EVENTS       // any of the EV_* events can be added freestanding
		// by setting eType to ET_EVENTS + eventNum
		// this avoids having to set eFlags and eventNum
	} entityType_t;

	typedef struct entityState_s
	{
		int          number; // entity index
		entityType_t eType; // entityType_t
		int          eFlags;

		trajectory_t pos; // for calculating position
		trajectory_t apos; // for calculating angles

		int          time;
		int          time2;

		vec3_t       origin;
		vec3_t       origin2;

		vec3_t       angles;
		vec3_t       angles2;

		int          otherEntityNum; // shotgun sources, etc
		int          otherEntityNum2;

		int          groundEntityNum; // ENTITYNUM_NONE = in air

		int          constantLight; // r + (g<<8) + (b<<16) + (intensity<<24)
		int          loopSound; // constantly loop this sound

		int          modelindex;
		int          modelindex2;
		int          clientNum; // 0 to (MAX_CLIENTS - 1), for players and corpses
		int          frame;

		int          solid; // for client side prediction, trap_linkentity sets this properly

		// old style events, in for compatibility only
		int event; // impulse events -- muzzle flashes, footsteps, etc
		int eventParm;

		int eventSequence; // pmove generated events
		int events[ MAX_EVENTS ];
		int eventParms[ MAX_EVENTS ];

		// for players
		int weapon; // determines weapon and flash model, etc
		int legsAnim; // mask off ANIM_TOGGLEBIT
		int torsoAnim; // mask off ANIM_TOGGLEBIT

		int           misc; // bit flags
		int           generic1;
		int           weaponAnim; // mask off ANIM_TOGGLEBIT
	} entityState_t;

	typedef enum
	{
	  CA_UNINITIALIZED,
	  CA_DISCONNECTED, // not talking to a server
	  CA_CONNECTING, // sending request packets to the server
	  CA_CHALLENGING, // sending challenge packets to the server
	  CA_CONNECTED, // netchan_t established, getting gamestate
	  CA_LOADING, // only during cgame initialization, never during main loop
	  CA_PRIMED, // got gamestate, waiting for first frame
	  CA_ACTIVE, // game views should be displayed
	  CA_CINEMATIC // playing a cinematic or a static pic, not connected to a server
	} connstate_t;

// clipboard
	typedef enum
	{
		SELECTION_PRIMARY,
		SELECTION_SECONDARY,
		SELECTION_CLIPBOARD
	} clipboard_t;

// font support

#define GLYPH_START     0
#define GLYPH_END       255
#define GLYPH_CHARSTART 32
#define GLYPH_CHAREND   127
#define GLYPHS_PER_FONT ( GLYPH_END - GLYPH_START + 1 )
typedef struct
{
	int       height; // number of scan lines
	int       top; // top of glyph in buffer
	int       bottom; // bottom of glyph in buffer
	int       pitch; // width for copying
	int       xSkip; // x adjustment
	int       imageWidth; // width of actual image
	int       imageHeight; // height of actual image
	float     s; // x offset in image where glyph starts
	float     t; // y offset in image where glyph starts
	float     s2;
	float     t2;
	qhandle_t glyph; // handle to the shader with the glyph
	char      shaderName[ 32 ];
} glyphInfo_t;

typedef int fontHandle_t;

#ifndef Q3_VM

typedef glyphInfo_t glyphBlock_t[256];

typedef struct
{
	void         *face, *faceData, *fallback, *fallbackData;
	glyphInfo_t  *glyphBlock[0x110000 / 256]; // glyphBlock_t
	int           pointSize;
	int           height;
	float         glyphScale;
	char          name[ MAX_QPATH ];
} fontInfo_t;

#endif

typedef struct
{
	fontHandle_t  handle;
	qboolean      isBitmap;
	int           pointSize;
	int           height;
	float         glyphScale;
} fontMetrics_t;

#define Square( x ) ( ( x ) * ( x ) )

// real time
//=============================================

	typedef struct qtime_s
	{
		int tm_sec; /* seconds after the minute - [0,59] */
		int tm_min; /* minutes after the hour - [0,59] */
		int tm_hour; /* hours since midnight - [0,23] */
		int tm_mday; /* day of the month - [1,31] */
		int tm_mon; /* months since January - [0,11] */
		int tm_year; /* years since 1900 */
		int tm_wday; /* days since Sunday - [0,6] */
		int tm_yday; /* days since January 1 - [0,365] */
		int tm_isdst; /* daylight savings time flag */
	} qtime_t;

// server browser sources
#define AS_LOCAL     0
#define AS_GLOBAL    1 // NERVE - SMF - modified
#define AS_FAVORITES 2

// cinematic states
	typedef enum
	{
	  FMV_IDLE,
	  FMV_PLAY, // play
	  FMV_EOF, // all other conditions, i.e. stop/EOF/abort
	  FMV_ID_BLT,
	  FMV_ID_IDLE,
	  FMV_LOOPED,
	  FMV_ID_WAIT
	} e_status;

	typedef enum _flag_status
	{
	  FLAG_ATBASE = 0,
	  FLAG_TAKEN, // CTF
	  FLAG_TAKEN_RED, // One Flag CTF
	  FLAG_TAKEN_BLUE, // One Flag CTF
	  FLAG_DROPPED
	} flagStatus_t;

	typedef enum
	{
	  DS_NONE,
	  DS_PLAYBACK,
	  DS_RECORDING,
	  DS_NUM_DEMO_STATES
	} demoState_t;

#define MAX_GLOBAL_SERVERS       4096
#define MAX_OTHER_SERVERS        128
#define MAX_PINGREQUESTS         16
#define MAX_SERVERSTATUSREQUESTS 16

#define GENTITYNUM_MASK           ( MAX_GENTITIES - 1 )

#define MAX_EMOTICON_NAME_LEN     16
#define MAX_EMOTICONS             64

#define MAX_LOCATIONS             64
#define MAX_MODELS                256 // these are sent over the net as 8 bits
#define MAX_SOUNDS                256 // so they cannot be blindly increased
#define MAX_GAME_SHADERS          64
#define MAX_GAME_PARTICLE_SYSTEMS 64
#define MAX_HOSTNAME_LENGTH       80
#define MAX_NEWS_STRING           10000

	typedef struct
	{
		char      name[ MAX_EMOTICON_NAME_LEN ];
#ifndef GAME
		int       width;
		qhandle_t shader;
#endif
	} emoticon_t;

	typedef struct
	{
		unsigned int hi;
		unsigned int lo;
	} clientList_t;

	qboolean Com_ClientListContains( const clientList_t *list, int clientNum );
	void     Com_ClientListAdd( clientList_t *list, int clientNum );
	void     Com_ClientListRemove( clientList_t *list, int clientNum );
	char     *Com_ClientListString( const clientList_t *list );
	void     Com_ClientListParse( clientList_t *list, const char *s );

	/* This should not be changed because this value is
	* expected to be the same on the client and on the server */
#define RSA_PUBLIC_EXPONENT 65537
#define RSA_KEY_LENGTH      2048
#define RSA_STRING_LENGTH   ( RSA_KEY_LENGTH / 4 + 1 )

#if defined( __cplusplus )
}
#endif

#endif // __Q_SHARED_H
