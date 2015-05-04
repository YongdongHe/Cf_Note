// MUSICDlg.h : header file
//

#if !defined(AFX_MUSICDLG_H__A43896A1_253D_4295_86B2_2F68F741BEAF__INCLUDED_)
#define AFX_MUSICDLG_H__A43896A1_253D_4295_86B2_2F68F741BEAF__INCLUDED_

#include "Client_PlayMusic.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMUSICDlg dialog
#include"Client_PlayMusic.h"
#include <vector>
using namespace std;
class CMUSICDlg : public CDialog
{
// Construction
public:
	CString m_font;
	CBitmap m_Bitmap_Musicbg;
	CString m_username;
	CClient_PlayMusic* hThread;

	CMUSICDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMUSICDlg)
	enum { IDD = IDD_MUSIC_DIALOG };
	CComboBox	m_ClientFont;
	CSpringButton	m_music_add;
	CSpringButton	m_music_mode;
	CSpringButton	m_music_pauseorplay;
	CSpringButton	m_music_Close;
	CSliderCtrl	m_Volume;
	CComboBox	m_Select;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMUSICDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	vector <CString> m_FontList;

	// Generated message map functions
	//{{AFX_MSG(CMUSICDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONPlay();
	afx_msg void OnBUTTONPause();
	afx_msg void OnSelchangeCOMBOMusicList();
	afx_msg void OnButtonExit();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnBUTTONMode();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeComboFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CtlVolume();
		MIXERCONTROLDETAILS_SIGNED volStruct;
	MIXERCONTROLDETAILS mxcd;

	MIXERLINECONTROLS mxlc;

	MIXERLINE mxl;

	MIXERCONTROL mxc;

	HMIXER m_hmx;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICDLG_H__A43896A1_253D_4295_86B2_2F68F741BEAF__INCLUDED_)
