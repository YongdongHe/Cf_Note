// DiaryDlg.h : header file
//
#include "SpringButton.h"
#include "Resource.h"
#if !defined(AFX_DIARYDLG_H__E922940B_8534_4715_B034_87C2D27DF072__INCLUDED_)
#define AFX_DIARYDLG_H__E922940B_8534_4715_B034_87C2D27DF072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// CDiaryDlg dialog
#include<vector> 
using namespace std;
class CDiaryDlg : public CDialog
{
// Construction
public:
	CString m_font;
	CBitmap m_Bitmap_Diarybg;
	CString m_username;
	CFont font;
	HWND hEdit;
	SYSTEMTIME Time1;


	void GetFileFromDir(CString csDirPath);
	void AutoSave();


	void CreateDiary();
	CDiaryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDiaryDlg)
	enum { IDD = IDD_DIARY_DIALOG };
	CSpringButton	m_weatherkid;
	CSpringButton	m_DiaryOpen;
	CSpringButton	m_DiarySave;
	CSpringButton	m_DiaryClose;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiaryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	vector<CString> m_FileList;

	// Generated message map functions
	//{{AFX_MSG(CDiaryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeCOMBODate();
	afx_msg void OnSetfocusEditText();
	afx_msg void OnSetfocusEditHead();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBUTTONWeather();
	afx_msg void OnButtonSd();
	afx_msg void OnChangeEditHead();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnChangeEditText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_ComBCtrl;
	void Refresh( long WindowID);
	CString m_Today;
	int m_weather;
	CBitmap m_Bitmap_text;

    CString strFolderPath;
	BOOL m_CreateFile;
	CFile m_file;
	CEdit	m_save;
	CEdit	m_head;
	CComboBox	m_Name;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIARYDLG_H__E922940B_8534_4715_B034_87C2D27DF072__INCLUDED_)
