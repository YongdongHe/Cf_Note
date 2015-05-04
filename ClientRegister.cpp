// ClientRegister.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientRegister.h"
#include "Ado.h"
#include "SpringButton.h"
#include "winuser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientRegister dialog


CClientRegister::CClientRegister(CWnd* pParent /*=NULL*/)
	: CDialog(CClientRegister::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientRegister)
	m_NewAdmin = _T("");
	//}}AFX_DATA_INIT
}


void CClientRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientRegister)
	DDX_Control(pDX, IDC_EDIT_PwdSure, m_pswsure);
	DDX_Control(pDX, IDC_BUTTON_AdminCheck, m_AdminCheck);
	DDX_Control(pDX, IDC_EDIT_PwdSet, m_newpwd);
	DDX_Control(pDX, IDC_Close, m_ReDlgClose);
	DDX_Control(pDX, IDOK, m_RegisterOk);
	DDX_Text(pDX, IDC_EDIT_NewAdmin, m_NewAdmin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClientRegister, CDialog)
	//{{AFX_MSG_MAP(CClientRegister)
	ON_BN_CLICKED(IDC_BUTTON_AdminCheck, OnBUTTONAdminCheck)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Close, OnClose)
	ON_WM_CTLCOLOR()
	ON_EN_SETFOCUS(IDC_EDIT_PwdSet, OnSetfocusEDITPwdSet)
	ON_EN_SETFOCUS(IDC_EDIT_PwdSure, OnSetfocusEDITPwdSure)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientRegister message handlers

void CClientRegister::OnBUTTONAdminCheck() 
{
	// TODO: Add your control notification handler code here
	BOOL checkresult=AdminCheck();
	if (checkresult)
	{
		MessageBox("此用户名可以被注册!");
	} 
	else
	{
		MessageBox("此用户名已被使用，请重新编辑用户名！");
		m_NewAdmin="";
		UpdateData(FALSE); 
	}
		
	
}

BOOL CClientRegister::AdminCheck()    //检查用户名是否已经被使用的函数，如果被使用，则返回false，反之返回true
{

	UpdateData(TRUE);
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset;
	
	CString sql = "select * from cli where 用户名 ='"+ m_NewAdmin +"'";
	
	pRecordset=ado.OpenRecordset(sql);
	
	if (pRecordset->RecordCount>0)
	{
        //用户名已存在，则返回false        
		return FALSE;            
	}
	else
	{
		return TRUE;
	}
}

BOOL CClientRegister::PwdCheck()  //检查两次输入密码是否相同，以及密码是否满足为8到15位的字符串
{
	UpdateData(TRUE);
	int i=0;
	CString pwd,pwddure;
	m_newpwd.GetWindowText(pwd);
/*	if (m_newpwd!=m_pswsrue)
	{
		i=1;
	}
	if ( 8>m_newpwd.GetLength()  ||  15<m_newpwd.GetLength() )
	{	
		i=2;
	}
	if ((m_newpwd!=m_pswsrue)  && (8>m_newpwd.GetLength()  ||  15<m_newpwd.GetLength())   )
	{
		i=3;
	}
*/
	m_pswsure.GetWindowText(pwddure);
   	if (pwd!=pwddure)
	{
		i=1;
	}
	if ( 8>pwd.GetLength()  ||  15<pwd.GetLength() )
	{	
		i=2;
	}
	if ((pwd!=pwddure)  && (8>pwd.GetLength()  ||  15<pwd.GetLength())   )
	{
		i=3;
	}

	switch (i)
	{
	case 1:
		MessageBox("两次输入的密码不对应！请重新输入");
		return FALSE;
		break;
	case 2:
		MessageBox("您输入的密码不符合要求，密码需要长度在8到15位，由数字和字母组成，区分大小写");
		return FALSE;
		break;
	case 3:
		MessageBox("两次输入的密码不对应！请重新输入");
		MessageBox("您输入的密码不符合要求，密码需要长度在8到15位，由数字和字母组成，区分大小写");
        return FALSE;
	default:
		break;
	}
	return  TRUE;
}

void CClientRegister::OnOK() 
{
	// TODO: Add extra validation here
    if (AdminCheck() && PwdCheck())
    {
		AddNewAdmin();
    } 
	else
	{
		MessageBox("您输入的用户名或者密码不合法，请重新输入");
	}
	CDialog::OnOK();
}

void CClientRegister::AddNewAdmin()//根据用户输入的用户名和密码在数据库中添加新的用户信息
{
	UpdateData(TRUE);
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset;
	pRecordset=ado.OpenRecordset("select * from cli"); 
	CString str;
	m_newpwd.GetWindowText(str);
	

	pRecordset->AddNew();
	pRecordset->PutCollect("用户名",_variant_t(m_NewAdmin));
	pRecordset->PutCollect("密码",_variant_t(str));

	pRecordset->Update();
	
	MessageBox("用户 "+m_NewAdmin+" 注册成功！");
	ado.ExitConnection();	
}

void CClientRegister::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

		BITMAP bm;
		CRect rect;
		CDC dcMem;
		m_background.GetBitmap (&bm);
		GetClientRect(&rect);
		dcMem.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem.SelectObject (&m_background);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(oldbitmap);              //重绘背景
		CDialog::OnPaint();
	
	
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CClientRegister::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_background.LoadBitmap(IDB_BITMAP_ReDlgbg);
	m_RegisterOk.LoadOnBitmap(IDB_BITMAP_Re3);
	m_RegisterOk.LoadLightBitmap(IDB_BITMAP_Re2);
	m_RegisterOk.LoadOffBitmap(IDB_BITMAP_Re1);
	m_ReDlgClose.LoadOnBitmap(IDB_BITMAP_Close3);
	m_ReDlgClose.LoadLightBitmap(IDB_BITMAP_Close2);
	m_ReDlgClose.LoadOffBitmap(IDB_BITMAP_ReDlgClose);

	m_AdminCheck.LoadOnBitmap(IDB_BITMAP_ReAdminC3);
	m_AdminCheck.LoadLightBitmap(IDB_BITMAP_ReAdminC2);
	m_AdminCheck.LoadOffBitmap(IDB_BITMAP_ReAdminC1);


	m_newpwd.SetPasswordChar(0);
	m_pswsure.SetPasswordChar(0);

	CEdit* pEdt=(CEdit*)GetDlgItem(IDC_EDIT_PwdSet);
    m_font.CreatePointFont(130,"黑体");
    pEdt->SetFont(&m_font);

	m_newpwd.SetWindowText("请输8~15位密码");

	pEdt=(CEdit*)GetDlgItem(IDC_EDIT_PwdSure);
	pEdt->SetFont(&m_font);
	m_pswsure.SetWindowText("确认密码");


	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClientRegister::OnClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

HBRUSH CClientRegister::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
		if (pWnd->GetDlgCtrlID()==IDC_EDIT_PwdSet)  
		{		
			pDC->SetTextColor(RGB(154,141,141));
		}
		if (pWnd->GetDlgCtrlID()==IDC_EDIT_PwdSure)  
		{		
			pDC->SetTextColor(RGB(154,141,141));
		}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CClientRegister::OnSetfocusEDITPwdSet() 
{
	// TODO: Add your control notification handler code here
	m_newpwd.SetWindowText("");
	m_newpwd.SetPasswordChar('*');	
	CEdit* pEdt=(CEdit*)GetDlgItem(IDC_EDIT_PwdSet);
    pEdt->SetFont(&m_font);
}

void CClientRegister::OnSetfocusEDITPwdSure() 
{
	// TODO: Add your control notification handler code 
	m_pswsure.SetWindowText("");
	m_pswsure.SetPasswordChar('*');	
	CEdit* pEdt=(CEdit*)GetDlgItem(IDC_EDIT_PwdSure);
    pEdt->SetFont(&m_font);
	
}
