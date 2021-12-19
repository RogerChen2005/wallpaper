﻿
// wlppegnuiDlg.h: 头文件
//

#pragma once
#include "vector"

struct conFig {
	//title
	CString name;
    //video path
	CString path;
	//setting
	bool mute = false;
	//extra
	CString Cmd;
	//inifile path
	CString location;
};

// CwlppegnuiDlg 对话框
class CwlppegnuiDlg : public CDialogEx
{
// 构造
public:
	CwlppegnuiDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CString path;
	std::vector<conFig> configs;
	void readConfig(CString pathname);
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
	afx_msg LRESULT OnNotifyMsg(WPARAM wparam, LPARAM lparam);
	afx_msg void OnNew();
	afx_msg void OnDblclkConfig();
//	afx_msg void OnSetfocusConfig();
	afx_msg void OnApply();
	afx_msg void OnSelchangeConfig();
	CString pathShow;
	CString cmdShow;
	afx_msg void OnClose();
	afx_msg void OnSetfocusConfig();
//	CString m_Edit;
	CEdit m_edit;
	afx_msg void OnKillfocusEditt();
	afx_msg void OnFile();
	afx_msg void OnClickedDel();
private:
	NOTIFYICONDATA m_notify;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnAboutD();
};
