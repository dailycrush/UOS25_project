#pragma once
#include "ManageOrder.h"
#include "NewOrder.h"
#include "SalesView.h"
// CContentView ���Դϴ�.

class CContentView : public CListView
{
	DECLARE_DYNCREATE(CContentView)

protected:
	CContentView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CContentView();

/*
	Attributes
*/
public:
	int CUR_CONTENT;
	CString current_date;
	CListCtrl * m_list;
	CSalesView * sales_view;
	CManageOrder * dlg_manage_order; //	�ֹ� ���� ���̾�α� ���� ������
	NewOrder * dlg_new_order; // �� �ֹ� �߰� ���̾�α� ���� ������
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void DeleteContent(CListCtrl * m_list);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


