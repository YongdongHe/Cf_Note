; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStaticCalendarDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "client.h"
LastPage=0

ClassCount=18
Class1=CClientApp
Class2=CClient_PlayMusic
Class3=CAboutDlg
Class4=CClientDlg
Class5=CClientRegister
Class6=CDiaryDlg
Class7=CMainDlg
Class8=CMUSICDlg
Class9=CSpringButton
Class10=CTip
Class11=CMyDlg

ResourceCount=12
Resource1=IDD_DIALOG_TIP
Resource2=IDD_DIARY_DIALOG
Resource3=IDD_CLIENT_Safety
Resource4=IDD_CLIENT_LoginDlg
Resource5=IDD_DIALOG_Setting
Resource6=IDD_CLIENT_RegisterDlg
Resource7=IDD_MUSIC_DIALOG
Resource8=IDD_ABOUTBOX
Resource9=IDD_CLIENT_INFO
Resource10=IDD_DIALOG_MAIN
Class12=CSetting
Class13=CSatety
Class14=CInfo
Class15=CMessage
Class16=CCalendarCtrl
Class17=CEditDlg
Class18=CStaticCalendarDlg
Resource11=IDD_MY_DIALOG
Resource12=IDD_STATICCALENDAR_DIALOG

[CLS:CClientApp]
Type=0
BaseClass=CWinApp
HeaderFile=Client.h
ImplementationFile=Client.cpp

[CLS:CClient_PlayMusic]
Type=0
BaseClass=CWinThread
HeaderFile=Client_PlayMusic.h
ImplementationFile=Client_PlayMusic.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ClientDlg.cpp
ImplementationFile=ClientDlg.cpp
LastObject=CAboutDlg

[CLS:CClientDlg]
Type=0
BaseClass=CDialog
HeaderFile=ClientDlg.h
ImplementationFile=ClientDlg.cpp
LastObject=IDC_EDIT_Pwd
Filter=D
VirtualFilter=dWC

[CLS:CClientRegister]
Type=0
BaseClass=CDialog
HeaderFile=ClientRegister.h
ImplementationFile=ClientRegister.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_PwdSure

[CLS:CDiaryDlg]
Type=0
BaseClass=CDialog
HeaderFile=DiaryDlg.h
ImplementationFile=DiaryDlg.cpp
Filter=W
VirtualFilter=dWC
LastObject=CDiaryDlg

[CLS:CMainDlg]
Type=0
BaseClass=CDialog
HeaderFile=MainDlg.h
ImplementationFile=MainDlg.cpp
LastObject=IDC_BUTTON_MINI
Filter=W
VirtualFilter=dWC

[CLS:CMUSICDlg]
Type=0
BaseClass=CDialog
HeaderFile=MUSICDlg.h
ImplementationFile=MUSICDlg.cpp
Filter=W
VirtualFilter=dWC
LastObject=CMUSICDlg

[CLS:CSpringButton]
Type=0
BaseClass=CButton
HeaderFile=SpringButton.h
ImplementationFile=SpringButton.cpp

[CLS:CTip]
Type=0
BaseClass=CDialog
HeaderFile=Tip.h
ImplementationFile=Tip.cpp
LastObject=CTip
Filter=W
VirtualFilter=dWC

[CLS:CMyDlg]
Type=0
BaseClass=CDialog
HeaderFile=定时提醒Dlg.h
ImplementationFile=定时提醒Dlg.cpp
Filter=W
VirtualFilter=dWC
LastObject=IDC_LIST_TIP

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CLIENT_LoginDlg]
Type=1
Class=CClientDlg
ControlCount=5
Control1=IDC_EDIT_Admin,edit,1342242944
Control2=IDC_EDIT_Pwd,edit,1342242976
Control3=IDC_BUTTON_Log,button,1342242816
Control4=IDC_BUTTON_Register,button,1342242816
Control5=IDC_BUTTON_Close,button,1342242816

[DLG:IDD_CLIENT_RegisterDlg]
Type=1
Class=CClientRegister
ControlCount=6
Control1=IDOK,button,1342242816
Control2=IDC_EDIT_NewAdmin,edit,1342242944
Control3=IDC_EDIT_PwdSet,edit,1342242976
Control4=IDC_EDIT_PwdSure,edit,1342242976
Control5=IDC_BUTTON_AdminCheck,button,1342242816
Control6=IDC_Close,button,1342242816

[DLG:IDD_DIARY_DIALOG]
Type=1
Class=CDiaryDlg
ControlCount=8
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_TEXT,edit,1350635588
Control4=IDC_EDIT_HEAD,edit,1350631492
Control5=IDC_COMBO_Date,combobox,1073807425
Control6=IDC_BUTTON_Weather,button,1342242816
Control7=IDC_BUTTON_SD,button,1342242816
Control8=IDC_STATIC_THE,static,1342308352

[DLG:IDD_DIALOG_MAIN]
Type=1
Class=CMainDlg
ControlCount=8
Control1=IDC_BUTTON_Memorandum,button,1342242816
Control2=IDC_BUTTON_Diary,button,1342242816
Control3=IDC_BUTTON_Setting,button,1342242816
Control4=IDC_BUTTON_Calendar,button,1342242816
Control5=IDC_Button_MainClose,button,1342242816
Control6=IDC_STATIC_Motto,static,1342308352
Control7=IDC_STATIC_GREET,static,1342308352
Control8=IDC_BUTTON_MINI,button,1342242816

[DLG:IDD_MUSIC_DIALOG]
Type=1
Class=CMUSICDlg
ControlCount=7
Control1=IDC_SLIDER_Volume,msctls_trackbar32,1342242840
Control2=IDC_COMBO_MusicList,combobox,1344339971
Control3=IDC_BUTTON_Play,button,1342242816
Control4=IDC_BUTTON_Pause,button,1342242816
Control5=IDC_BUTTON_Mode,button,1342242816
Control6=IDC_BUTTON_EXIT,button,1342242816
Control7=IDC_COMBO_FONT,combobox,1344339970

[DLG:IDD_DIALOG_TIP]
Type=1
Class=CTip
ControlCount=7
Control1=IDC_EDIT_REGULARTIP,edit,1342242944
Control2=IDC_EDIT_LASTMINUTE,edit,1350631552
Control3=IDC_BUTTON_OK,button,1342242816
Control4=IDC_EDIT_TIME,edit,1342247044
Control5=IDC_BUTTON_SHUT,button,1342242816
Control6=IDC_CHECK_OPEN,button,1342242819
Control7=IDC_BUTTON_TipClose,button,1342242816

[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=12
Control1=IDCANCEL,button,1342242816
Control2=IDC_EDIT_TIP,edit,1350631552
Control3=IDC_DATETIMEPICKER_DATE,SysDateTimePick32,1342242848
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_HOUR,combobox,1344340226
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMBO_MINUTE,combobox,1344340226
Control9=IDC_LIST_TIP,SysListView32,1350631425
Control10=IDC_BUTTON_SAVE,button,1342242816
Control11=IDC_BUTTON_DELETE,button,1342242816
Control12=IDC_CHECK_SETALARM,button,1342242819

[DLG:IDD_CLIENT_Safety]
Type=1
Class=CSatety
ControlCount=5
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_FIRST,edit,1350631584
Control4=IDC_EDIT_SECOND,edit,1350631584
Control5=IDC_EDIT_THIRD,edit,1350631584

[DLG:IDD_CLIENT_INFO]
Type=1
Class=CInfo
ControlCount=8
Control1=IDOK,button,1342242816
Control2=IDC_EDIT_NICKNAME,edit,1350631552
Control3=IDC_EDIT_BIRTHDAY,edit,1350631552
Control4=IDC_EDIT_HABIT,edit,1350631552
Control5=IDC_EDITCONSTELLATION,edit,1350631552
Control6=IDC_EDIT_WEIGHT,edit,1350631552
Control7=IDC_EDIT_HEIGHT,edit,1350631552
Control8=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_Setting]
Type=1
Class=CSetting
ControlCount=4
Control1=IDC_BUTTON_Safety,button,1342242816
Control2=IDC_BUTTON_INFO,button,1342242816
Control3=IDC_BUTTON_MUSIC,button,1342242816
Control4=IDC_BUTTON_SetClose,button,1342242816

[CLS:CSetting]
Type=0
HeaderFile=Setting.h
ImplementationFile=Setting.cpp
BaseClass=CDialog
Filter=W
LastObject=CSetting
VirtualFilter=dWC

[CLS:CSatety]
Type=0
HeaderFile=Satety.h
ImplementationFile=Satety.cpp
BaseClass=CDialog
Filter=W
LastObject=IDC_EDIT_THIRD
VirtualFilter=dWC

[CLS:CInfo]
Type=0
HeaderFile=Info.h
ImplementationFile=Info.cpp
BaseClass=CDialog
Filter=W
LastObject=IDC_EDIT_BIRTHDAY
VirtualFilter=dWC

[CLS:CMessage]
Type=0
HeaderFile=Message.h
ImplementationFile=Message.cpp
BaseClass=CDialog

[CLS:CCalendarCtrl]
Type=0
HeaderFile=CalendarCtrl.h
ImplementationFile=CalendarCtrl.cpp
BaseClass=CStatic

[CLS:CEditDlg]
Type=0
HeaderFile=EditDlg.h
ImplementationFile=EditDlg.cpp
BaseClass=CDialog

[CLS:CStaticCalendarDlg]
Type=0
HeaderFile=StaticCalendarDlg.h
ImplementationFile=StaticCalendarDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATIC_Holiday

[DLG:IDD_STATICCALENDAR_DIALOG]
Type=1
Class=CStaticCalendarDlg
ControlCount=9
Control1=IDC_CALENDAR,static,1342177287
Control2=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control3=IDC_CHECK1,button,1073807363
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_BUTTON3,button,1342242816
Control7=IDC_BUTTON4,button,1342242816
Control8=IDC_BUTTON5,button,1342242816
Control9=IDC_BUTTON6,button,1342242816

