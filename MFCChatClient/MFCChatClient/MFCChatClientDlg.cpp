
// MFCChatClientDlg.cpp : ʵ���ļ�
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


// CMFCChatClientDlg �Ի���


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
	DDX_Control(pDX, IDC_COLOR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenameBtn)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCChatClientDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_AUTOSEND_CHECK, &CMFCChatClientDlg::OnBnClickedAutosendCheck)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCChatClientDlg::OnBnClickedDisconnectBtn)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatClientDlg ��Ϣ�������

BOOL CMFCChatClientDlg::OnInitDialog()
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
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	//���ǳƴ������ļ����������
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR wszPath[MAX_PATH] = { 0 };
	//��ȡ��ǰ·��
	GetCurrentDirectoryW(MAX_PATH, wszPath);

	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", wszPath);

	DWORD dw = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL, wszName, MAX_PATH, strFilePath);
	TRACE("####wszName = %ls ; dw = %d", wszName, dw);

	if (dw == 0) {
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"�ͻ���", strFilePath);
		memcpy_s(wszName, MAX_PATH, L"�ͻ���", MAX_PATH);
	}
	SetDlgItemText(IDC_NAME_EDIT, wszName);
	UpdateData(FALSE);

	//��ʼ���ؼ�
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	m_WordColorCombo.AddString(_T("��ɫ"));
	m_WordColorCombo.AddString(_T("��ɫ"));
	m_WordColorCombo.AddString(_T("��ɫ"));
	m_WordColorCombo.AddString(_T("��ɫ"));

	//���õ�ǰ�±�Ϊ��
	m_WordColorCombo.SetCurSel(0);//set ����	cur	current��ǰ��	sel	selectѡ��
	//SetDlgItemText(IDC_COLOR_COMBO, _T("��ɫ"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCChatClientDlg::OnPaint()
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
		bmpBackGround.LoadBitmap(IDB_WATER_BMP);
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
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnBnClickedConnectBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(TRUE);


	TRACE("####OnBnClickedConnectBtn");
	CString strPort, strIP;

	//��ȡ�ı��������
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

//�ַ���ƴ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//1 ��ȡ�༭������
	CString strTmpMsg;
	CString strName;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(strTmpMsg);
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);

	strTmpMsg = strName + _T("��") + strTmpMsg;
	USES_CONVERSION;
	char *szSendBuf = T2A(strTmpMsg);

	//2 ���͸�������
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	//3 ��ʾ���б��

	//CString strShow = _T("�ң�");
	//CString strTime;
	//m_tm = CTime::GetCurrentTime();
	//strTime = m_tm.Format("%X ");
	//strShow = strTime + strShow;
	//strShow += strTmpMsg;

	CString strShow;
	//CString strInfo = _T("�ң�");
	strShow = CatShowString(_T(""), strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

	//��ձ༭��
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}



//�����ǳ�
void CMFCChatClientDlg::OnBnClickedSavenameBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength() <= 0) {
		AfxMessageBox(_T("�ǳƲ���Ϊ�գ�"));
		return;
	}

	if (IDOK == AfxMessageBox(_T("ȷ��Ҫ�޸��ǳ���")), MB_OKCANCEL) {
		WCHAR strPath[MAX_PATH] = { 0 };
		//��ȡ��ǰ·��
		GetCurrentDirectoryW(MAX_PATH, strPath);
		_bstr_t bsPath(strPath);
		const char *zsPath = bsPath;
		TRACE("####strPath = %s", zsPath);

		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);

		//��ȡ�ؼ�����	
		GetDlgItemText(IDC_NAME_EDIT, strName);
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}

}


//����
void CMFCChatClientDlg::OnBnClickedClearmsgBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_list.ResetContent();
}


void CMFCChatClientDlg::OnBnClickedAutosendCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck()) {
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(FALSE);
	}
	else {
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(TRUE);
	}
}


void CMFCChatClientDlg::OnBnClickedDisconnectBtn()
{
	// 1 ���ƿؼ�
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	//2 ������Դ
	m_client->Close();
	if (m_client != NULL) {
		delete m_client;
		m_client = NULL;
	}

	//3 ��ʾ���б��
	CString strShow;
	strShow = CatShowString(_T(""), _T("�Ͽ��������������"));
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString strColor;
	GetDlgItemTextW(IDC_COLOR_COMBO, strColor);

	if (IDC_LIST == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID()) {
		if (strColor == _T("��ɫ")) {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == _T("��ɫ")) {
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


BOOL CMFCChatClientDlg::PreTranslateMessage(MSG* pMsg)
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
