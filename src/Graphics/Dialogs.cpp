// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Dialogs.hpp"

Color4f GetChoosenColor(HWND hWnd)
{
	CHOOSECOLOR color = { sizeof(CHOOSECOLOR) };
	color.hwndOwner = hWnd;

	COLORREF cust_colors[16] = { };
	color.lpCustColors = cust_colors;

	return ((ChooseColor(&color))? Color4f(color.rgbResult) : DO_NOT_CHANGE_COLOR);
}

INT_PTR CALLBACK StdDialog(HWND hDlg, UINT msg, WPARAM wParam, LPARAM)
{
    switch(msg)
    {
	case WM_INITDIALOG:
        return static_cast<INT_PTR>(TRUE);

    case WM_COMMAND:
        if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return static_cast<INT_PTR>(TRUE);
        }
        break;

	default: return static_cast<INT_PTR>(FALSE);
    }
    return static_cast<INT_PTR>(TRUE);
}

INT_PTR CALLBACK SetNumDialog(HWND hDlg, UINT msg, WPARAM wParam, LPARAM)
{
    switch(msg)
    {
	case WM_INITDIALOG:
        return static_cast<INT_PTR>(TRUE);

    case WM_COMMAND:
        if(LOWORD(wParam) == IDOK)
		{
			CHAR num[10] = { };

            GetDlgItemText(hDlg, IDC_EDIT, num, 10);
            if(!strlen(num)) MessageBox(hDlg, "Поле ввода пусто", "Ошибка", MB_OK | MB_ICONERROR);
            else EndDialog(hDlg, atoi(num));

		}
		else if(LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, -1);

    default: return static_cast<INT_PTR>(FALSE);
    }
}

INT_PTR CALLBACK SetDisplayDialog(HWND hDlg, UINT msg, WPARAM wParam, LPARAM)
{
	static BOOL loaded = FALSE;
	static BOOL show[Graphics::NUMBER_OF_ELEMENTS] = { };
	for(auto i = static_cast<SIZE_T>(0); i < Graphics::NUMBER_OF_ELEMENTS; ++i)
	{
		if(!loaded) show[i] = Graphics::getVisibility(i);

		CheckDlgButton(hDlg, IDC_C_ALF + i, ((show[i])? BST_CHECKED : BST_UNCHECKED));
	}

	loaded = TRUE;

    switch(msg)
    {
	case WM_INITDIALOG:
        return static_cast<INT_PTR>(TRUE);

    case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
		{
			for(SIZE_T i = 0; i < Graphics::NUMBER_OF_ELEMENTS; ++i)
				Graphics::setVisibility(i, show[i]);

			loaded = FALSE;

			EndDialog(hDlg, TRUE);
		}
		case IDCANCEL:
			loaded = FALSE,
			EndDialog(hDlg, -1);
			break;
		case IDC_C_ALF:
			show[Graphics::VISINDEX::ALFA] = !show[Graphics::VISINDEX::ALFA];
			break;
		case IDC_C_ROTX:
			show[Graphics::VISINDEX::ROTX] = !show[Graphics::VISINDEX::ROTX];
			break;
		case IDC_C_ROTY:
			show[Graphics::VISINDEX::ROTY] = !show[Graphics::VISINDEX::ROTY];
			break;
		case IDC_C_ROTZ:
			show[Graphics::VISINDEX::ROTZ] = !show[Graphics::VISINDEX::ROTZ];
			break;
		case IDC_C_TRX:
			show[Graphics::VISINDEX::TRX] = !show[Graphics::VISINDEX::TRX];
			break;
		case IDC_C_TRY:
			show[Graphics::VISINDEX::TRY] = !show[Graphics::VISINDEX::TRY];
			break;
		case IDC_C_TRZ:
			show[Graphics::VISINDEX::TRZ] = !show[Graphics::VISINDEX::TRZ];
			break;
		case IDC_C_ENERGY:
			show[Graphics::VISINDEX::ENERGY] = !show[Graphics::VISINDEX::ENERGY];
			break;
		case IDC_C_COORDS:
			show[Graphics::VISINDEX::COORDS] = !show[Graphics::VISINDEX::COORDS];
			break;

        default: break;
		}

    default: return static_cast<INT_PTR>(FALSE);
    }
}
