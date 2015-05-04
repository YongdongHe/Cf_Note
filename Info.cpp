// Info.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "Info.h"
#include "Ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog


CInfo::CInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfo)
	//}}AFX_DATA_INIT
}


void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfo)
	DDX_Control(pDX, IDCANCEL, m_info_Close);
	DDX_Control(pDX, IDOK, m_info_Save);
	DDX_Control(pDX, IDC_EDITCONSTELLATION, m_Constellation);
	DDX_Control(pDX, IDC_EDIT_WEIGHT, m_Weight);
	DDX_Control(pDX, IDC_EDIT_NICKNAME, m_Nickname);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_Height);
	DDX_Control(pDX, IDC_EDIT_HABIT, m_Habit);
	DDX_Control(pDX, IDC_EDIT_BIRTHDAY, m_Birthday);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfo, CDialog)
	//{{AFX_MSG_MAP(CInfo)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR()
	ON_EN_SETFOCUS(IDC_EDIT_BIRTHDAY, OnSetfocusEditBirthday)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfo message handlers



void CInfo::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CString csNickname,csHabit,csBirthday,csConstellation,csHeight,csWeight;
	m_Nickname.GetWindowText(csNickname);
    m_Habit.GetWindowText(csHabit);
	m_Birthday.GetWindowText(csBirthday);	
	m_Constellation.GetWindowText(csConstellation);
	m_Height.GetWindowText(csHeight);
	m_Weight.GetWindowText(csWeight);
	
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();

    CString sql="select * from cli where 用户名='"+m_username1+"'";
    pRecordset = ado.OpenRecordset(sql);

	if(csNickname!="")
	{
		pRecordset->PutCollect("昵称",(_bstr_t)csNickname);
	}
	else
	{
		pRecordset->PutCollect("昵称",(_bstr_t)"");
	}


	if(csHabit!="")
	{
		pRecordset->PutCollect("爱好",(_bstr_t)csHabit);
	}
	else
	{
		pRecordset->PutCollect("爱好",(_bstr_t)"");
	}

	if(csConstellation!="")
	{
		pRecordset->PutCollect("星座",(_bstr_t)csConstellation);
	}
	else
	{
		pRecordset->PutCollect("星座",(_bstr_t)"");
	}

	if(csHeight!="")
	{
		pRecordset->PutCollect("身高",(_bstr_t)csHeight);
	}
	else
	{
		pRecordset->PutCollect("身高",(_bstr_t)"");
	}

	if(csWeight!="")
	{
		pRecordset->PutCollect("体重",(_bstr_t)csWeight);
	}
	else
	{
		pRecordset->PutCollect("体重",(_bstr_t)"");
	}

	if(csBirthday!="年/月/日"&&csBirthday!="")

	{
		for (int p=0;p<csBirthday.GetLength();p++)
		{
		if (csBirthday.GetAt(p)=='-')
		{
			csBirthday.SetAt(p,'/');
		}
		}
		int year1,month1,day1;
	    CString cstr,nYear,nMonth,nDay;
	    year1=_ttoi(csBirthday.Left(4));
        cstr=csBirthday.Right(csBirthday.GetLength()-1-csBirthday.Find('/'));
        month1=_ttoi(cstr.Left(cstr.Find('/')));
        day1=_ttoi(cstr.Right(cstr.GetLength()-1-cstr.Find('/')));
	    nYear.Format("%d",year1);
        nMonth.Format("%02d",month1);
	    nDay.Format("%02d",day1);
	    csBirthday=nYear+"/"+nMonth+"/"+nDay;

		pRecordset->PutCollect("生日",(_bstr_t)csBirthday);
	}
	else
	{
		pRecordset->PutCollect("生日",(_bstr_t)"");
	}
	pRecordset->Update();
	pRecordset->Close();
    ado.ExitConnection();

	CDialog::OnOK();
}

BOOL CInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here  
	//加载背景和按钮资源
	m_bitmap_Infobg.LoadBitmap(IDB_BITMAP_Infobg);

	m_info_Save.LoadOnBitmap(IDB_BITMAP_Diary_Save1);
	m_info_Save.LoadLightBitmap(IDB_BITMAP_Diary_Save2);
	m_info_Save.LoadOffBitmap(IDB_BITMAP_Diary_Save1);

	m_info_Close.LoadOnBitmap(IDB_BITMAP_Diary_Close1);
	m_info_Close.LoadLightBitmap(IDB_BITMAP_Diary_Close2);
	m_info_Close.LoadOffBitmap(IDB_BITMAP_Diary_Close1);


	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();

    CString sql="select * from cli where 用户名='"+m_username1+"'";
    pRecordset = ado.OpenRecordset(sql);

	_variant_t csNickname,csHabit,csBirthday,csConstellation,csHeight,csWeight;
    csNickname= pRecordset->GetCollect("昵称");
	csHabit= pRecordset->GetCollect("爱好");
	csBirthday= pRecordset->GetCollect("生日");

	CString Birthday="";
	if (csBirthday.vt!=VT_NULL)
	{
		Birthday=(TCHAR*)(_bstr_t)csBirthday;
	}

	csConstellation= pRecordset->GetCollect("星座");
	csHeight= pRecordset->GetCollect("身高");
	csWeight= pRecordset->GetCollect("体重");
    if(csBirthday.vt==VT_NULL)
	{
		m_Birthday.SetWindowText("年/月/日");
	}
	else if(Birthday=="")
	{
		m_Birthday.SetWindowText("年/月/日");
	}
	else
	{
		m_Birthday.SetWindowText((_bstr_t)csBirthday);
	}

	if(csNickname.vt!=VT_NULL)
	{
		m_Nickname.SetWindowText((_bstr_t)csNickname);
	}

	if(csHabit.vt!=VT_NULL)
	{
		m_Habit.SetWindowText((_bstr_t)csHabit);
	}

	if(csConstellation.vt!=VT_NULL)
	{
		m_Constellation.SetWindowText((_bstr_t)csConstellation);
	}
	if(csHeight.vt!=VT_NULL)
	{
		m_Height.SetWindowText((_bstr_t)csHeight);
	}
	if(csWeight.vt!=VT_NULL)
	{
		m_Weight.SetWindowText((_bstr_t)csWeight);
	}

	ado.ExitConnection();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInfo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	BITMAP bm;
	CRect rect;
	CDC dcMem;
	m_bitmap_Infobg.GetBitmap (&bm);
	GetClientRect(&rect);
	dcMem.CreateCompatibleDC (&dc);
	CBitmap *oldbitmap=dcMem.SelectObject (&m_bitmap_Infobg);
	dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(oldbitmap);
    CDialog::OnPaint();
	
	// Do not call CDialog::OnPaint() for painting messages
}



UINT CInfo::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
    return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}

HBRUSH CInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
		if (pWnd->GetDlgCtrlID()==IDC_EDIT_BIRTHDAY)//注意此处的（pWnd->），否则没效果
		{		
			pDC->SetTextColor(RGB(154,141,141));
		}

	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CInfo::OnSetfocusEditBirthday() 
{
	// TODO: Add your control notification handler code here
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();

    CString sql="select * from cli where 用户名='"+m_username1+"'";
    pRecordset = ado.OpenRecordset(sql);

	_variant_t Birthday;
    Birthday= pRecordset->GetCollect("生日");

	CString csBirthday="";
	if (Birthday.vt!=VT_NULL)
	{
		csBirthday=(TCHAR*)(_bstr_t)Birthday;
	}


    if(Birthday.vt==VT_NULL||csBirthday=="")
	{
		m_Birthday.SetWindowText("");
	}	
	ado.ExitConnection();

	
}
