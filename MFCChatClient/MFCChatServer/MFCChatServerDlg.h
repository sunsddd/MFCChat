
// MFCChatServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CServerSocket.h"
#include "ChatServer.h"

// CMFCChatServerDlg 对话框
class CMFCChatServerDlg : public CDialogEx
{
// 构造
public:
	CMFCChatServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
