#include "Cafe.h"

Cafe* Cafe::ptr = NULL;
double PricesCafe[4] = { 5,6,7,8 };

Cafe::Cafe(void)
{
	ptr = this;
}

Cafe::Cafe(LPCTSTR lpStr)
{
	ptr = this;
	_tcscpy_s(text, lpStr);
}

Cafe::~Cafe(void)
{

}

void Cafe::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL Cafe::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	TCHAR str[200];
	for (int i = 0; i < 4; i++) {
		hEdit = GetDlgItem(hwnd, IDC_EDIT20+i);
		_stprintf_s(str, TEXT("%f"), PricesCafe[i]);
		SetWindowText(hEdit, str);

	}
	return TRUE;
}


void Cafe::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDOK)
	{
		TCHAR FinalPrice[200];
		double Price = 0;
		int CheckBoxAmount = 4;
		for (int i = 0; i < CheckBoxAmount; i++) {
			TCHAR buffer[200];
			hCheckBox = GetDlgItem(hwnd, IDC_CHECK1+i);
			if (SendMessage(hCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				hEdit = GetDlgItem(hwnd, IDC_EDIT7+i);
				GetWindowText(hEdit, buffer, 200);
				Price += (PricesCafe[i]*_ttoi(buffer));
			}
		}
		hEdit = GetDlgItem(hwnd, IDC_EDIT11);
		_stprintf_s(FinalPrice,TEXT("%f"), Price);
		SetWindowText(hEdit, FinalPrice);
		_tcscpy_s(text, FinalPrice);
	}
	else if (id == IDMENU)
	{
		EndDialog(hwnd, IDMENU);
	}
}

BOOL CALLBACK Cafe::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

