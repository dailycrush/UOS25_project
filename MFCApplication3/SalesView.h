#pragma once


// CSalesView ���Դϴ�.

class CSalesView : public CView
{
	DECLARE_DYNCREATE(CSalesView)

protected:
	CSalesView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CSalesView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


