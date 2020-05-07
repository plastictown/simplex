#include "stdafx.h"
#include "Simplex_GUI.h"
#include "Simplex_GUIDlg.h"
#include <stdlib.h>

#include <iostream>
#include <fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// диалоговое окно CSimplex_GUIDlg

CSimplex_GUIDlg::CSimplex_GUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimplex_GUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimplex_GUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimplex_GUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SETSIZE, &CSimplex_GUIDlg::OnBnClickedSetsize)
	ON_BN_CLICKED(IDC_SIMPLEX, &CSimplex_GUIDlg::OnBnClickedSimplex)
	ON_BN_CLICKED(IDC_CHANGE, &CSimplex_GUIDlg::OnBnClickedChange)
END_MESSAGE_MAP()


// обработчики сообщений CSimplex_GUIDlg

BOOL CSimplex_GUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Добавление пункта ''О программе...'' в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	//Кнопка "изменить размер"
	GetDlgItem(IDC_CHANGE)->EnableWindow(FALSE);

	m_pProgress=(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);

	m_pProgress->SetRange(0,100);
	m_pProgress->SetPos(0);


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CSimplex_GUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей средой.

void CSimplex_GUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CSimplex_GUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSimplex_GUIDlg::OnBnClickedSetsize()
{
	//	Получаем значения длины и высоты массива
	int nRows=GetDlgItemInt(IDC_MATRIX_ROWS,NULL, 0);
	int nCols=GetDlgItemInt(IDC_MATRIX_COLS,NULL, 0);

	if(nRows>0 && nCols>0)
	{
		//Устанавливаем размер массива и отключаем элементы управления
		m_simplex.SetSize(nRows, nCols);
		nc=nCols;
		nr=nRows;
		GetDlgItem(IDC_MATRIX_ROWS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MATRIX_COLS)->EnableWindow(FALSE);
		GetDlgItem(IDC_SETSIZE)->EnableWindow(FALSE);

		//Кнопка "изменить размер"
		GetDlgItem(IDC_CHANGE)->EnableWindow(TRUE);

		//Выделяем память под массив описателей
		m_pHwnd=new HWND*[nRows+1];

		for(int i=0; i<(nRows+1); i++)
		{
			m_pHwnd[i]=new HWND[nCols];
		}

		for(int i=0; i<(nRows+1); i++)
		{
			for(int j=0; j<nCols; j++)
			{
				//Тут нужно создать кучу EditBox'ов
				m_pHwnd[i][j]=CreateWindowExW( 0,
											L"EDIT",
											L"",
											 ES_LEFT | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
											14+42*j,
											120+22*i,
											40,
											20,
											this->m_hWnd,
											NULL,
											theApp.m_hInstance,
											NULL);
			}
		}
	
		GetDlgItem(IDC_SIMPLEX)->EnableWindow(TRUE);
	}
	else
	{
		AfxMessageBox(L"Неверный размер массива!", MB_OK | MB_ICONEXCLAMATION);
	}
}

void CSimplex_GUIDlg::OnBnClickedSimplex()
{
	//Отключаем кнопку "Вычислить"
	GetDlgItem(IDC_SIMPLEX)->EnableWindow(FALSE);
	//Отключаем кнопку "Изменить"
	GetDlgItem(IDC_CHANGE)->EnableWindow(FALSE);
	//Устанавливаем ProgressCtrl в ноль
	m_pProgress->SetPos(0);
	//Включаем ProgressCtrl;
	m_pProgress->ShowWindow(SW_SHOW);


	PWSTR tmp=new WCHAR[12];
	float f=0;
	wcsset(tmp, 0);

	for(int i=0; i<(nr+1); i++)
		{
			for(int j=0; j<(nc-1); j++)
			{
				wcsset(tmp, 0);
				::GetWindowText(m_pHwnd[i][j], tmp, 10);
				f=(float)_wtof(tmp);
				m_simplex.matrix[i][j]=f;
			}

			wcsset(tmp, 0);
			::GetWindowText(m_pHwnd[i][nc-1], tmp, 10);
			f=(float)_wtof(tmp);
			m_simplex.matrix[i][m_simplex.size.x-1]=f;
		}

	m_simplex.CalculateL_x();
	m_simplex.Copy_L_x_to_Matrix();

	m_simplex.matrix[m_simplex.size.y-2][m_simplex.size.x-1]=-m_simplex.matrix[m_simplex.size.y-2][m_simplex.size.x-1];

	//Итерации

	int result=0;

	while(!result)
	{
		result=m_simplex.iteration();

	}

	m_pProgress->SetPos(50);

	if(result==-1)
	{
		DestroyWindows();
		GetDlgItem(IDC_MATRIX_ROWS)->EnableWindow(TRUE);
		GetDlgItem(IDC_MATRIX_COLS)->EnableWindow(TRUE);
		GetDlgItem(IDC_SETSIZE)->EnableWindow(TRUE);
		//Выключаем ProgressCtrl;
		m_pProgress->ShowWindow(SW_HIDE);
		AfxMessageBox(L"Нет решений");
		return;
	}

	//Итерации без L(x)

	result=0;

	while(!result)
	{
		result=m_simplex.iteration_small();

	}

	if(result==-1)
	{
		DestroyWindows();
		GetDlgItem(IDC_MATRIX_ROWS)->EnableWindow(TRUE);
		GetDlgItem(IDC_MATRIX_COLS)->EnableWindow(TRUE);
		GetDlgItem(IDC_SETSIZE)->EnableWindow(TRUE);
		//Выключаем ProgressCtrl;
		m_pProgress->ShowWindow(SW_HIDE);
		AfxMessageBox(L"Нет решений");
		return;
	}
	m_pProgress->SetPos(100);

	CString str,str2;

	str.Format(L"min g(x)=%4.2f",-m_simplex.matrix[m_simplex.size.y-2][m_simplex.size.x-1]);

	for(int i=0; i<m_simplex.size_small.y; i++)
	{
		str2.Format(L"\nx%d=%4.2f",m_simplex.vertX[i].num,m_simplex.matrix[i][m_simplex.size.x-1]);
		str=str+str2;
	}

	AfxMessageBox(str);
	DestroyWindows();
	GetDlgItem(IDC_MATRIX_ROWS)->EnableWindow(TRUE);
	GetDlgItem(IDC_MATRIX_COLS)->EnableWindow(TRUE);
	GetDlgItem(IDC_SETSIZE)->EnableWindow(TRUE);
	//Выключаем ProgressCtrl;
	m_pProgress->ShowWindow(SW_HIDE);
	m_pProgress->SetPos(0);
	
}

void CSimplex_GUIDlg::DestroyWindows()
{
	for(int i=0; i<(nr+1); i++)
		{
			for(int j=0; j<nc; j++)
			{
				::DestroyWindow(m_pHwnd[i][j]);
				
			}
		}
}
void CSimplex_GUIDlg::OnBnClickedChange()
{
	DestroyWindows();
	//Отключаем/включаем кнопки
	GetDlgItem(IDC_SIMPLEX)->EnableWindow(FALSE);
	GetDlgItem(IDC_MATRIX_ROWS)->EnableWindow(TRUE);
	GetDlgItem(IDC_MATRIX_COLS)->EnableWindow(TRUE);
	GetDlgItem(IDC_SETSIZE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHANGE)->EnableWindow(FALSE);
}
