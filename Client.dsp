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

SOURCE=".\��ʱ����Dlg.cpp"
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

SOURCE=".\��ʱ����Dlg.h"
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

SOURCE=".\res\login������ɫ.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\login͹����ɫ.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\log����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\u=1463911280,1493303818&fm=90&gp=0.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½����1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½�����½��ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½�����½��ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½�����½��ť3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½����رհ�ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½����رհ�ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½����رհ�ť3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½����ע�ᰴť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½����ע�ᰴť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��½����ע�ᰴť3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���Ի�����2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���Ի����ð�ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�������޲�����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������Ц.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������һ��.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ̱���¼�򿪰�ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ̱���¼�򿪰�ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ̱���¼�򿪰�ť3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ�����-ɾ��1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ�����-ɾ��2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ�����-���1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ�����-���2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ����ѱ���.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ����Ѳ�������1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ����Ѳ�������2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ����ѹر�1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ����ѹر�2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ�����ȷ��1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ճ�����ȷ��2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ�.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ����水ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ����水ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ�����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ��򿪰�ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ��򿪰�ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ����ذ�ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ����ذ�ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ�����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�ռǱ�����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�����ر�1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�����ر�2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�����л����1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�����л����2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���ø�������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���ý���.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������Ŀ����ѭ��.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������Ŀ��������1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������Ŀ��������2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������Ŀ˳�򲥷�.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������Ŀ�������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������Ŀ�˻���ȫ����2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������Ŀ�˻���ť����1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�����˻���ȫ.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���ѽ���.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������ǰ��.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���ֲ���.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�������1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������ͣ.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������رհ�ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������رհ�ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\������رհ�ť3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�������ռǴ򿪰�ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�������ռǴ򿪰�ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\�������ռǴ򿪰�ť3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���������ô򿪰�ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���������ô򿪰�ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\���������ô򿪰�ť3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������С����ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������С����ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\��������С����ť3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ע�ᰴť��.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ע�ᰴť͹.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ע�����1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ע�����رհ�ť.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ע������鰴ť1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ע������鰴ť2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ע������鰴ť3.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Onimer.wav
# End Source File
# Begin Source File

SOURCE=".\res\qq ��Ϣ��Ƥ���� ������ʾ��.wav"
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
