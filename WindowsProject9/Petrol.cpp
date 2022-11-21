#include "Petrol.h"

Petrol* Petrol::ptr = NULL;
double PricesPetrol[4] = { 5,6,7,8 };

Petrol::Petrol(void)
{
	ptr = this;
}

Petrol::Petrol(LPCTSTR lpStr)
{
	ptr = this;
	_tcscpy_s(text, lpStr);
}

Petrol::~Petrol(void)
{

}

void Petrol::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL Petrol::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT12);
	hCombo = GetDlgItem(hwnd, IDC_COMBO1);
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("А-92")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("А-95")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("А-98")));
	SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("ДП")));
	return TRUE;
}


void Petrol::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR str[200];
	if (id == IDC_COMBO1 && codeNotify == CBN_SELCHANGE)
	{
		int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		for (int i =0 ; i < 4; i++) {
			if (i == index) {
				_stprintf_s(str, TEXT("%f"), PricesPetrol[i]);
				SetWindowText(hEdit, str);
			}
		}

	}
	if (SendDlgItemMessage(hwnd, IDC_RADIO1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
		SendDlgItemMessage(hwnd, IDC_EDIT2, EM_SETREADONLY, 1, 0);
		SendDlgItemMessage(hwnd, IDC_EDIT1, EM_SETREADONLY, 0, 0);
	}
	else if (SendDlgItemMessage(hwnd, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED) {
		SendDlgItemMessage(hwnd, IDC_EDIT1, EM_SETREADONLY, 1, 0);
		SendDlgItemMessage(hwnd, IDC_EDIT2, EM_SETREADONLY, 0, 0);
	}
	if (id == IDOK)
	{
		if (SendDlgItemMessage(hwnd, IDC_RADIO1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
			TCHAR FinalPrice[200];
			double Price = 0;
			TCHAR buffer1[20];
			TCHAR buffer2[20];
			GetWindowText(hEdit, buffer1, 20);
			hEdit = GetDlgItem(hwnd, IDC_EDIT1);
			GetWindowText(hEdit, buffer2, 20);
			Price += (_ttof(buffer1) * _ttoi(buffer2));


			hEdit = GetDlgItem(hwnd, IDC_EDIT3);
			_stprintf_s(FinalPrice, TEXT("%f"), Price);
			SetWindowText(hEdit, FinalPrice);
			_tcscpy_s(text, FinalPrice);

		}
		else if (SendDlgItemMessage(hwnd, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED) {
			TCHAR FinalPrice[200];
			double Price = 0;
			TCHAR buffer1[20];
			TCHAR buffer2[20];
			GetWindowText(hEdit, buffer1, 20);
			hEdit = GetDlgItem(hwnd, IDC_EDIT2);
			GetWindowText(hEdit, buffer2, 20);

			if (_ttof(buffer1) > _ttoi(buffer2)) {
				hEdit = GetDlgItem(hwnd, IDC_EDIT3);
				SetWindowText(hEdit, TEXT("Недостаточно денег!"));
			}
			else {
				Price +=_ttoi(buffer2);
				hEdit = GetDlgItem(hwnd, IDC_EDIT3);
				_stprintf_s(FinalPrice, TEXT("%f"), Price);
				SetWindowText(hEdit, FinalPrice);
				_tcscpy_s(text, FinalPrice);
			}

		}
	}
	else if (id == IDMENU)
	{
		EndDialog(hwnd, IDMENU);
	}
}

BOOL CALLBACK Petrol::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

