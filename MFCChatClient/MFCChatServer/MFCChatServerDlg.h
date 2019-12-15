
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
	CServerSocket *m_server = NULL;
	ChatServer *m_chat = NULL;
	CTime m_tm;
	afx_msg void OnBnClickedSendBtn();
	CString CatShowString(CString strInfo, CString strMsg);
	afx_msg void OnBnClickedClearBtn();
	afx_msg void OnBnClickedStopBtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox m_WordColorCombo;
	afx_msg void OnBnClickedCalBtn();
	afx_msg void OnBnClickedMailBtn();
	afx_msg void OnClickedQqBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
