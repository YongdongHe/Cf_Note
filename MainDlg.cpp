// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "MainDlg.h"
#include "ClientDlg.h"
#include "DiaryDlg.h"
#include "MUSICDlg.h"
#include "定时提醒Dlg.h"
#include "Setting.h"
#include "stdlib.h"
#include "Ado.h"
#include "Tip.h"
#include "StaticCalendarDlg.h"
#include "wingdi.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog
DWORD _stdcall Thread_TipFunc(LPVOID pParam);

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
	//}}AFX_DATA_INIT

}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_BUTTON_MINI, m_Button_MainMini);
	DDX_Control(pDX, IDC_BUTTON_Calendar, m_Button_Calendar);
	DDX_Control(pDX, IDC_BUTTON_Setting, m_Button_Setting);
	DDX_Control(pDX, IDC_BUTTON_Diary, m_Button_Diary);
	DDX_Control(pDX, IDC_Button_MainClose, m_Button_MainClose);
	DDX_Control(pDX, IDC_BUTTON_Memorandum, m_Button_Memorandum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_BN_CLICKED(IDC_BUTTON_Diary, OnBUTTONDiary)
	ON_BN_CLICKED(IDC_BUTTON_Setting, OnBUTTONSetting)
	ON_BN_CLICKED(IDC_BUTTON_Memorandum, OnBUTTONMemorandum)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Button_MainClose, OnButtonMainClose)
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Calendar, OnBUTTONCalendar)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_MINI, OnButtonMini)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	//任务栏托盘图标
	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
    m_nid.hWnd    = this->m_hWnd;
    m_nid.uID     = IDR_MAINFRAME;
    m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
    m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
    m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
    strcpy(m_nid.szTip, "CF日记");                // 信息提示条为"服务器程序"，VS2008 UNICODE编码用wcscpy_s()函数
    Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标
	/////////////////////////////////////////////////////////////////////////
	m_bmp_Mainbg.LoadBitmap(IDB_BITMAP_MainDlgbg);

	m_Button_Calendar.LoadOnBitmap(IDB_BITMAP_WhiteBrush);
	m_Button_Calendar.LoadLightBitmap(IDB_BITMAP_WhiteBrush);
	m_Button_Calendar.LoadOffBitmap(IDB_BITMAP_WhiteBrush);
	m_Button_Calendar.SetTextClr(RGB(0,0,0));



	m_Button_Memorandum.LoadOnBitmap(IDB_BITMAP_Main_Note3);//通讯录按钮加载
	m_Button_Memorandum.LoadLightBitmap(IDB_BITMAP_Main_Note2);
	m_Button_Memorandum.LoadOffBitmap(IDB_BITMAP_Main_Note1);
	
	m_Button_MainClose.LoadOnBitmap(IDB_BITMAP_Main_Close3);//关闭按钮加载
	m_Button_MainClose.LoadLightBitmap(IDB_BITMAP_Main_Close2);
	m_Button_MainClose.LoadOffBitmap(IDB_BITMAP_Main_Close1);

	m_Button_MainMini.LoadOnBitmap(IDB_BITMAP_MainMini3);//最小化按钮加载
	m_Button_MainMini.LoadLightBitmap(IDB_BITMAP_MainMini2);
	m_Button_MainMini.LoadOffBitmap(IDB_BITMAP_MainMini1);

	
	m_Button_Diary.LoadOnBitmap(IDB_BITMAP_Main_Diary3);//日记按钮加载
	m_Button_Diary.LoadLightBitmap(IDB_BITMAP_Main_Diary2);
	m_Button_Diary.LoadOffBitmap(IDB_BITMAP_Main_Diary1);
	
	m_Button_Setting.LoadOnBitmap(IDB_BITMAP_Main_Set3);//设置按钮加载
	m_Button_Setting.LoadLightBitmap(IDB_BITMAP_Main_Set2);
	m_Button_Setting.LoadOffBitmap(IDB_BITMAP_Main_Set1);
	int Ii=m_ClientDlg.DoModal();
	if (Ii==IDCANCEL)
	{
		SendMessage(WM_CLOSE);
	}


		
	ShowMotto();

	
	SetTimer(1,900,NULL);


	CStatic* pSta=(CStatic*)GetDlgItem(IDC_STATIC_Motto);

	AddFontResource("博洋行书7000.TTF");
	::SendMessage(HWND_BROADCAST,WM_FONTCHANGE,0,0);
	AddFontResource("華康童童體.ttc");
	::SendMessage(HWND_BROADCAST,WM_FONTCHANGE,0,0);

    m_font_motto.CreatePointFont(270,"hakuyoxingshu7000");
    pSta->SetFont(&m_font_motto);

	CStatic* pStat=(CStatic*)GetDlgItem(IDC_STATIC_GREET);

	m_font_greet.CreatePointFont(200,"華康童童體");
    pStat->SetFont(&m_font_greet);

	    m_font="楷体";
		CButton* pBut=(CButton*)GetDlgItem(IDC_BUTTON_Calendar);
		m_Buttonfont.CreatePointFont(170, "華康童童體");
	    pBut->SetFont(&m_Buttonfont);
//	m_Button_Calendar.SetFont(&m_Buttonfont);
//  设置日历按钮上的字体，以及将上面的文字改成当天日期
	CString strrM,m_Today;
	GetLocalTime(&Time1);

	strrM.Format("%02d",Time1.wMonth);
	m_Today+=strrM+"-";
	strrM.Format("%02d",Time1.wDay);
	m_Today+=strrM;


	SetDlgItemText(IDC_BUTTON_Calendar,m_Today); 


	CDialog::OnInitDialog();
	return TRUE;
}

void CMainDlg::OnBUTTONDiary() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CDiaryDlg Dlg;
	Dlg.m_font=m_font;
	Dlg.m_username=m_ClientDlg.m_Admin;
	Dlg.DoModal();
	ShowWindow(SW_SHOW);
}

void CMainDlg::OnBUTTONSetting() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CSetting dlg;
	dlg.m_username=m_ClientDlg.m_Admin;
	
	dlg.DoModal();
	m_font=dlg.m_font;
	ShowWindow(SW_SHOW);
	
}

void CMainDlg::OnBUTTONMemorandum() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CMyDlg dlg;
	dlg.m_font=m_font;
	dlg.DiaryFlag=0;

	dlg.m_usersname=m_ClientDlg.m_Admin;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
	
}

void CMainDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

		BITMAP bm;
		CRect rect;
		CDC dcMem;
		m_bmp_Mainbg.GetBitmap (&bm);
		GetClientRect(&rect);
		dcMem.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem.SelectObject (&m_bmp_Mainbg);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(oldbitmap);              //重绘背景
		CDialog::OnPaint();
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CMainDlg::OnButtonMainClose() 
{
	// TODO: Add your control notification handler code here
		CAdo ado;
	_RecordsetPtr pRecordset_kk;
		ado.OnInitAdoConn();
	
	CString sql_hh = "select * from cli where 用户名 ='"+ m_ClientDlg.m_Admin +"'";
	pRecordset_kk=ado.OpenRecordset(sql_hh);

	if(pRecordset_kk->RecordCount>0)
	{
		pRecordset_kk->PutCollect("检索登录",(_bstr_t)"否");
		pRecordset_kk->Update();
	}
		ado.ExitConnection();
	CDialog::OnCancel();
	
}

UINT CMainDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
 //return CDialog::OnNcHitTest(point);
}

void CMainDlg::ShowMotto()
{
	CAdo ado;
	SYSTEMTIME Time;
	ado.OnInitAdoConn();
	_RecordsetPtr	m_pRecordset= ado.OpenRecordset("select * from Motto");
	
	m_pRecordset->MoveFirst();
	_variant_t cMotto;
	srand(time(0));

	int i=rand()%50;
	int j=0;
	while (i>j)
	{
		m_pRecordset->MoveNext();
		j++;
	}
		//测试获取字段值
		cMotto = m_pRecordset->GetCollect("每日一语");
		CString mot;
		mot=(LPCTSTR)(_bstr_t)cMotto;
		mot="    "+mot;
		GetDlgItem(IDC_STATIC_Motto)->SetWindowText(mot);

				GetLocalTime(&Time);
		CString str;
		int hour=Time.wHour;
		switch (hour/6)
		{
		case 0:
			str="早上好!";
			break;
		case 1:
			str="上午好!";
				break;
		case 2:
			str="下午好!";
				break;
		case 3:
			str="晚上好!";
			break;
		default:
			break;
		}
 CString sql="select * from cli where 用户名='"+m_ClientDlg.m_Admin+"'";
        m_pRecordset = ado.OpenRecordset(sql);
		_variant_t csNickname;
        csNickname=m_pRecordset->GetCollect("昵称");
		if(csNickname.vt!=VT_NULL)
		{
			CString nickName=(TCHAR*)(_bstr_t)csNickname;
			if(nickName=="")
			{
				str+=m_ClientDlg.m_Admin;
			}
			if(nickName!="")
			{
				str+=nickName;
			}
		}
		else
		{
			str+=m_ClientDlg.m_Admin;
		}



	//获取当前日期不需要年份
/*	int i = 0;
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

*/	CString strrM,m_Today;
	GetLocalTime(&Time1);

	strrM.Format("%d",Time1.wMonth);
	m_Today+=strrM+"-";
	strrM.Format("%d",Time1.wDay);
	m_Today+=strrM;
//	m_Today="-"+m_Today;


	//读取数据库并转换类型
	ado;
    ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();
	CString sql_H = "select * from Holiday";
	pRecordset = ado.OpenRecordset(sql_H);
	_variant_t cHoliday;
	_variant_t cHolidayName;
	if(pRecordset->RecordCount != 0)
	{
		pRecordset->MoveFirst();
	}
	int CountNo = 0;
	CString m_sHoliday,m_sHolidayName;
	while (!pRecordset->adoEOF)
	{
		cHoliday= pRecordset->GetCollect("日期");
		cHolidayName = pRecordset->GetCollect("节日");
		m_sHoliday =(TCHAR*)(_bstr_t)cHoliday;
		m_sHolidayName = (TCHAR*)(_bstr_t)cHolidayName;
		
		if( m_sHoliday == m_Today )
		{
			CString Hello = "你好,";
			CString Happy = "快乐!";
			m_sHolidayName = Hello + m_sHolidayName + Happy;
			str=m_sHolidayName;
		//	UpdateData(FALSE);
			break;
		}

		
		pRecordset->MoveNext();	
                
	}


		GetDlgItem(IDC_STATIC_GREET)->SetWindowText(str);
		ado.ExitConnection();

}

DWORD _stdcall Thread_TipFunc(LPVOID pParam)
{
    CMyDlg dlg;
//	dlg.m_usersname=m_ClientDlg.m_Admin;
//	GetDlgItem
//	SetTimer()
	
	dlg.OnInitDialog();
	SetTimer(dlg.hWnd,1,900,NULL);
	return 0;

}



HBRUSH CMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor== CTLCOLOR_STATIC) 
    { 

        pDC->SetBkMode(TRANSPARENT);//设置背景模式为透明
        return (HBRUSH)GetStockObject(NULL_BRUSH);//返回一个空画刷
    }
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CMainDlg::OnTimer(UINT nIDEvent)
{
/*	CDialog::OnTimer(nIDEvent);
		
    if(nIDEvent==1)
	{	
		SYSTEMTIME st;
	    ::GetLocalTime(&st);
	    CString nDate,nTime,str;
        nDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
        nTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);	
		//获取现在的时分秒
		int year,month,day,hour,minute,second;
		year=_ttoi(nDate.Left(4));
        str=nDate.Left(7);
		month=_ttoi(str.Right(2));
		day=_ttoi(nDate.Right(2));

		hour=_ttoi(nTime.Left(2));
		str=nTime.Left(5);
		minute=_ttoi(str.Right(2));
		second=_ttoi(nTime.Right(2));
        //连接数据库
        CAdo ado;
	
	    ado.OnInitAdoConn();
	    _RecordsetPtr pRecordset = ado.GetRecordset();

	    pRecordset = ado.OpenRecordset("select * from users");

	    if(pRecordset->RecordCount>0)
		{
			pRecordset->MoveFirst();
	
	        CString cDate,cTime,cThing,cstr;
	        int year1,month1,day1,hour1,minute1;
			int i=0;
	        while (!pRecordset->adoEOF)
			{
				cDate= (char*)(_bstr_t)pRecordset->GetCollect("日期");
		        cTime = (char*)(_bstr_t)pRecordset->GetCollect("时间");
	    	    cThing = (char*)(_bstr_t)pRecordset->GetCollect("事件");
                //分解时分秒
		        year1=_ttoi(cDate.Left(4));
                cstr=cDate.Right(cDate.GetLength()-1-cDate.Find('/'));
				month1=_ttoi(cstr.Left(cstr.Find('/')));
                day1=_ttoi(cstr.Right(cstr.GetLength()-1-cstr.Find('/')));

				hour1=_ttoi(cTime.Left(cTime.Find(':')));
                cstr=cTime.Right(cTime.GetLength()-1-cTime.Find(':'));
				minute1=_ttoi(cstr.Left(cstr.Find(':')));

				if(year==year1 && month==month1 && day==day1 && hour==hour1 &&minute==minute1&&second==0)	
				{
					CTip tip;
					tip.tipContent=cThing;
                    tip.tipTime=cTime;

					tip.DoModal();

				}

			    pRecordset->MoveNext();
			}
		}
	    ado.ExitConnection();
	}
	*/
	CDialog::OnTimer(nIDEvent);
		
    if(nIDEvent==1)
	{	
		SYSTEMTIME st;
	    ::GetLocalTime(&st);
	    CString nDate,nTime,str;
        nDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
        nTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);	
		//获取现在的时分秒
		int year,month,day,hour,minute,second;
		year=_ttoi(nDate.Left(4));
        str=nDate.Left(7);
		month=_ttoi(str.Right(2));
		day=_ttoi(nDate.Right(2));

		hour=_ttoi(nTime.Left(2));
		str=nTime.Left(5);
		minute=_ttoi(str.Right(2));
		second=_ttoi(nTime.Right(2));
        //连接数据库
        CAdo ado;
	
	    ado.OnInitAdoConn();
	    _RecordsetPtr pRecordset = ado.GetRecordset();

	    pRecordset = ado.OpenRecordset("select * from users where 用户='"+m_ClientDlg.m_Admin+"'");

	    if(pRecordset->RecordCount>0)
		{
			pRecordset->MoveFirst();
	
	        CString cDate,cTime,cThing,cstr,setalarm;
	        int year1,month1,day1,hour1,minute1;
	        while (!pRecordset->adoEOF)
			{
				cDate= (char*)(_bstr_t)pRecordset->GetCollect("日期");
		        cTime = (char*)(_bstr_t)pRecordset->GetCollect("时间");
	    	    cThing = (char*)(_bstr_t)pRecordset->GetCollect("事件");
                setalarm=(char*)(_bstr_t)pRecordset->GetCollect("设置");
                //分解时分秒
		        year1=_ttoi(cDate.Left(4));
                cstr=cDate.Right(cDate.GetLength()-1-cDate.Find('/'));
				month1=_ttoi(cstr.Left(cstr.Find('/')));
                day1=_ttoi(cstr.Right(cstr.GetLength()-1-cstr.Find('/')));

				hour1=_ttoi(cTime.Left(cTime.Find(':')));
                cstr=cTime.Right(cTime.GetLength()-1-cTime.Find(':'));
				minute1=_ttoi(cstr.Left(cstr.Find(':')));

				if(year==year1 && month==month1 && day==day1 && hour==hour1 &&minute==minute1&&second==0&&setalarm=="是")	
				{
					CTip tip;
					tip.tipContent=cThing;
                    tip.tipTime=cTime;
					tip.usersname=m_ClientDlg.m_Admin;
					tip.DoModal();
				}

			    pRecordset->MoveNext();
			}
		}
	    ado.ExitConnection();
	}

	}
		


void CMainDlg::OnBUTTONCalendar() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CStaticCalendarDlg dlg;
	dlg.m_username=m_ClientDlg.m_Admin;

	dlg.DoModal();
	ShowWindow(SW_SHOW);
	
}



void CMainDlg::OnSize(UINT nType, int cx, int cy) 
{
	
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	if(nType == SIZE_MINIMIZED)  
	{  
		ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口              
  
	}  
	
	// TODO: Add your message handler code here
	
}

BOOL CMainDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	Shell_NotifyIcon(NIM_DELETE, &m_nid);             
	return CDialog::DestroyWindow();
}

LRESULT CMainDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:                                        // 右键起来时弹出菜单
		{
			
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // 得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();                    // 声明一个弹出式菜单
			menu.AppendMenu(MF_STRING, WM_DESTROY, "关闭");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
		{
			this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口
		}
		break;

	case WM_LBUTTONUP:
		{
			ShowWindow(SW_SHOW);
		}
		break;
	}
	return 0;
    }

void CMainDlg::OnButtonMini() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}
