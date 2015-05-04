// ��ʱ����Dlg.cpp : implementation file
#include "stdafx.h"
#include "client.h"
#include "��ʱ����Dlg.h"
#include "Ado.h"
#include "Tip.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
/*
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
*/
/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDCANCEL, m_Note_Close);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_Note_Delete);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Note_Save);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, m_date);
	DDX_Control(pDX, IDC_EDIT_TIP, m_tipcontent);
	DDX_Control(pDX, IDC_COMBO_MINUTE, m_minute);
	DDX_Control(pDX, IDC_COMBO_HOUR, m_hour);
	DDX_Control(pDX, IDC_LIST_TIP, m_list_tip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TIP, OnDblclkListTip)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	hWnd=AfxGetMainWnd()->m_hWnd;

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
	//���ر����Ͱ�ť��Դ
	m_bitmap_Notebg.LoadBitmap(IDB_BITMAP_Notebg);
	
	m_Note_Delete.LoadOnBitmap(IDB_BITMAP_NoteDelete1);
	m_Note_Delete.LoadLightBitmap(IDB_BITMAP_NoteDelete2);
	m_Note_Delete.LoadOffBitmap(IDB_BITMAP_NoteDelete1);

	m_Note_Save.LoadOnBitmap(IDB_BITMAP_NoteSave1);
	m_Note_Save.LoadLightBitmap(IDB_BITMAP_NoteSave2);
	m_Note_Save.LoadOffBitmap(IDB_BITMAP_NoteSave1);

	m_Note_Close.LoadOnBitmap(IDB_BITMAP_Diary_Close1);
	m_Note_Close.LoadLightBitmap(IDB_BITMAP_Diary_Close2);
	m_Note_Close.LoadOffBitmap(IDB_BITMAP_Diary_Close1);


	//ʱ���ֳ�ʼ��

	CTime st;
	st=CTime::GetCurrentTime();
	CString nHour,nMinute;
	nHour=st.Format("%H");
    nMinute=st.Format("%M");

	m_hour.SetWindowText(nHour);
	m_minute.SetWindowText(nMinute);
	
	//�б����ʽ��ʼ��
	m_list_tip.SetExtendedStyle(LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rect;
	m_list_tip.GetWindowRect( &rect );
	int width = rect.right - rect.left;
	
	//m_list.InsertColumn(0, "ID", LVCFMT_LEFT, width/3 );
	m_list_tip.InsertColumn(1, "����", LVCFMT_LEFT, width/4 );
	m_list_tip.InsertColumn(2, "ʱ��", LVCFMT_LEFT, width/4 );
	m_list_tip.InsertColumn(3, "�¼�", LVCFMT_LEFT, width/3 );
	m_list_tip.InsertColumn(4, "��ע", LVCFMT_LEFT, width/6 );

    m_list_tip.DeleteAllItems();

	//�������ݿⲢ��ʾ
    nItem=-1;
   	Show();
	//��������
	CListCtrl* pEdt=(CListCtrl*)GetDlgItem(IDC_LIST_TIP);
    font.CreatePointFont(120,m_font);
    pEdt->SetFont(&font);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
/*	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
*/
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CMyDlg::OnPaint() 
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
		m_bitmap_Notebg.GetBitmap (&bm);
		GetClientRect(&rect);
		dcMem.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem.SelectObject (&m_bitmap_Notebg);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
        dcMem.SelectObject(oldbitmap);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

////////////////////////////////////////////////��

void CMyDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString TipContent,TipDate,TipHour,TipMinute,TipTime;
	m_date.GetWindowText(TipDate);

		for (int p=0;p<TipDate.GetLength();p++)
	{
		if (TipDate.GetAt(p)=='-')
		{
			TipDate.SetAt(p,'/');
		}
	}

    int year1,month1,day1;
	CString cstr,nYear,nMonth,nDay;
	year1=_ttoi(TipDate.Left(4));
    cstr=TipDate.Right(TipDate.GetLength()-1-TipDate.Find('/'));
    month1=_ttoi(cstr.Left(cstr.Find('/')));
    day1=_ttoi(cstr.Right(cstr.GetLength()-1-cstr.Find('/')));
	nYear.Format("%d",year1);
    nMonth.Format("%02d",month1);
	nDay.Format("%02d",day1);
	TipDate=nYear+"/"+nMonth+"/"+nDay;

    m_hour.GetWindowText(TipHour);
	if(TipHour.GetLength()==1)
	{
		TipHour="0"+TipHour;
	}
    m_minute.GetWindowText(TipMinute);
	if(TipMinute.GetLength()==1)
	{
		TipMinute="0"+TipMinute;
	}
    TipTime=TipHour+":"+TipMinute+":00";
    m_tipcontent.GetWindowText(TipContent);

	if(TipContent=="\0")
	{
		MessageBox("����¼Ϊ��","����");
	}
	else
	{
        CAdo ado;
	    ado.OnInitAdoConn();
	    _RecordsetPtr pRecordset = ado.GetRecordset();

        CString sql="select * from users where �û�='"+m_usersname+"'";
        pRecordset = ado.OpenRecordset(sql);
       
        try
		{//���Ӽ�¼
            pRecordset->AddNew();
            pRecordset->PutCollect("�û�",(_bstr_t)m_usersname);
            pRecordset->PutCollect("����",(_bstr_t)TipDate);
            pRecordset->PutCollect("ʱ��",(_bstr_t)TipTime);
            pRecordset->PutCollect("�¼�",(_bstr_t)TipContent);
         //�ж���û����������
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SETALARM);
            int state = pBtn->GetCheck();
			if(state==1)
			{
				pRecordset->PutCollect("����",(_bstr_t)"��");
			}
			if(state==0)
			{
				pRecordset->PutCollect("����",(_bstr_t)"��");
			}

            pRecordset->Update();
            CString sql1 = "select * from set01 where �û�='"+m_usersname+"'";
            pRecordset = ado.OpenRecordset(sql1);

			int flag=0;
			
			if(pRecordset->RecordCount>0)
			{
				pRecordset->MoveFirst();
	            _variant_t cName,cDate,cTip;	
				CString csName,csDate,csTip;
	            while (!pRecordset->adoEOF)
				{
					cName=pRecordset->GetCollect("�û�");
					cDate=pRecordset->GetCollect("����");
					cTip=pRecordset->GetCollect("����¼");
					csName=(TCHAR*)(_bstr_t)cName;
					csDate=(TCHAR*)(_bstr_t)cDate;
                    csTip=(TCHAR*)(_bstr_t)cTip;

					if(csName==m_usersname&&csDate==TipDate&&csTip=="��")
					{
						flag=1;
					}
                    if(csName==m_usersname&&csDate==TipDate&&csTip=="��")
					{
						pRecordset->PutCollect("����¼",(_bstr_t)"��");
                        flag=1;
                        pRecordset->Update();
					} 
					
		            pRecordset->MoveNext();
				}
				if(flag==0)
				{
					pRecordset->AddNew();
                    pRecordset->PutCollect("�û�",(_bstr_t)m_usersname);
                    pRecordset->PutCollect("����",(_bstr_t)TipDate);
                    pRecordset->PutCollect("����¼",(_bstr_t)"��");
					pRecordset->PutCollect("�ռ�",(_bstr_t)"��");

                    pRecordset->Update();
				}
                
			}
            if(pRecordset->RecordCount==0)
			{
				pRecordset->AddNew();
                pRecordset->PutCollect("�û�",(_bstr_t)m_usersname);
                pRecordset->PutCollect("����",(_bstr_t)TipDate);
                pRecordset->PutCollect("����¼",(_bstr_t)"��");
				pRecordset->PutCollect("�ռ�",(_bstr_t)"��");
                pRecordset->Update();
			}
            pRecordset->Close();
            ado.ExitConnection();
		//	MessageBox("����ɹ���");
		}
		catch(...)
		{
			MessageBox("����ʧ�ܣ�");
		}
        
	}
	if(nItem!=-1)
	{
		CString bDate=m_list_tip.GetItemText(nItem, 0);
		CString bTime=m_list_tip.GetItemText(nItem, 1);
		CAdo ado;
	    ado.OnInitAdoConn();
	    _RecordsetPtr pRecordset = ado.GetRecordset();

	    CString Sql = "select * from users where ʱ�� = '"+bTime+"' AND �û�='"+m_usersname+"' AND ����='"+bDate+"'";		//sql���
	    pRecordset = ado.OpenRecordset(Sql);

        pRecordset->Delete(adAffectCurrent);
		pRecordset->Update();

        CString sql2= "select * from users where �û�='"+m_usersname+"'";		//sql���
	    pRecordset = ado.OpenRecordset(sql2);
	    if(pRecordset->RecordCount > 0)
		{
			int flag=0;
		    pRecordset->MoveFirst();
	        _variant_t cName,cDate;	
		    CString csName,csDate;
	        while (!pRecordset->adoEOF)
			{
				cName=pRecordset->GetCollect("�û�");
		        cDate=pRecordset->GetCollect("����");
			    csName=(TCHAR*)(_bstr_t)cName;
			    csDate=(TCHAR*)(_bstr_t)cDate;

			    if(csName==m_usersname&&csDate==bDate)
				{
					flag=1;
				}
			    pRecordset->MoveNext();
			}
		 
		    if(flag==0)
			{
				CString sql1 = "select * from set01 where ����= '"+bDate+"' AND �û�='"+m_usersname+"'";
                pRecordset = ado.OpenRecordset(sql1);
			    pRecordset->PutCollect("����¼",(_bstr_t)"��");
                pRecordset->Update();
			}
//			MessageBox("ɾ���ɹ�");

		}
	    else if(pRecordset->RecordCount ==0)
		{ 
		 CString sql3= "select * from set01 where ����= '"+bDate+"' AND �û�='"+m_usersname+"'";
         pRecordset = ado.OpenRecordset(sql3);
	     pRecordset->PutCollect("����¼",(_bstr_t)"��");
         pRecordset->Update();
 //        MessageBox("ɾ���ɹ�");
		}
		pRecordset->Close();
	    ado.ExitConnection();
	    m_list_tip.DeleteItem(nItem);		//ɾ������
	}

	m_list_tip.DeleteAllItems();
	Show();

	nItem=-1;
    m_tipcontent.SetWindowText("");

    
}

/////////////////////////////��
void CMyDlg::Show()
{   
	//��ʾ��������
	UpdateData(TRUE);
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();

	//���ø�ѡ��δѡ��
    CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SETALARM);
	pBtn->SetCheck(0);


    //��ʾ���б��
	CString Sql;
	if (DiaryFlag==0)
	{
		Sql="select * from users where �û�='"+m_usersname+"'ORDER BY ����,ʱ��";
	}
	if (DiaryFlag==1)
	{
		Sql="select * from users where �û�='"+m_usersname+"'and ����='"+DiaryDate+"'ORDER BY ʱ��";
	}
    pRecordset = ado.OpenRecordset(Sql);

	if(pRecordset->RecordCount>0)
	{
		pRecordset->MoveFirst();
	
	    CString cDate, cTime, cThing,cIfset;

	    int i=0;
	
	    while (!pRecordset->adoEOF)
		{
			m_list_tip.InsertItem(i, "");
		
		    cDate= (TCHAR*)(_bstr_t)pRecordset->GetCollect("����");
		    cTime = (TCHAR*)(_bstr_t)pRecordset->GetCollect("ʱ��");
		    cThing = (TCHAR*)(_bstr_t)pRecordset->GetCollect("�¼�");
			cIfset = (TCHAR*)(_bstr_t)pRecordset->GetCollect("����");
		
		    m_list_tip.SetItemText(i, 0, cDate);
		    m_list_tip.SetItemText(i, 1, cTime);
		    m_list_tip.SetItemText(i, 2,cThing);

			if(cIfset=="��")
			{
				m_list_tip.SetItemText(i,3,"��");
                SYSTEMTIME st;
	            ::GetLocalTime(&st);
	            CString nDate,nTime,str;
                nDate.Format("%4d/%02d/%02d",st.wYear,st.wMonth,st.wDay);
                nTime.Format("%02d:%02d:%02d",st.wHour,st.wMinute,st.wSecond);	
		    
		    	if(cDate<nDate||(cDate==nDate&&cTime<nTime))
				{
					m_list_tip.SetItemText(i,3,"��");
				}
			}			
			i++;
		
		    pRecordset->MoveNext();
		}
	}

	ado.ExitConnection();
	
}




void CMyDlg::OnDblclkListTip(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
     *pResult = 0;
    nItem=-1;
    int nitem;

	POSITION pos = m_list_tip.GetFirstSelectedItemPosition();
	if (NULL == pos)
	{
		TRACE0("No items were selected!\n");
	}
	else
	{
		nitem = m_list_tip.GetNextSelectedItem(pos);
		nItem=nitem;
		   CString bDate=m_list_tip.GetItemText(nitem,0);
	CString bTime=m_list_tip.GetItemText(nitem,1);
	CString bThing=m_list_tip.GetItemText(nitem,2);

    CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();

    CString sql="select * from users where ʱ��= '"+bTime+"' AND �û�='"+m_usersname+"' AND ����='"+bDate+"'";
    pRecordset = ado.OpenRecordset(sql);

    CString ifset=(TCHAR*)(_bstr_t)pRecordset->GetCollect("����");

	if(ifset=="��")
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SETALARM);
	    pBtn->SetCheck(1);
	}
	if(ifset=="��")
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_SETALARM);
	    pBtn->SetCheck(0);
	}

	int y,m,d;
    sscanf(bDate,"%d/%d/%d",&y,&m,&d);
	CTime bDate1(y,m,d,0,0,0);

	m_date.SetTime(&bDate1);
	m_hour.SetWindowText(bTime.Left(bTime.Find(':')));
	CString str1=bTime.Right(bTime.GetLength()-1-bTime.Find(':'));
    m_minute.SetWindowText(str1.Left(str1.Find(':')));
	m_tipcontent.SetWindowText(bThing);
	}

 

}



void CMyDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	 int nitem;

	 POSITION pos = m_list_tip.GetFirstSelectedItemPosition();
	 if (NULL == pos)
	 {
		 TRACE0("No items were selected!\n");
	 }
	 else
	 {
		 nitem = m_list_tip.GetNextSelectedItem(pos);
		 CString cDate=m_list_tip.GetItemText(nitem, 0);
	 CString cTime=m_list_tip.GetItemText(nitem, 1);
	 CAdo ado;
	 ado.OnInitAdoConn();
	 _RecordsetPtr pRecordset = ado.GetRecordset();

	 CString sql = "select * from users where ʱ��= '"+cTime+"' AND �û�='"+m_usersname+"'AND ����='"+cDate+"'";		//sql���
	 pRecordset = ado.OpenRecordset(sql);
     pRecordset->Delete(adAffectCurrent);
	 pRecordset->Update();

     CString sql2= "select * from users where �û�='"+m_usersname+"'";		//sql���
	 pRecordset = ado.OpenRecordset(sql2);
	 if(pRecordset->RecordCount > 0)
	 {
		 int flag=0;
		 pRecordset->MoveFirst();
	     _variant_t cName1,cDate1;	
		 CString csName,csDate;
	     while (!pRecordset->adoEOF)
		{
			 cName1=pRecordset->GetCollect("�û�");
		     cDate1=pRecordset->GetCollect("����");
			 csName=(TCHAR*)(_bstr_t)cName1;
			 csDate=(TCHAR*)(_bstr_t)cDate1;

			 if(csName==m_usersname&&csDate==cDate)
			 {
				 flag=1;
			 }
			 pRecordset->MoveNext();
		}
		 
		 if(flag==0)
		 {
			 CString sql1 = "select * from set01 where ����= '"+cDate+"' AND �û�='"+m_usersname+"'";
             pRecordset = ado.OpenRecordset(sql1);
			 pRecordset->PutCollect("����¼",(_bstr_t)"��");
             pRecordset->Update();
		 }
		 MessageBox("ɾ���ɹ�");
	}
	 else if(pRecordset->RecordCount ==0)
	 {
		 CString sql3= "select * from set01 where ����= '"+cDate+"' AND �û�='"+m_usersname+"'";
         pRecordset = ado.OpenRecordset(sql3);
	     pRecordset->PutCollect("����¼",(_bstr_t)"��");
          pRecordset->Update();
   //       MessageBox("ɾ���ɹ�");
	 }

    pRecordset->Close();
	ado.ExitConnection();
	m_list_tip.DeleteItem(nitem);	
	nItem=-1;
    m_tipcontent.SetWindowText("");
	 }

	 //��ȡ��ǰ��ѡ�ж����1�е���
	 
}



UINT CMyDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
    return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}
//////////////////////////�¼��룬��Ϣӳ��
HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
		if(nCtlColor== CTLCOLOR_STATIC) 
    { 

        pDC->SetBkMode(TRANSPARENT);//���ñ���ģʽΪ͸��
        return (HBRUSH)GetStockObject(NULL_BRUSH);//����һ���ջ�ˢ
    }
	// TODO: Return a different brush if the default is not desired

	return hbr;
}
