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
	//	str += _T("和服务器连接成功！");
	//}
	//else {
	//	str += _T("和服务器连接失败！");
	//}

	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg;
	if (!nErrorCode) {
		strMsg += _T("和服务器连接成功！");
	}
	else {
		strMsg += _T("和服务器连接失败！");
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
	
	//2 显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3 显示到列表框
	//CString strShow = _T("服务端：");
	//CString strTime;
	//dlg->m_tm = CTime::GetCurrentTime();
	//strTime = dlg->m_tm.Format("%X ");
	//strShow = strTime + strShow;
	//strShow += strRecvMsg;

	CString strShow;
	CString strInfo = _T("服务端：");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);

	//自动回复
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck()) {
		//获取自动发送内容
		CString strAutoMsg;
		dlg->GetDlgItemText(IDC_SENDAUTOMSG_EDIT, strAutoMsg);
		//获取昵称
		CString strName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, strName);
		//内容拼接 时间+昵称[自动回复]：+自动发送内容
		CString strSendMsg;
		strSendMsg = strName + _T("[自动回复]：") + strAutoMsg;
		char *szSendMsg = T2A(strSendMsg);
		//发送内容
		dlg->m_client->Send(szSendMsg, strlen(szSendMsg) + 1, 0);
		//本地列表显示
		strShow = dlg->CatShowString(_T(""), strSendMsg);
		dlg->m_list.AddString(strShow);
		dlg->UpdateData(FALSE);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
