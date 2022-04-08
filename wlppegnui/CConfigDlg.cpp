// CConfigDlg.cpp: 实现文件
//

#include "pch.h"
#include "wlppegnui.h"
#include "CConfigDlg.h"
#include "afxdialogex.h"


// CConfigDlg 对话框

IMPLEMENT_DYNAMIC(CConfigDlg, CDialogEx)

CConfigDlg::CConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTINGS, pParent)
	, m_configname(_T(""))
	, m_videopath(_T(""))
	, m_Command(_T(""))
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::getConfig(conFig& config)
{
	UpdateData(TRUE);
	config.location = location;
	config.name = m_configname;
	config.Cmd = m_Command;
	config.mute = m_mute.GetCheck();
	config.full = m_full.GetCheck();
	config.path = m_videopath;
	UpdateData(FALSE);
}

void CConfigDlg::setConfig(conFig &config)
{
	location = config.location;
	m_configname = config.name;
	m_full.SetCheck(config.full);
	m_mute.SetCheck(config.mute);
	m_videopath = config.path;
	m_Command = config.Cmd;
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CONFIGNAME, m_configname);
	DDX_Text(pDX, IDC_VIDEOPATH, m_videopath);
	DDX_Control(pDX, IDC_FULL, m_full);
	DDX_Control(pDX, IDC_MUTE, m_mute);
	DDX_Text(pDX, IDC_COMMAND, m_Command);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDC_FILECHOOSE, &CConfigDlg::OnFilechoose)
	ON_BN_CLICKED(IDOK, &CConfigDlg::OnOK)
END_MESSAGE_MAP()


// CConfigDlg 消息处理程序


void CConfigDlg::OnFilechoose()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, _T("Video Files"), NULL, OFN_HIDEREADONLY, _T("Video Files|*.avi;*.mp4;*.flv;*mkv| All Files (*.*)|*.*||"), this);
	if (dlg.DoModal() == IDOK) {
		m_videopath = dlg.GetPathName();
	}
	UpdateData(FALSE);
}


BOOL CConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);
	setConfig(digConfig);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CConfigDlg::OnOK()
{
	// TODO: 在此添加控件通知处理程序代码
	getConfig(digConfig);
	CDialogEx::OnOK();
}
