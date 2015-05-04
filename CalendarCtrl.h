#if !defined(AFX_CALENDARCTRL_H__EE4F7C89_4F56_4062_B80B_A00646FA02E2__INCLUDED_)
#define AFX_CALENDARCTRL_H__EE4F7C89_4F56_4062_B80B_A00646FA02E2__INCLUDED_

//#include "EditDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalendarCtrl window
#define WM_SINGLE_SELECT_DAY (WM_USER+110)
#define WM_DOUBLE_SELECT_DAY (WM_USER+111)
#define WM_DOUBLECLICK_SELECT_DAY (WM_USER+112)
#define WM_DOUBLECLICK_SELECT_ANOTHER_DAY (WM_USER+113)

#define WM_SINGLE_SELECT_DAY_UPDATECURRENT WM_USER+1
#define WM_SINGLE_SELECT_DAY_UPDATEFORMER WM_USER+2
#define WM_SINGLE_SELECT_DAY_UPDATELATTER WM_USER+3

class CCalendarCtrl : public CStatic
{
// Construction
public:
	//-----------------------------------------------------------
	// 构造数组 [军子 2009年4月23日 14:50:52]
	CCalendarCtrl();
	virtual ~CCalendarCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CCalendarCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Implementation
public:
	afx_msg void OnPaint();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

public:	
	COLORREF m_clrBack;
	COLORREF m_clrBackHeader;
	COLORREF m_clrTextHeader;	
	COLORREF m_clrText;
	COLORREF m_clrTextRest;
	COLORREF m_clrActive;
	COLORREF m_clrLine;
	COLORREF m_clrActiveBk;
	COLORREF m_clrToday;
	COLORREF m_clrTextLunar;
	COLORREF m_clrTextSolor;
	COLORREF m_clrLunor;
	BOOL	 m_bFirstDay;
	COleDateTime m_Time;
	void SetTime(COleDateTime newTime);
	int GetMonthDays(COleDateTime nTime);

public:
	SYSTEMTIME m_tSelSolor;
	SYSTEMTIME m_tSelLunar;	
	HWND m_hWndTemp;
protected:
	
//	CString sTip;
//	CEditDlg m_checkTime;
	
	int		 m_nCurrentIndex ;
	int		 m_nFirstDay;
	CRect	 m_rWin;
	void DrawCanlendar(CPaintDC* pWinDC);

private:
	
	int GetSelectDay(CPoint pt);
	CToolTipCtrl m_ToolTip;
	BOOL m_bTip;

	//-----------------------------------------------------------
	// 公历与农历相互转换 [军子 2009年4月24日 0:47:46]
public:
	int GetAllMonthDaysBefore(COleDateTime before);
	CString m_Today;
	int GetLastMonthDays(COleDateTime LastMonth);
	BOOL Holiday();
	CString VariantToString(VARIANT var);
	CString m_sCheckTime;
	COleDateTime ConvertSysTime2OleDateTime ( PSYSTEMTIME pSt );
	CString GetLunarString ( IN PSYSTEMTIME pSt, BOOL bEmbolism ,BOOL bWholeName = TRUE);
	BOOL Gregorian2Lunar ( IN PSYSTEMTIME pSt, OUT PSYSTEMTIME pDst, OUT BOOL *pEmbolism );
	BOOL Lunar2Gregorian ( IN PSYSTEMTIME pSt, IN BOOL bEmbolism, OUT PSYSTEMTIME pDst );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARCTRL_H__EE4F7C89_4F56_4062_B80B_A00646FA02E2__INCLUDED_)
