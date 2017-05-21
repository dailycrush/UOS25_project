#pragma once
#include "ManageOrder.h"
#include "NewOrder.h"
// CContentView 뷰입?�다.

class CContentView : public CListView
{
	DECLARE_DYNCREATE(CContentView)

protected:
	CContentView();           // ?�적 만들기에 ?�용?�는 protected ?�성?�입?�다.
	virtual ~CContentView();

/*
	Attributes
*/
public:
	int CUR_CONTENT;
	CString current_date;
	CListCtrl * m_list;
	CManageOrder * dlg_manage_order; //	
	NewOrder * dlg_new_order; // ??주문 추�? ?�이?�로�?지???�인??
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


