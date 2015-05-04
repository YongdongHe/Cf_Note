#if !defined(AFX_CLIENT_PLAYMUSIC_H__FAE40B35_4340_4FD0_AE44_CA322E4244E9__INCLUDED_)
#define AFX_CLIENT_PLAYMUSIC_H__FAE40B35_4340_4FD0_AE44_CA322E4244E9__INCLUDED_
#define WM_STOP WM_USER+1
	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Client_PlayMusic.h : header file
//
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")


/////////////////////////////////////////////////////////////////////////////
// CClient_PlayMusic thread

class CClient_PlayMusic : public CWinThread
{
	DECLARE_DYNCREATE(CClient_PlayMusic)
protected:
	CClient_PlayMusic();           // protected constructor used by dynamic creation

// Attributes
public:


// Operations
public:
	LRESULT Stop(WPARAM wParam,LPARAM lParam);
	void Play();
	MCIDEVICEID m_DeviceID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient_PlayMusic)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CClient_PlayMusic();

	// Generated message map functions
	//{{AFX_MSG(CClient_PlayMusic)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_PLAYMUSIC_H__FAE40B35_4340_4FD0_AE44_CA322E4244E9__INCLUDED_)
