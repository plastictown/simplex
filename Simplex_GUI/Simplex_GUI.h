
#ifndef __SIMPLEX_GUI_H__
#define __SIMPLEX_GUI_H__

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CSimplex_GUIApp:
// � ���������� ������� ������ ��. Simplex_GUI.cpp
//

class CSimplex_GUIApp : public CWinApp
{
public:
	CSimplex_GUIApp();

// ���������������
	public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CSimplex_GUIApp theApp;

#endif // !__SIMPLEX_GUI_H__