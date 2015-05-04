#if !defined(AFX_MAINDLG_H__DAE286B4_0C45_4EFB_8BA0_FAE6C39D8B20__INCLUDED_)
#define AFX_MAINDLG_H__DAE286B4_0C45_4EFB_8BA0_FAE6C39D8B20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDlg.h : header file
//

#include "DiaryDlg.h"
#include "MUSICDlg.h"
#include "∂® ±Ã·–—Dlg.h"
#include "ClientDlg.h"
#define WM_SHOWTASK (WM_USER+1)

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog


class CMainDlg : public CDialog
{
// Construction
public:
	NOTIFYICONDATA m_nid;
	CString m_font;
	CFont m_Buttonfont;
	HANDLE hThread;
	CBitmap m_bmp_Mainbg;
	BOOL OnInitDialog();
	CMainDlg(CWnd* pParent = NULL);   // standard constructor
	CFont m_font_motto;
	CFont m_font_greet;

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_DIALOG_MAIN };
	CSpringButton	m_Button_MainMini;
	CSpringButton	m_Button_Calendar;
	CSpringButton	m_Button_Setting;
	CSpringButton	m_Button_Diary;
	CSpringButton	m_Button_MainClose;
	CSpringButton	m_Button_Memorandum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	afx_msg void OnBUTTONDiary();
	afx_msg void OnBUTTONSetting();
	afx_msg void OnBUTTONMemorandum();
	afx_msg void OnPaint();
	afx_msg void OnButtonMainClose();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBUTTONCalendar();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonMini();
	//}}AFX_MSG
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()


	CClientDlg m_ClientDlg;
private:
	void ShowMotto();
	SYSTEMTIME Time1;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__DAE286B4_0C45_4EFB_8BA0_FAE6C39D8B20__INCLUDED_)
