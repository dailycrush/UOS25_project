// SalesView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "SalesView.h"


// CSalesView

IMPLEMENT_DYNCREATE(CSalesView, CView)

CSalesView::CSalesView()
{

}

CSalesView::~CSalesView()
{
}

BEGIN_MESSAGE_MAP(CSalesView, CView)
END_MESSAGE_MAP()


// CSalesView �׸����Դϴ�.

void CSalesView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

}


// CSalesView �����Դϴ�.

#ifdef _DEBUG
void CSalesView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSalesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSalesView �޽��� ó�����Դϴ�.
