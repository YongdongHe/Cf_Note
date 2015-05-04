// ¶¨Ê±ÌáÐÑDlg.h : header file
//

#if !defined(AFX_DLG_H__A94F21B2_2AA8_4B64_AED7_542E8D6AFB2E__INCLUDED_)
#define AFX_DLG_H__A94F21B2_2AA8_4B64_AED7_542E8D6AFB2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
private:
	
	CFont m_font_Tip;

	int nItem;
public:
	int DiaryFlag;
	CString DiaryDate;
	CFont font;
	CString m_font;
	CBitmap m_bitmap_Notebg;
	void Show();
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
	CString m_usersname;
	virtual BOOL OnInitDialog();


// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CSpringButton	m_Note_Close;
	CSpringButton	m_Note_Delete;
	CSpringButton	m_Note_Save;
	CDateTimeCtrl	m_date;
	CEdit	m_tipcontent;
	CComboBox	m_minute;
	CComboBox	m_hour;
	CListCtrl	m_list_tip;
	HWND hWnd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSave();
	afx_msg void OnDblclkListTip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDelete();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__A94F21B2_2AA8_4B64_AED7_542E8D6AFB2E__INCLUDED_)
