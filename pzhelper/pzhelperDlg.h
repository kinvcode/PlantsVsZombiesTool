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
	HANDLE m_game_handle; // 游戏进程句柄
	DWORD m_base_address; // 入口地址

	virtual void OnOK();
	afx_msg void OnBnClickedSunUpdate(); // 修改阳光按钮事件
	afx_msg void OnBnClickedsunlock(); // 锁定阳光事件
	CEdit m_sun_number; // 阳光数值控件
	CButton m_ctr_sun_modify; //修改阳光按钮控件
	CButton m_sun_lock; // 锁定阳光控件
};
