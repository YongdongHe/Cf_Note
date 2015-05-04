// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "Ado.h"
#include "ClientRegister.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_Admin = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_EDIT_Pwd, m_Pwd);
	DDX_Control(pDX, IDC_BUTTON_Close, m_CloseButton);
	DDX_Control(pDX, IDC_BUTTON_Register, m_RegSpringButton);
	DDX_Control(pDX, IDC_BUTTON_Log, m_LogSpringButton);
	DDX_Text(pDX, IDC_EDIT_Admin, m_Admin);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Log, OnBUTTONLog)
	ON_BN_CLICKED(IDC_BUTTON_Register, OnBUTTONRegister)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON_Close, OnBUTTONClose)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_background.LoadBitmap(IDB_BITMAP_Clientbg);
	m_LogSpringButton.LoadOnBitmap(IDB_BITMAP_Log3);
	m_LogSpringButton.LoadOffBitmap(IDB_BITMAP_Log1);
	m_LogSpringButton.LoadLightBitmap(IDB_BITMAP_Log2);
	m_RegSpringButton.LoadOnBitmap(IDB_BITMAP_Re3);
	m_RegSpringButton.LoadOffBitmap(IDB_BITMAP_Re1);
	m_RegSpringButton.LoadLightBitmap(IDB_BITMAP_Re2);
	m_CloseButton.LoadOnBitmap(IDB_BITMAP_Close3);
	m_CloseButton.LoadLightBitmap(IDB_BITMAP_Close2);
	m_CloseButton.LoadOffBitmap(IDB_BITMAP_Close1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint() 
{
	CPaintDC dc(this);//device context for painting
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
		m_background.GetBitmap (&bm);
		GetClientRect(&rect);
		dcMem.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem.SelectObject (&m_background);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(oldbitmap);              //重绘背景
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CClientDlg::OnBUTTONLog() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset;

    CString sql = "select * from cli where 用户名 ='"+ m_Admin +"'";


	pRecordset=ado.OpenRecordset(sql);

	if(pRecordset->RecordCount>0)
	{
		CString sPwd = (LPCTSTR)(_bstr_t)pRecordset->GetCollect("密码");   //将数据库中获取的密码转为CString类型
		CString Pwd;
		m_Pwd.GetWindowText(Pwd);
		if(sPwd == Pwd)
		{
			
				//为与主界面对接而修改 BY 张
				CDialog::OnOK();

		}
		//如果密码错误时需要修改的地方 BY ZYY
		else
		{
			MessageBox("密码错误，请重新输入！");
			m_Pwd.SetWindowText("");
			m_Pwd.SetFocus();

		}

	}
	else
	{
		MessageBox("此用户名不存在，请先注册！");

	}

	ado.ExitConnection();
		_RecordsetPtr pRecordset_kk;
	ado.OnInitAdoConn();
	
	CString sql_hh = "select * from cli where 用户名 ='"+ m_Admin +"'";
	pRecordset_kk=ado.OpenRecordset(sql_hh);

	if(pRecordset_kk->RecordCount>0)
	{
		pRecordset_kk->PutCollect("检索登录",(_bstr_t)"是");
		pRecordset_kk->Update();
	}
		ado.ExitConnection();
	

	
}

void CClientDlg::OnBUTTONRegister() 
{
	// TODO: Add your control notification handler code here
	CClientRegister Dlg;
	ShowWindow(FALSE);
	if(Dlg.DoModal())
	ShowWindow(TRUE);
}

void CClientDlg::OnOK()
{
	OnBUTTONLog();
}

UINT CClientDlg::OnNcHitTest(CPoint point) //实现无边框对话框的拖动
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
//  return CDialog::OnNcHitTest(point);
//	return CDialog::OnNcHitTest(point);
}

void CClientDlg::OnBUTTONClose() 
{
	// TODO: Add your control notification handler code here
//	SendMessage(WM_CLOSE);//发送WM_CLOSE消息，使消息函数OnClose()响应，关闭窗口
	CDialog::OnCancel();

}

void CClientDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/*	CRect B_log; 
	m_LogSpringButton.GetWindowRect(&B_log);//获取当前窗口边界
	if(!B_log.PtInRect(point))//看鼠标是否在窗口中，是则返回真，反之假
	{
		m_LogSpringButton.is_focused=false;
		m_LogSpringButton.Invalidate();
	}
*/	
	CDialog::OnMouseMove(nFlags, point);
}
