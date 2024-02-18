#pragma once

// CpzhelperDlg 对话框
class CpzhelperDlg : public CDialogEx
{
// 构造
public:
	CpzhelperDlg(CWnd* pParent = nullptr);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PZHELPER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_game_status;	// 游戏运行状态[文字]
	int m_status_int; // 游戏运行状态【数字】
	int m_game_pid; // 游戏PID
	int m_in_dungeon; // 是否在关卡中
	BOOL m_sun_locked; // 阳光锁定状态
	BOOL m_plants_cool_down; // 植物冷却
	HANDLE m_game_handle; // 游戏进程句柄
	DWORD m_base_address; // 入口地址

	virtual void OnOK();
	afx_msg void OnBnClickedSunUpdate(); // 修改阳光按钮事件
	afx_msg void OnBnClickedsunlock(); // 锁定阳光事件
	CEdit m_sun_number; // 阳光数值控件
	CButton m_ctr_sun_modify; //修改阳光按钮控件
	CButton m_sun_lock; // 锁定阳光控件
	afx_msg void OnBnClickedCheckCoolDown();
	CButton m_check_plants_cd;
	CStatic m_dungeon_status;
	afx_msg void OnBnClickedButton1();
	CComboBox Plant_ctr_01;
	CComboBox Plant_ctr_02;
	CComboBox Plant_ctr_03;
	CComboBox Plant_ctr_04;
	CComboBox Plant_ctr_05;
	CComboBox Plant_ctr_11;
	CComboBox Plant_ctr_12;
	CComboBox Plant_ctr_13;
	CComboBox Plant_ctr_14;
	CComboBox Plant_ctr_15;
	CComboBox Plant_ctr_21;
	CComboBox Plant_ctr_22;
	CComboBox Plant_ctr_23;
	CComboBox Plant_ctr_24;
	CComboBox Plant_ctr_25;

	// 种植植物
	void growplant(byte x, byte y, byte id);
	// 种植僵尸
	void growpZombie(byte x, byte y, byte id);
	CComboBox Plant_ctr_31;
	CComboBox Plant_ctr_32;
	CComboBox Plant_ctr_33;
	CComboBox Plant_ctr_34;
	CComboBox Plant_ctr_35;
	CComboBox Plant_ctr_41;
	CComboBox Plant_ctr_42;
	CComboBox Plant_ctr_43;
	CComboBox Plant_ctr_44;
	CComboBox Plant_ctr_45;
	CComboBox Plant_ctr_51;
	CComboBox Plant_ctr_52;
	CComboBox Plant_ctr_53;
	CComboBox Plant_ctr_54;
	CComboBox Plant_ctr_55;
	CComboBox Plant_ctr_61;
	CComboBox Plant_ctr_62;
	CComboBox Plant_ctr_63;
	CComboBox Plant_ctr_64;
	CComboBox Plant_ctr_65;
	CComboBox Plant_ctr_71;
	CComboBox Plant_ctr_72;
	CComboBox Plant_ctr_73;
	CComboBox Plant_ctr_74;
	CComboBox Plant_ctr_75;
	CComboBox Plant_ctr_81;
	CComboBox Plant_ctr_82;
	CComboBox Plant_ctr_83;
	CComboBox Plant_ctr_84;
	CComboBox Plant_ctr_85;
	afx_msg void OnBnClickedCheck1();
	CButton m_fire_seed;
	afx_msg void OnBnClickedButton2();
	CEdit m_gold_number;
	afx_msg void OnBnClickedCheck2();
	CButton m_super_speed;
	afx_msg void OnBnClickedCheck3();
	CButton m_auto_gather_sun;
	afx_msg void OnBnClickedButton4();
	CComboBox m_zombie_x;
	CComboBox m_zombie_y;
	CComboBox m_zombie_id;
	afx_msg void OnBnClickedCheck4();
	CButton m_skill_zombies;
	afx_msg void OnBnClickedCheck5();
	CButton m_back_run;
	CButton m_bullet_change;
	afx_msg void OnBnClickedCheck7();
};
