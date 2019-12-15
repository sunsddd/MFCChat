
// MFCChatServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCChatServerDlg �Ի���



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

// CMFCChatServerDlg ��Ϣ�������

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	AfxSocketInit();
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));

	//���ƿؼ�
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);

	m_WordColorCombo.AddString(L"��ɫ");
	m_WordColorCombo.AddString(L"��ɫ");
	m_WordColorCombo.AddString(L"��ɫ");
	m_WordColorCombo.AddString(L"��ɫ");

	m_WordColorCombo.SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//һ ȷ��Ŀ������		�� ������ԴͼƬ����ת��Ϊ�ڴ��豸	�� ��ͼ
		//1 ����dc
		CPaintDC dc(this);
		//2 ȷ�����Ƶ�����
		CRect rect;
		GetClientRect(&rect);
		//TRACE("####width: %d,height: %d", rect.Width(), rect.Height());
		//3 ���岢����һ���ڴ��豸���� ����������DC
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);

		//4 ������ԴͼƬ
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmap(IDB_HILL_BMP);
		//5 ��ͼƬ��Դ���뵽λͼ���� bBitMapλͼ
		BITMAP bBitMap;
		bmpBackGround.GetBitmap(&bBitMap);
		//6 ��λͼѡ����ʱ���ڴ��豸����
		CBitmap *pbmOld = dcBmp.SelectObject(&bmpBackGround);

		//7 ��ʼ����
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, bBitMap.bmWidth, bBitMap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatServerDlg::OnBnClickedStartBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ƿؼ�
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
	//str += _T("��������");

	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg = _T("��������");
	strShow = CatShowString(strInfo, strMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);
}

//�ַ���ƴ��
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

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//1 ��ȡ���������
	TRACE("####OnBnClickedSendBtn");
	CString strTmpMsg;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowTextW(strTmpMsg);

	USES_CONVERSION;
	char *szSendBuf = T2A(strTmpMsg);

	//2 ���͸�������
	m_chat->Send(szSendBuf, strlen(szSendBuf) + 1, 0);

	//3 ��ʾ���б��
	//CString strShow = _T("����ˣ�");
	//CString strTime;
	//m_tm = CTime::GetCurrentTime();
	//strTime = m_tm.Format("%X ");
	//strShow = strTime + strShow;
	//strShow += strTmpMsg;

	CString strShow;
	CString strInfo = _T("����ˣ�");
	strShow = CatShowString(strInfo, strTmpMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);

	//��ձ����
	GetDlgItem(IDC_SEND_EDIT)->SetWindowTextW(_T(""));
}

//����
void CMFCChatServerDlg::OnBnClickedClearBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_list.ResetContent();
}


void CMFCChatServerDlg::OnBnClickedStopBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ƿؼ�
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);

	//������Դ
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

	//��ʾ���б��
	CString strShow;
	strShow = CatShowString(_T(""), _T("������ֹͣ"));
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strColor;
	GetDlgItemTextW(IDC_COLOR_COMBO, strColor);

	if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID()) {
		if (strColor == _T("��ɫ")) {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"��ɫ") {
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"��ɫ") {
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"��ɫ") {
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}

	return hbr;
}


void CMFCChatServerDlg::OnBnClickedCalBtn()
{
	// ִ��Shell����
	ShellExecute(NULL, L"open", L"calc.exe", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedMailBtn()
{
	// ������
	ShellExecute(NULL, L"open", L"https://mail.qq.com", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnClickedQqBtn()
{
	// ��QQ
	ShellExecute(NULL, L"open", L"C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOWNORMAL);
}


BOOL CMFCChatServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		//TRACE("####�س�");
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) {
		//TRACE("####�ո�");
		return TRUE;
	}
	//��ӿ�ݼ�
	if (pMsg->message == WM_KEYDOWN) {
		if (GetKeyState(VK_CONTROL) < 0) {
			if (pMsg->wParam == 'X') {
				CDialogEx::OnOK();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
