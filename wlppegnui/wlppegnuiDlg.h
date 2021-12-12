
// wlppegnuiDlg.h: 头文件
//

#pragma once


// CwlppegnuiDlg 对话框
class CwlppegnuiDlg : public CDialogEx
{
// 构造
public:
	CwlppegnuiDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WLPPEGNUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_config;
	CButton m_mute;
	afx_msg void OnSave();
	afx_msg void OnNew();
	afx_msg void OnDblclkConfig();
	afx_msg void OnSetfocusConfig();
	afx_msg void OnApply();
};
