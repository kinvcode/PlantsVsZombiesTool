
// pzhelperDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "pzhelper.h"
#include "pzhelperDlg.h"
#include "afxdialogex.h"
#include "common.h"
#include <vector>

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
	DDX_Control(pDX, IDC_CHECK_COOL_DOWN, m_check_plants_cd);
	DDX_Control(pDX, IDC_DUNGEON_STATUS, m_dungeon_status);
	DDX_Control(pDX, IDC_COMBO1, Plant_ctr_01);
	DDX_Control(pDX, IDC_COMBO2, Plant_ctr_02);
	DDX_Control(pDX, IDC_COMBO3, Plant_ctr_03);
	DDX_Control(pDX, IDC_COMBO4, Plant_ctr_04);
	DDX_Control(pDX, IDC_COMBO5, Plant_ctr_05);
	DDX_Control(pDX, IDC_COMBO6, Plant_ctr_11);
	DDX_Control(pDX, IDC_COMBO7, Plant_ctr_12);
	DDX_Control(pDX, IDC_COMBO8, Plant_ctr_13);
	DDX_Control(pDX, IDC_COMBO9, Plant_ctr_14);
	DDX_Control(pDX, IDC_COMBO10, Plant_ctr_15);
	DDX_Control(pDX, IDC_COMBO11, Plant_ctr_21);
	DDX_Control(pDX, IDC_COMBO12, Plant_ctr_22);
	DDX_Control(pDX, IDC_COMBO13, Plant_ctr_23);
	DDX_Control(pDX, IDC_COMBO14, Plant_ctr_24);
	DDX_Control(pDX, IDC_COMBO15, Plant_ctr_25);
	DDX_Control(pDX, IDC_COMBO16, Plant_ctr_31);
	DDX_Control(pDX, IDC_COMBO17, Plant_ctr_32);
	DDX_Control(pDX, IDC_COMBO18, Plant_ctr_33);
	DDX_Control(pDX, IDC_COMBO19, Plant_ctr_34);
	DDX_Control(pDX, IDC_COMBO20, Plant_ctr_35);
	DDX_Control(pDX, IDC_COMBO21, Plant_ctr_41);
	DDX_Control(pDX, IDC_COMBO22, Plant_ctr_42);
	DDX_Control(pDX, IDC_COMBO23, Plant_ctr_43);
	DDX_Control(pDX, IDC_COMBO24, Plant_ctr_44);
	DDX_Control(pDX, IDC_COMBO25, Plant_ctr_45);
	DDX_Control(pDX, IDC_COMBO26, Plant_ctr_51);
	DDX_Control(pDX, IDC_COMBO27, Plant_ctr_52);
	DDX_Control(pDX, IDC_COMBO28, Plant_ctr_53);
	DDX_Control(pDX, IDC_COMBO29, Plant_ctr_54);
	DDX_Control(pDX, IDC_COMBO30, Plant_ctr_55);
	DDX_Control(pDX, IDC_COMBO31, Plant_ctr_61);
	DDX_Control(pDX, IDC_COMBO32, Plant_ctr_62);
	DDX_Control(pDX, IDC_COMBO33, Plant_ctr_63);
	DDX_Control(pDX, IDC_COMBO34, Plant_ctr_64);
	DDX_Control(pDX, IDC_COMBO35, Plant_ctr_65);
	DDX_Control(pDX, IDC_COMBO36, Plant_ctr_71);
	DDX_Control(pDX, IDC_COMBO37, Plant_ctr_72);
	DDX_Control(pDX, IDC_COMBO38, Plant_ctr_73);
	DDX_Control(pDX, IDC_COMBO39, Plant_ctr_74);
	DDX_Control(pDX, IDC_COMBO40, Plant_ctr_75);
	DDX_Control(pDX, IDC_COMBO41, Plant_ctr_81);
	DDX_Control(pDX, IDC_COMBO42, Plant_ctr_82);
	DDX_Control(pDX, IDC_COMBO43, Plant_ctr_83);
	DDX_Control(pDX, IDC_COMBO44, Plant_ctr_84);
	DDX_Control(pDX, IDC_COMBO45, Plant_ctr_85);
}

// 消息映射
BEGIN_MESSAGE_MAP(CpzhelperDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SUN_UPDATE, &CpzhelperDlg::OnBnClickedSunUpdate)
	ON_BN_CLICKED(IDC_sun_lock, &CpzhelperDlg::OnBnClickedsunlock)
	ON_BN_CLICKED(IDC_CHECK_COOL_DOWN, &CpzhelperDlg::OnBnClickedCheckCoolDown)
	ON_BN_CLICKED(IDC_BUTTON1, &CpzhelperDlg::OnBnClickedButton1)
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
	/*========初始化开始====*/
	// 监控游戏运行状态、关卡状态
	HANDLE run_thread = CreateThread(NULL, 0, GameIsRuning, this, 0, NULL);
	// 阳光锁定、植物无冷却
	HANDLE fast_thread = CreateThread(NULL, 0, FastScan, this, 0, NULL);
	// 阳光默认值
	m_sun_number.SetWindowTextW(L"99999");

	CComboBox* plantsBox[45];
	plantsBox[0] = &Plant_ctr_01;
	plantsBox[1] = &Plant_ctr_02;
	plantsBox[2] = &Plant_ctr_03;
	plantsBox[3] = &Plant_ctr_04;
	plantsBox[4] = &Plant_ctr_05;

	plantsBox[5] = &Plant_ctr_11;
	plantsBox[6] = &Plant_ctr_12;
	plantsBox[7] = &Plant_ctr_13;
	plantsBox[8] = &Plant_ctr_14;
	plantsBox[9] = &Plant_ctr_15;

	plantsBox[10] = &Plant_ctr_21;
	plantsBox[11] = &Plant_ctr_22;
	plantsBox[12] = &Plant_ctr_23;
	plantsBox[13] = &Plant_ctr_24;
	plantsBox[14] = &Plant_ctr_25;

	plantsBox[15] = &Plant_ctr_31;
	plantsBox[16] = &Plant_ctr_32;
	plantsBox[17] = &Plant_ctr_33;
	plantsBox[18] = &Plant_ctr_34;
	plantsBox[19] = &Plant_ctr_35;

	plantsBox[20] = &Plant_ctr_41;
	plantsBox[21] = &Plant_ctr_42;
	plantsBox[22] = &Plant_ctr_43;
	plantsBox[23] = &Plant_ctr_44;
	plantsBox[24] = &Plant_ctr_45;

	plantsBox[25] = &Plant_ctr_51;
	plantsBox[26] = &Plant_ctr_52;
	plantsBox[27] = &Plant_ctr_53;
	plantsBox[28] = &Plant_ctr_54;
	plantsBox[29] = &Plant_ctr_55;

	plantsBox[30] = &Plant_ctr_61;
	plantsBox[31] = &Plant_ctr_62;
	plantsBox[32] = &Plant_ctr_63;
	plantsBox[33] = &Plant_ctr_64;
	plantsBox[34] = &Plant_ctr_65;

	plantsBox[35] = &Plant_ctr_71;
	plantsBox[36] = &Plant_ctr_72;
	plantsBox[37] = &Plant_ctr_73;
	plantsBox[38] = &Plant_ctr_74;
	plantsBox[39] = &Plant_ctr_75;

	plantsBox[40] = &Plant_ctr_81;
	plantsBox[41] = &Plant_ctr_82;
	plantsBox[42] = &Plant_ctr_83;
	plantsBox[43] = &Plant_ctr_84;
	plantsBox[44] = &Plant_ctr_85;


	for (int i = 0; i < 45; i++) 
	{
		plantsBox[i]->InsertString(0, L"豌豆射手");
		plantsBox[i]->InsertString(1, L"向日葵");
		plantsBox[i]->InsertString(2, L"樱桃炸弹");
		plantsBox[i]->InsertString(3, L"坚果");
		if (i < 5) 
		{
			plantsBox[i]->SetCurSel(1);
		}
		else {
			plantsBox[i]->SetCurSel(0);
		}
	}
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



void CpzhelperDlg::OnBnClickedCheckCoolDown()
{
	m_plants_cool_down = m_check_plants_cd.GetCheck();
}


void CpzhelperDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	if (this->m_status_int)
	{
		// 判断是否已在图中
		if (this->m_in_dungeon)
		{
			int code;
			// ID,y,x
			code = Plant_ctr_01.GetCurSel();
			growplant(code, 0, 0);
			code = Plant_ctr_02.GetCurSel();
			growplant(code, 1, 0);
			code = Plant_ctr_03.GetCurSel();
			growplant(code, 2, 0);
			code = Plant_ctr_04.GetCurSel();
			growplant(code, 3, 0);
			code = Plant_ctr_05.GetCurSel();
			growplant(code, 4, 0);

			code = Plant_ctr_11.GetCurSel();
			growplant(code, 0, 1);
			code = Plant_ctr_12.GetCurSel();
			growplant(code, 1, 1);
			code = Plant_ctr_13.GetCurSel();
			growplant(code, 2, 1);
			code = Plant_ctr_14.GetCurSel();
			growplant(code, 3, 1);
			code = Plant_ctr_15.GetCurSel();
			growplant(code, 4, 1);

			code = Plant_ctr_21.GetCurSel();
			growplant(code, 0, 2);
			code = Plant_ctr_22.GetCurSel();
			growplant(code, 1, 2);
			code = Plant_ctr_23.GetCurSel();
			growplant(code, 2, 2);
			code = Plant_ctr_24.GetCurSel();
			growplant(code, 3, 2);
			code = Plant_ctr_25.GetCurSel();
			growplant(code, 4, 2);

			code = Plant_ctr_31.GetCurSel();
			growplant(code, 0, 3);
			code = Plant_ctr_32.GetCurSel();
			growplant(code, 1, 3);
			code = Plant_ctr_33.GetCurSel();
			growplant(code, 2, 3);
			code = Plant_ctr_34.GetCurSel();
			growplant(code, 3, 3);
			code = Plant_ctr_35.GetCurSel();
			growplant(code, 4, 3);

			code = Plant_ctr_41.GetCurSel();
			growplant(code, 0, 4);
			code = Plant_ctr_42.GetCurSel();
			growplant(code, 1, 4);
			code = Plant_ctr_43.GetCurSel();
			growplant(code, 2, 4);
			code = Plant_ctr_44.GetCurSel();
			growplant(code, 3, 4);
			code = Plant_ctr_45.GetCurSel();
			growplant(code, 4, 4);

			code = Plant_ctr_51.GetCurSel();
			growplant(code, 0, 5);
			code = Plant_ctr_52.GetCurSel();
			growplant(code, 1, 5);
			code = Plant_ctr_53.GetCurSel();
			growplant(code, 2, 5);
			code = Plant_ctr_54.GetCurSel();
			growplant(code, 3, 5);
			code = Plant_ctr_55.GetCurSel();
			growplant(code, 4, 5);

			code = Plant_ctr_61.GetCurSel();
			growplant(code, 0, 6);
			code = Plant_ctr_62.GetCurSel();
			growplant(code, 1, 6);
			code = Plant_ctr_63.GetCurSel();
			growplant(code, 2, 6);
			code = Plant_ctr_64.GetCurSel();
			growplant(code, 3, 6);
			code = Plant_ctr_65.GetCurSel();
			growplant(code, 4, 6);

			code = Plant_ctr_71.GetCurSel();
			growplant(code, 0, 7);
			code = Plant_ctr_72.GetCurSel();
			growplant(code, 1, 7);
			code = Plant_ctr_73.GetCurSel();
			growplant(code, 2, 7);
			code = Plant_ctr_74.GetCurSel();
			growplant(code, 3, 7);
			code = Plant_ctr_75.GetCurSel();
			growplant(code, 4, 7);

			code = Plant_ctr_81.GetCurSel();
			growplant(code, 0, 8);
			code = Plant_ctr_82.GetCurSel();
			growplant(code, 1, 8);
			code = Plant_ctr_83.GetCurSel();
			growplant(code, 2, 8);
			code = Plant_ctr_84.GetCurSel();
			growplant(code, 3, 8);
			code = Plant_ctr_85.GetCurSel();
			growplant(code, 4, 8);


		}
		else {
			MessageBox(L"未进入关卡！");
		}
	}
	else {
		MessageBox(L"游戏未运行！");
	}
}

void CpzhelperDlg::growplant(byte x, byte y, byte id)
{
	DWORD moduleBase, fun_param;
	// 读取种植基址
	moduleBase = this->m_base_address;
	readMemery(this->m_game_handle, moduleBase + 0x3794F8, fun_param);
	readMemery(this->m_game_handle, fun_param + 0x868, fun_param);

	byte* param_b = (byte*)&fun_param;

	byte head_1 = *param_b;
	byte head_2 = *(param_b + 1);
	byte head_3 = *(param_b + 2);
	byte head_4 = *(param_b + 3);

	std::vector<byte> funData;

	funData.push_back(0x60);
	funData.push_back(0x68);
	funData.push_back(0xFF);
	funData.push_back(0xFF);
	funData.push_back(0xFF);
	funData.push_back(0xFF);
	funData.push_back(0x6A);
	funData.push_back(x); // 坐标Y
	funData.push_back(0x6A);
	funData.push_back(id); // 植物ID
	funData.push_back(0xB8);
	funData.push_back(y); // 坐标X
	funData.push_back(0x00);
	funData.push_back(0x00);
	funData.push_back(0x00);
	funData.push_back(0x68);

	// 种植基址
	funData.push_back(head_1);
	funData.push_back(head_2);
	funData.push_back(head_3);
	funData.push_back(head_4);

	funData.push_back(0xBB);
	funData.push_back(0x10);
	funData.push_back(0x26);
	funData.push_back(0x42);
	funData.push_back(0x00);
	funData.push_back(0xFF);
	funData.push_back(0xD3);
	funData.push_back(0x61);
	funData.push_back(0xC3);

	size_t funSize = (size_t)funData.size();

	byte* ThreadFunc = new byte[funSize];
	for (size_t i = 0; i < funSize; i++)
	{
		ThreadFunc[i] = funData[i];
	}

	void* funAddr = VirtualAllocEx(this->m_game_handle, NULL, funSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (funAddr != NULL)
	{
		if (WriteProcessMemory(this->m_game_handle, funAddr, ThreadFunc, funSize, NULL) == 0) {
			MessageBox(L"写入内存失败！");
			return;
		}

		HANDLE thread_handle = CreateRemoteThread(this->m_game_handle, NULL, 0, (LPTHREAD_START_ROUTINE)funAddr, NULL, 0, NULL);
		Sleep(500);
		if (thread_handle == NULL)
		{
			MessageBox(L"创建线程失败！");
			return;
		}

		VirtualFreeEx(this->m_game_handle, funAddr, 0, MEM_RELEASE);
	}
	delete[] ThreadFunc;
	funData.clear();
}
