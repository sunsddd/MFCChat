
// MFCChatClientDlg.h : ͷ�ļ�
//

#pragma once
#include "MySocket.h"
#include "afxwin.h"

// CMFCChatClientDlg �Ի���
class CMFCChatClientDlg : public CDialogEx
{
// ����
public:
	CMFCChatClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATCLIENT_DIALOG };
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
	afx_msg void OnBnClickedConnectBtn();
	MySocket *m_client;

	CListBox m_list;
	CEdit m_input;
	//CTime m_tm; //ʵʱʱ��
	afx_msg void OnBnClickedSendBtn();
	CString CatShowString(CString strInfo, CString strMsg);
	afx_msg void OnBnClickedSavenameBtn();
	afx_msg void OnBnClickedClearmsgBtn();
	afx_msg void OnBnClickedAutosendCheck();
	afx_msg void OnBnClickedDisconnectBtn();
	CComboBox m_WordColorCombo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
