#include "Menu.h"
#include "Petrol.h"
#include "Cafe.h"

Menu* Menu::ptr = NULL;
double TotalPrice=0;

Menu::Menu(void)
{
	ptr = this;
}

Menu::~Menu(void)
{

}

void Menu::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL Menu::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT3);
	return TRUE;
}


void Menu::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR str[200];
	if (id == IDC_BUTTON2)
	{
		Petrol dlg;
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, Petrol::DlgProc);
		if (result == IDMENU)
		{
			TotalPrice += _ttof(dlg.text);
			_stprintf_s(str, TEXT("%f"), TotalPrice);
			SetWindowText(hEdit, str);
		}
	}
	else if (id == IDC_BUTTON1)
	{
		Cafe dlg;
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, Cafe::DlgProc);
		if (result == IDMENU)
		{
			TotalPrice += _ttof(dlg.text);
			_stprintf_s(str, TEXT("%f"), TotalPrice);
			SetWindowText(hEdit, str);
		}
	}
}

BOOL CALLBACK Menu::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

