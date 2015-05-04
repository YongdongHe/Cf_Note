// Tip.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "Tip.h"
#include "Ado.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTip dialog

DWORD _stdcall Thread_PlaySound(LPVOID pParam);
CTip::CTip(CWnd* pParent /*=NULL*/)
	: CDialog(CTip::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTip)
	//}}AFX_DATA_INIT
}


void CTip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTip)
	DDX_Control(pDX, IDC_BUTTON_TipClose, m_TipClose);
	DDX_Control(pDX, IDC_BUTTON_SHUT, m_droptip);
	DDX_Control(pDX, IDC_BUTTON_OK, m_setlasttip);
	DDX_Control(pDX, IDC_EDIT_LASTMINUTE, m_lastminute);
	DDX_Control(pDX, IDC_EDIT_REGULARTIP, m_regularTip);
	DDX_Control(pDX, IDC_EDIT_TIME, m_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTip, CDialog)
	//{{AFX_MSG_MAP(CTip)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_CHECK_OPEN, OnCheckOpen)
	ON_BN_CLICKED(IDC_BUTTON_SHUT, OnButtonShut)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON_TipClose, OnBUTTONTipClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTip message handlers


BOOL CTip::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//加载背景和按钮资源
	m_tipbg.LoadBitmap(IDB_BITMAP_Tipbg);

	m_droptip.LoadOnBitmap(IDB_BITMAP_Tip_Dtip1);
	m_droptip.LoadLightBitmap(IDB_BITMAP_Tip_Dtip2);
	m_droptip.LoadOffBitmap(IDB_BITMAP_Tip_Dtip1);

	m_setlasttip.LoadOnBitmap(IDB_BITMAP_Tip_OK1);
	m_setlasttip.LoadLightBitmap(IDB_BITMAP_Tip_OK2);
	m_setlasttip.LoadOffBitmap(IDB_BITMAP_Tip_OK1);

	m_TipClose.LoadOnBitmap(IDB_BITMAP_Tip_Close1);
	m_TipClose.LoadLightBitmap(IDB_BITMAP_Tip_Close2);
	m_TipClose.LoadOffBitmap(IDB_BITMAP_Tip_Close1);


	//设置定时器
	SetTimer(2,900,NULL);

	// TODO: Add extra initialization here
    m_regularTip.SetWindowText(tipContent);

	//设置复选框未选中
    CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_OPEN);
	pBtn->SetCheck(0);

	//设置确定键灰
    m_setlasttip.ShowWindow(SW_HIDE);

	hThread=CreateThread(NULL,0,Thread_PlaySound,this,0,NULL);



//	PlaySound((LPCTSTR)(IDR_WAVE1), AfxGetInstanceHandle(), SND_RESOURCE | SND_SYNC);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTip::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnTimer(nIDEvent);

	if(nIDEvent==2)
	{
		CTime st; 
 	    st=CTime::GetCurrentTime();
 	    CString nTime;
 	    nTime=st.Format("%m-%d %H:%M:%S");
 	    m_Time.SetWindowText(nTime);
	}
}



void CTip::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	PlaySound(0,0,SND_FILENAME);
	//获取延迟时间
	CString LastMinute;
	int lastminute,plusHour,plusMinute;
	m_lastminute.GetWindowText(LastMinute);
    lastminute=_ttoi(LastMinute);
//增加的小时和分钟
	plusHour=lastminute/60;
	plusMinute=lastminute%60;
//获取要求延时的记录	
    CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();

	CString Sql = "select * from users where 时间 = '"+tipTime+"'and 用户='"+usersname+"'";		//sql语句
	pRecordset = ado.OpenRecordset(Sql);
 
	CString bDate,bTime,cstr;
    bDate= (char*)(_bstr_t)pRecordset->GetCollect("日期");
    bTime = (char*)(_bstr_t)pRecordset->GetCollect("时间");
//分解记录的时间
    int year1,month1,day1,hour1,minute1;
    year1=_ttoi(bDate.Left(4));
    cstr=bDate.Right(bDate.GetLength()-1-bDate.Find('/'));
	month1=_ttoi(cstr.Left(cstr.Find('/')));
    day1=_ttoi(cstr.Right(cstr.GetLength()-1-cstr.Find('/')));

	hour1=_ttoi(bTime.Left(bTime.Find(':')));
    cstr=bTime.Right(bTime.GetLength()-1-bTime.Find(':'));
	minute1=_ttoi(cstr.Left(cstr.Find(':')));
//增加时间
	int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

	minute1+=plusMinute;
	if(minute1>=60)
	{
		minute1=minute1%60;
		hour1+=1;
	}

	hour1+=plusHour;
	if(hour1>=24)
	{
		hour1=hour1%24;
		day1+=1;
	}

	if(!leapYear(year1)||month1!=2)
	{
		if(day1>days[month1])
		{
			month1+=1;
            day1=1;
		}
	}

	if(month1==2&&leapYear(year1))
	{
		if(day1>29)
		{
			day1=1;
			month1=3;
		}
	}
	if(month1>12)
	{
		year1+=1;
		month1=1;
	}

	CString nYear,nMonth,nDay,nDate;
	CString nHour,nMinute,nTime;
	nYear.Format("%d",year1);
    nMonth.Format("%02d",month1);
	nDay.Format("%02d",day1);
	nHour.Format("%02d",hour1);

    nMinute.Format("%02d",minute1);


	nDate=nYear+"/"+nMonth+"/"+nDay;
	nTime=nHour+":"+nMinute+":00";

	pRecordset->PutCollect("日期",(_bstr_t)nDate);
    pRecordset->PutCollect("时间",(_bstr_t)nTime);
	pRecordset->Update();
    pRecordset->Close();
    ado.ExitConnection();

	CDialog::OnOK();
}

void CTip::OnCheckOpen() 
{
	// TODO: Add your control notification handler code here
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_OPEN);
    int state = pBtn->GetCheck();
	
	if(state==1)
	{
		m_setlasttip.ShowWindow(SW_SHOW); 
		m_lastminute.SetWindowText("10");
	}
	if(state==0)
	{
		m_setlasttip.ShowWindow(SW_HIDE);    
		m_lastminute.SetWindowText("");
	}
}


DWORD _stdcall Thread_PlaySound(LPVOID pParam)
{
	PlaySound((LPCTSTR)(IDR_WAVE4), AfxGetInstanceHandle(), SND_RESOURCE |SND_ASYNC|SND_LOOP);
	return 0;

}

void CTip::OnButtonShut() 
{
	// TODO: Add your control notification handler code her
	PlaySound(0,0,SND_FILENAME);
	
}

BOOL CTip::leapYear(int year)
{//判断是否闰年
	if(year%400==0||
		(year%100!=0&&year%4==0))
		return true;//是闰年
	else
		return false;//不是闰年
}

void CTip::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	BITMAP bm;
	CRect rect;
	CDC dcMem;
	m_tipbg.GetBitmap (&bm);
	GetClientRect(&rect);
	dcMem.CreateCompatibleDC (&dc);
	CBitmap *oldbitmap=dcMem.SelectObject (&m_tipbg);
	dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
    dcMem.SelectObject(oldbitmap);
	
	// Do not call CDialog::OnPaint() for painting messages
}

UINT CTip::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
    return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);

}

void CTip::OnBUTTONTipClose() 
{
	// TODO: Add your control notification handler code here
	PlaySound(0,0,SND_FILENAME);
	CDialog::OnCancel();
	

	
}
