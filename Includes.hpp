#ifndef __INCLUDES_HPP_INCLUDED__
#define __INCLUDES_HPP_INCLUDED__

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
    
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
    #pragma GCC diagnostic ignored "-Wshadow"
    #pragma GCC diagnostic ignored "-Wold-style-cast"
    #pragma GCC diagnostic ignored "-Winline"
    
#endif // __GNUC__

#ifdef __TXLIB_H_INCLUDED
	#error Ќ»«я ё«ј“№ TXLib
#endif // __TXLIB_H_INCLUDED

#pragma region INCLUDES


#include <Windows.h>
#include <gl\GL.h>

#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Noncopyable.hpp"

#pragma endregion ¬ключаемые библиотеки

#ifdef _WINDOWS

	#undef VOID
	
	typedef void VOID;

#endif // _WINDOWS

#endif // __INCLUDES_HPP_INCLUDED__