// Ado.cpp: implementation of the CAdo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "Ado.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdo::CAdo()
{

}

CAdo::~CAdo()
{

}

void CAdo::ExitConnection()
{
	if(m_pRecordset->GetState() == adStateOpen)
	{
		m_pRecordset->Close();
		m_pRecordset = NULL;
	}
	
	if(m_pConnection->State)
	{
		m_pConnection->Close();
		m_pConnection = NULL;
	}
}

BOOL CAdo::OnInitAdoConn()
{
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");//创建connection对象
		if(SUCCEEDED(hr))
		{
			//获取当前应用程序所在位置

			CString path;
			GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
			path.ReleaseBuffer();
			int pos = path.ReverseFind('\\');
			path = path.Left(pos); 
			pos = path.ReverseFind('\\');
			path = path.Left(pos);
			path="Provider=Microsoft.ACE.OLEDB.12.0;Data Source="+path;
			path+="\\client.accdb";

			hr=m_pConnection->Open((_bstr_t)path,"","",adModeUnknown);//连接数据库
		}
		
	}
	catch(_com_error e)
	{
		CString errorMsg;
		errorMsg.Format("连接数据库失败","","",adModeUnknown);
		AfxMessageBox(errorMsg);
	}
	return TRUE;
}

_RecordsetPtr& CAdo::OpenRecordset(CString sql)
{
	ASSERT(!sql.IsEmpty());
	
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		
		if (NULL == m_pRecordset)
		{
			AfxMessageBox("Recordset对象创建失败！请确认是否初始化了COM环境");
		}
		
		//设置游标属性
		m_pRecordset->CursorLocation = adUseClient;
		
		//打开记录集
		m_pRecordset->Open(_variant_t(sql),_variant_t((IDispatch *)m_pConnection , true) ,adOpenDynamic ,adLockOptimistic,adCmdText);
		
	}
	catch(_com_error e)
	{
		CString errorMsg;
		errorMsg.Format("连接数据库失败!\r\n错误信息：%s",e.ErrorMessage());
		AfxMessageBox(errorMsg);
	}
	return m_pRecordset;

}

_RecordsetPtr CAdo::GetRecordset()
{
	return m_pRecordset;

}
