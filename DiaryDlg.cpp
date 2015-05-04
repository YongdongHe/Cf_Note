// DiaryDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "DiaryDlg.h"
#include "Ado.h"

#include "winuser.h"
#include "windef.h"
#pragma comment(lib,"user32.LIB")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int weather;

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
// CDiaryDlg dialog

CDiaryDlg::CDiaryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiaryDlg::IDD, pParent),strFolderPath("d:\\Learning\\׿��\\MyProjects\\�ռ�\\")
{
	//{{AFX_DATA_INIT(CDiaryDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_weather=1;
	
}

void CDiaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiaryDlg)
	DDX_Control(pDX, IDC_BUTTON_Weather, m_weatherkid);
	DDX_Control(pDX, IDC_BUTTON_SD, m_DiaryOpen);
	DDX_Control(pDX, IDOK, m_DiarySave);
	DDX_Control(pDX, IDCANCEL, m_DiaryClose);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_save);
	DDX_Control(pDX, IDC_EDIT_HEAD, m_head);
	DDX_Control(pDX, IDC_COMBO_Date, m_Name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDiaryDlg, CDialog)
	//{{AFX_MSG_MAP(CDiaryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_Date, OnSelchangeCOMBODate)
	ON_EN_SETFOCUS(IDC_EDIT_TEXT, OnSetfocusEditText)
	ON_EN_SETFOCUS(IDC_EDIT_HEAD, OnSetfocusEditHead)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_Weather, OnBUTTONWeather)
	ON_BN_CLICKED(IDC_BUTTON_SD, OnButtonSd)
	ON_EN_CHANGE(IDC_EDIT_HEAD, OnChangeEditHead)
	ON_WM_NCHITTEST()
	ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiaryDlg message handlers

BOOL CDiaryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos); 
	pos = path.ReverseFind('\\');
	path = path.Left(pos);
	strFolderPath="d"+strFolderPath.Right(strFolderPath.GetLength()-1);	
	strFolderPath=path+"\\�ռ�\\";

	SECURITY_ATTRIBUTES attribute;
    attribute.nLength = sizeof(attribute);
	attribute.lpSecurityDescriptor = NULL;
    attribute.bInheritHandle = FALSE;

	CreateDirectoryA(strFolderPath,&attribute) ;
	strFolderPath=path+"\\�ռ�\\"+m_username+"\\";
	

    //����
    CreateDirectoryA(strFolderPath,&attribute) ;

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
	//���ر����Ͱ�ť��Դ
	m_weatherkid.SetButtonType(m_weatherkid.BS_FIXED);
	switch(m_weather)
	{
	case 1:
		m_Bitmap_Diarybg.LoadBitmap(IDB_BITMAP_Diarybg1);
		m_weatherkid.LoadFixBitmap(IDB_BITMAP_Kid1);
		break;
	case 2:
		m_Bitmap_Diarybg.LoadBitmap(IDB_BITMAP_Diarybg2);
		m_weatherkid.LoadFixBitmap(IDB_BITMAP_Kid2);
		break;
	case 3:
		m_Bitmap_Diarybg.LoadBitmap(IDB_BITMAP_Diarybg3);
		m_weatherkid.LoadFixBitmap(IDB_BITMAP_Kid3);
		break;
	default:
		break;
	}


	m_DiarySave.LoadOffBitmap(IDB_BITMAP_Diary_Save1);
	m_DiarySave.LoadLightBitmap(IDB_BITMAP_Diary_Save2);
	m_DiarySave.LoadOnBitmap(IDB_BITMAP_Diary_Save1);

	m_DiaryOpen.LoadOffBitmap(IDB_BITMAP_Diary_Open1);
	m_DiaryOpen.LoadLightBitmap(IDB_BITMAP_Diary_Open2);
	m_DiaryOpen.LoadOnBitmap(IDB_BITMAP_Diary_Open1);

	m_DiaryClose.LoadOffBitmap(IDB_BITMAP_Diary_Close1);
	m_DiaryClose.LoadLightBitmap(IDB_BITMAP_Diary_Close2);
	m_DiaryClose.LoadOnBitmap(IDB_BITMAP_Diary_Close1);


	GetFileFromDir(strFolderPath);
	m_CreateFile=FALSE;
	

	SetTimer(2,60000,NULL);

	m_Bitmap_text.LoadBitmap(IDB_BITMAP1);
	hEdit=GetDlgItem(IDC_EDIT_TEXT)->m_hWnd;
		
	CEdit* pEdt=(CEdit*)GetDlgItem(IDC_EDIT_TEXT);
    font.CreatePointFont(144,m_font);
    pEdt->SetFont(&font);
	
	pEdt=(CEdit*)GetDlgItem(IDC_EDIT_HEAD);
    pEdt->SetFont(&font);
	
	CStatic* pSta=(CStatic*)GetDlgItem(IDC_STATIC_THE);
    pSta->SetFont(&font);


	//��ʼ����������,0��ʾδ�趨��1�������죬2�������죬3��������
//	m_weather=0;

	//�����ռǱ༭������ʾ�ĵ�������
	CString strrM;
	GetLocalTime(&Time1);
	strrM.Format("%4d",Time1.wYear);
	m_Today+=strrM+"/";	
	strrM.Format("%02d",Time1.wMonth);
	m_Today+=strrM+"/";
	strrM.Format("%02d",Time1.wDay);
	m_Today+=strrM;
	m_Today+="                \r\n";
	m_save.SetWindowText(m_Today);

	m_ComBCtrl=FALSE;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDiaryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
	}
//	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDiaryDlg::OnPaint() 
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
		m_Bitmap_Diarybg.GetBitmap (&bm);
		GetClientRect(&rect);
		dcMem.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem.SelectObject (&m_Bitmap_Diarybg);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
		dcMem.SelectObject(oldbitmap);
        CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDiaryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDiaryDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!m_CreateFile)
	{
		CreateDiary();
		m_CreateFile=TRUE;
		CString strr;
		m_head.GetWindowText(strr);
		m_Name.AddString(strr);
	}

		CString DiaryTime;
		m_save.GetWindowText(DiaryTime);
		DiaryTime=m_Today.Left(10);

	    CAdo ado;
	    ado.OnInitAdoConn();
	    _RecordsetPtr pRecordset = ado.GetRecordset();


        CString sql="select * from set01 where �û�='"+m_username+"'";
        pRecordset = ado.OpenRecordset(sql);
       
    int flag=0;
	try
	{

		if(pRecordset->RecordCount>0)
			{
				pRecordset->MoveFirst();
	            _variant_t cName,cDate,cTip;	
				CString csName,csDate,csTip;
	            while (!pRecordset->adoEOF)
				{
					cName=pRecordset->GetCollect("�û�");
					cDate=pRecordset->GetCollect("����");
					cTip=pRecordset->GetCollect("�ռ�");

					csName=(TCHAR*)(_bstr_t)cName;
					csDate=(TCHAR*)(_bstr_t)cDate;
                    csTip=(TCHAR*)(_bstr_t)cTip;

					if(csName==m_username&&csDate==DiaryTime&&csTip=="��")
					{
						flag=1;
					}
                    if(csName==m_username&&csDate==DiaryTime&&csTip=="��")
					{
						pRecordset->PutCollect("�ռ�",(_bstr_t)"��");
                        flag=1;
                        pRecordset->Update();
					} 
		            pRecordset->MoveNext();
				}
				if(flag==0)
				{
					pRecordset->AddNew();
                    pRecordset->PutCollect("�û�",(_bstr_t)m_username);
                    pRecordset->PutCollect("����",(_bstr_t)DiaryTime);
					pRecordset->PutCollect("����¼",(_bstr_t)"��");
                    pRecordset->PutCollect("�ռ�",(_bstr_t)"��");
                    pRecordset->Update();
				}
                
			}
            if(pRecordset->RecordCount==0)
			{
				pRecordset->AddNew();
                pRecordset->PutCollect("�û�",(_bstr_t)m_username);
                pRecordset->PutCollect("����",(_bstr_t)DiaryTime);
                pRecordset->PutCollect("�ռ�",(_bstr_t)"��");
				pRecordset->PutCollect("����¼",(_bstr_t)"��");
                pRecordset->Update();
			}
            pRecordset->Close();
            ado.ExitConnection();
		}
		catch(...)
		{
			MessageBox("����ʧ��");
		}

	AutoSave();

	//CDialog::OnOK();
}

//�����ռ��ļ���
void CDiaryDlg::CreateDiary()   
{

	CString str;
	m_head.GetWindowText(str);

	if (""==str)
	{
		str.Format("%4d%02d%02d",Time1.wYear,Time1.wMonth,Time1.wDay);
	}
    //��������

	str=strFolderPath+str;
   	str+=".txt";
	m_file.Open(_T(str),CFile::modeCreate|CFile::modeNoTruncate);
	m_file.Close();

	
}

//�Զ������ռ�
void CDiaryDlg::AutoSave()    
{
	CString strText="";
	char write[10000];
	CString Title;
	m_head.GetWindowText(Title);
	if (Title=="")
	{
		Title.Format("%4d%02d%02d",Time1.wYear,Time1.wMonth,Time1.wDay);
	}
	Title=strFolderPath+Title+".txt";
	m_file.Open(Title,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	m_save.GetWindowText(strText);
	strcpy(write,strText);
	m_file.Write(write,strText.GetLength());
	m_file.Close();
}

void CDiaryDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	  if (nIDEvent==2)
	  {
		AutoSave();
	  }
	CDialog::OnTimer(nIDEvent);


}

//��ȡ�ռ��ļ����е��ļ�
void CDiaryDlg::GetFileFromDir(CString csDirPath)
{
	csDirPath+="\\*.txt";  
    HANDLE file3;  
    WIN32_FIND_DATA fileData;  
    char line[1024]="";  
    char fn[1000]="";  
    //mbstowcs(fn,csDirPath.GetBuffer(),999);  
	file3 = FindFirstFile(csDirPath.GetBuffer(500), &fileData);  
	if (file3!=INVALID_HANDLE_VALUE)
	{

		m_FileList.push_back(fileData.cFileName);  
		bool bState = false;  
		bState = FindNextFile(file3, &fileData);  
		while(bState)
		{  
			//wcstombs(line,(const char*)fileData.cFileName,259);  
			m_FileList.push_back(fileData.cFileName);  
			bState = FindNextFile(file3, &fileData);  
		}  
	}
		if (m_FileList.size()>0)
		{
			for (int i=0;i<m_FileList.size();i++)
			{
				m_FileList[i]=m_FileList[i].Left(m_FileList[i].GetLength()-4);
				m_Name.AddString(m_FileList[i]);
			}
		}

}

//ͨ��ѡ���������鿴��ǰ���ռ�
void CDiaryDlg::OnSelchangeCOMBODate() 
{
	// TODO: Add your control notification handler code here

	CString csText;
	int index=m_Name.GetCurSel();
	m_Name.GetLBText(index,csText);

	if ("�µ��ռ�"==csText)	       //�½��ռ�
	{	
		m_CreateFile=FALSE;
		m_head.SetWindowText("");
		m_save.SetWindowText(m_Today);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
	else                       //�������ռ�
	{
	m_CreateFile=TRUE;

	CFile File;
	CString ssss=strFolderPath+csText+".txt";
	File.Open(ssss,CFile::modeCreate|CFile::modeNoTruncate);

	CFileStatus fStatus;
	File.GetStatus(fStatus);
	File.Close();
	CString time=fStatus.m_ctime.Format("%Y%m%d");
	CString Date;
	Date.Format("%4d%02d%02d",Time1.wYear,Time1.wMonth,Time1.wDay);
			
	m_save.EnableWindow(TRUE);
	m_head.EnableWindow(TRUE);
	m_head.SetWindowText(csText);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
		
	m_file.Open(ssss,CFile::modeRead);		
	char read[10000]="";
	m_file.Read(read,10000);
	m_save.SetWindowText(read);
	m_file.Close();
	AutoSave();    

	}
	Refresh(IDC_EDIT_TEXT);
	Refresh(IDC_COMBO_Date);
	Refresh(IDC_EDIT_HEAD);

}

void CDiaryDlg::OnSetfocusEditText() 
{
	// TODO: Add your control notification handler code here

	    m_save.CreateCaret(&m_Bitmap_text);
		m_save.ShowCaret();
		Refresh(IDC_EDIT_TEXT);

}


void CDiaryDlg::OnSetfocusEditHead() 
{
	// TODO: Add your control notification handler code here
		m_head.CreateCaret(&m_Bitmap_text);
		m_head.ShowCaret();
		Refresh(IDC_EDIT_HEAD);

}

HBRUSH CDiaryDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor== CTLCOLOR_EDIT) 
    { 

        pDC->SetBkMode(TRANSPARENT);//���ñ���ģʽΪ͸��
        return (HBRUSH)GetStockObject(NULL_BRUSH);//����һ���ջ�ˢ
    }
     if(nCtlColor== CTLCOLOR_STATIC) 
    { 

        pDC->SetBkMode(TRANSPARENT);//���ñ���ģʽΪ͸��
        return (HBRUSH)GetStockObject(NULL_BRUSH);//����һ���ջ�ˢ
    }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}



void CDiaryDlg::OnBUTTONWeather() 
{
	// TODO: Add your control notification handler code here
/*	CString str;
	CString sttr;
	m_save.GetWindowText(str);

	sttr=str.Right(str.GetLength()-26);
	str=str.Left(15);


	m_weather++;
	str+="   ������";
	if (4==m_weather)
	{
		m_weather=0;
	}

	switch (m_weather)
	{
	case 0:
		str+="  ";
		break;
	case 1:
		str+="��";
		break;
	case 2:
		str+="��";
		break;
	case 3:
		str+="��";
		break;
	default:
		break;
	}*/
	m_weather++;
	if(m_weather==4)
	{
		m_weather=1;
	}
	switch(m_weather)
	{
	case 1:
		m_Bitmap_Diarybg.DeleteObject();
		m_Bitmap_Diarybg.LoadBitmap(IDB_BITMAP_Diarybg1);
		m_weatherkid.LoadFixBitmap(IDB_BITMAP_Kid1);
		break;
	case 2:
		m_Bitmap_Diarybg.DeleteObject();
		m_Bitmap_Diarybg.LoadBitmap(IDB_BITMAP_Diarybg2);
		m_weatherkid.LoadFixBitmap(IDB_BITMAP_Kid2);
		break;
	case 3:
		m_Bitmap_Diarybg.DeleteObject();
		m_Bitmap_Diarybg.LoadBitmap(IDB_BITMAP_Diarybg3);
		m_weatherkid.LoadFixBitmap(IDB_BITMAP_Kid3);
		break;
	default:
		break;
	}
	Invalidate();
	m_weatherkid.Invalidate();


	
}

void CDiaryDlg::Refresh(long WindowID)
{
	CRect rc;
    GetDlgItem(WindowID)->GetWindowRect(&rc);
    //ת��Ϊ�������
    ScreenToClient(&rc);
    //ˢ��ָ������,ע���2������Ϊ��,��ˢ�±���
    InvalidateRect(&rc,TRUE);
	rc.left=rc.right;
	rc.right=rc.right+16;
	InvalidateRect(&rc,TRUE);
}

void CDiaryDlg::OnButtonSd() 
{
	// TODO: Add your control notification handler code here
	if (!m_ComBCtrl)
	{
		m_Name.ShowWindow(TRUE);
		m_ComBCtrl=!m_ComBCtrl;
	}
	else
	{
		m_Name.ShowWindow(FALSE);
		m_ComBCtrl=!m_ComBCtrl;
	}
	

	
}

void CDiaryDlg::OnChangeEditHead() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	Refresh(IDC_EDIT_HEAD);
	// TODO: Add your control notification handler code here
	
}

UINT CDiaryDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
    return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}

void CDiaryDlg::OnChangeEditText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	Refresh(IDC_EDIT_TEXT);
	
	// TODO: Add your control notification handler code here
	
}
