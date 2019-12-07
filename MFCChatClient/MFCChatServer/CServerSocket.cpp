#include "stdafx.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"

CServerSocket::CServerSocket()
{
}


CServerSocket::~CServerSocket()
{
}

//重写接收socket
void CServerSocket::OnAccept(int nErrorCode) {
	TRACE("####OnAccept");

	CMFCChatServerDlg *dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

	dlg->m_chat = new ChatServer;

	//接收连接
	Accept(*(dlg->m_chat));

	//CString str;
	//dlg->m_tm = CTime::GetCurrentTime();
	//str += dlg->m_tm.Format("%X ");
	//str += _T("客户端连接成功！");

	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg = _T("客户端连接成功！");
	strShow = dlg->CatShowString(strInfo, strMsg);

	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnAccept(nErrorCode);
}
