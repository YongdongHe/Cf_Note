#if !defined(AFX_MESSAGE_H__08EF6F72_3B84_472B_A556_01A73D7C4322__INCLUDED_)
#define AFX_MESSAGE_H__08EF6F72_3B84_472B_A556_01A73D7C4322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Message.h : header file
//
#include "Ado.h"

/////////////////////////////////////////////////////////////////////////////
// CMessage dialog

class CMessage : public CDialog
{
// Construction
public:
	void ShowMotto();
	CMessage(CWnd* pParent = NULL);   // standard constructor
	_RecordsetPtr m_pRecordset;
	_ConnectionPtr m_pConnection;

// Dialog Data
	//{{AFX_DATA(CMessage)
	enum { IDD = IDD_DIALOG_Message };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnInitDialog();
		HICON m_hIcon;
	


	// Generated message map functions
	//{{AFX_MSG(CMessage)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
		    CAdo ado;
			SYSTEMTIME Time;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGE_H__08EF6F72_3B84_472B_A556_01A73D7C4322__INCLUDED_)
