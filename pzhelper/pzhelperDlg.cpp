
// pzhelperDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "pzhelper.h"
#include "pzhelperDlg.h"
#include "afxdialogex.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 构造函数实现
CpzhelperDlg::CpzhelperDlg(CWnd* pParent) : CDialogEx(IDD_PZHELPER_DIALOG, pParent)
{
	// 加载应用图标
	m_hIcon = AfxGetApp()->LoadIcon(IDI_SUN_FLOWER);
	m_status_int = 0;
	m_in_dungeon = false;
}

void CpzhelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_STATUS, m_game_status);
	DDX_Control(pDX, IDC_SUN_NUMBER, m_sun_number);
	DDX_Control(pDX, IDC_sun_lock, m_sun_lock);
	DDX_Control(pDX, IDC_SUN_UPDATE, m_ctr_sun_modify);
}

// 消息映射
BEGIN_MESSAGE_MAP(CpzhelperDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SUN_UPDATE, &CpzhelperDlg::OnBnClickedSunUpdate)
	ON_BN_CLICKED(IDC_sun_lock, &CpzhelperDlg::OnBnClickedsunlock)
END_MESSAGE_MAP()


// CpzhelperDlg 消息处理程序

BOOL CpzhelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	
	// TODO: 在此添加额外的初始化代码
	/* [ 初 始 化 开 始 ] */
	// 创建线程监控游戏运行状态
	HANDLE thread = CreateThread(NULL, 0, ThreadProc, this, 0, NULL);
	m_sun_number.SetWindowTextW(L"50");
	/* [ 初 始 化 结 束 ] */
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpzhelperDlg::OnPaint()
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
HCURSOR CpzhelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CpzhelperDlg::OnOK()
{

}


void CpzhelperDlg::OnBnClickedSunUpdate()
{
	if (this->m_status_int)
	{
		// 判断是否已在图中
		if (this->m_in_dungeon)
		{
			CString numeric;
			m_sun_number.GetWindowTextW(numeric);
			int number = _ttoi(numeric);
			if (number < 0 || number > 999999) 
			{
				MessageBox(L"数值范围：0~99999");
			}
			else {
				sunUpdate(this, number);
			}
		}
		else {
			MessageBox(L"未进入关卡！");
		}
	}
	else {
		MessageBox(L"游戏未运行！");
	}
}

void CpzhelperDlg::OnBnClickedsunlock()
{
	m_sun_locked = m_sun_lock.GetCheck();
	if (m_sun_locked) 
	{
		m_sun_number.EnableWindow(false);
		m_ctr_sun_modify.EnableWindow(false);
	}
	else {
		m_sun_number.EnableWindow(true);
		m_ctr_sun_modify.EnableWindow(true);
	}
}

