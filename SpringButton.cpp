// SpringButton.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "SpringButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpringButton

CSpringButton::CSpringButton()
:m_TextClr(RGB(255,255,255)),
m_ButtonType(BS_AUTO),
m_fixrc_isok(FALSE),m_onrc_isok(FALSE),m_offrc_isok(FALSE),m_lightrc_isok(FALSE)
{
}

CSpringButton::~CSpringButton()
{

}


BEGIN_MESSAGE_MAP(CSpringButton, CButton)
	//{{AFX_MSG_MAP(CSpringButton)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
    ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()





void CSpringButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW);  
    m_is_pressed = false;
	m_is_focused = false;
	CButton::PreSubclassWindow();
}



BOOL CSpringButton::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}

void CSpringButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch(m_ButtonType)
	{
	case BS_AUTO://当按钮需要自动弹起时，is_pressed在鼠标松开后改变值
		m_is_pressed = false;
	    CButton::OnLButtonUp(nFlags, point);
		break;
	case BS_UNAUTO://当按钮不需要自动弹起时，按钮的状态只和鼠标按下的次数有关，不需要对is_pressed进行改变
		CButton::OnLButtonUp(nFlags, point);
		break;
	default:
		CButton::OnLButtonUp(nFlags, point);
		break;
			
	}
}

void CSpringButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch(m_ButtonType)
	{
	case BS_AUTO://当按钮需要自动弹起时，is_pressed在鼠标按下后改变值
		m_is_pressed = true;
		CButton::OnLButtonDown(nFlags, point);
		break;
	case BS_UNAUTO://当按钮不需要自动弹起时，按钮的状态只在鼠标按下时会改变，原来是凹陷，则改为凸起，原来是突起，则改变为按下
		m_is_pressed=!m_is_pressed;
		CButton::OnLButtonDown(nFlags, point);
		break;
	default:
		CButton::OnLButtonDown(nFlags, point);
		break;
	}
}



void CSpringButton::OnMouseMove(UINT nFlags, CPoint point) //当鼠标按住按钮却移出了按钮区域时，使按钮弹起
{
	// TODO: Add your message handler code here and/or call default
	BOOL _bMouseTrack=true;//每次鼠标移动都重置_bMouseTrack的值为真，已方便不停地发出下面的消息
    //************************************************************************************************************
	if (_bMouseTrack)
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE | TME_HOVER;//要触发的消息
        tme.hwndTrack = this->m_hWnd;
        tme.dwHoverTime = 1000;// 若不设此参数，则无法触发mouseHover
		
        if (::_TrackMouseEvent(&tme)) //MOUSELEAVE|MOUSEHOVER消息由此函数触发
        {
            _bMouseTrack = FALSE;   
        }
    }
	//************************************************************************************************************


	
	CRect Boundary; 
	this->GetWindowRect(&Boundary);//获取按钮区域
	m_is_focused=true;
	Invalidate();
	switch(m_ButtonType)
	{
	case BS_AUTO:
		if (MK_LBUTTON == nFlags)
		{
			m_is_pressed=false;
		}

		break;
	default:
		break;
	}
	CButton::OnMouseMove(nFlags, point);
}

 LRESULT CSpringButton::OnMouseLeave(WPARAM  wParam,LPARAM lParam)       
 {     
 	//what you want to do
	 m_is_focused=false;
	Invalidate();
 	return       0;       
 }       

 LRESULT CSpringButton::OnMouseHover(WPARAM  wParam,LPARAM lParam)       
 {       
 	//what you want to do
 	return       0;       
 }       

BOOL CSpringButton::LoadOnBitmap(UINT nIDResource)
{
	m_onbitmap.DeleteObject();//删除原来的图像，避免对onbitmap的重复加载
	m_onrc_isok=TRUE;//标记onbitmap的资源加载完毕了
	return(m_onbitmap.LoadBitmap(nIDResource));
}

BOOL CSpringButton::LoadOffBitmap(UINT nIDResource)
{
	m_offbitmap.DeleteObject();
	m_offrc_isok=TRUE;
	return(m_offbitmap.LoadBitmap(nIDResource));
}

void CSpringButton::DrawItem(LPDRAWITEMSTRUCT lp) //可使用Invalidate(TRUE)发出WM_PAINT消息以执行此函数
{
	// TODO: Add your code to draw the specified item
	CDC dc;  
	CString str; 
	CRect rc = lp->rcItem; 
	dc.Attach(lp->hDC);  
	dc.SetBkMode(TRANSPARENT);
	switch(m_ButtonType)//判断按钮类型以进行不同操作
	{
	case BS_AUTO:
	case BS_UNAUTO:
		if (m_onrc_isok&&m_offrc_isok)//如果凹下和凸起的资源都加载了，则绘图，反之不进行操作
		{
			if (m_is_pressed)  
			{  
				CBrush br(&m_onbitmap);  
				dc.SelectObject(&br);
				CPen pen(PS_NULL,1,m_TextClr);  //风格，线条粗细，颜色
				dc.SelectObject(&pen); 
				dc.Rectangle(0,0,rc.Width(),rc.Height());  
				dc.SetTextColor(m_TextClr); 
			}  
			else  
			{ 
				if (m_is_focused&&m_lightrc_isok)//如果加载过高亮图标资源并且鼠标移动到了按钮内部，则加载高亮的图标
				{
					CBrush br(&m_lightbitmap);  
					dc.SelectObject(&br);
					CPen pen(PS_NULL,1,m_TextClr);  
					dc.SelectObject(&pen); 
					dc.Rectangle(0,0,rc.Width(),rc.Height());  
				    dc.SetTextColor(m_TextClr); 
				} 
				else
				{
					CBrush br(&m_offbitmap);  
					dc.SelectObject(&br);
					CPen pen(PS_NULL,1,m_TextClr);  
					dc.SelectObject(&pen); 
					dc.Rectangle(0,0,rc.Width(),rc.Height());  
				    dc.SetTextColor(m_TextClr); 
				}	
			}
		} 
		else
		{
		}
		break; //break
		
	
	case BS_FIXED:
		if (m_fixrc_isok)
		{
			CBrush br(&m_fixbitmap);  
			dc.SelectObject(&br);
			CPen pen(PS_NULL,1,m_TextClr);  
			dc.SelectObject(&pen); 
			dc.Rectangle(0,0,rc.Width(),rc.Height());  
		    dc.SetTextColor(m_TextClr); 
		} 
		else
		{
		}
		break;
	
	
	default:
		break;
	}
	GetWindowText(str);  
	dc.DrawText(str,CRect(0,0,rc.right,rc.bottom),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.Detach();
    dc.DeleteDC(); 
	
}



UINT CSpringButton::SetButtonType(UINT type)
{
	m_ButtonType=type;
    return m_ButtonType;
}


BOOL CSpringButton::LoadFixBitmap(UINT nIDResource)
{
	m_fixbitmap.DeleteObject();
	m_fixrc_isok=TRUE;
	return(m_fixbitmap.LoadBitmap(nIDResource));
}

COLORREF CSpringButton::SetTextClr(COLORREF clr)
{
	m_TextClr=clr;
	return m_TextClr;
}

BOOL CSpringButton::LoadLightBitmap(UINT nIDResource)
{
	m_lightbitmap.DeleteObject();
	m_lightrc_isok=TRUE;
	return(m_lightbitmap.LoadBitmap(nIDResource));
}

bool CSpringButton::GetPress()
{
	return m_is_pressed;
}
