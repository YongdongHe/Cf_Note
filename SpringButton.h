#if !defined(AFX_SPRINGBUTTON_H__CB226B7D_A3D7_4395_B6B2_41BEBADD5144__INCLUDED_)
#define AFX_SPRINGBUTTON_H__CB226B7D_A3D7_4395_B6B2_41BEBADD5144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpringButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpringButton window

class CSpringButton : public CButton
{
// Construction
public:
	CSpringButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpringButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:

	bool GetPress();
	BOOL LoadLightBitmap(UINT nIDResource);
	COLORREF SetTextClr(COLORREF clr);
	BOOL LoadFixBitmap(UINT nIDResource);
	UINT SetButtonType(UINT type);
	enum buttontype{BS_AUTO,BS_UNAUTO,BS_FIXED};
	BOOL LoadOffBitmap(UINT nIDResource);
	BOOL LoadOnBitmap(UINT nIDResource);
	virtual ~CSpringButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpringButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM  wParam,LPARAM  lParam);       
    afx_msg LRESULT OnMouseHover(WPARAM  wParam,LPARAM  lParam); 

	DECLARE_MESSAGE_MAP()
private:	
	bool m_is_focused;
	CBitmap m_lightbitmap;
	CBitmap m_fixbitmap;
	UINT m_ButtonType;//按钮类型
	COLORREF m_TextClr;
	CBitmap m_offbitmap;
	CBitmap m_onbitmap;
	bool m_is_pressed;//标记按钮是否被按下的变量
	bool m_onrc_isok,m_offrc_isok,m_fixrc_isok,m_lightrc_isok;//标记onbitmap，offbitmap,fixbitmap,lightbitmap是否被加载过位图的变量
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPRINGBUTTON_H__CB226B7D_A3D7_4395_B6B2_41BEBADD5144__INCLUDED_)
