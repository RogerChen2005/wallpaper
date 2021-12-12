
// wlppegnuiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "wlppegnui.h"
#include "wlppegnuiDlg.h"
#include "afxdialogex.h"
#include "vector"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CwlppegnuiDlg 对话框



CwlppegnuiDlg::CwlppegnuiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WLPPEGNUI_DIALOG, pParent)
	, pathShow(_T(""))
	, cmdShow(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwlppegnuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIG, m_config);
	DDX_Control(pDX, IDC_MUTE, m_mute);
	DDX_Text(pDX, IDC_PATH2, pathShow);
	DDX_Text(pDX, IDC_PATH, cmdShow);
}

BEGIN_MESSAGE_MAP(CwlppegnuiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE, &CwlppegnuiDlg::OnSave)
	ON_BN_CLICKED(IDC_NEW, &CwlppegnuiDlg::OnNew)
	ON_LBN_DBLCLK(IDC_CONFIG, &CwlppegnuiDlg::OnDblclkConfig)
//	ON_LBN_SETFOCUS(IDC_CONFIG, &CwlppegnuiDlg::OnSetfocusConfig)
	ON_BN_CLICKED(IDC_APPLY, &CwlppegnuiDlg::OnApply)
	ON_LBN_SELCHANGE(IDC_CONFIG, &CwlppegnuiDlg::OnSelchangeConfig)
END_MESSAGE_MAP()

void CwlppegnuiDlg::readConfig(CString pathname) {
	conFig temp;
	TCHAR szValue[MAX_PATH + 1] = _T("");
	GetPrivateProfileString(_T("Settings"), _T("name"), _T("Config"), szValue, MAX_PATH, pathname); temp.name = szValue;
	GetPrivateProfileString(_T("Path"), _T("path"), _T("None"), szValue, MAX_PATH, pathname); temp.path = szValue;
	int check = GetPrivateProfileInt(_T("Settings"), _T("mute"), 0, pathname);check == 0 ? temp.mute = false : temp.mute = true;
	GetPrivateProfileString(_T("Extra"), _T("Cmd"), _T("None"), szValue, MAX_PATH, pathname); temp.Cmd = szValue;
	configs.push_back(temp);
}


// CwlppegnuiDlg 消息处理程序

BOOL CwlppegnuiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	path = "H:\\code\\package\\wlppegnui";
	int cnt = 1;
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用
	BOOL ifFind = finder.FindFile(path + "\\configs\\*.ini");
	CString configPath;
	while (ifFind){
		ifFind = finder.FindNextFile();
		if(finder.IsDots()) continue;
		if (!finder.IsDirectory()) {
			configPath = finder.GetFilePath();
			readConfig(configPath);
		}
		else continue;
	}
	int Size = configs.size();
	for (int i = 0; i < Size;i++){
		m_config.InsertString(i,configs[i].name);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CwlppegnuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CwlppegnuiDlg::OnPaint()
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
HCURSOR CwlppegnuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CwlppegnuiDlg::OnSave()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CwlppegnuiDlg::OnNew()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CwlppegnuiDlg::OnDblclkConfig()
{
	// TODO: 在此添加控件通知处理程序代码
}


//void CwlppegnuiDlg::OnSetfocusConfig()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CwlppegnuiDlg::OnApply()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CwlppegnuiDlg::OnSelchangeConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_config.GetCurSel();
	UpdateData(TRUE);
	pathShow = configs[index].path;
	m_mute.SetCheck(configs[index].mute);
	cmdShow = configs[index].Cmd;
	UpdateData(FALSE);
}
