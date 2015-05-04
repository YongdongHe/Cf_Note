// Satety.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "Satety.h"
#include "Ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSatety dialog


CSatety::CSatety(CWnd* pParent /*=NULL*/)
	: CDialog(CSatety::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSatety)
	//}}AFX_DATA_INIT
}


void CSatety::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSatety)
	DDX_Control(pDX, IDC_EDIT_THIRD, m_ThirdPassword);
	DDX_Control(pDX, IDOK, m_safe_Save);
	DDX_Control(pDX, IDCANCEL, m_safe_Close);
	DDX_Control(pDX, IDC_EDIT_SECOND, m_SecondPassword);
	DDX_Control(pDX, IDC_EDIT_FIRST, m_FirstPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSatety, CDialog)
	//{{AFX_MSG_MAP(CSatety)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatety message handlers

void CSatety::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();

    CString sql="select * from cli where 用户名='"+m_username+"'";
    pRecordset = ado.OpenRecordset(sql);

	CString FirstPW=(char*)(_bstr_t)pRecordset->GetCollect("密码");
	CString WritePW;
    m_FirstPassword.GetWindowText(WritePW);
	if(WritePW==FirstPW)
	{
		CString SecondPW,ThirdPW;
        m_SecondPassword.GetWindowText(SecondPW);
		m_ThirdPassword.GetWindowText(ThirdPW);
		if(SecondPW==ThirdPW)
		{
			pRecordset->PutCollect("密码",(_bstr_t)SecondPW);
			pRecordset->Update();
		    pRecordset->Close();
		    ado.ExitConnection();
	        CDialog::OnOK();
		}
		else
		{
			MessageBox("两次输入密码不一致");
			m_ThirdPassword.SetWindowText("");
			m_ThirdPassword.SetFocus();
		}
        
	}
	else
	{
        ado.ExitConnection();
		MessageBox("原密码输入错误");
	}	

	
	CDialog::OnOK();
}

BOOL CSatety::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//加载背景和按钮资源
	m_bitmap_safebg.LoadBitmap(IDB_BITMAP_safebg);

	m_safe_Save.LoadOnBitmap(IDB_BITMAP_Diary_Save1);
	m_safe_Save.LoadLightBitmap(IDB_BITMAP_Diary_Save2);
	m_safe_Save.LoadOffBitmap(IDB_BITMAP_Diary_Save1);
	
	m_safe_Close.LoadOnBitmap(IDB_BITMAP_Diary_Close1);
	m_safe_Close.LoadLightBitmap(IDB_BITMAP_Diary_Close2);
	m_safe_Close.LoadOffBitmap(IDB_BITMAP_Diary_Close1);



	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSatety::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	BITMAP bm;
	CRect rect;
	CDC dcMem;
	m_bitmap_safebg.GetBitmap (&bm);
	GetClientRect(&rect);
	dcMem.CreateCompatibleDC (&dc);
	CBitmap *oldbitmap=dcMem.SelectObject (&m_bitmap_safebg);
	dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(oldbitmap);
    CDialog::OnPaint();
	
	// Do not call CDialog::OnPaint() for painting messages
}

UINT CSatety::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
    return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}
