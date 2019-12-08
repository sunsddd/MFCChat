
// MFCChatClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
#include "afxdialogex.h"

#include <atlbase.h>
#include<comdef.h>

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


// CMFCChatClientDlg 对话框


CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenameBtn)
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
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
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	//将昵称从配置文件里面读出来
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR wszPath[MAX_PATH] = { 0 };
	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, wszPath);

	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", wszPath);

	DWORD dw = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL, wszName, MAX_PATH, strFilePath);
	TRACE("####wszName = %ls ; dw = %d", wszName, dw);

	if (dw == 0) {
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端", strFilePath);
		memcpy_s(wszName, MAX_PATH, L"客户端", MAX_PATH);
	}
	SetDlgItemText(IDC_NAME_EDIT, wszName);
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatClientDlg::OnPaint()
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
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnBnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####OnBnClickedConnectBtn");
	CString strPort, strIP;

	//获取文本框的内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);
	int iPort = _ttoi(strPort);
	TRACE("####szPort = %s , szIP = %s", szPort, szIP);

	m_client = new MySocket;
	if (!m_client->Create()) {
		TRACE("####m_client Create error %d", GetLastError());
		return;
	}
	else {
		TRACE("####m_client Create Success");
	}

	m_client->Connect(strIP, iPort);
}

//字符串拼接
CString CMFCChatClientDlg::CatShowString(CString strInfo, CString strMsg) {

	CTime tmTime;
	tmTime = CTime::GetCurrentTime();
	CString strTime = tmTime.Format("%X ");
	CString strShow;

	strShow = strTime + strInfo;
	strShow += strMsg;

	return strShow;
}


void CMFCChatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	//1 获取编辑框内容
	CString strTmpMsg;
	CString strName;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(strTmpMsg);
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);

	strTmpMsg = strName + _T("：") + strTmpMsg;
	USES_CONVERSION;
	char *szSendBuf = T2A(strTmpMsg);

	//2 发送给服务器
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	//3 显示到列表框

	//CString strShow = _T("我：");
	//CString strTime;
	//m_tm = CTime::GetCurrentTime();
	//strTime = m_tm.Format("%X ");
	//strShow = strTime + strShow;
	//strShow += strTmpMsg;

	CString strShow;
	//CString strInfo = _T("我：");
	strShow = CatShowString(_T(""), strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}



//保存昵称
void CMFCChatClientDlg::OnBnClickedSavenameBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength() <= 0) {
		AfxMessageBox(_T("昵称不能为空！"));
		return;
	}

	if (IDOK == AfxMessageBox(_T("确定要修改昵称吗？")), MB_OKCANCEL) {
		WCHAR strPath[MAX_PATH] = { 0 };
		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		_bstr_t bsPath(strPath);
		const char *zsPath = bsPath;
		TRACE("####strPath = %s", zsPath);

		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);

		//获取控件内容	
		GetDlgItemText(IDC_NAME_EDIT, strName);
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}

}
