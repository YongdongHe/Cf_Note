// Ado.h: interface for the CAdo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADO_H__343C1E0F_84E6_4552_AF54_04C96AB93962__INCLUDED_)
#define AFX_ADO_H__343C1E0F_84E6_4552_AF54_04C96AB93962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAdo  
{
public:
	_RecordsetPtr GetRecordset();
	_RecordsetPtr& OpenRecordset(CString sql);
	BOOL OnInitAdoConn();
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;

	void ExitConnection();
	CAdo();
	virtual ~CAdo();

};

#endif // !defined(AFX_ADO_H__343C1E0F_84E6_4552_AF54_04C96AB93962__INCLUDED_)
