
// MFCChatServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CServerSocket.h"
#include "ChatServer.h"

// CMFCChatServerDlg �Ի���
class CMFCChatServerDlg : public CDialogEx
{
// ����
public:
	CMFCChatServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartBtn(); //mark
	CListBox m_list;
	CServerSocket *m_server;
	ChatServer *m_chat;
	CTime m_tm;
	afx_msg void OnBnClickedSendBtn();
	CString CatShowString(CString strInfo, CString strMsg);
};
