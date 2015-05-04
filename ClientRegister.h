#if !defined(AFX_CLIENTREGISTER_H__27747427_25AF_4F12_9343_FCAAE0998CC9__INCLUDED_)
#define AFX_CLIENTREGISTER_H__27747427_25AF_4F12_9343_FCAAE0998CC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientRegister.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientRegister dialog

class CClientRegister : public CDialog
{
// Construction
public:
	CBitmap m_background;
	void AddNewAdmin();
	BOOL PwdCheck();
	BOOL AdminCheck();
	CClientRegister(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClientRegister)
	enum { IDD = IDD_CLIENT_RegisterDlg };
	CEdit	m_pswsure;
	CSpringButton	m_AdminCheck;
	CEdit	m_newpwd;
	CSpringButton	m_ReDlgClose;
	CSpringButton	m_RegisterOk;
	CString	m_NewAdmin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientRegister)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClientRegister)
	afx_msg void OnBUTTONAdminCheck();
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSetfocusEDITPwdSet();
	afx_msg void OnSetfocusEDITPwdSure();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTREGISTER_H__27747427_25AF_4F12_9343_FCAAE0998CC9__INCLUDED_)
