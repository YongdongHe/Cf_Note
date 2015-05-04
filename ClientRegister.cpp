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
		MessageBox("���û������Ա�ע��!");
	} 
	else
	{
		MessageBox("���û����ѱ�ʹ�ã������±༭�û�����");
		m_NewAdmin="";
		UpdateData(FALSE); 
	}
		
	
}

BOOL CClientRegister::AdminCheck()    //����û����Ƿ��Ѿ���ʹ�õĺ����������ʹ�ã��򷵻�false����֮����true
{

	UpdateData(TRUE);
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset;
	
	CString sql = "select * from cli where �û��� ='"+ m_NewAdmin +"'";
	
	pRecordset=ado.OpenRecordset(sql);
	
	if (pRecordset->RecordCount>0)
	{
        //�û����Ѵ��ڣ��򷵻�false        
		return FALSE;            
	}
	else
	{
		return TRUE;
	}
}

BOOL CClientRegister::PwdCheck()  //����������������Ƿ���ͬ���Լ������Ƿ�����Ϊ8��15λ���ַ���
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
		MessageBox("������������벻��Ӧ������������");
		return FALSE;
		break;
	case 2:
		MessageBox("����������벻����Ҫ��������Ҫ������8��15λ�������ֺ���ĸ��ɣ����ִ�Сд");
		return FALSE;
		break;
	case 3:
		MessageBox("������������벻��Ӧ������������");
		MessageBox("����������벻����Ҫ��������Ҫ������8��15λ�������ֺ���ĸ��ɣ����ִ�Сд");
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
		MessageBox("��������û����������벻�Ϸ�������������");
	}
	CDialog::OnOK();
}

void CClientRegister::AddNewAdmin()//�����û�������û��������������ݿ�������µ��û���Ϣ
{
	UpdateData(TRUE);
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset;
	pRecordset=ado.OpenRecordset("select * from cli"); 
	CString str;
	m_newpwd.GetWindowText(str);
	

	pRecordset->AddNew();
	pRecordset->PutCollect("�û���",_variant_t(m_NewAdmin));
	pRecordset->PutCollect("����",_variant_t(str));

	pRecordset->Update();
	
	MessageBox("�û� "+m_NewAdmin+" ע��ɹ���");
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
		dcMem.SelectObject(oldbitmap);              //�ػ汳��
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
    m_font.CreatePointFont(130,"����");
    pEdt->SetFont(&m_font);

	m_newpwd.SetWindowText("����8~15λ����");

	pEdt=(CEdit*)GetDlgItem(IDC_EDIT_PwdSure);
	pEdt->SetFont(&m_font);
	m_pswsure.SetWindowText("ȷ������");


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
