
#ifndef __SIMPLEX_GUI_H__
#define __SIMPLEX_GUI_H__

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CSimplex_GUIApp:
// О реализации данного класса см. Simplex_GUI.cpp
//

class CSimplex_GUIApp : public CWinApp
{
public:
	CSimplex_GUIApp();

// Переопределение
	public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CSimplex_GUIApp theApp;

#endif // !__SIMPLEX_GUI_H__