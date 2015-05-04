// Message.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "Message.h"
#include "stdlib.h"
#include "Ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessage dialog


CMessage::CMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessage, CDialog)
	//{{AFX_MSG_MAP(CMessage)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessage message handlers

void CMessage::ShowMotto()
{
		ado.OnInitAdoConn();
	m_pRecordset= ado.OpenRecordset("select * from Motto");
	
	m_pRecordset->MoveFirst();
	_variant_t cMotto;
	srand(time(0));

	int i=rand()%29;
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
		GetDlgItem(IDC_STATIC_Motto)->SetWindowText(mot);

				GetLocalTime(&Time);
		CString str;
		int hour=Time.wHour;
		switch (hour/6)
		{
		case 0:
			str="早上好";
			break;
		case 1:
			str="上午好";
				break;
		case 2:
			str="下午好";
				break;
		case 3:
			str="晚上好";
			break;
		default:
			break;
		}
		GetDlgItem(IDC_STATIC_Greet)->SetWindowText(str);

}

BOOL CMessage::OnInitDialog()
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
	ShowMotto();


}

HBRUSH CMessage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor== CTLCOLOR_STATIC) //如果是静态标签
    { 
        pDC->SetBkMode(TRANSPARENT);//设置背景模式为透明
        return (HBRUSH)GetStockObject(NULL_BRUSH);//返回一个空画刷
    }
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
