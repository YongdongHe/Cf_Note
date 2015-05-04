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
		hr = m_pConnection.CreateInstance("ADODB.Connection");//����connection����
		if(SUCCEEDED(hr))
		{
			//��ȡ��ǰӦ�ó�������λ��

			CString path;
			GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
			path.ReleaseBuffer();
			int pos = path.ReverseFind('\\');
			path = path.Left(pos); 
			pos = path.ReverseFind('\\');
			path = path.Left(pos);
			path="Provider=Microsoft.ACE.OLEDB.12.0;Data Source="+path;
			path+="\\client.accdb";

			hr=m_pConnection->Open((_bstr_t)path,"","",adModeUnknown);//�������ݿ�
		}
		
	}
	catch(_com_error e)
	{
		CString errorMsg;
		errorMsg.Format("�������ݿ�ʧ��","","",adModeUnknown);
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
			AfxMessageBox("Recordset���󴴽�ʧ�ܣ���ȷ���Ƿ��ʼ����COM����");
		}
		
		//�����α�����
		m_pRecordset->CursorLocation = adUseClient;
		
		//�򿪼�¼��
		m_pRecordset->Open(_variant_t(sql),_variant_t((IDispatch *)m_pConnection , true) ,adOpenDynamic ,adLockOptimistic,adCmdText);
		
	}
	catch(_com_error e)
	{
		CString errorMsg;
		errorMsg.Format("�������ݿ�ʧ��!\r\n������Ϣ��%s",e.ErrorMessage());
		AfxMessageBox(errorMsg);
	}
	return m_pRecordset;

}

_RecordsetPtr CAdo::GetRecordset()
{
	return m_pRecordset;

}
