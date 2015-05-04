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
	case BS_AUTO://����ť��Ҫ�Զ�����ʱ��is_pressed������ɿ���ı�ֵ
		m_is_pressed = false;
	    CButton::OnLButtonUp(nFlags, point);
		break;
	case BS_UNAUTO://����ť����Ҫ�Զ�����ʱ����ť��״ֻ̬����갴�µĴ����йأ�����Ҫ��is_pressed���иı�
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
	case BS_AUTO://����ť��Ҫ�Զ�����ʱ��is_pressed����갴�º�ı�ֵ
		m_is_pressed = true;
		CButton::OnLButtonDown(nFlags, point);
		break;
	case BS_UNAUTO://����ť����Ҫ�Զ�����ʱ����ť��״ֻ̬����갴��ʱ��ı䣬ԭ���ǰ��ݣ����Ϊ͹��ԭ����ͻ����ı�Ϊ����
		m_is_pressed=!m_is_pressed;
		CButton::OnLButtonDown(nFlags, point);
		break;
	default:
		CButton::OnLButtonDown(nFlags, point);
		break;
	}
}



void CSpringButton::OnMouseMove(UINT nFlags, CPoint point) //����갴ס��ťȴ�Ƴ��˰�ť����ʱ��ʹ��ť����
{
	// TODO: Add your message handler code here and/or call default
	BOOL _bMouseTrack=true;//ÿ������ƶ�������_bMouseTrack��ֵΪ�棬�ѷ��㲻ͣ�ط����������Ϣ
    //************************************************************************************************************
	if (_bMouseTrack)
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE | TME_HOVER;//Ҫ��������Ϣ
        tme.hwndTrack = this->m_hWnd;
        tme.dwHoverTime = 1000;// ������˲��������޷�����mouseHover
		
        if (::_TrackMouseEvent(&tme)) //MOUSELEAVE|MOUSEHOVER��Ϣ�ɴ˺�������
        {
            _bMouseTrack = FALSE;   
        }
    }
	//************************************************************************************************************


	
	CRect Boundary; 
	this->GetWindowRect(&Boundary);//��ȡ��ť����
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
	m_onbitmap.DeleteObject();//ɾ��ԭ����ͼ�񣬱����onbitmap���ظ�����
	m_onrc_isok=TRUE;//���onbitmap����Դ���������
	return(m_onbitmap.LoadBitmap(nIDResource));
}

BOOL CSpringButton::LoadOffBitmap(UINT nIDResource)
{
	m_offbitmap.DeleteObject();
	m_offrc_isok=TRUE;
	return(m_offbitmap.LoadBitmap(nIDResource));
}

void CSpringButton::DrawItem(LPDRAWITEMSTRUCT lp) //��ʹ��Invalidate(TRUE)����WM_PAINT��Ϣ��ִ�д˺���
{
	// TODO: Add your code to draw the specified item
	CDC dc;  
	CString str; 
	CRect rc = lp->rcItem; 
	dc.Attach(lp->hDC);  
	dc.SetBkMode(TRANSPARENT);
	switch(m_ButtonType)//�жϰ�ť�����Խ��в�ͬ����
	{
	case BS_AUTO:
	case BS_UNAUTO:
		if (m_onrc_isok&&m_offrc_isok)//������º�͹�����Դ�������ˣ����ͼ����֮�����в���
		{
			if (m_is_pressed)  
			{  
				CBrush br(&m_onbitmap);  
				dc.SelectObject(&br);
				CPen pen(PS_NULL,1,m_TextClr);  //���������ϸ����ɫ
				dc.SelectObject(&pen); 
				dc.Rectangle(0,0,rc.Width(),rc.Height());  
				dc.SetTextColor(m_TextClr); 
			}  
			else  
			{ 
				if (m_is_focused&&m_lightrc_isok)//������ع�����ͼ����Դ��������ƶ����˰�ť�ڲ�������ظ�����ͼ��
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
