#pragma once


// CinputDlg 对话框

class CinputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CinputDlg)

public:
	CinputDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CinputDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_input;
	afx_msg void OnSelect();
};
