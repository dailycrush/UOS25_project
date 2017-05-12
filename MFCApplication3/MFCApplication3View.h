
// MFCApplication3View.h : CMFCApplication3View Ŭ������ �������̽�
//

#pragma once
#include "MainFrm.h"
#include "MFCApplication3.h"
#include "MFCApplication3Doc.h"

class CMFFCApplication3Doc;
class CMFCApplication3View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

// Ư���Դϴ�.
public:
	CMFCApplication3Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCApplication3View.cpp�� ����� ����
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

