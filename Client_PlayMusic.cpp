// Client_PlayMusic.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "Client_PlayMusic.h"
#include <stdlib.h>

#include <vector>
using namespace std;
vector<CString> Music_list;
extern begin;
extern mode;
extern pause;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CClient_PlayMusic
IMPLEMENT_DYNCREATE(CClient_PlayMusic, CWinThread)


CClient_PlayMusic::CClient_PlayMusic()
{
}

CClient_PlayMusic::~CClient_PlayMusic()
{
}

BOOL CClient_PlayMusic::InitInstance()
{
	// TODO:  perform and per-thread initialization here
    Play();
	return TRUE;
}

int CClient_PlayMusic::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CClient_PlayMusic, CWinThread)
	//{{AFX_MSG_MAP(CClient_PlayMusic)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
afx_msg ON_THREAD_MESSAGE(WM_STOP,Stop)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient_PlayMusic message handlers

void CClient_PlayMusic::Play()
{

   MCI_OPEN_PARMS open={0};
  // stop=1;
	//定义并初始化结构体  
    char szErr[100]="";//定义保存错误数组  
	int i=begin;
	mciSendCommand (0, MCI_CLOSE, NULL, NULL);
	pause=1;
    //open.lpstrElementName ="D:\\Entertainment\\Music\\songs\\G-Dragon - Black (feat. Jennie Kim of YG New Artist).mp3";//指定不放文件路径  
	open.lpstrElementName=Music_list[i];

    open.lpstrDeviceType = "mpegvideo";//指定播放设备  
  
    DWORD err;//定义错误信息  
    err = mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT|MCI_WAIT,(DWORD)(LPVOID)&open);//初始化音频设备  
	m_DeviceID=open.wDeviceID;
	
    if (err == 0)  
    {  
        MCI_PLAY_PARMS play;  
        play.dwFrom = 0;  
        play.dwCallback = NULL;  
 //       mciSendCommand(open.wDeviceID,MCI_PLAY,MCI_DGV_PLAY_REPEAT,(DWORD)&play);    //单曲循环
//		mciSendCommand(open.wDeviceID,MCI_PLAY,0,(DWORD)&play); 
		
		mciSendCommand(m_DeviceID,MCI_PLAY,MCI_NOTIFY|MCI_FROM,(DWORD)&play);
		//Sleep(10000);
		mciSendCommand (m_DeviceID, MCI_PAUSE, NULL, NULL);              //设置暂停
	//		mciSendCommand (m_DeviceID, MCI_RESUME, NULL, NULL); 		
//		mciSendCommand (m_DeviceID, MCI_STOP, NULL, NULL); 
		
//		mciSendCommand (m_DeviceID, MCI_CLOSE, NULL, NULL);              //设置停止
	do
	{

		MCI_STATUS_PARMS StatusParms;
		mciSendCommand (m_DeviceID, MCI_SEEK,MCI_SEEK_TO_END,NULL);
		StatusParms.dwItem = MCI_STATUS_POSITION;
		unsigned long wLength;
		mciSendCommand (m_DeviceID, MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&StatusParms);
		wLength=StatusParms.dwReturn;
        play.dwFrom = 0;  
        play.dwCallback = NULL;  
		mciSendCommand(m_DeviceID,MCI_PLAY,MCI_NOTIFY|MCI_FROM,(DWORD)&play);
//		if (stop==1)
//			mciSendCommand(m_DeviceID,MCI_CLOSE,NULL,NULL);

		while(1)
		{
			StatusParms.dwItem = MCI_STATUS_POSITION;
			mciSendCommand (m_DeviceID, MCI_STATUS,MCI_STATUS_ITEM,(DWORD)(LPVOID)&StatusParms);
			if (int(StatusParms.dwReturn>=wLength))
			{
				mciSendCommand(m_DeviceID,MCI_CLOSE,NULL,NULL);
				MCI_OPEN_PARMS open={0};
				switch (mode)
				{
					case  1:    //单曲循环
					break;
					case  2:    //列表循环
					i++;
					if (i==Music_list.size())
					{
						i=0;
					}
					break;
					case  3:	//随机播放
					i=rand()% Music_list.size();
					break;
					default :
					break;
				}
			   
				open.lpstrElementName=Music_list[i];
				open.lpstrDeviceType = "mpegvideo";
				mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT|MCI_WAIT,(DWORD)(LPVOID)&open);
				MCI_PLAY_PARMS play;  
				play.dwFrom = 0;  
				play.dwCallback = NULL;  
				mciSendCommand(m_DeviceID,MCI_PLAY,MCI_NOTIFY|MCI_FROM,(DWORD)&play);
				break;
			}
			if (pause==0)
			mciSendCommand(m_DeviceID,MCI_PAUSE,NULL,NULL);
			if (pause==1)
			mciSendCommand(m_DeviceID,MCI_RESUME,NULL,NULL);
			if (pause==3)
			{
			mciSendCommand(m_DeviceID,MCI_CLOSE,NULL,NULL);
			break;
			}

		}
			if (pause==3)
			{
			break;
			}
		
	}
	while (i<Music_list.size());
}
}



LRESULT CClient_PlayMusic::Stop(WPARAM wParam, LPARAM lParam)
{
    mciSendCommand(m_DeviceID,MCI_CLOSE,NULL,NULL);
	return 0;

}
