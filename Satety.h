#if !defined(AFX_SATETY_H__9015AC08_3C83_498B_ACC3_CF1F3060D71A__INCLUDED_)
#define AFX_SATETY_H__9015AC08_3C83_498B_ACC3_CF1F3060D71A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Satety.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSatety dialog

class CSatety : public CDialog
{
// Construction
public:
	CBitmap m_bitmap_safebg;
	CString m_username;
	CSatety(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSatety)
	enum { IDD = IDD_CLIENT_Safety };
	CEdit	m_ThirdPassword;
	CSpringButton	m_safe_Save;
	CSpringButton	m_safe_Close;
	CEdit	m_SecondPassword;
	CEdit	m_FirstPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatety)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSatety)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SATETY_H__9015AC08_3C83_498B_ACC3_CF1F3060D71A__INCLUDED_)
