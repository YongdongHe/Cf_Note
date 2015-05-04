# Microsoft Developer Studio Project File - Name="Client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Client - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak" CFG="Client - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Client - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Client - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Client - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Client - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 gdi32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Client - Win32 Release"
# Name "Client - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Ado.cpp
# End Source File
# Begin Source File

SOURCE=.\CalendarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.rc
# End Source File
# Begin Source File

SOURCE=.\Client_PlayMusic.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Info.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MUSICDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Satety.cpp
# End Source File
# Begin Source File

SOURCE=.\Setting.cpp
# End Source File
# Begin Source File

SOURCE=.\SpringButton.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticCalendarDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tip.cpp
# End Source File
# Begin Source File

SOURCE=".\定时提醒Dlg.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Ado.h
# End Source File
# Begin Source File

SOURCE=.\CalendarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Client.h
# End Source File
# Begin Source File

SOURCE=.\Client_PlayMusic.h
# End Source File
# Begin Source File

SOURCE=.\ClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClientRegister.h
# End Source File
# Begin Source File

SOURCE=.\DiaryDlg.h
# End Source File
# Begin Source File

SOURCE=.\Info.h
# End Source File
# Begin Source File

SOURCE=.\MainDlg.h
# End Source File
# Begin Source File

SOURCE=.\MUSICDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Satety.h
# End Source File
# Begin Source File

SOURCE=.\Setting.h
# End Source File
# Begin Source File

SOURCE=.\SpringButton.h
# End Source File
# Begin Source File

SOURCE=.\StaticCalendarDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tip.h
# End Source File
# Begin Source File

SOURCE=".\定时提醒Dlg.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\70018411d14f55ebdf4d7f1258b31b8d-img2ico.net.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\9a504fc2d56285356100e54691ef76c6a6ef63f0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Client.ico
# End Source File
# Begin Source File

SOURCE=.\res\Client.rc2
# End Source File
# Begin Source File

SOURCE=".\res\login凹陷蓝色.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\login凸起蓝色.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\log背景.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\u=1463911280,1493303818&fm=90&gp=0.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面登陆按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面登陆按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面登陆按钮3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面关闭按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面关闭按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面关闭按钮3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面注册按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面注册按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆界面注册按钮3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\个性化设置2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\个性化设置按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\晴天娃娃不开心.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\晴天娃娃笑.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\晴天娃娃一般.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程备忘录打开按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程备忘录打开按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程备忘录打开按钮3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒-删除1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒-删除2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒-添加1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒-添加2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒背景.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒不再提醒1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒不再提醒2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒关闭1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒关闭2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒确定1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日程提醒确定2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本保存按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本保存按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本背景.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本打开按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本打开按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本返回按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本返回按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本下雨.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日记本阳光.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历背景.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历关闭1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历关闭2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历切换风格1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历切换风格2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历右1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历右2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历右右1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历右右2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历左1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历左2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历左左1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\日历左左2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置个人资料.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置界面.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置项目单曲循环.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置项目个人资料1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置项目个人资料2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置项目顺序播放.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置项目随机播放.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置项目账户安全设置2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置项目账户按钮设置1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置音乐.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\设置账户安全.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\提醒界面.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\星期天后置.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\星期天前置.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\音乐播放.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\音乐添加1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\音乐暂停.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面关闭按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面关闭按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面关闭按钮3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面日记打开按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面日记打开按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面日记打开按钮3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面设置打开按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面设置打开按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面设置打开按钮3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面最小化按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面最小化按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\主界面最小化按钮3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\注册按钮凹.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\注册按钮凸.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\注册界面1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\注册界面关闭按钮.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\注册界面检查按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\注册界面检查按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\注册界面检查按钮3.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Onimer.wav
# End Source File
# Begin Source File

SOURCE=".\res\qq 消息声皮卡丘 短信提示音.wav"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\res\steer life.wav"
# End Source File
# Begin Source File

SOURCE=.\res\tik.wav
# End Source File
# End Target
# End Project
# Section Client : {CAA971DB-9F22-455B-818F-D8EEB1A975C4}
# 	2:16:CalendarCtrl.cpp:CalendarCtrl.cpp
# 	2:14:CalendarCtrl.h:CalendarCtrl.h
# 	2:20:CLASS: CCalendarCtrl:CCalendarCtrl
# 	2:19:Application Include:client.h
# End Section
# Section Client : {E30B5C8A-7DC7-42B3-A31B-45F68CA48E9C}
# 	1:25:IDD_STATICCALENDAR_DIALOG:110
# 	2:16:Resource Include:resource.h
# 	2:19:StaticCalendarDlg.h:StaticCalendarDlg.h
# 	2:25:CLASS: CStaticCalendarDlg:CStaticCalendarDlg
# 	2:21:StaticCalendarDlg.cpp:StaticCalendarDlg.cpp
# 	2:10:ENUM: enum:enum
# 	2:25:IDD_STATICCALENDAR_DIALOG:IDD_STATICCALENDAR_DIALOG
# 	2:19:Application Include:client.h
# End Section
