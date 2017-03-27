#pragma once

#include "Includes.hpp"

struct Control
{
	enum Buttons : SIZE_T
	{
		XTRM = 0,
		XTRP,
		YTRM,
		YTRP,
		ZTRM,
		ZTRP,

		XROTM,
		XROTP,
		YROTM,
		YROTP,
		ZROTM,
		ZROTP,

		ALFAM,
		ALFAP
	};

private:
	static CONST SIZE_T NUMBER_OF_BUTTONS = 7;

	UCHAR buttons_[NUMBER_OF_BUTTONS * 2];

public:
	FLOAT xrot,
		  yrot,
		  zrot;

	FLOAT angle;

	FLOAT xtr,
		  ytr,
		  ztr;

	Control() :
		xrot(0.0f),
		yrot(0.5f),
		zrot(0.0f),
		angle(0.05f),
		xtr(0.0f),
		ytr(0.0f),
		ztr(0.0f)
	{
		buttons_[Buttons::XTRM] = VK_LEFT;
		buttons_[Buttons::XTRP] = VK_RIGHT;
		buttons_[Buttons::YTRM] = VK_DOWN;
		buttons_[Buttons::YTRP] = VK_UP;
		buttons_[Buttons::ZTRM] = VK_DELETE;
		buttons_[Buttons::ZTRP] = VK_END;

		buttons_[Buttons::XROTM] = 'A';
		buttons_[Buttons::XROTP] = 'D';
		buttons_[Buttons::YROTM] = 'S';
		buttons_[Buttons::YROTP] = 'W';
		buttons_[Buttons::ZROTM] = 'Q';
		buttons_[Buttons::ZROTP] = 'E';

		buttons_[Buttons::ALFAM] = 189;
		buttons_[Buttons::ALFAP] = 187;
	}

	VOID setButton(Buttons index, UCHAR newKey) { buttons_[index] = newKey; }

	VOID manage()
	{
		static CONST FLOAT d = 0.005f;

#define Key(param) GetAsyncKeyState(param)

		if     (Key(buttons_[Buttons::XTRP])) xtr += d; // Translation vector managment
		else if(Key(buttons_[Buttons::XTRM])) xtr -= d;

		else if(Key(buttons_[Buttons::YTRP])) ytr += d;
		else if(Key(buttons_[Buttons::YTRM])) ytr -= d;

		else if(Key(buttons_[Buttons::ZTRP])) ztr += d;
		else if(Key(buttons_[Buttons::ZTRM])) ztr -= d;


		else if(Key(buttons_[Buttons::XROTM])) xrot -= d * 100; // Rotating vector managment
		else if(Key(buttons_[Buttons::XROTP])) xrot += d * 100;

		else if(Key(buttons_[Buttons::YROTP])) yrot += d * 100;
		else if(Key(buttons_[Buttons::YROTM])) yrot -= d * 100;

		else if(Key(buttons_[Buttons::ZROTM])) zrot -= d * 100;
		else if(Key(buttons_[Buttons::ZROTP])) zrot += d * 100;


		else if(Key(buttons_[Buttons::ALFAM])) angle -= d * 10; // Rotating angle managment
		else if(Key(buttons_[Buttons::ALFAP])) angle += d * 10;

#undef Key
	}

	inline VOID dump() const
	{
		std::cout << "alf: " << angle << " xrot: " << xrot << " yrot: " << yrot << " zrot: " << zrot << std::endl <<
			         "xtr: " << xtr << " ytr: " << ytr << " ztr: " << ztr << std::endl;
	}
};
