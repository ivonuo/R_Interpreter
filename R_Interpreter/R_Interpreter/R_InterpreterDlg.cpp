﻿
// R_InterpreterDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "R_Interpreter.h"
#include "R_InterpreterDlg.h"
#include "afxdialogex.h"
#include <string>
#include "InterpreterTransfer.h"
#include "DrawDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "DrawDlgCreator.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRInterpreterDlg 对话框



CRInterpreterDlg::CRInterpreterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_R_INTERPRETER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRInterpreterDlg::DoDataExchange(CDataExchange* pDX)
{
	//CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDOK, InputMsg);
}

BEGIN_MESSAGE_MAP(CRInterpreterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_INPUT, &CRInterpreterDlg::OnEnChangeEditInput)
	ON_EN_CHANGE(IDC_EDIT_OUPTPUT, &CRInterpreterDlg::OnEnChangeEditOuptput)
	ON_BN_CLICKED(IDCANCEL, &CRInterpreterDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDCLEAN, &CRInterpreterDlg::OnBnClickedClean)
	ON_BN_CLICKED(IDTRANSFER, &CRInterpreterDlg::OnBnClickedTransfer)
	ON_BN_CLICKED(IDTRANSFER2, &CRInterpreterDlg::OnBnClickedTransfer2)
	ON_BN_CLICKED(IDTRANSFER3, &CRInterpreterDlg::OnBnClickedTransfer3)
END_MESSAGE_MAP()


// CRInterpreterDlg 消息处理程序

BOOL CRInterpreterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRInterpreterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRInterpreterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRInterpreterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRInterpreterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

void CRInterpreterDlg::OnEnChangeEditInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CRInterpreterDlg::OnEnChangeEditOuptput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CRInterpreterDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CRInterpreterDlg::OnBnClickedClean()
{
	SetDlgItemTextW(IDC_EDIT_INPUT, _T(""));
	SetDlgItemTextW(IDC_EDIT_OUPTPUT, _T(""));
}

void CRInterpreterDlg::OnBnClickedTransfer()
{
	CString text;
	GetDlgItemTextW(IDC_EDIT_INPUT, text);
	CString transferedItem = InterpreterTransfer::getInstance()->transferText(text);
	SetDlgItemTextW(IDC_EDIT_OUPTPUT, transferedItem);
}


void CRInterpreterDlg::OnBnClickedTransfer2()
{
	DrawDlgCreator* creator = new DrawDlgCreator();
	creator->DrawDemoBarlotView();
}


void CRInterpreterDlg::OnBnClickedTransfer3()
{
	DrawDlgCreator* creator = new DrawDlgCreator();
	creator->DrawDemoPieView();
}
