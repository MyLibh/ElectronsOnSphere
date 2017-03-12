#ifndef __INCLUDES_HPP_INCLUDED__
#define __INCLUDES_HPP_INCLUDED__

#define DEBUG

#ifdef _MSC_VER

    #pragma warning(push, 4)

    #pragma setlocale("russian")

    #ifndef NDEBUG
        #pragma check_stack(on)
        #pragma strict_gs_check(push, on)
    #endif // NDEBUG

    #define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1

#endif // _MSC_VER

#ifdef __GNUC__

    #pragma GCC diagnostic push

    #pragma GCC optimize("no-strict-aliasing")

    #pragma GCC diagnostic ignored "-Wunknown-pragmas"
    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    #pragma GCC diagnostic ignored "-Wconversion-null"
    #pragma GCC diagnostic ignored "-Weffc++"

	#define abstract
	#define _In_
	#define _In_opt_

	#ifdef __STRICT_ANSI__
		#undef __STRICT_ANSI__
	#endif // __STRICT_ANSI__

    #define CDSIZEOF_STRUCT(structname, member)  (((int)((LPBYTE)(&((structname*)0)->member) - ((LPBYTE)((structname*)0)))) + sizeof(((structname*)0)->member))
    #define OPENFILENAME_SIZE_VERSION_400A  CDSIZEOF_STRUCT(OPENFILENAMEA,lpTemplateName)

#endif // __GNUC__

#ifdef __TXLIB_H_INCLUDED
	#error Ќ»«я ё«ј“№ TXLib
#endif // __TXLIB_H_INCLUDED

#pragma region INCLUDES

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include <ctime>
#include <commdlg.h>

#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>

#include <string>
#include <sstream>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "wrapResource.hpp"
#include "Noncopyable.hpp"

#pragma endregion ¬ключаемые библиотеки

#ifdef _WINDOWS

	#undef VOID

	typedef void VOID;

#endif // _WINDOWS

#ifdef DEBUG

	enum DBGMODE : INT
	{
		INFO    = 0,
		STATUS,
		FAIL
	};

	VOID DBG(std::string, DBGMODE = DBGMODE::INFO);

#else

#define DBG(inf, mode)
#define DBG(inf)

#endif // DEBUG

#endif // __INCLUDES_HPP_INCLUDED__
