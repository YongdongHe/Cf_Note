// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__8F6BC49A_42A5_408E_AFFF_1A699BF25F04__INCLUDED_)
#define AFX_CLIENTDLG_H__8F6BC49A_42A5_408E_AFFF_1A699BF25F04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpringButton.h"
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	virtual void OnOK();
	CBitmap m_background;
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_LoginDlg };
	CEdit	m_Pwd;
	CSpringButton	m_CloseButton;
	CSpringButton	m_RegSpringButton;
	CSpringButton	m_LogSpringButton;
	CString	m_Admin;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONLog();
	afx_msg void OnBUTTONRegister();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnBUTTONClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__8F6BC49A_42A5_408E_AFFF_1A699BF25F04__INCLUDED_)
