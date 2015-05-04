// MUSICDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "MUSICDlg.h"
#include "Client_PlayMusic.h"
#include "Ado.h"

#include <vector>
using namespace std;
extern vector<CString> Music_list;

int mode=2;
int begin;
int pause=1;
BOOL stop=0;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/*
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
private:

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
// CMUSICDlg dialog

CMUSICDlg::CMUSICDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUSICDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMUSICDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMUSICDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMUSICDlg)
	DDX_Control(pDX, IDC_COMBO_FONT, m_ClientFont);
	DDX_Control(pDX, IDC_BUTTON_Play, m_music_add);
	DDX_Control(pDX, IDC_BUTTON_Mode, m_music_mode);
	DDX_Control(pDX, IDC_BUTTON_Pause, m_music_pauseorplay);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_music_Close);
	DDX_Control(pDX, IDC_SLIDER_Volume, m_Volume);
	DDX_Control(pDX, IDC_COMBO_MusicList, m_Select);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMUSICDlg, CDialog)
	//{{AFX_MSG_MAP(CMUSICDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Play, OnBUTTONPlay)
	ON_BN_CLICKED(IDC_BUTTON_Pause, OnBUTTONPause)
	ON_CBN_SELCHANGE(IDC_COMBO_MusicList, OnSelchangeCOMBOMusicList)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON_Mode, OnBUTTONMode)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_FONT, OnSelchangeComboFont)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMUSICDlg message handlers

BOOL CMUSICDlg::OnInitDialog()
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
	CtlVolume();
	//加载背景和按钮资源：
	m_Bitmap_Musicbg.LoadBitmap(IDB_BITMAP_Musicbg);

	m_music_pauseorplay.SetButtonType(m_music_pauseorplay.BS_UNAUTO);
	m_music_pauseorplay.LoadOnBitmap(IDB_BITMAP_Musicpause);
	m_music_pauseorplay.LoadOffBitmap(IDB_BITMAP_Musicplay);

	m_music_add.LoadOnBitmap(IDB_BITMAP_Musicadd);
	m_music_add.LoadOffBitmap(IDB_BITMAP_Musicadd);

	m_music_Close.LoadOnBitmap(IDB_BITMAP_Diary_Close1);
	m_music_Close.LoadLightBitmap(IDB_BITMAP_Diary_Close2);
	m_music_Close.LoadOffBitmap(IDB_BITMAP_Diary_Close1);


	//mode按钮未编完整，暂时代替by 何。9.14
	m_music_mode.SetButtonType(m_music_mode.BS_FIXED);
	switch(mode)
	{
	case 1:
		m_music_mode.LoadFixBitmap(IDB_BITMAP_MusicSingle);
		break;
	case 2:
		m_music_mode.LoadFixBitmap(IDB_BITMAP_MusicOrder);
		break;
    case 3:
		m_music_mode.LoadFixBitmap(IDB_BITMAP_MusicRandom);
		break;
	default:
		break;
	}
	
	



	//加载音乐列表
	CAdo ado;
	ado.OnInitAdoConn();
	_RecordsetPtr pRecordset = ado.GetRecordset();
	CString sql="select * from MusicList where 用户='"+m_username+"'";
    pRecordset = ado.OpenRecordset(sql);
	
	if(pRecordset->RecordCount>0)
	{
		pRecordset->MoveFirst();
        _variant_t cMusic;	
		CString csMusic;
		while (!pRecordset->adoEOF)
		{
			cMusic=pRecordset->GetCollect("音乐");
			csMusic=(TCHAR*)(_bstr_t)cMusic;
			Music_list.push_back(csMusic);
			int n=csMusic.ReverseFind('\\');
			csMusic=csMusic.Right(csMusic.GetLength()-n-1);
			csMusic=csMusic.Left(csMusic.GetLength()-4);
			m_Select.AddString(csMusic);

			pRecordset->MoveNext();

		}
	}
	
	m_FontList.push_back("隶书");
	m_FontList.push_back("华文新魏");
	m_FontList.push_back("微软雅黑");
	m_FontList.push_back("方正舒体");		




	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMUSICDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMUSICDlg::OnPaint() 
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
		m_Bitmap_Musicbg.GetBitmap (&bm);
		GetClientRect(&rect);
		dcMem.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem.SelectObject (&m_Bitmap_Musicbg);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem,0,0,SRCCOPY);
        dcMem.SelectObject(oldbitmap);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMUSICDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}





void CMUSICDlg::OnBUTTONPlay() 
{
	CString FilePathName;
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_ALLOWMULTISELECT|OFN_ENABLESIZING,NULL);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
   int size=Music_list.size();
	if(dlg.DoModal()==IDOK)
   {
   //FilePathName=dlg.GetPathName();
	   
	   POSITION pos=dlg.GetStartPosition( );
	   while(pos!=NULL)
	   {
    	Music_list.push_back(dlg.GetNextPathName(pos));
	   }
	   	CAdo ado;
	    ado.OnInitAdoConn();
	    _RecordsetPtr pRecordset = ado.GetRecordset();


        CString sql="select * from MusicList where 用户='"+m_username+"'";
        pRecordset = ado.OpenRecordset(sql);
       
        try
		{
			if(Music_list.size()>0)
			for (int i=size;i<Music_list.size();i++)
			{
            pRecordset->AddNew();
            pRecordset->PutCollect("用户",(_bstr_t)m_username);
            pRecordset->PutCollect("音乐",(_bstr_t)Music_list[i]);
            pRecordset->Update();

			}
	   }
		catch(...)
		{
			AfxMessageBox("出现错误");
		}



   }
    CString str;

	for (int i=size;i<Music_list.size();i++)
	{	

	str=Music_list[i];
	int n=str.ReverseFind('\\');
	str=str.Right(str.GetLength()-n-1);
	str=str.Left(str.GetLength()-4);
		m_Select.AddString(str);

	}
}

void CMUSICDlg::OnBUTTONPause() 
{
	// TODO: Add your control notification handler code here

	pause=!pause;
}


void CMUSICDlg::OnSelchangeCOMBOMusicList() 
{
	// TODO: Add your control notification handler code here

	begin=m_Select.GetCurSel();
	pause=3;
	if (begin<0)
		begin=Music_list.size()-1;
	hThread=(CClient_PlayMusic*)AfxBeginThread(RUNTIME_CLASS(CClient_PlayMusic));
	
}

void CMUSICDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
		if((CWnd*)pScrollBar == (CWnd*)&m_Volume)  
    {  
        int pos = mxc.Bounds.dwMaximum - m_Volume.GetPos();  
        CString str;  
        str.Format("%d",pos);  
       // MessageBox(str);  
        volStruct.lValue = pos; //想要设置的值  
        mixerSetControlDetails((HMIXEROBJ)m_hmx, &mxcd,  
        MIXER_SETCONTROLDETAILSF_VALUE);   
    }  
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMUSICDlg::CtlVolume()
{

		unsigned long err;  
	CString str;  
	err = mixerOpen(&m_hmx,0,0,0,0);  
	if(err)  
	{  
		MessageBox("ERROR:Can't open Mixer Device!");  
	}  

	//初始化MIXERLINE结构体  
	ZeroMemory(&mxl,sizeof(mxl));  
	mxl.cbStruct = sizeof(mxl);
  
// 指出需要获取的通道，扬声器用MIXERLINE_COMPONENTTYPE_DST_SPEAKERS  
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;  
	if(mixerGetLineInfo((HMIXEROBJ)m_hmx,&mxl,  
    MIXER_GETLINEINFOF_COMPONENTTYPE))  
	{  
		MessageBox("Couldn't get the mixer line!");  
	}
  
// 取得控制器.  
	ZeroMemory(&mxlc, sizeof(mxlc));  
	mxlc.cbStruct = sizeof(mxlc);  
	mxlc.dwLineID = mxl.dwLineID;  
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;  
	mxlc.cControls =1;  
	mxlc.cbmxctrl = sizeof(mxc);  
	mxlc.pamxctrl = &mxc;  
	ZeroMemory(&mxc, sizeof(mxc));  
	mxc.cbStruct = sizeof(mxc);  
	if(mixerGetLineControls((HMIXEROBJ)m_hmx,&mxlc,  
    MIXER_GETLINECONTROLSF_ONEBYTYPE))  
	{  
		MessageBox("取得控制器失败!");  
	}  
// 获取控制器中的值的音量范围：mxc.Bounds.lMinimum到mxc.Bounds.lMaximum.  
  
// 初始化MIXERCONTROLDETAILS结构体  
	ZeroMemory(&mxcd, sizeof(mxcd));  
	mxcd.cbStruct = sizeof(mxcd);  
	mxcd.cbDetails = sizeof(volStruct);  
	mxcd.dwControlID = mxc.dwControlID;  
	mxcd.paDetails = &volStruct;  
	mxcd.cChannels = 1;  
  
// 获得音量值  
	if(mixerGetControlDetails((HMIXEROBJ)m_hmx, &mxcd,  
    MIXER_GETCONTROLDETAILSF_VALUE))  
	{  
		MessageBox("无法获得音量");  
	}  

m_Volume.SetRange(mxc.Bounds.dwMinimum,mxc.Bounds.dwMaximum);
m_Volume.SetPos(mxc.Bounds.dwMaximum - volStruct.lValue);  
}

void CMUSICDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}


UINT CMUSICDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
    return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
}

void CMUSICDlg::OnBUTTONMode() 
{
	// TODO: Add your control notification handler code here
	mode++;
	if (mode==4)
		mode=1;
	switch(mode)
	{
	case 1:
		m_music_mode.LoadFixBitmap(IDB_BITMAP_MusicSingle);
		break;
	case 2:
		m_music_mode.LoadFixBitmap(IDB_BITMAP_MusicOrder);
		break;
    case 3:
		m_music_mode.LoadFixBitmap(IDB_BITMAP_MusicRandom);
		break;
	default:
		break;
	}
	m_music_mode.Invalidate();

/*	CRect rc;
	GetDlgItem(IDC_BUTTON_Mode)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	InvalidateRect(&rc,TRUE);
	*/
	
}


void CMUSICDlg::OnSelchangeComboFont() 
{
	// TODO: Add your control notification handler code here
	 int select=m_ClientFont.GetCurSel();
     m_font=m_FontList[select];
	
}
