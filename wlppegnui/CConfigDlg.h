#pragma once

#include "wlppegnuiDlg.h"
// CConfigDlg 对话框

class CConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CConfigDlg();
	void getConfig(conFig &config);
	void setConfig(conFig &config);
	conFig digConfig;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS };
#endif
private:
	CString location;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_cmd;
	CString m_configname;
	CButton m_full;
	CButton m_mute;
	CString m_videopath;
//	CString m_command;
	afx_msg void OnFilechoose();
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	CString m_Command;
};
