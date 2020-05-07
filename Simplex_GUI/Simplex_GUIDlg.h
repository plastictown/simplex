// Simplex_GUIDlg.h : файл заголовка

#ifndef __SIMPLEX_GUI_DLG_H__
#define __SIMPLEX_GUI_DLG_H__

#include "Structures.h"
#include "Simplex.h"

#pragma once


// диалоговое окно CSimplex_GUIDlg
class CSimplex_GUIDlg : public CDialog
{
public:
	CSimplex m_simplex;
	HWND**	  m_pHwnd;
	int nc, nr;
	void DestroyWindows();
	CProgressCtrl* m_pProgress;
// Создание
public:
	CSimplex_GUIDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_SIMPLEX_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetsize();
	afx_msg void OnBnClickedSimplex();
	afx_msg void OnBnClickedChange();
};

#endif // !__SIMPLEX_GUI_DLG_H__