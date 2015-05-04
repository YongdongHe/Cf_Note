// StaticCalendarDlg.h : header file
//

#if !defined(AFX_STATICCALENDARDLG_H__45A7FE7C_92A3_472A_9893_ACCB9827D19E__INCLUDED_)
#define AFX_STATICCALENDARDLG_H__45A7FE7C_92A3_472A_9893_ACCB9827D19E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalendarCtrl.h"
//#include "EditDlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CStaticCalendarDlg dialog

class CStaticCalendarDlg : public CDialog
{
// Construction
public:
	CString m_username;
	CString VariantToString(VARIANT var);
	void Holiday();
	CString m_sHoliday;
	CBitmap m_bitmap_Calbg;
	CStaticCalendarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStaticCalendarDlg)
	enum { IDD = IDD_STATICCALENDAR_DIALOG };
	CSpringButton	m_FirstDay;
	CSpringButton	m_Cal_Close;
	CSpringButton	m_cal_left2;
	CSpringButton	m_cal_right2;
	CSpringButton	m_cal_left1;
	CSpringButton	m_cal_right1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticCalendarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
//	CEditDlg m_editDlg;
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	HICON m_hIcon;
	CCalendarCtrl	m_pCanlendar;
	COleDateTime	m_newTime;
	BOOL	m_bSun;

	int m_nRecordCurrentYear;
	int m_nRecordCurrentMonth;
	int m_nRecordCurrentDay;


	// Generated message map functions
	//{{AFX_MSG(CStaticCalendarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCloseupDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck1();
	afx_msg void OnAdd();
	afx_msg void OnDec();
	afx_msg void OnButton_AddYear();
	afx_msg void OnButton_DecYear();
	afx_msg int OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex);
	afx_msg void OnCancelMode();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	//}}AFX_MSG
	afx_msg void OnSelTime(WPARAM wPa, LPARAM lPa);
	afx_msg void OnDouSelAnoTime(WPARAM wPa, LPARAM lPa);
	afx_msg void OnDouSelTime();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICCALENDARDLG_H__45A7FE7C_92A3_472A_9893_ACCB9827D19E__INCLUDED_)
