#include "stdafx.h"
#include "MySocket.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"

MySocket::MySocket()
{
}


MySocket::~MySocket()
{
}

void MySocket::OnConnect(int nErrorCode) {
	TRACE("####OnConnect nErrorCode=%d", nErrorCode);
	CMFCChatClientDlg *dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	//CString str;
	//dlg->m_tm = CTime::GetCurrentTime();
	//str = dlg->m_tm.Format("%X ");
	//if (!nErrorCode) {
	//	str += _T("�ͷ��������ӳɹ���");
	//}
	//else {
	//	str += _T("�ͷ���������ʧ�ܣ�");
	//}

	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg;
	if (!nErrorCode) {
		strMsg += _T("�ͷ��������ӳɹ���");
	}
	else {
		strMsg += _T("�ͷ���������ʧ�ܣ�");
	}
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnSend(nErrorCode);
}

void MySocket::OnReceive(int nErrorCode) {
	TRACE("####CMySocket OnReceive");
	CMFCChatClientDlg *dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("####Server szRecvBuf = %s", szRecvBuf);

	//2 ��ʾbuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3 ��ʾ���б��
	//CString strShow = _T("����ˣ�");
	//CString strTime;
	//dlg->m_tm = CTime::GetCurrentTime();
	//strTime = dlg->m_tm.Format("%X ");
	//strShow = strTime + strShow;
	//strShow += strRecvMsg;

	CString strShow;
	CString strInfo = _T("����ˣ�");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);
	CAsyncSocket::OnReceive(nErrorCode);
}
