// Setting.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "Setting.h"
#include "Info.h"
#include "Satety.h"
#include "MUSICDlg.h"
#include "Winuser.h"
#pragma comment(lib,"user32.LIB")



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetting dialog


CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetting)
	//}}AFX_DATA_INIT
}


void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetting)
	DDX_Control(pDX, IDC_BUTTON_SetClose, m_set_Close);
	DDX_Control(pDX, IDC_BUTTON_INFO, m_set_PerDoc);
	DDX_Control(pDX, IDC_BUTTON_MUSIC, m_set_Music);
	DDX_Control(pDX, IDC_BUTTON_Safety, m_set_Safety);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetting, CDialog)
	//{{AFX_MSG_MAP(CSetting)
	ON_BN_CLICKED(IDC_BUTTON_Safety, OnBUTTONSafety)
	ON_BN_CLICKED(IDC_BUTTON_MUSIC, OnButtonMusic)
	ON_BN_CLICKED(IDC_BUTTON_INFO, OnButtonInfo)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SetClose, OnBUTTONSetClose)
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetting message handlers

void CSetting::OnBUTTONSafety() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CSatety dlg;
	dlg.m_username=m_username;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CSetting::OnButtonMusic() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CMUSICDlg dlg;
	dlg.m_username=m_username;
	dlg.DoModal();
	m_font=dlg.m_font;
	ShowWindow(SW_SHOW);
	
}

void CSetting::OnButtonInfo() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CInfo dlg;
	dlg.m_username1=m_username;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	
}
BOOL CSetting::OnInitDialog()
{
	CDialog::OnInitDialog();
	//初始化背景和按钮资源
	m_Bitmap_Setbg.LoadBitmap(IDB_BITMAP_Setbg);

	m_set_Music.LoadOffBitmap(IDB_BITMAP_Set_perS1);
	m_set_Music.LoadLightBitmap(IDB_BITMAP_Set_perS2);
	m_set_Music.LoadOnBitmap(IDB_BITMAP_Set_perS1);

	m_set_PerDoc.LoadOffBitmap(IDB_BITMAP_Set_perD1);
	m_set_PerDoc.LoadLightBitmap(IDB_BITMAP_Set_perD2);
	m_set_PerDoc.LoadOnBitmap(IDB_BITMAP_Set_perD1);

	m_set_Safety.LoadOffBitmap(IDB_BITMAP_Set_Safe1);
	m_set_Safety.LoadLightBitmap(IDB_BITMAP_Set_Safe2);
	m_set_Safety.LoadOnBitmap(IDB_BITMAP_Set_Safe1);

	m_set_Close.LoadOffBitmap(IDB_BITMAP_Diary_Close1);
	m_set_Close.LoadLightBitmap(IDB_BITMAP_Diary_Close2);
	m_set_Close.LoadOnBitmap(IDB_BITMAP_Diary_Close1);



	return TRUE;
}

void CSetting::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here


		BITMAP bm;
		CRect rect;
		CDC dcMem;
		m_Bitmap_Setbg.GetBitmap (&bm);
		GetClientRect(&rect);
		dcMem.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem.SelectObject (&m_Bitmap_Setbg);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(oldbitmap);
		CDialog::OnPaint();
 
	// Do not call CDialog::OnPaint() for painting messages
}

void CSetting::OnBUTTONSetClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
	
}

UINT CSetting::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
 //return CDialog::OnNcHitTest(point);
}
