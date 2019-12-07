#include "stdafx.h"
#include "ChatServer.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"

ChatServer::ChatServer()
{
}


ChatServer::~ChatServer()
{
}

void ChatServer::OnReceive(int nErrorCode) {
	//1 �������ݵ�buf
	TRACE("####Server OnReceive");
	CMFCChatServerDlg *dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("####Server szRecvBuf = %s", szRecvBuf);

	//2 ��ʾbuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);

	//3 ��ʾ���б��
	//CString strShow = _T("�ͻ��ˣ�");
	//CString strTime;
	//dlg->m_tm = CTime::GetCurrentTime();
	//strTime = dlg->m_tm.Format("%X ");
	//strShow = strTime + strShow;
	//strShow += strRecvMsg;

	CString strShow;
	CString strInfo = _T("�ͻ��ˣ�");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnReceive(nErrorCode);
}
