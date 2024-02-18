
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

std::vector<byte> makeByteArray(std::vector<byte> data)
{
	return data;
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
	DDX_Control(pDX, IDC_CHECK1, m_fire_seed);
	DDX_Control(pDX, IDC_EDIT1, m_gold_number);
	DDX_Control(pDX, IDC_CHECK2, m_super_speed);
	DDX_Control(pDX, IDC_CHECK3, m_auto_gather_sun);
	DDX_Control(pDX, IDC_COMBO57, m_zombie_x);
	DDX_Control(pDX, IDC_COMBO58, m_zombie_y);
	DDX_Control(pDX, IDC_COMBO59, m_zombie_id);
	DDX_Control(pDX, IDC_CHECK4, m_skill_zombies);
	DDX_Control(pDX, IDC_CHECK5, m_back_run);
	DDX_Control(pDX, IDC_CHECK7, m_bullet_change);
}

// 消息映射
BEGIN_MESSAGE_MAP(CpzhelperDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SUN_UPDATE, &CpzhelperDlg::OnBnClickedSunUpdate)
	ON_BN_CLICKED(IDC_sun_lock, &CpzhelperDlg::OnBnClickedsunlock)
	ON_BN_CLICKED(IDC_CHECK_COOL_DOWN, &CpzhelperDlg::OnBnClickedCheckCoolDown)
	ON_BN_CLICKED(IDC_BUTTON1, &CpzhelperDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CpzhelperDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CpzhelperDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK2, &CpzhelperDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CpzhelperDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON4, &CpzhelperDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK4, &CpzhelperDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CpzhelperDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK7, &CpzhelperDlg::OnBnClickedCheck7)
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
		plantsBox[i]->InsertString(4, L"土豆地雷");
		plantsBox[i]->InsertString(5, L"寒冰射手");
		plantsBox[i]->InsertString(6, L"大嘴花");
		plantsBox[i]->InsertString(7, L"双重射手");
		plantsBox[i]->InsertString(8, L"小喷菇");
		plantsBox[i]->InsertString(9, L"阳光菇");
		plantsBox[i]->InsertString(10, L"大喷菇");
		plantsBox[i]->InsertString(11, L"咬咬碑");
		plantsBox[i]->InsertString(12, L"迷惑菇");
		plantsBox[i]->InsertString(13, L"胆小菇");
		plantsBox[i]->InsertString(14, L"冰川菇");
		plantsBox[i]->InsertString(15, L"末日菇");
		plantsBox[i]->InsertString(16, L"莲叶");
		plantsBox[i]->InsertString(17, L"窝瓜");
		plantsBox[i]->InsertString(18, L"三重射手");
		plantsBox[i]->InsertString(19, L"缠绕水草");
		plantsBox[i]->InsertString(20, L"火爆辣椒");
		plantsBox[i]->InsertString(21, L"地刺");
		plantsBox[i]->InsertString(22, L"火炬树桩");
		plantsBox[i]->InsertString(23, L"高坚果");
		plantsBox[i]->InsertString(24, L"水兵菇");
		plantsBox[i]->InsertString(25, L"路灯花");
		plantsBox[i]->InsertString(26, L"仙人掌");
		plantsBox[i]->InsertString(27, L"三叶草");
		plantsBox[i]->InsertString(28, L"双向射手");
		plantsBox[i]->InsertString(29, L"星星果");
		plantsBox[i]->InsertString(30, L"南瓜头");
		plantsBox[i]->InsertString(31, L"磁力菇");
		plantsBox[i]->InsertString(32, L"卷心菜投手");
		plantsBox[i]->InsertString(33, L"花盆");
		plantsBox[i]->InsertString(34, L"玉米投手");
		plantsBox[i]->InsertString(35, L"咖啡豆");
		plantsBox[i]->InsertString(36, L"大蒜");
		plantsBox[i]->InsertString(37, L"萝卜伞");
		plantsBox[i]->InsertString(38, L"金盏花");
		plantsBox[i]->InsertString(39, L"西瓜投手");
		plantsBox[i]->InsertString(40, L"机枪射手");
		plantsBox[i]->InsertString(41, L"双胞向日葵");
		plantsBox[i]->InsertString(42, L"多嘴小蘑菇");
		plantsBox[i]->InsertString(43, L"猫尾草");
		plantsBox[i]->InsertString(44, L"冰西瓜");
		plantsBox[i]->InsertString(45, L"吸金菇");
		plantsBox[i]->InsertString(46, L"钢地刺");
		plantsBox[i]->InsertString(47, L"玉米加农炮");
		if (i < 5)
		{
			plantsBox[i]->SetCurSel(1);
		}
		else {
			plantsBox[i]->SetCurSel(0);
		}
	}

	// 僵尸种植控件初始化
	m_zombie_x.InsertString(0, L"第一行");
	m_zombie_x.InsertString(1, L"第二行");
	m_zombie_x.InsertString(2, L"第三行");
	m_zombie_x.InsertString(3, L"第四行");
	m_zombie_x.InsertString(4, L"第五行");

	m_zombie_y.InsertString(0, L"第一列");
	m_zombie_y.InsertString(1, L"第二列");
	m_zombie_y.InsertString(2, L"第三列");
	m_zombie_y.InsertString(3, L"第四列");
	m_zombie_y.InsertString(4, L"第五列");
	m_zombie_y.InsertString(5, L"第六列");
	m_zombie_y.InsertString(6, L"第七列");
	m_zombie_y.InsertString(7, L"第八列");
	m_zombie_y.InsertString(8, L"第九列");

	m_zombie_id.InsertString(0, L"普通僵尸");
	m_zombie_id.InsertString(1, L"旗帜僵尸");
	m_zombie_id.InsertString(2, L"路障僵尸");
	m_zombie_id.InsertString(3, L"撑杆僵尸");
	m_zombie_id.InsertString(4, L"铁桶僵尸");
	m_zombie_id.InsertString(5, L"读报僵尸");
	m_zombie_id.InsertString(6, L"铁网门僵尸");
	m_zombie_id.InsertString(7, L"橄榄球僵尸");
	m_zombie_id.InsertString(8, L"舞者僵尸");
	m_zombie_id.InsertString(9, L"伴舞僵尸");
	m_zombie_id.InsertString(10, L"救生圈僵尸");
	m_zombie_id.InsertString(11, L"潜水僵尸");
	m_zombie_id.InsertString(12, L"雪橇车僵尸");
	m_zombie_id.InsertString(13, L"雪橇车僵尸小队");
	m_zombie_id.InsertString(14, L"海豚僵尸");
	m_zombie_id.InsertString(15, L"小丑僵尸");
	m_zombie_id.InsertString(16, L"气球僵尸");
	m_zombie_id.InsertString(17, L"旷工僵尸");
	m_zombie_id.InsertString(18, L"蹦蹦僵尸");
	m_zombie_id.InsertString(19, L"未知僵尸");
	m_zombie_id.InsertString(20, L"飞贼僵尸");
	m_zombie_id.InsertString(21, L"梯子僵尸");
	m_zombie_id.InsertString(22, L"投石车僵尸");
	m_zombie_id.InsertString(23, L"巨人僵尸");
	m_zombie_id.InsertString(24, L"小鬼僵尸");

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
	/* 种植CALL原型
	004265BE  |.  8B4424 14     mov eax,dword ptr ss:[esp+0x14]          ;  Y轴
	004265C2  |.  51            push ecx                                 ;  固定-1
	004265C3  |.  52            push edx                                 ;  植物ID
	004265C4  |.  53            push ebx                                 ;  X轴
	004265C5  |.  57            push edi                                 ;  种植基址
	004265C6  |.  E8 45C0FFFF   call PlantsVs.00422610                   ;  植物种植CALL
	*/


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


void CpzhelperDlg::OnBnClickedCheck1()
{
	// 开启子弹射速
	bool seed_on = m_fire_seed.GetCheck();
	if (seed_on)
	{
		rapidFire(this, true);
	}
	else {
		rapidFire(this, false);
	}

}


void CpzhelperDlg::OnBnClickedButton2()
{
	// 修改金币数量
	// TODO: 在此添加控件通知处理程序代码


	if (this->m_status_int)
	{
		CString numeric;
		m_gold_number.GetWindowTextW(numeric);
		int number = _ttoi(numeric);
		if (number < 0 || number > 999999)
		{
			MessageBox(L"数值范围：0~99999");
		}
		else {
			goldUpdate(this, number);
		}

	}
	else {
		MessageBox(L"游戏未运行！");
	}
}


void CpzhelperDlg::OnBnClickedCheck2()
{
	// TODO: 开启超级投手
	bool seed_on = m_super_speed.GetCheck();
	if (seed_on)
	{
		superFire(this, true);
	}
	else {
		superFire(this, false);
	}
}


void CpzhelperDlg::OnBnClickedCheck3()
{
	// 自动收集阳光
	bool auto_on = m_auto_gather_sun.GetCheck();
	if (auto_on)
	{
		autoGatherSun(this, true);
	}
	else {
		autoGatherSun(this, false);
	}
}

// 种植僵尸
void CpzhelperDlg::growpZombie(byte x, byte y, byte id)
{
	/* 种植僵尸原型
	00444B2E | 8B4C24 58                | mov ecx,dword ptr ss:[esp+58]           | X轴
	00444B32 | 50                       | push eax                                | 僵尸ID
	00444B33 | 8B4424 60                | mov eax,dword ptr ss:[esp+60]           | Y轴
	00444B37 | 55                       | push ebp                                | 种植基址
	00444B38 | E8 23FDFFFF              | call plantsvszombies.444860             | 僵尸CALL
	*/

	std::vector<byte> asmData = { 0x60 }; // pushad
	asmData = asmData + makeByteArray({ 0x8B, 0x05, 0xF8, 0x94, 0x77, 0x0 }); // mov eax,[7794F8]
	asmData = asmData + makeByteArray({ 0x8B, 0x80, 0x68, 0x08, 0x0, 0x0 }); // mov eax,[eax+00000868]
	asmData = asmData + makeByteArray({ 0x8B, 0x80, 0x78, 0x01, 0x0, 0x0 }); // mov eax, [eax + 00000178]
	asmData = asmData + makeByteArray({ 0x8B, 0xE8 }); // mov ebp,eax
	asmData = asmData + makeByteArray({ 0xB9, y, 0x0, 0x0, 0x0 }); // mov ecx,00000000
	asmData = asmData + makeByteArray({ 0x6A, id }); // push 0A
	asmData = asmData + makeByteArray({ 0xB8, x, 0x0, 0x0, 0x0 }); // mov eax,00000000
	asmData = asmData + makeByteArray({ 0x55 }); // push ebp
	asmData = asmData + makeByteArray({ 0xBB, 0x60, 0x48, 0x44, 0x00 }); // mov ebx,444860
	asmData = asmData + makeByteArray({ 0xFF,0xD3 }); // call ebx
	asmData = asmData + makeByteArray({ 0x61 }); // popad
	asmData = asmData + makeByteArray({ 0xC3 }); // ret

	// 汇编字节数量
	size_t funSize = (size_t)asmData.size();

	// 创建字节数组，并将机器码转移到字节数组中
	byte* ThreadFunc = new byte[funSize];
	for (size_t i = 0; i < funSize; i++)
	{
		ThreadFunc[i] = asmData[i];
	}

	// 远程申请内存空间
	void* funAddr = VirtualAllocEx(this->m_game_handle, NULL, funSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (funAddr != NULL)
	{
		// 远程写入机器码
		if (WriteProcessMemory(this->m_game_handle, funAddr, ThreadFunc, funSize, NULL) == 0) {
			MessageBox(L"写入内存失败！");
			return;
		}

		// 创建远程线程
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
	asmData.clear();
}


void CpzhelperDlg::OnBnClickedButton4()
{
	// 僵尸种植
	int x, y, code;
	x = m_zombie_x.GetCurSel();
	y = m_zombie_y.GetCurSel();
	code = m_zombie_id.GetCurSel();

	if (x < 0 || x > 4) {
		MessageBox(L"无效的行数！");
		return;
	}

	if (y < 0 || y > 8) {
		MessageBox(L"无效的列数！");
		return;
	}

	if (code < 0 || code > 24) {
		MessageBox(L"无效的僵尸ID！");
		return;
	}

	growpZombie(x, y, code);
}


void CpzhelperDlg::OnBnClickedCheck4()
{
	// 僵尸秒杀
	bool skill_on = m_skill_zombies.GetCheck();
	if (skill_on)
	{
		skillZombies(this, true);
	}
	else {
		skillZombies(this, false);
	}
}


void CpzhelperDlg::OnBnClickedCheck5()
{
	// 后台运行
	bool back_on = m_back_run.GetCheck();
	if (back_on) {
		backgroundRunning(this, true);
	}
	else {
		backgroundRunning(this, false);
	}
}


void CpzhelperDlg::OnBnClickedCheck7()
{
	// 子弹修改
	bool bullet_on = m_bullet_change.GetCheck();
	if (bullet_on) {
		changebullet(this, true, 0xb);
	}
	else {
		changebullet(this, false, 0xb);
	}
}
