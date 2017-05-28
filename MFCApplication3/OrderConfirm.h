#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// COrderConfirm ��ȭ �����Դϴ�.

class COrderConfirm : public CDialogEx
{
	DECLARE_DYNAMIC(COrderConfirm)

public:
	COrderConfirm(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	COrderConfirm(CWnd* pParent, CString order_code);
	virtual ~COrderConfirm();
	CString order_id;
	CDatabase db_order;
// ��ȭ ���� �������Դϴ�.
// #ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIRMED_ORDER };
// #endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void ShowData(CDatabase & db_order);
	CListCtrl m_orderList;
	CEdit reorder_code;
	CEdit return_code;
	CListBox reorderCode;
	CListBox returnCode;
};
