
// wlppegnuiDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "wlppegnui.h"
#include "wlppegnuiDlg.h"
#include "afxdialogex.h"
#include "vector"
#include "CinputDlg.h"
#include "CConfigDlg.h"

#define WM_USER_NOTIFYICON WM_USER+1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND hFfplay = NULL;

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
public:
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

LRESULT  CwlppegnuiDlg::OnNotifyMsg(WPARAM wparam, LPARAM lparam)
//wParam接收的是图标的ID，而lParam接收的是鼠标的行为   
{
	if (wparam != IDR_MAINFRAME)
		return    1;
	switch (lparam)
	{
	case  WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”   
	{
		LPPOINT    lpoint = new    tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置   
		CMenu    menu;
		menu.CreatePopupMenu();//声明一个弹出式菜单   
		//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已   
		//隐藏），将程序结束。   
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭"));
		//确定弹出式菜单的位置   
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		//资源回收   
		HMENU    hmenu = menu.Detach();
		menu.DestroyMenu();
		delete    lpoint;
	}
	break;
	case    WM_LBUTTONDBLCLK://双击左键的处理   
	{
		this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿   
	}
	break;
	}
	return 0;
}


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
	//  DDX_Text(pDX, IDC_EDITT, m_Edit);
	DDX_Control(pDX, IDC_FULL, fulFill);
}

BEGIN_MESSAGE_MAP(CwlppegnuiDlg, CDialogEx)
	ON_MESSAGE(WM_USER_NOTIFYICON, OnNotifyMsg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NEW, &CwlppegnuiDlg::OnNew)
	ON_LBN_DBLCLK(IDC_CONFIG, &CwlppegnuiDlg::OnDblclkConfig)
//	ON_LBN_SETFOCUS(IDC_CONFIG, &CwlppegnuiDlg::OnSetfocusConfig)
	ON_BN_CLICKED(IDC_APPLY, &CwlppegnuiDlg::OnApply)
	ON_LBN_SELCHANGE(IDC_CONFIG, &CwlppegnuiDlg::OnSelchangeConfig)
	ON_WM_CLOSE()
	ON_LBN_SETFOCUS(IDC_CONFIG, &CwlppegnuiDlg::OnSetfocusConfig)
	ON_BN_CLICKED(IDC_FILECHOOSE, &CwlppegnuiDlg::OnFile)
	ON_BN_CLICKED(IDC_DEL, &CwlppegnuiDlg::OnClickedDel)
	ON_COMMAND(ID_32773, &CwlppegnuiDlg::OnAboutD)
	ON_COMMAND(ID_32772, &CwlppegnuiDlg::OnExitProc)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_32771, &CwlppegnuiDlg::OnSetPath)
	ON_COMMAND(ID_32774, &CwlppegnuiDlg::OnPause)
END_MESSAGE_MAP()

void CwlppegnuiDlg::readConfig(CString pathname) {
	conFig temp;
	temp.location = pathname;
	TCHAR szValue[MAX_PATH + 1] = _T("");
	GetPrivateProfileString(_T("Settings"), _T("name"), _T("Config"), szValue, MAX_PATH, pathname); temp.name = szValue;
	GetPrivateProfileString(_T("Path"), _T("path"), _T("None"), szValue, MAX_PATH, pathname); temp.path = szValue;
	int check = GetPrivateProfileInt(_T("Settings"), _T("mute"), 0, pathname);check == 0 ? temp.mute = false : temp.mute = true;
	check = GetPrivateProfileInt(_T("Settings"), _T("full"), 0, pathname); check == 0 ? temp.full = false : temp.full = true;
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
	UpdateData(TRUE);
 	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	path = path.Left(path.ReverseFind('\\'));
	CFileFind pathFinder;
	bool ifCus = pathFinder.FindFile(path + "\\settings\\ffpath.ini");
	if (ifCus) {
		ifCus = pathFinder.FindNextFileW();
		TCHAR szValue[MAX_PATH + 1] = _T("");
		GetPrivateProfileString(_T("path"), _T("location"),_T(""), szValue, MAX_PATH, pathFinder.GetFilePath());
		ffpath = szValue;
		if (ffpath.IsEmpty()) {
			ffpath = path + _T("\\ffplay\\bin\\ffplay.exe");
		}
	}
	else { ffpath = path + _T("\\ffplay\\bin\\ffplay.exe"); }
	int cnt = 1;
	CFileFind finder;
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
	if (configs.size()>0) {
		m_config.SetCurSel(0);
		pathShow = configs[0].path;
		m_mute.SetCheck(configs[0].mute);
		fulFill.SetCheck(configs[0].full);
		cmdShow = configs[0].Cmd;
	}
	m_notify.cbSize = sizeof(NOTIFYICONDATA);
	m_notify.hWnd = this->m_hWnd;
	m_notify.uID = IDR_MAINFRAME;
	m_notify.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_notify.szTip, L"Video Wallpaper");
	m_notify.uCallbackMessage = WM_USER_NOTIFYICON;
	m_notify.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_notify);
	UpdateData(FALSE);
	return true;
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
		//CPaintDC dc(this);
		//CRect rect;
		//GetClientRect(rect);
		//dc.FillSolidRect(rect, RGB(252, 252, 252));
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CwlppegnuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CwlppegnuiDlg::OnSave()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	int index = m_config.GetCurSel();
//	if (index >= configs.size()) return;
//	UpdateData(TRUE);
//	configs[index].Cmd = cmdShow;
//	configs[index].path = pathShow;
//	configs[index].mute = m_mute.GetCheck();
//	WritePrivateProfileString(_T("Path"), _T("path"), pathShow, configs[index].location);
//	CString tempInt; tempInt.Format(_T("%d"), m_mute.GetCheck());
//	WritePrivateProfileString(_T("Settings"), _T("mute"), tempInt, configs[index].location);
//	tempInt.Format(_T("%d"), fulFill.GetCheck());
//	WritePrivateProfileString(_T("Settings"), _T("full"), tempInt, configs[index].location);
//	WritePrivateProfileString(_T("Extra"), _T("Cmd"), cmdShow, configs[index].location);
//	UpdateData(FALSE);
//}

void saveConfig(conFig& config)
{
	WritePrivateProfileString(_T("Path"), _T("path"), config.path, config.location);
	CString tempInt; tempInt.Format(_T("%d"), config.mute);
	WritePrivateProfileString(_T("Settings"), _T("mute"), tempInt, config.location);
	tempInt.Format(_T("%d"), config.full);
	WritePrivateProfileString(_T("Settings"), _T("full"), tempInt, config.location);
	WritePrivateProfileString(_T("Extra"), _T("Cmd"), config.Cmd, config.location);
	WritePrivateProfileString(_T("Settings"), _T("name"), config.name, config.location);
}

void CwlppegnuiDlg::OnNew()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime time;
	time = CTime::GetCurrentTime();
	CString tempInt = time.Format(_T("%Y-%m-%d-%H-%M-%S"));
	int index = configs.size();
	CString tempPath = path + "\\configs\\";
	tempPath += tempInt + _T(".ini");
	conFig temp;
	temp.location = tempPath;
	CFileFind finder;
	BOOL ifFind = finder.FindFile(tempPath);
	if (!ifFind){
		/*WritePrivateProfileString(_T("Settings"), _T("name"), configs[index].name, configs[index].location);
		WritePrivateProfileString(_T("Path"), _T("path"), configs[index].path, configs[index].location);
		tempInt.Format(_T("%d"), configs[index].mute);
		WritePrivateProfileString(_T("Settings"), _T("mute"), tempInt, configs[index].location);
		tempInt.Format(_T("%d"), configs[index].full);
		WritePrivateProfileString(_T("Settings"), _T("full"), tempInt, configs[index].location);
		WritePrivateProfileString(_T("Extra"), _T("Cmd"), configs[index].Cmd, configs[index].location);*/
		CConfigDlg m_Dlg;
		m_Dlg.digConfig.location = temp.location;
		m_Dlg.DoModal();
		temp = m_Dlg.digConfig;
		configs.push_back(temp);
		saveConfig(configs[index]);
		m_config.InsertString(index,configs[index].name);
		m_config.SetCurSel(index);
		refreshWindow(temp);
	}	
	/*UpdateData(TRUE);
	m_config.InsertString(index, configs[index].name);
	m_config.SetCurSel(index);
	pathShow = configs[index].path;
	m_mute.SetCheck(configs[index].mute);
	cmdShow = configs[index].Cmd;
	UpdateData(FALSE);*/
}


void CwlppegnuiDlg::OnDblclkConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	//NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//CRect rc;
	//m_config.GetItemRect(m_config.GetCurSel(),rc);
	//m_edit.SetParent(&m_config);//转换坐标为列表框中的坐标
	//m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
	//CString tempShow;
	//m_config.GetText(m_config.GetCurSel(), tempShow);
	//m_edit.SetWindowText(tempShow);//将该子项中的值放在Edit控件中；
	//m_edit.ShowWindow(SW_SHOW);//显示Edit控件；
	//m_edit.SetFocus();//设置Edit焦点
	//m_edit.ShowCaret();//显示光标
	//m_edit.SetSel(-1);//将光标移动到最后
	CConfigDlg m_cDlg;
	int index = m_config.GetCurSel();
	if (index >= configs.size()) return;
	m_cDlg.digConfig = configs[index];
	int ext = m_cDlg.DoModal();
	configs[index] = m_cDlg.digConfig;
	refreshWindow(configs[index]);
	m_config.DeleteString(index);
	m_config.InsertString(index,configs[index].name);
	m_config.SetCurSel(index);
	saveConfig(configs[index]);
}

BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam) {
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);
		return FALSE;
	}
	return TRUE;
}

void ShowW(LPCWSTR lpParameter,CString path,bool full, bool horw) {
	if (hFfplay!=NULL) {
		DWORD dwPID = 0;
		GetWindowThreadProcessId(hFfplay, &dwPID);
		char strCmd[MAX_PATH] = { 0 };
		sprintf_s(strCmd, "taskkill /pid %d -f", dwPID);
		system(strCmd);
	}
	STARTUPINFO si{ 0 };
	//si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	PROCESS_INFORMATION pi{ 0 };
	if (CreateProcess(path, (LPWSTR)lpParameter, 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &si, &pi)) {
		Sleep(500);//等待视频播放器启动完成
		HWND hProgman = FindWindow(L"Progman", 0);// 找到PI窗口
		SendMessageTimeout(hProgman, 0x052c, 0, 0, 0, 100, 0);// 给它发特殊消息
		hFfplay = FindWindow(L"SDL_app", 0);// 找到视频窗口
		SetParent(hFfplay, hProgman);// 将视频窗口设苦为PM的子窗口
		int swidth = GetSystemMetrics(0);
		int sheight = GetSystemMetrics(1);
		if (full) {
			RECT cRct;
			GetWindowRect(hFfplay, &cRct);
			if (horw) {
				int width = cRct.right - cRct.left;
				int x = (swidth - width) / 2;
				MoveWindow(hFfplay, x, 0,cRct.right - cRct.left,cRct.bottom - cRct.top,0);
			}
			else {
				int height = cRct.bottom - cRct.top;
				int x = (sheight - height) / 2;
				MoveWindow(hFfplay, 0, x,cRct.right - cRct.left,cRct.bottom - cRct.top, 0);
			}
		}
		else {
			MoveWindow(hFfplay, 0, 0, swidth, sheight, 0);
		}
		EnumWindows(EnumWindowsProc, 0);// 找到第二个workerw窗口并隐藏它
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void runProbe(CString path,CString pathShow) {
	CString temp2 = L"-v error -select_streams v:0 -show_entries stream=width,height -of default=nw=1 -print_format ini > \"" + path + L"\\ffplay\\bin\\temp.ini\" 2>&1 \"" + pathShow + L"\"";
	CString bpath = path + L"\\ffplay\\bin\\ffprobe.exe";
	CString strcmd = bpath + L" " + temp2; 
	USES_CONVERSION;
	char* strCmd = W2A(strcmd);
	system(strCmd);
}

void CwlppegnuiDlg::OnApply()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fcmd = _T(" \"");
	fcmd += pathShow + _T("\"");
	fcmd += _T(" -noborder -loop 0");
	if (m_mute.GetCheck()) {
		fcmd += _T(" -an");
	}
	bool bigger = false;
	if (fulFill.GetCheck()) {
		runProbe(path, pathShow);
		Sleep(50);
		int width = GetPrivateProfileInt(L"streams.stream.0", L"width", 0, path + L"\\ffplay\\bin\\temp.ini");
		int height = GetPrivateProfileInt(L"streams.stream.0", L"height", 0, path + L"\\ffplay\\bin\\temp.ini");
		bigger = (double(width) / height) > cRect.proPortion;
		if (bigger) {
			CString sHeight;
			sHeight.Format(L"%d", cRect.height);
			fcmd += L" -y " + sHeight;
		}
		else {
			CString sWidth;
			sWidth.Format(L"%d", cRect.width);
			fcmd += L" -x " + sWidth;
		}
	}
	else {
		fcmd += L" -fs";
	}
	LPCWSTR tempStr = fcmd;
	ShowW(tempStr,ffpath,fulFill.GetCheck(),bigger);
}


void CwlppegnuiDlg::OnSelchangeConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_config.GetCurSel();
	if (index >= configs.size()) return;
	refreshWindow(configs[index]);
}


void CwlppegnuiDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_HIDE);
}


void CwlppegnuiDlg::OnSetfocusConfig()
{
	// TODO: 在此添加控件通知处理程序代码
}


//void CwlppegnuiDlg::OnKillfocusEditt()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString tem;
//	m_edit.GetWindowText(tem); //得到用户输入的新的内容
//	int index = m_config.GetCurSel();
//	if (index >= configs.size()) return;
//	m_config.DeleteString(index);
//	CString str; m_edit.GetWindowTextW(str);
//	m_config.InsertString(index,str);
//	configs[index].name = str;
//	WritePrivateProfileString(_T("Settings"), _T("name"), str, configs[index].location);
//	m_edit.ShowWindow(SW_HIDE); //隐藏编辑框
//}


void CwlppegnuiDlg::OnFile()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog dlg(TRUE,_T("Video Files"),NULL,OFN_HIDEREADONLY,_T("Video Files|*.avi;*.mp4;*.flv;*mkv| All Files (*.*)|*.*||"),this);
	if (dlg.DoModal() == IDOK){
		pathShow = dlg.GetPathName();
	}
	UpdateData(FALSE);
}


void CwlppegnuiDlg::OnClickedDel()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_config.GetCurSel();
	if (index >= configs.size()) return;
	UpdateData(TRUE);
	cmdShow = "";
	pathShow = "";
	m_mute.SetCheck(0);
	m_config.DeleteString(index);
	m_config.SetCurSel(index-1);
	CFile delFile;
	delFile.Remove(configs[index].location);
	UpdateData(FALSE);
}


LRESULT CwlppegnuiDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (message) //判断消息类型
	{
	case WM_USER_NOTIFYICON:
		if (lParam == WM_LBUTTONDBLCLK) {
			if (AfxGetApp()->m_pMainWnd->IsWindowVisible()) {
				AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE); 
			}
			else {
				AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
			}
		}
		else if (lParam == WM_RBUTTONDOWN) {
			CMenu menu;
			menu.LoadMenu(IDR_MENU1);
			CMenu* pMenu = menu.GetSubMenu(0);
			CPoint pos;
			GetCursorPos(&pos);
			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, AfxGetMainWnd());
		}
		break;
	case WM_SYSCOMMAND:
		//if (wParam == SC_MINIMIZE) {
		//	AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);
		//	return 0;
		//}
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

void CwlppegnuiDlg::refreshWindow(conFig &config)
{
	UpdateData(TRUE);
	pathShow = config.path;
	m_mute.SetCheck(config.mute);
	fulFill.SetCheck(config.full);
	cmdShow = config.Cmd;
	UpdateData(FALSE);
}

void CwlppegnuiDlg::OnAboutD()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg aDlg;
	aDlg.DoModal();
}


void CwlppegnuiDlg::OnExitProc()
{
	// TODO: 在此添加命令处理程序代码
	if (hFfplay != NULL) {
		DWORD dwPID = 0;
		GetWindowThreadProcessId(hFfplay, &dwPID);
		char strCmd[MAX_PATH] = { 0 };
		sprintf_s(strCmd, "taskkill /pid %d -f", dwPID);
		system(strCmd);
	}
	::Shell_NotifyIcon(NIM_DELETE, &m_notify);
	DestroyWindow();
}


HBRUSH CwlppegnuiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CwlppegnuiDlg::OnSetPath()
{
	// TODO: 在此添加命令处理程序代码
	CinputDlg iDlg;
	CString Path;
	if(iDlg.DoModal() == IDOK){
		Path = iDlg.m_input;
	}
	WritePrivateProfileString(L"path", L"location",Path,path+L"\\settings\\ffpath.ini");
}

void Pause() {
	SetForegroundWindow(hFfplay);
	Sleep(100);
	INPUT input;
	WORD vkey = 0x50; // see link below
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}


void CwlppegnuiDlg::OnPause()
{
	// TODO: 在此添加命令处理程序代码
	if (hFfplay != NULL) {
		Pause();
		SetForegroundWindow();
	}
}