#if !defined(AFX_EDITDLG_H__EE3ADDB6_C00B_4B43_93B5_B874D1AA93DB__INCLUDED_)
#define AFX_EDITDLG_H__EE3ADDB6_C00B_4B43_93B5_B874D1AA93DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
//
#include "EditDlg.h"
#include "Resource.h"

#define WM_SINGLE_SELECT_JOURNAL WM_USER+4
#define WM_SINGLE_SELECT_NOTE WM_USER+5
#define WM_SINGLE_SELECT_BIRTHDAY WM_USER+6
/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


class CEditDlg : public CDialog
{
// Construction
public:
	HWND m_hWndEdit;
	CEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_DIALOG1 };
	int		m_year;
	int		m_month;
	int		m_day;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	afx_msg void OnButtonJournal();
	afx_msg void OnButtonNote();
	afx_msg void OnButtonBirth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__EE3ADDB6_C00B_4B43_93B5_B874D1AA93DB__INCLUDED_)
