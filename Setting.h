#if !defined(AFX_SETTING_H__B36EEF15_ECF6_449D_BBBC_B37A9D99977F__INCLUDED_)
#define AFX_SETTING_H__B36EEF15_ECF6_449D_BBBC_B37A9D99977F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetting dialog

class CSetting : public CDialog
{
// Construction
public:
	CString m_font;
	CBitmap m_Bitmap_Setbg;
	CString m_username;
	CSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetting)
	enum { IDD = IDD_DIALOG_Setting };
	CSpringButton	m_set_Close;
	CSpringButton	m_set_PerDoc;
	CSpringButton	m_set_Music;
	CSpringButton	m_set_Safety;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetting)
	afx_msg void OnBUTTONSafety();
	afx_msg void OnButtonMusic();
	afx_msg void OnButtonInfo();
		virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBUTTONSetClose();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTING_H__B36EEF15_ECF6_449D_BBBC_B37A9D99977F__INCLUDED_)
