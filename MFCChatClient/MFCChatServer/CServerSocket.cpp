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

	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str += dlg->m_tm.Format("%X ");
	str += _T("客户端连接成功！");
	dlg->m_list.AddString(str);
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnAccept(nErrorCode);
}
