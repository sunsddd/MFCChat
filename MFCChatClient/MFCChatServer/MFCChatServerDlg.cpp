
// MFCChatServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "afxdialogex.h"


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


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatServerDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCChatServerDlg::OnBnClickedClearBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CMFCChatServerDlg::OnBnClickedStopBtn)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CAL_BTN, &CMFCChatServerDlg::OnBnClickedCalBtn)
	ON_BN_CLICKED(IDC_MAIL_BTN, &CMFCChatServerDlg::OnBnClickedMailBtn)
	ON_BN_CLICKED(IDC__QQ_BTN, &CMFCChatServerDlg::OnClickedQqBtn)
END_MESSAGE_MAP()
//mark

// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	AfxSocketInit();
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));

	//控制控件
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);

	m_WordColorCombo.AddString(L"黑色");
	m_WordColorCombo.AddString(L"红色");
	m_WordColorCombo.AddString(L"蓝色");
	m_WordColorCombo.AddString(L"绿色");

	m_WordColorCombo.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatServerDlg::OnPaint()
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
		//一 确定目的区域		二 加载资源图片并且转化为内存设备	三 绘图
		//1 定义dc
		CPaintDC dc(this);
		//2 确定绘制的区域
		CRect rect;
		GetClientRect(&rect);
		//TRACE("####width: %d,height: %d", rect.Width(), rect.Height());
		//3 定义并创建一个内存设备环境 创建兼容性DC
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);

		//4 载入资源图片
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmap(IDB_HILL_BMP);
		//5 将图片资源载入到位图里面 bBitMap位图
		BITMAP bBitMap;
		bmpBackGround.GetBitmap(&bBitMap);
		//6 将位图选入临时的内存设备环境
		CBitmap *pbmOld = dcBmp.SelectObject(&bmpBackGround);

		//7 开始绘制
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, bBitMap.bmWidth, bBitMap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatServerDlg::OnBnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//控制控件
	GetDlgItem(IDC_START_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);


	TRACE("####OnBnClickedStartBtn");
	CString strPort;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	TRACE("####szPort = %s ", szPort);
	int iPort = _ttoi(strPort);
	m_server = new CServerSocket;

	if (!m_server->Create(iPort)) {
		TRACE("####m_server create errorCode %d", GetLastError());
		return;
	}

	if (!m_server->Listen()) {
		TRACE("####m_server listen errorCode %d", GetLastError());
		return;
	}

	//CString str;
	//m_tm = CTime::GetCurrentTime();
	//str += m_tm.Format("%X ");
	//str += _T("建立服务");

	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg = _T("建立服务");
	strShow = CatShowString(strInfo, strMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);
}

//字符串拼接
CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg) {

	CTime tmTime;
	tmTime = CTime::GetCurrentTime();
	CString strTime = tmTime.Format("%X ");
	CString strShow;

	strShow = strTime + strInfo;
	strShow += strMsg;

	return strShow;
}

void CMFCChatServerDlg::OnBnClickedSendBtn()
{

	// TODO: 在此添加控件通知处理程序代码
	//1 获取编译框内容
	TRACE("####OnBnClickedSendBtn");
	CString strTmpMsg;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowTextW(strTmpMsg);

	USES_CONVERSION;
	char *szSendBuf = T2A(strTmpMsg);

	//2 发送给服务器
	m_chat->Send(szSendBuf, strlen(szSendBuf) + 1, 0);

	//3 显示到列表框
	//CString strShow = _T("服务端：");
	//CString strTime;
	//m_tm = CTime::GetCurrentTime();
	//strTime = m_tm.Format("%X ");
	//strShow = strTime + strShow;
	//strShow += strTmpMsg;

	CString strShow;
	CString strInfo = _T("服务端：");
	strShow = CatShowString(strInfo, strTmpMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);

	//清空编译框
	GetDlgItem(IDC_SEND_EDIT)->SetWindowTextW(_T(""));
}

//清屏
void CMFCChatServerDlg::OnBnClickedClearBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatServerDlg::OnBnClickedStopBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//控制控件
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);

	//回收资源
	m_server->Close();
	if (m_server != NULL) {
		delete m_server;
		m_server = NULL;
	}
	if (m_chat != NULL) {
		m_chat->Close();
		delete m_chat;
		m_chat = NULL;
	}

	//显示到列表框
	CString strShow;
	strShow = CatShowString(_T(""), _T("服务器停止"));
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strColor;
	GetDlgItemTextW(IDC_COLOR_COMBO, strColor);

	if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID()) {
		if (strColor == _T("黑色")) {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"红色") {
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"蓝色") {
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"绿色") {
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}

	return hbr;
}


void CMFCChatServerDlg::OnBnClickedCalBtn()
{
	// 执行Shell命令
	ShellExecute(NULL, L"open", L"calc.exe", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedMailBtn()
{
	// 打开邮箱
	ShellExecute(NULL, L"open", L"https://mail.qq.com", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnClickedQqBtn()
{
	// 打开QQ
	ShellExecute(NULL, L"open", L"C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOWNORMAL);
}


BOOL CMFCChatServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		//TRACE("####回车");
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) {
		//TRACE("####空格");
		return TRUE;
	}
	//添加快捷键
	if (pMsg->message == WM_KEYDOWN) {
		if (GetKeyState(VK_CONTROL) < 0) {
			if (pMsg->wParam == 'X') {
				CDialogEx::OnOK();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
