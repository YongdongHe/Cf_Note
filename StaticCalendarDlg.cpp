// StaticCalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "StaticCalendarDlg.h"
#include "CalendarCtrl.h"
#include "Ado.h"
#include "定时提醒Dlg.h"
//#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticCalendarDlg dialog

CStaticCalendarDlg::CStaticCalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStaticCalendarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStaticCalendarDlg)
	m_newTime = COleDateTime::GetCurrentTime();
	m_bSun = TRUE;
	//}}AFX_DATA_INIT
	m_pCanlendar.m_sCheckTime = m_newTime.Format();

	m_nRecordCurrentYear = m_newTime.GetYear();
	m_nRecordCurrentMonth = m_newTime.GetMonth();
	m_nRecordCurrentDay = m_newTime.GetDay();
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStaticCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStaticCalendarDlg)
	DDX_Control(pDX, IDC_BUTTON6, m_FirstDay);
	DDX_Control(pDX, IDC_BUTTON5, m_Cal_Close);
	DDX_Control(pDX, IDC_BUTTON4, m_cal_left2);
	DDX_Control(pDX, IDC_BUTTON3, m_cal_right2);
	DDX_Control(pDX, IDC_BUTTON2, m_cal_left1);
	DDX_Control(pDX, IDC_BUTTON1, m_cal_right1);
	DDX_Control(pDX, IDC_CALENDAR, m_pCanlendar);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_newTime);
	DDX_Check(pDX, IDC_CHECK1, m_bSun);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStaticCalendarDlg, CDialog)
	//{{AFX_MSG_MAP(CStaticCalendarDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKER1, OnCloseupDatetimepicker1)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, OnAdd)
	ON_BN_CLICKED(IDC_BUTTON2, OnDec)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton_AddYear)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton_DecYear)
	ON_WM_CHARTOITEM()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SINGLE_SELECT_DAY, OnSelTime)
	ON_MESSAGE(WM_DOUBLECLICK_SELECT_DAY, OnDouSelTime)
	ON_MESSAGE(WM_DOUBLECLICK_SELECT_ANOTHER_DAY, OnDouSelAnoTime)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticCalendarDlg message handlers

BOOL CStaticCalendarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_newTime=COleDateTime::GetCurrentTime();
	UpdateData(FALSE);

	m_pCanlendar.m_hWndTemp = m_hWnd;
//	m_editDlg.m_hWndEdit = m_hWnd;
	//加载背景和按钮资源
	m_bitmap_Calbg.LoadBitmap(IDB_BITMAP_Calbg);

	m_cal_left1.LoadOffBitmap(IDB_BITMAP_Calz1);
	m_cal_left1.LoadLightBitmap(IDB_BITMAP_Calz2);
	m_cal_left1.LoadOnBitmap(IDB_BITMAP_Calz1);

	m_cal_left2.LoadOffBitmap(IDB_BITMAP_Calzz1);
	m_cal_left2.LoadLightBitmap(IDB_BITMAP_Calzz2);
	m_cal_left2.LoadOnBitmap(IDB_BITMAP_Calzz1);

	m_cal_right1.LoadOffBitmap(IDB_BITMAP_Caly1);
	m_cal_right1.LoadLightBitmap(IDB_BITMAP_Caly2);
	m_cal_right1.LoadOnBitmap(IDB_BITMAP_Caly1);

	m_cal_right2.LoadOffBitmap(IDB_BITMAP_Calyy1);
	m_cal_right2.LoadLightBitmap(IDB_BITMAP_Calyy2);
	m_cal_right2.LoadOnBitmap(IDB_BITMAP_Calyy1);


	m_FirstDay.SetButtonType(m_FirstDay.BS_UNAUTO);
	m_FirstDay.LoadOffBitmap(IDB_BITMAP_CalStyle1);
	m_FirstDay.LoadOnBitmap(IDB_BITMAP_CalStyle1);


	m_Cal_Close.LoadOffBitmap(IDB_BITMAP_CalClose1);
	m_Cal_Close.LoadLightBitmap(IDB_BITMAP_CalClose2);
	m_Cal_Close.LoadOnBitmap(IDB_BITMAP_CalClose1);

//    Holiday();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStaticCalendarDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
		

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		BITMAP bm;
		CRect rect;
		CDC dcMem;
		m_bitmap_Calbg.GetBitmap (&bm);
		GetClientRect(&rect);
		dcMem.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem.SelectObject (&m_bitmap_Calbg);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(oldbitmap);
        CDialog::OnPaint();
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStaticCalendarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CStaticCalendarDlg::OnCloseupDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_pCanlendar.SetTime(m_newTime);
	
	CString sTime;
	sTime = m_newTime.Format("%Y-%m-%d %H:%M:%S");
	SetWindowText(sTime);
	
	*pResult = 0;
}

void CStaticCalendarDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	SetDlgItemText(IDC_CHECK1, m_FirstDay.GetPress()?"前置星期天":"星期天后置");
	m_pCanlendar.m_bFirstDay = m_FirstDay.GetPress();
//	m_pCanlendar.(m_FirstDay.GetPress()) = m_bFirstDay;
	m_pCanlendar.Invalidate();
}

void CStaticCalendarDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int m_nCurrentDay = m_newTime.GetDay();//28
	//int m_nCurrentMonth = m_newTime.GetMonth();//2
	int m_nCurrentTotalDays = m_pCanlendar.GetMonthDays( m_newTime );
	int CorrectDays = m_nCurrentTotalDays + 1 - m_nCurrentDay;
	
	COleDateTimeSpan sp= COleDateTimeSpan::COleDateTimeSpan(CorrectDays,0,0,0);
	m_newTime += sp;

	if(m_nRecordCurrentMonth == m_newTime.GetMonth() && m_nRecordCurrentYear == m_newTime.GetYear())
	{
		sp= COleDateTimeSpan::COleDateTimeSpan(m_nRecordCurrentDay-1,0,0,0);
		m_newTime +=sp;
	}
	
	m_pCanlendar.SetTime(m_newTime);
	m_pCanlendar.m_sCheckTime = m_newTime.Format();
	UpdateData(FALSE);
}

void CStaticCalendarDlg::OnDec() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int m_nCurrentDay = m_newTime.GetDay();
	int m_nLastMonthTotalDays = m_pCanlendar.GetLastMonthDays( m_newTime );
	int CorrectDays = m_nLastMonthTotalDays + m_nCurrentDay -1;
	
	COleDateTimeSpan sp= COleDateTimeSpan::COleDateTimeSpan(CorrectDays,0,0,0);
	m_newTime -= sp;

    if(m_nRecordCurrentMonth == m_newTime.GetMonth() && m_nRecordCurrentYear == m_newTime.GetYear())
	{
		sp= COleDateTimeSpan::COleDateTimeSpan(m_nRecordCurrentDay-1,0,0,0);
		m_newTime +=sp;
	}
	
	m_pCanlendar.SetTime(m_newTime);
    m_pCanlendar.m_sCheckTime = m_newTime.Format();
	//MessageBox(m_pCanlendar.m_sCheckTime,0,0);
	UpdateData(FALSE);
}


void CStaticCalendarDlg::OnSelTime(WPARAM wPa, LPARAM lPa)
{
	SYSTEMTIME tmNow;	tmNow=m_pCanlendar.m_tSelSolor;
	SYSTEMTIME tmLun;	tmLun=m_pCanlendar.m_tSelLunar;
	CString s;
	s.Format(_T("公历: %d-%d-%d   \t\t 农历: %d-%d-%d"),
		tmNow.wYear, tmNow.wMonth, tmNow.wDay,
		tmLun.wYear, tmLun.wMonth, tmLun.wDay);
	SetWindowText(s);
}

void CStaticCalendarDlg::OnButton_AddYear() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int m=m_newTime.GetYear();
	int day=m_newTime.GetDay();
	int before=m_pCanlendar.GetAllMonthDaysBefore(m_newTime);
	int m_nCurrentTotalYearDays = 365;
	if(m % 4 ==0 && m % 100 !=0 || m % 400 ==0) 
	{
		m_nCurrentTotalYearDays++;
	}
	   
	int CorrectDays = m_nCurrentTotalYearDays + 1 - day - before;
	
	COleDateTimeSpan sp= COleDateTimeSpan::COleDateTimeSpan(CorrectDays,0,0,0);
	m_newTime += sp;
	
	m_pCanlendar.SetTime(m_newTime);
	m_pCanlendar.m_sCheckTime = m_newTime.Format();
	UpdateData(FALSE);
}

void CStaticCalendarDlg::OnButton_DecYear() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int m=m_newTime.GetYear() - 1;
    int before=m_pCanlendar.GetAllMonthDaysBefore(m_newTime);
	int m_nLastTotalYearDays = 365;
	if(m % 4 ==0 && m % 100 !=0 || m % 400 ==0) 
	{
		m_nLastTotalYearDays++;
	}
	int CorrectDays = m_nLastTotalYearDays + before ;
	COleDateTimeSpan sp= COleDateTimeSpan::COleDateTimeSpan(CorrectDays,0,0,0);
	m_newTime -= sp;

	m_pCanlendar.SetTime(m_newTime);
	m_pCanlendar.m_sCheckTime = m_newTime.Format();
	UpdateData(FALSE);
}


int CStaticCalendarDlg::OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnCharToItem(nChar, pListBox, nIndex);
}

void CStaticCalendarDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}



//DEL int CStaticCalendarDlg::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 	return CDialog::OnCompareItem(nIDCtl, lpCompareItemStruct);
//DEL }



//DEL void CStaticCalendarDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
//DEL {
//DEL 	// TODO: Add your message handler code here
//DEL 	
//DEL }



LRESULT CStaticCalendarDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	COleDateTime m_setNewTime;
	m_setNewTime = COleDateTime::GetCurrentTime();
	switch( message )
	{
	case(WM_SINGLE_SELECT_DAY_UPDATECURRENT):
		{
			m_newTime = m_setNewTime;
	    	UpdateData(FALSE);
			break;
		}
/*	case(WM_SINGLE_SELECT_DAY_UPDATEFORMER):
		{
            m_newTime.SetDate(m_setNewTime.GetYear(),m_setNewTime.GetMonth()-1,m_setNewTime.GetDay());
	        UpdateData(FALSE);
        	break;
		}
	case(WM_SINGLE_SELECT_DAY_UPDATELATTER):
		{
            m_newTime.SetDate(m_setNewTime.GetYear(),m_setNewTime.GetMonth()+1,m_setNewTime.GetDay());
	        UpdateData(FALSE);
        	break;
		}
*/
/*	case(WM_SINGLE_SELECT_BIRTHDAY):
		{
			MessageBox("OH",0);
			break;
		}
	case(WM_SINGLE_SELECT_NOTE):
		{
			MessageBox("OH",0);
			break;
		}
	case(WM_SINGLE_SELECT_JOURNAL):
		{
			MessageBox("OH",0);
			break;
		}
*/
    default:
		return CDialog::DefWindowProc(message, wParam, lParam);
	}
}



void CStaticCalendarDlg::OnDouSelTime()
{

}

void CStaticCalendarDlg::OnDouSelAnoTime(WPARAM wPa, LPARAM lPa)
{
	CMyDlg dlg;
	CString* Date=(CString*)wPa;
	dlg.m_usersname=m_username;
	dlg.DiaryFlag=1;
	CString date=*Date;
	date=date.Right(10);
	dlg.DiaryDate=date;   //  从日历获得的日期
	dlg.DoModal();

}

void CStaticCalendarDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
	
}

void CStaticCalendarDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	SetDlgItemText(IDC_CHECK1, m_FirstDay.GetPress()?"前置星期天":"星期天后置");
	m_pCanlendar.m_bFirstDay = m_FirstDay.GetPress();
	//	m_pCanlendar.(m_FirstDay.GetPress()) = m_bFirstDay;
	m_pCanlendar.Invalidate();
	
}

void CStaticCalendarDlg::Holiday()
{
	//获取当前日期不需要年份
	int i = 0;
	int flag = 0;
	CString tempHold = "";
	for(; i<m_sHoliday.GetLength() && m_sHoliday.GetAt(i) != ' '; i++)
	{
		if(m_sHoliday.GetAt(i) == '-')
		{
			flag = 1;
		}
		if(flag == 1)
		{
			tempHold+=m_sHoliday.GetAt(i);
		}
	}

	//读取数据库并转换类型
	CAdo ado;
    ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();
	CString sql = "select * from Holiday";
	pRecordset = ado.OpenRecordset(sql);
	_variant_t cHoliday;
	_variant_t cHolidayName;
	if(pRecordset->RecordCount != 0)
	{
		pRecordset->MoveFirst();
	}
	int CountNo = 0;
	while (!pRecordset->adoEOF)
	{
		cHoliday= pRecordset->GetCollect("日期");
		cHolidayName = pRecordset->GetCollect("节日");
		m_sHoliday = VariantToString(cHoliday);
		m_sHoliday.Insert(0,'-');
		CString m_sHolidayName = VariantToString(cHolidayName);
		
		if( m_sHoliday == tempHold )
		{
			CString Hello = "你好，";
			CString Happy = "快乐。";
			m_sHoliday = Hello + m_sHolidayName + Happy;
		//	UpdateData(FALSE);
			break;
		}

		CountNo;
		pRecordset->MoveNext();	
                
	}
    // m_sHoliday="Hello Baby";
	 UpdateData(FALSE);
}


CString CStaticCalendarDlg::VariantToString(VARIANT var)
{
	CString strValue;
	_variant_t var_t;
	_bstr_t bstr_t;
	time_t cur_time;
	CTime time_value;
	COleCurrency var_currency;
	switch(var.vt)
	{
	case VT_EMPTY:
	case VT_NULL:strValue=_T("");break;
	case VT_UI1:strValue.Format("%d",var.bVal);break;
	case VT_I2:strValue.Format("%d",var.iVal);break;
	case VT_I4:strValue.Format("%d",var.lVal);break;
	case VT_R4:strValue.Format("%f",var.fltVal);break;
	case VT_R8:strValue.Format("%f",var.dblVal);break;
	case VT_CY:
		var_currency=var;
		strValue=var_currency.Format(0);break;
	case VT_BSTR:
		var_t =var;
		bstr_t=var_t;
		strValue.Format("%s",(const char *)bstr_t);break;
	case VT_DATE:
		cur_time=var.date;
		time_value=cur_time;
		strValue.Format("%A,%B,%d,%Y");break;
	case VT_BOOL:strValue.Format("%d",var.boolVal);break;
	default:strValue=_T("");break;
	}
	return strValue;

}

