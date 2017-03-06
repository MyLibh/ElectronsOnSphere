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

	#define abstract
	#define _In_
	#define _In_opt_

	#ifdef __STRICT_ANSI__
		#undef __STRICT_ANSI__
	#endif // __STRICT_ANSI__

#endif // __GNUC__

#ifdef __TXLIB_H_INCLUDED
	#error ���� ����� TXLib
#endif // __TXLIB_H_INCLUDED

#pragma region INCLUDES

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>

#include <string>
#include <iostream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>

#include "wrapResource.hpp"
#include "Noncopyable.hpp"

#pragma endregion ���������� ����������

#ifdef DEBUG
	
	enum DBGMODE : INT
	{
		INFO  = 0,
		FAIL 
	};
	
	VOID DBG(std::string, DBGMODE = DBGMODE::INFO);

#else

#define DBG(inf, mode)

#endif // DEBUG

#ifdef _WINDOWS

	#undef VOID

	typedef void VOID;

#endif // _WINDOWS

#endif // __INCLUDES_HPP_INCLUDED__
