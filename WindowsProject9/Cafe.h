#pragma once
#include "header.h"
#include "Menu.h"

class Cafe
{
public:
	Cafe(void);
	Cafe(LPCTSTR lpStr);
public:
	~Cafe(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static Cafe* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	TCHAR text[200];
	HWND hEdit,hCheckBox;
};


