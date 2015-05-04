// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDlg)
	m_year = 0;
	m_month = 0;
	m_day = 0;
	//}}AFX_DATA_INIT
}


void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Text(pDX, IDC_EDIT_YEAR, m_year);
	DDX_Text(pDX, IDC_EDIT_MONTH, m_month);
	DDX_Text(pDX, IDC_EDIT_DAY, m_day);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_JOURNAL, OnButtonJournal)
	ON_BN_CLICKED(IDC_BUTTON_NOTE, OnButtonNote)
	ON_BN_CLICKED(IDC_BUTTON_BIRTH, OnButtonBirth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers

void CEditDlg::OnButtonJournal() 
{
	// TODO: Add your control notification handler code here
	::SendMessage(m_hWndEdit,WM_SINGLE_SELECT_JOURNAL,0,0);
}

void CEditDlg::OnButtonNote() 
{
	// TODO: Add your control notification handler code here
	::SendMessage(m_hWndEdit,WM_SINGLE_SELECT_NOTE,0,0);
}

void CEditDlg::OnButtonBirth() 
{
	// TODO: Add your control notification handler code here
	::SendMessage(m_hWndEdit,WM_SINGLE_SELECT_BIRTHDAY,0,0);
}
