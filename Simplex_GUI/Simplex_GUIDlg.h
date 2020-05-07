// Simplex_GUIDlg.h : ���� ���������

#ifndef __SIMPLEX_GUI_DLG_H__
#define __SIMPLEX_GUI_DLG_H__

#include "Structures.h"
#include "Simplex.h"

#pragma once


// ���������� ���� CSimplex_GUIDlg
class CSimplex_GUIDlg : public CDialog
{
public:
	CSimplex m_simplex;
	HWND**	  m_pHwnd;
	int nc, nr;
	void DestroyWindows();
	CProgressCtrl* m_pProgress;
// ��������
public:
	CSimplex_GUIDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_SIMPLEX_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
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