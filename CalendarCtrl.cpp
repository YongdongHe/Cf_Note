// CalendarCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "SkinTAB.h"
#include "CalendarCtrl.h"
#include "Resource.h"
#include "Ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CALENDAR_X_GRID_TIME 7
#define CALENDAR_Y_GRID_TIME 7

/////////////////////////////////////////////////////////////////////////////
// CCalendarCtrl

CCalendarCtrl::CCalendarCtrl()
{
	m_clrBack = RGB(150,50,80);
	m_clrBackHeader = RGB(20,100,20);;
	m_clrTextHeader = RGB(255,255,255);	
	m_clrTextRest = RGB(255,0,0);
	m_clrText = RGB(0,0,0);
	m_clrActive = RGB(0,0,255);
	m_clrActiveBk = RGB(49,196,232);
	m_clrToday = RGB(100,0,100);
	m_clrTextLunar =RGB(150,54,255);
	m_clrTextSolor =  RGB(150,0,100);
	m_clrLine = RGB(200,200,255);
	m_clrLunor = RGB(70,50,80);

	m_bFirstDay = TRUE;	
	m_nCurrentIndex = 0;
	m_nFirstDay = 0;
	m_Time = COleDateTime::GetCurrentTime();
}

CCalendarCtrl::~CCalendarCtrl()
{
}


BEGIN_MESSAGE_MAP(CCalendarCtrl, CStatic)
	//{{AFX_MSG_MAP(CCalendarCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_KEYUP()
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarCtrl message handlers

void CCalendarCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if(dc)
		DrawCanlendar(&dc);	
}

void CCalendarCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CCalendarCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	
}

void CCalendarCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	OnPaint();
}

//////////////////////////////////////////////////////////////////////////
// 内存画图, 以防闪烁 [Juncox 2009年4月23日 15:32:06]
 void CCalendarCtrl::DrawCanlendar(CPaintDC* pWinDC)
{
	//-----------------------------------------------------------
	// 建立画板 [Juncox 2009年4月23日 15:31:49]
	CRect rtWnd;	GetClientRect(&rtWnd);
	CDC* pMemDC=new CDC;	
	pMemDC->CreateCompatibleDC(pWinDC);
	CBitmap bmp;	bmp.CreateCompatibleBitmap(pWinDC,rtWnd.Width(),rtWnd.Height());
	pMemDC->SelectObject(bmp);
	//-----------------------------------------------------------
	// 画背景 [Juncox 2009年4月23日 15:30:46]
	CBitmap bitmap;
	if(m_bFirstDay == TRUE)
	{
		bitmap.LoadBitmap(IDB_BITMAP_Sunday1);
	}
	else
	{
		bitmap.LoadBitmap(IDB_BITMAP_Sunday2);
	}
	CBrush* Brush=new CBrush(&bitmap);
	CBrush* pOldBrush = pMemDC->SelectObject(Brush);
	COLORREF pOldColor= pMemDC->GetTextColor();
	pMemDC->FillRect(rtWnd,Brush);
	//-----------------------------------------------------------
	// 分格 [Juncox 2009年4月23日 15:40:16]
	int xCon = CALENDAR_X_GRID_TIME, yCon = CALENDAR_Y_GRID_TIME;
	double xStep =(double) rtWnd.Width()/xCon;	
	double yStep =(double) rtWnd.Height()/7;

	CFont cFont;
	cFont.CreateFont((int)(rtWnd.Height()/8), 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, "宋体");		
	//-----------------------------------------------------------
	// 画标题 [Juncox 2009年4月23日 16:03:02]	
	{
		//-----------------------------------------------------------
		// 画方格 [Juncox 2009年4月23日 18:06:58]
		Brush->Detach(); delete Brush; Brush =new CBrush(m_clrLine); pMemDC->SelectObject(Brush);
		pMemDC->FrameRect(rtWnd,Brush);
		// use the pen to draw the lines so that you can change the color of the lines

		CPen pen(PS_SOLID, 1, m_clrLine);
		CPen *pOldPen = pMemDC->SelectObject(&pen);
		for(int i=0; i<xCon; i++)
		{
			//double temp = yStep*1.2;
			for(int j=1; j<yCon; j++)
			{
				pMemDC->MoveTo((int)((i+1)*xStep), (int)(j*yStep));
				pMemDC->LineTo((int)(i*xStep), (int)(j*yStep));
				pMemDC->LineTo((int)(i*xStep), (int)((j+1)*yStep));
			}
		}
		pMemDC->SelectObject(pOldPen);
			
		CString sInfo[] = {"日","一","二","三","四","五","六","日"};
		CRect rW;
		Brush->Detach(); delete Brush; Brush =new CBrush(RGB(255,255,0)); pMemDC->SelectObject(Brush);
		rW = rtWnd;		rW.bottom =(int) yStep;
		//pMemDC->FillRect(rW,Brush);
		pMemDC->SetTextColor(RGB(255,255,255));//m_clrTextHeader);
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SelectObject(cFont);
		
		/*for(i=0; i<7; i++)
		{
			rW.left = (int)( i*xStep );		rW.top = 0;
			rW.right= (int)((i+1)*xStep);	rW.bottom = (int)yStep;
			if(m_bFirstDay)
				pMemDC->DrawText(sInfo[i],rW,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			else
				pMemDC->DrawText(sInfo[i+1],rW,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}*/		
		cFont.Detach();
		
		//-----------------------------------------------------------
		// 建立字体 [Juncox 2009年4月23日 16:39:14]
		cFont.CreateFont((int)(yStep/2), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH,"Candara");
		Brush->Detach(); delete Brush; Brush =new CBrush(m_clrBack); pMemDC->SelectObject(Brush);
		pMemDC->SelectObject(cFont);

		

		int iY = m_Time.GetYear();
		int iM = m_Time.GetMonth();		
		CString sFirstDay;
		sFirstDay.Format("%04d-%02d-01",iY,iM);
		COleDateTime tFirst;
		tFirst.ParseDateTime((LPCTSTR)sFirstDay);
		int iTotalDay = GetMonthDays(tFirst);		

		int iFDay = tFirst.GetDayOfWeek()-1;
		m_nFirstDay = iFDay;
		int iLine=(i+iFDay-1)/7;
		if(iLine == 0) iLine =1;
		int iCol=iFDay;

		int nCurrentDay = 0;
		{
			COleDateTime tm = COleDateTime::GetCurrentTime();
			if( tm.GetYear() == m_Time.GetYear() &&
				tm.GetMonth()== m_Time.GetMonth())
				nCurrentDay = tm.GetDay();
		}
		//Week
		CString m_sFirstDayCheck = "";
		CString m_sLastDayCheck = "";
		CString m_sTempHoldTotalDay = "";
		//CString m_temp = m_sCheckTime;

		for(int p = 0; p < m_sCheckTime.GetLength() && m_sCheckTime.GetAt(p)!= ' '; p++)
		{
			if(m_sCheckTime.GetAt(p) == '-')
			{
				m_sCheckTime.SetAt(p,'/');
			}
		}
		//CString strTemp = m_sCheckTime;

        m_sTempHoldTotalDay.Format("%d",iTotalDay);
		m_sFirstDayCheck = m_sCheckTime.Left(7) + "01";
		if(m_sFirstDayCheck.GetAt(6) == '/')
		{
			m_sFirstDayCheck.Insert(5,'0');
		}
		else
		{
            m_sFirstDayCheck.Insert(7,"/");
		}
		m_sLastDayCheck = m_sCheckTime.Left(7) + m_sTempHoldTotalDay;
		if(m_sLastDayCheck.GetAt(6) == '/')
		{
			m_sLastDayCheck.Insert(5,'0');
		}
		else
		{
            m_sFirstDayCheck.Insert(7,"/");
		}

		CAdo ado;
        ado.OnInitAdoConn();
	    _RecordsetPtr pRecordset = ado.GetRecordset();

		_RecordsetPtr pRecordset_NameCheck = ado.GetRecordset();
		//_RecordsetPtr pRecordset_Birthday = ado.GetRecordset();

		CString sql_Name = "select * from cli where 检索登录='是'";
		pRecordset_NameCheck = ado.OpenRecordset(sql_Name);
		//pRecordset_Birthday = ado.OpenRecordset(sql_Name);
		_variant_t cName;
		//_variant_t cBirthday;
		cName= pRecordset_NameCheck->GetCollect("用户名");
		//cBirthday = pRecordset_NameCheck->GetCollect("生日");
//		CString m_sBirthday = VariantToString(cBirthday);

		/*if(m_sCheckTime.GetAt(6) == '/')
		{
			m_sCheckTime.Insert(5,'0');
		}
		if(m_sCheckTime.GetAt(8) !='0')
		{
			m_sCheckTime.Insert(8,'0');
		}
		*/
		//m_sCheckTime.Left(10);
		/*CString m_stempHoldTime = "";
		int m = 0;
		for(; m<10;m++)
		{
			m_stempHoldTime += m_sCheckTime.GetAt(m);
		}

		if(m_sBirthday == m_stempHoldTime)
		{
			pMemDC->SetTextColor(RGB(255,255,0));
			pMemDC->DrawText("o",rW,DT_CENTER|DT_SINGLELINE|DT_BOTTOM|DT_LEFT);
			pMemDC->SetTextColor(RGB(0,255,0));
			pMemDC->DrawText("o",rW,DT_CENTER|DT_SINGLELINE|DT_BOTTOM|DT_RIGHT);
			pMemDC->SetTextColor(RGB(255,0,0));
			pMemDC->DrawText("o",rW,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_LEFT);
			pMemDC->SetTextColor(RGB(0,0,255));
			pMemDC->DrawText("o",rW,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_RIGHT);
		}
		*/

		//cName = (TCHAR*)(_bstr_t)pRecordset_NameCheck->GetCollect("用户名");
		CString m_sName = VariantToString(cName); 
		

		CString sql = "select * from set01 where (备忘录='是' or 日记='是') and (日期>='" + m_sFirstDayCheck + "' and 日期<='"+m_sLastDayCheck+"') and 用户='"+m_sName+"'";
	   // pRecordset = ado.OpenRecordset("select * from 呆呆良 where 日程='是' or 日记='是' and m_sFirstDayCheck<=时间 and 时间<=m_sLastDayCheck");
	    pRecordset = ado.OpenRecordset(sql);

	  // pRecordset->MoveFirst();
	
	    _variant_t cTime, cNote, cJournal;

		for(i = 1; i<= iTotalDay; i++)
		{
			if(iCol>=7)
			{
				iCol=0;
				iLine++;
			}
			if(iCol==6 || iCol==0)
				pMemDC->SetTextColor(m_clrTextRest);
			else
				pMemDC->SetTextColor(m_clrText);
			
			int iNcol = iCol;
			int iNLin = iLine;
			if(!m_bFirstDay)
			{
				iNcol -= 1;
				if(iNcol<0)
				{
					iNcol=6;
					iNLin-=1;
				}
			}
			if(iNLin>=CALENDAR_Y_GRID_TIME) iNLin = 1;
			if(iNLin<1){
				iLine++;
				iNLin =1;
			}
			rW.left =(int)(iNcol  * xStep);	rW.right=(int)((iNcol+1) * xStep);
			rW.top = (int)(iNLin * yStep);	rW.bottom=(int)((iNLin+1)* yStep);	
			//Select
	    	if(i == m_nCurrentIndex)
			{
				pMemDC->SetTextColor(m_clrActive);
				Brush->Detach(); delete Brush; Brush =new CBrush(m_clrActiveBk); pMemDC->SelectObject(Brush);
				pMemDC->FrameRect(rW,Brush);
			}
			//Current
			if(i == nCurrentDay)
			{
				pMemDC->SetTextColor(m_clrToday);
				Brush->Detach(); delete Brush; Brush =new CBrush(m_clrActiveBk); pMemDC->SelectObject(Brush);
				rW.left+=1;	rW.right-=1; rW.top+=1;	rW.bottom-=1;
				pMemDC->FillRect(rW,Brush);
			}
			//Current & Select
			if(m_nCurrentIndex==i && nCurrentDay==i)
				pMemDC->SetTextColor(m_clrActive);

			//CString sTip1 = "";
			//CString sTip2 = "";
			CString sTip = "";
			CString sNow=""; 
			{
				sNow.Format("%d-%d-%d 0:0:1",m_Time.GetYear(),m_Time.GetMonth(),i);
				COleDateTime tNow;		tNow.ParseDateTime(sNow);
				SYSTEMTIME tmNow={0};	tNow.GetAsSystemTime(tmNow);
				SYSTEMTIME tmLun={0};
				BOOL bLeapYear=FALSE;
				sNow ="";
				if(Gregorian2Lunar(&tmNow,&tmLun,&bLeapYear))
					sNow = GetLunarString(&tmLun,bLeapYear,FALSE);
				if(tmLun.wDay == 1)
					pMemDC->SetTextColor(m_clrTextLunar);
			}
            pMemDC->SetTextColor(RGB(11,10,12));
			sTip.Format("%d\n",i);
			pMemDC->DrawText(sTip,rW,DT_CENTER|DT_VCENTER);
		 
			cFont.Detach();
			cFont.CreateFont((int)(yStep/4), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		    DEFAULT_QUALITY, DEFAULT_PITCH,"方正舒体");
		    /*Brush->Detach(); delete Brush; Brush =new CBrush(RGB(255,0,0)); pMemDC->SelectObject(Brush);*/
			pMemDC->SetTextColor(RGB(130,131,132));
		    CFont* pOldFont = pMemDC->SelectObject(&cFont);

			sTip = "";
			sTip.Format("%s\n",sNow);
		    pMemDC->DrawText(sTip,rW,DT_CENTER|DT_SINGLELINE|DT_VCENTER);

			pMemDC->SelectObject(pOldFont);
			 	
        	int ItemOfNO=0;
	        CString tempHold_cTime ="";
			int count = pRecordset->RecordCount;
			if(count != 0)
			{
		 		pRecordset->MoveFirst();
			}

			CString cNoteYes = "是";
			CString cJournalYes = "是";
			CString cNoteNo = "否";
			CString cJournalNo = "否";

        	while (!pRecordset->adoEOF)
			{
		        cTime = pRecordset->GetCollect("日期");
				tempHold_cTime = (char *)(_bstr_t)cTime;
				int theDay = atoi(tempHold_cTime.Right(2));
				if(theDay == i)
				{
					cNote = pRecordset->GetCollect("备忘录");
		            cJournal = pRecordset->GetCollect("日记");

					/*
				    int NoteCheck = _ttoi((TCHAR*)(_bstr_t)cNote);
			    	int JournalCheck =  _ttoi((TCHAR*)(_bstr_t)cJournal);
					*/
                    
	
                    if((_bstr_t)cNote == cNoteYes && (_bstr_t)cJournal == cJournalYes)
					{
						pMemDC->SetTextColor(RGB(0,255,0));
			            pMemDC->DrawText("o",rW,DT_CENTER|DT_SINGLELINE|DT_BOTTOM);
					}
				    else if((_bstr_t)cNote == cNoteNo && (_bstr_t)cJournal == cJournalYes)
					{
					    pMemDC->SetTextColor(RGB(188,73,183));
			            pMemDC->DrawText("o",rW,DT_CENTER|DT_SINGLELINE|DT_BOTTOM);
					}
				    else if((_bstr_t)cNote == cNoteYes && (_bstr_t)cJournal == cJournalNo)
					{
				    	pMemDC->SetTextColor(RGB(255,0,0));
			            pMemDC->DrawText("o",rW,DT_CENTER|DT_SINGLELINE|DT_BOTTOM);
					}
				}

		        ItemOfNO++;
		        pRecordset->MoveNext();	
                
			}
			iCol++;
		}
	ado.ExitConnection();	
	}

	//-----------------------------------------------------------
	//  [Juncox 2009年4月23日 15:30:50]
	//DrawTitleBar(pMemDC);
	pWinDC->BitBlt(rtWnd.left,rtWnd.top,rtWnd.Width(),rtWnd.Height(),pMemDC,0,0,SRCCOPY);
	//-----------------------------------------------------------
	// 恢复原状 [Juncox 2009年4月23日 16:12:23]
	pMemDC->SetTextColor(pOldColor);
	pMemDC->SelectObject(pOldBrush);
	//-----------------------------------------------------------
	// 释放内存 [Juncox 2009年4月21日 20:02:58]
	cFont.Detach();
	Brush->Detach(); 
	delete Brush;
	ReleaseDC(pMemDC);
	delete pMemDC;
}

void CCalendarCtrl::SetTime(COleDateTime newTime)
{
	m_Time=newTime;
	Invalidate(TRUE);
}

void CCalendarCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rct,rctWin;
	GetClientRect(rctWin);
	if(rctWin.PtInRect(point))
	{
		int xCon = (point.x - rctWin.left) *  CALENDAR_X_GRID_TIME / rctWin.Width();
		int yCon = (point.y - rctWin.top) * CALENDAR_Y_GRID_TIME / rctWin.Height();
		m_nCurrentIndex = GetSelectDay(point);
		if(yCon && m_nCurrentIndex)
		{
			m_Time.GetAsSystemTime(m_tSelSolor);
			m_tSelSolor.wDay = m_nCurrentIndex;
			BOOL bLeap=FALSE;
			Gregorian2Lunar(&m_tSelSolor,&m_tSelLunar,&bLeap);
			GetParent()->SendMessage(WM_SINGLE_SELECT_DAY,(WPARAM)(&m_tSelSolor),(LPARAM)(&m_tSelLunar));
			Invalidate(FALSE);
		}	
		else if(yCon == 0)
		{
			COleDateTimeSpan sp= COleDateTimeSpan::COleDateTimeSpan(30,0,0,0);
		    /*if(xCon==0)
			{
				m_Time -= sp;
			}
			*/
			if(xCon == 3)
			{
				m_Time = COleDateTime::GetCurrentTime();
				::SendMessage(m_hWndTemp,WM_SINGLE_SELECT_DAY_UPDATECURRENT,0,0);
			}
			/*else if(xCon == 6)
			{
				m_Time += sp;	
			}
			*/
			Invalidate(FALSE);
		}
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CCalendarCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rct,rctWin;
	GetClientRect(rctWin);
	if(rctWin.PtInRect(point))
	{
		int xCon = (point.x - rctWin.left) *  CALENDAR_X_GRID_TIME / rctWin.Width();
		int yCon = (point.y - rctWin.top) * CALENDAR_Y_GRID_TIME / rctWin.Height();
		m_nCurrentIndex = GetSelectDay(point);
		if(yCon && m_nCurrentIndex)
		{
			m_Time.GetAsSystemTime(m_tSelSolor);
			m_tSelSolor.wDay = m_nCurrentIndex;
			BOOL bLeap=FALSE;
			Gregorian2Lunar(&m_tSelSolor,&m_tSelLunar,&bLeap);
			GetParent()->SendMessage(WM_DOUBLECLICK_SELECT_DAY,0,0);
			Invalidate(FALSE);
		}
	}

//	GetParent()->SendMessage(WM_DOUBLE_SELECT_DAY,(WPARAM)(&m_tSelSolor),(LPARAM)(&m_tSelLunar));
	GetParent()->SendMessage(WM_DOUBLECLICK_SELECT_ANOTHER_DAY,(WPARAM)(&m_Today),NULL);

	CStatic::OnLButtonDblClk(nFlags, point);
}

void CCalendarCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, SS_NOTIFY);
	CStatic::PreSubclassWindow();
}

int CCalendarCtrl::GetMonthDays(COleDateTime nTime)
{
	int iY = nTime.GetYear();
	int iM = nTime.GetMonth();
	int iTotalDay = 31;		
	if(iM == 2) 
	{
		//闰年可以被4或者400整除 但是不能被100整除
		if(iY % 4 ==0 && iY % 100 !=0 || iY % 400 ==0) 
			iTotalDay= 29;
		else
			iTotalDay=28;
	}
	else if(iM==4 || iM==6 || iM==9||iM==11)
		iTotalDay = 30;
	return iTotalDay;
}

#define TIP_TIMER_INTERVAL 200
void CCalendarCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == TIP_TIMER_INTERVAL)
	{
		m_bTip = TRUE;
		KillTimer(TIP_TIMER_INTERVAL);
	}
	CStatic::OnTimer(nIDEvent);
}

void CCalendarCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{

	CStatic::OnMouseMove(nFlags, point);

	if (!m_bTip) return;
	SetTimer(TIP_TIMER_INTERVAL,50,NULL);
	m_bTip = FALSE;

	CRect rct,rctWin;
	GetClientRect(rctWin);
	if(rctWin.PtInRect(point))
	{
		int xCon = (point.x - rctWin.left) *  CALENDAR_X_GRID_TIME / rctWin.Width();
		int yCon = (point.y - rctWin.top) * CALENDAR_Y_GRID_TIME / rctWin.Height();
		
		CString sTip="";	
		if (m_ToolTip.GetToolCount() == 0)
		{
			m_ToolTip.AddTool(this, sTip, rctWin, 1);				
		}

		if(yCon ==0)
		{
			switch (xCon)
			{
			case 0:
				sTip = "单击: 减小月份";
				break;
			case 6:
				sTip = "单击: 增加月份";
				break;
			case 3:
				sTip = "单击: 切换到当前日期";
				break;
			}
			
		}
		else
		{
			int iDay = GetSelectDay(point);
			if(iDay)
			{
				CString sNow; sNow.Format("%d-%d-%d 0:0:1",m_Time.GetYear(),m_Time.GetMonth(),iDay);
				COleDateTime tNow;	tNow.ParseDateTime(sNow);
				SYSTEMTIME tmNow={0};	tNow.GetAsSystemTime(tmNow);
				SYSTEMTIME tmLun={0};
				BOOL bLeapYear=FALSE;
				if(Gregorian2Lunar(&tmNow,&tmLun,&bLeapYear))
					sNow = GetLunarString(&tmLun,bLeapYear);
				else
					sNow = "我也不知道...";

				sTip.Format("当前日期: %04d年%02d月%02d日\n农历日期:%s",
					m_Time.GetYear(), m_Time.GetMonth(), iDay, sNow);

				m_Today.Format(" %04d/%02d/%02d",m_Time.GetYear(), m_Time.GetMonth(), iDay) ;      
	            

			}
			else
				sTip="开玩笑, 这里没东西, 呵呵!";	
		}
		m_ToolTip.UpdateTipText(sTip,this,1);
		m_ToolTip.Activate(TRUE);
	}
	
}

int CCalendarCtrl::GetSelectDay(CPoint pt)
{	
	int iRtn = 0;
	CRect rct,rctWin;
	GetClientRect(rctWin);
	if(rctWin.PtInRect(pt))
	{
		int xCon = (pt.x - rctWin.left) *  CALENDAR_X_GRID_TIME / rctWin.Width();
		int yCon = (pt.y - rctWin.top) * CALENDAR_Y_GRID_TIME / rctWin.Height();
		if(yCon)
		{
			//-----------------------------------------------------------
			// 正常日期 [Juncox 2009年4月23日 20:40:26]
			int xFirst= m_nFirstDay-1;
			if(!m_bFirstDay) xFirst -=1;
			iRtn = (yCon-1) * CALENDAR_X_GRID_TIME + xCon-xFirst;
			if(xFirst==-2) iRtn -= 7;
			if(iRtn<=0)	iRtn += 35;
			if(iRtn > GetMonthDays(m_Time))	iRtn = 0;
		}		
		else
			iRtn = 0;		
	}
	return iRtn;
}

BOOL CCalendarCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_ToolTip.m_hWnd==NULL)
	{ 
		m_ToolTip.Create(this, 0);
		m_ToolTip.Activate(FALSE);
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
	}
	else
	{
		m_ToolTip.RelayEvent(pMsg);
	}
	return CStatic::PreTranslateMessage(pMsg);
}

//-----------------------------------------------------------
// 得到表示农历通用表示的字串 [Juncox 2009年4月24日 0:49:45]
CString CCalendarCtrl::GetLunarString ( IN PSYSTEMTIME pSt, BOOL bEmbolism , BOOL bWholeName)
{
	TCHAR szNongli[30], szNongliDay[10],szShuXiang[10];
	/*天干名称*/
	const char *cTianGan[] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
	/*地支名称*/
	const char *cDiZhi[] = {"子","丑","寅","卯","辰","巳","午",	"未","申","酉","戌","亥"};
	/*属相名称*/
	const char *cShuXiang[] = {"鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗","猪"};
	/*农历日期名*/
	const char *cDayName[] = { "*","初一","初二","初三","初四","初五",
		"初六","初七","初八","初九","初十",
		"十一","十二","十三","十四","十五",
		"十六","十七","十八","十九","二十",
		"廿一","廿二","廿三","廿四","廿五",       
		"廿六","廿七","廿八","廿九","三十"};
	/*农历月份名*/
	const char *cMonName[] = {"*","正","二","三","四","五","六", "七","八","九","十","十一","腊"};

	/*--生成农历天干、地支、属相 ==> wNongli--*/
	int nShuXiang = ((pSt->wYear - 4) % 60) % 12;
	if ( nShuXiang < 0 || nShuXiang >= sizeof(cShuXiang)/sizeof(cShuXiang[0]) )
		return "Error Year";
	wsprintf(szShuXiang,"%s",cShuXiang[nShuXiang]);
	int nTianGan = ((pSt->wYear - 4) % 60) % 10;
	if ( nTianGan < 0 || nTianGan >= sizeof(cTianGan)/sizeof(cTianGan[0]) )
		return "Error Year";
	int nDiZhi = ((pSt->wYear - 4) % 60) % 12;
	if ( nDiZhi < 0 || nDiZhi >= sizeof(cDiZhi)/sizeof(cDiZhi[0]) )
		return "Error Year";
	wsprintf(szNongli,"%s(%s%s)年",szShuXiang,cTianGan[nTianGan],cDiZhi[nDiZhi]);
	
	/*--生成农历月、日 ==> wNongliDay--*/
	if ( pSt->wMonth < 0 || pSt->wMonth >= sizeof(cMonName)/sizeof(cMonName[0]) )
		return "Error Month";

	if(bWholeName == FALSE)	szNongli[0] = 0;

	if ( bEmbolism )
	{
		wsprintf(szNongliDay,"闰%s",cMonName[pSt->wMonth]);
	}
	else
	{
		strcpy(szNongliDay,cMonName[pSt->wMonth]);
	}
	
	strcat(szNongliDay,"月");
	
	if ( pSt->wDay < 0 || pSt->wDay >= sizeof(cDayName)/sizeof(cDayName[0]) )
		return "Error Day";
	
	if(bWholeName == FALSE)
	{
		if(pSt->wDay == 1)
			strcat(szNongli, szNongliDay);
		else
			strcat(szNongli,cDayName[pSt->wDay]);
	}
	else
	{
		strcat(szNongliDay,cDayName[pSt->wDay]);
		strcat(szNongli,szNongliDay);
	}
	
	return szNongli;
}

//-----------------------------------------------------------
// 公历转农历 [Juncox 2009年4月24日 0:49:33]
BOOL CCalendarCtrl::Gregorian2Lunar ( IN PSYSTEMTIME pSt, OUT PSYSTEMTIME pDst, OUT BOOL *pEmbolism )
{
	if ( !pSt || !pDst || !pEmbolism ) return FALSE;

	SYSTEMTIME Dst = {0};	
	/*公历每月前面的天数*/
	const int wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
	/*农历数据*/
	const int wNongliData[100] = {2635,333387,1701,1748,267701,694,2391,133423,1175,396438
		,3402,3749,331177,1453,694,201326,2350,465197,3221,3402
		,400202,2901,1386,267611,605,2349,137515,2709,464533,1738
		,2901,330421,1242,2651,199255,1323,529706,3733,1706,398762
		,2741,1206,267438,2647,1318,204070,3477,461653,1386,2413
		,330077,1197,2637,268877,3365,531109,2900,2922,398042,2395
		,1179,267415,2635,661067,1701,1748,398772,2742,2391,330031
		,1175,1611,200010,3749,527717,1452,2742,332397,2350,3222
		,268949,3402,3493,133973,1386,464219,605,2349,334123,2709
		,2890,267946,2773,592565,1210,2651,395863,1323,2707,265877};
	static int wCurYear,wCurMonth,wCurDay;
	static int nTheDate,nIsEnd,m,k,n,i,nBit;
	/*---取当前公历年、月、日---*/
	wCurYear = pSt->wYear;
	wCurMonth = pSt->wMonth;
	wCurDay = pSt->wDay;
	/*---计算到初始时间1921年2月8日的天数：1921-2-8(正月初一)---*/
	nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd[wCurMonth - 1] - 38;
	if ( nTheDate < 0 ) return FALSE;
	if((!(wCurYear % 4)) && (wCurMonth > 2))
		nTheDate = nTheDate + 1;
	
	/*--计算农历天干、地支、月、日---*/
	nIsEnd = 0;
	m = 0;
	while(nIsEnd != 1)
	{
		if(wNongliData[m] < 4095)
			k = 11;
		else
			k = 12;
		n = k;
		while(n>=0)
		{
			//获取wNongliData(m)的第n个二进制位的值
			nBit = wNongliData[m];
			for(i=1;i<n+1;i++)
				nBit = nBit/2;
			
			nBit = nBit % 2;
			
			if (nTheDate <= (29 + nBit))
			{
				nIsEnd = 1;
				break;
			}
			
			nTheDate = nTheDate - 29 - nBit;
			n = n - 1;
		}
		if(nIsEnd)
			break;
		m = m + 1;
	}
	wCurYear = 1921 + m;
	wCurMonth = k - n + 1;
	wCurDay = nTheDate;
	if ( wCurDay < 0 ) return FALSE;

	if (k == 12)
	{
		if (wCurMonth == wNongliData[m] / 65536 + 1)
			wCurMonth = 1 - wCurMonth;
		else if (wCurMonth > wNongliData[m] / 65536 + 1)
			wCurMonth = wCurMonth - 1;
	}
	
	Dst.wYear = (USHORT)wCurYear;
	if (wCurMonth < 1)
	{
		Dst.wMonth = -wCurMonth;
		*pEmbolism = TRUE;
	}
	else
	{
		Dst.wMonth = wCurMonth;
		*pEmbolism = FALSE;
	}
	Dst.wDay = wCurDay;
	memcpy ( pDst, &Dst, sizeof(SYSTEMTIME) );

	return TRUE;
}


//-----------------------------------------------------------
// 农历转公历 [Juncox 2009年4月24日 0:49:18]
BOOL CCalendarCtrl::Lunar2Gregorian ( IN PSYSTEMTIME pSt, IN BOOL bEmbolism, OUT PSYSTEMTIME pDst )
{
	if ( !pSt || !pDst ) return FALSE;
	COleDateTimeSpan Span(1,0,0,0);
	COleDateTime tStart ( *pSt );
	for ( int i=0; i<100; i++ )
	{
		SYSTEMTIME Src = {0};
		SYSTEMTIME Dst = {0};
		BOOL bDstEmbolism = FALSE;
		if ( !tStart.GetAsSystemTime ( Src ) )
			return FALSE;

		if ( !Gregorian2Lunar ( &Src, &Dst, &bDstEmbolism ) )
			return FALSE;
		if ( Dst.wYear==pSt->wYear && Dst.wMonth==pSt->wMonth && Dst.wDay==pSt->wDay && bEmbolism==bDstEmbolism )
		{
			memcpy ( pDst, &Src, sizeof(SYSTEMTIME) );
			return TRUE;
		}
		tStart+=Span;
	}

	return FALSE;
}

COleDateTime CCalendarCtrl::ConvertSysTime2OleDateTime(PSYSTEMTIME pSt)
{
	ASSERT ( pSt );
	COleDateTime t ( *pSt );
	return t;
}

CString CCalendarCtrl::VariantToString(VARIANT var)
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

BOOL CCalendarCtrl::Holiday()
{
	return TRUE;
}

int CCalendarCtrl::GetLastMonthDays(COleDateTime LastMonth)
{
	int iY = LastMonth.GetYear();
	switch (LastMonth.GetMonth())
	{
	case 1:
		{
			return 31;
		}
	case 2:
		{
			return 31;
		}
	case 3:
		{
			if(iY % 4 ==0 && iY % 100 !=0 || iY % 400 ==0) 
			{
				return 29;
			}
		    else
			{
				return 28;
			}
		}
	case 4:
		{
			return 31;
		}
	case 5:
		{
			return 30;
		}
	case 6:
		{
			return 31;
		}
	case 7:
		{
			return 30;
		}
	case 8:
		{
			return 31;
		}
	case 9:
		{
			return 31;
		}
	case 10:
		{
			return 30;
		}
	case 11:
		{
			return 31;
		}
	case 12:
		{
			return 30;
		}
	default :
		return 0;
	}
}

int CCalendarCtrl::GetAllMonthDaysBefore(COleDateTime before)
{
	int iY = before.GetYear();
	int iM = before.GetMonth();//0,31,59,90,120,151,181,212,243,273,304,334

	if(iY % 4 ==0 && iY % 100 !=0 || iY % 400 ==0) 
	{
		switch (iM)
		{
		case 1:
			return 0;
		case 2:
			return 31;
		case 3:
			return 60;
		case 4:
			return 91;
		case 5:
			return 121;
		case 6:
			return 152;
		case 7:
			return 182;
		case 8:
			return 213;
		case 9:
			return 244;
		case 10:
			return 274;
		case 11:
			return 305;
		case 12:
			return 335;
		default:
			return 0;
		}
	}
	else
	{
		switch (iM)
		{
		case 1:
			return 0;
		case 2:
			return 31;
		case 3:
			return 59;
		case 4:
			return 90;
		case 5:
			return 120;
		case 6:
			return 151;
		case 7:
			return 181;
		case 8:
			return 212;
		case 9:
			return 243;
		case 10:
			return 273;
		case 11:
			return 304;
		case 12:
			return 334;
		default:
			return 0;
		}
	}
}
