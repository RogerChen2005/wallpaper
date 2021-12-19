// CinputDlg.cpp: 实现文件
//

#include "pch.h"
#include "wlppegnui.h"
#include "CinputDlg.h"
#include "afxdialogex.h"


// CinputDlg 对话框

IMPLEMENT_DYNAMIC(CinputDlg, CDialogEx)

CinputDlg::CinputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT, pParent)
	, m_input(_T(""))
{

}

CinputDlg::~CinputDlg()
{
}

void CinputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_input);
}


BEGIN_MESSAGE_MAP(CinputDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CinputDlg::OnSelect)
END_MESSAGE_MAP()


// CinputDlg 消息处理程序


void CinputDlg::OnSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, _T("FFpaly.exe"), NULL, OFN_HIDEREADONLY, _T("Program|*.exe| All Files (*.*)|*.*||"), this);
	if (dlg.DoModal() == IDOK) {
		m_input = dlg.GetPathName();
	}
	UpdateData(FALSE);
}
