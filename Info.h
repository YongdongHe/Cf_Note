#if !defined(AFX_INFO_H__548A965A_DAE0_4959_93EC_92DFAE8AD85B__INCLUDED_)
#define AFX_INFO_H__548A965A_DAE0_4959_93EC_92DFAE8AD85B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Info.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog

class CInfo : public CDialog
{
// Construction
public:
	CBitmap m_bitmap_Infobg;
	CString m_username1;
	CInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfo)
	enum { IDD = IDD_CLIENT_INFO };
	CSpringButton	m_info_Close;
	CSpringButton	m_info_Save;
	CEdit	m_Constellation;
	CEdit	m_Weight;
	CEdit	m_Nickname;
	CEdit	m_Height;
	CEdit	m_Habit;
	CEdit	m_Birthday;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSetfocusEditBirthday();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFO_H__548A965A_DAE0_4959_93EC_92DFAE8AD85B__INCLUDED_)
