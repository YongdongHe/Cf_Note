#if !defined(AFX_TIP_H__882AEDD6_EFC1_4EB6_A7A1_895572EB697D__INCLUDED_)
#define AFX_TIP_H__882AEDD6_EFC1_4EB6_A7A1_895572EB697D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Tip.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTip dialog

class CTip : public CDialog
{
// Construction
public:
	CBitmap m_tipbg;
	BOOL leapYear(int year);
	CString tipContent,tipTime,usersname;
	CTip(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTip)
	enum { IDD = IDD_DIALOG_TIP };
	CSpringButton	m_TipClose;
	CSpringButton	m_droptip;
	CSpringButton	m_setlasttip;
	CEdit	m_lastminute;
	CEdit	m_regularTip;
	CEdit	m_Time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTip)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
		HANDLE hThread;

	// Generated message map functions
	//{{AFX_MSG(CTip)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonOk();
	afx_msg void OnCheckOpen();
	afx_msg void OnButtonShut();
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnBUTTONTipClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIP_H__882AEDD6_EFC1_4EB6_A7A1_895572EB697D__INCLUDED_)
