
#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CManageOrder ��ȭ �����Դϴ�.

class CManageOrder : public CDialogEx
{
	DECLARE_DYNAMIC(CManageOrder)

/*
	Attributes
*/
public:
	class CContentView * p_contentView;
	CString current_date; // � ��¥�� �ֹ������ �ҷ��;� �ϴ���~
	CDatabase db_order;
	int order_id;
/*
	Operations
*/
public:
	void ShowData(CDatabase & db_order);

public:
	CManageOrder(CWnd* pParent = NULL);
	CManageOrder(CWnd * pParent, int selected_itm);
	// ǥ�� �������Դϴ�.
	virtual ~CManageOrder();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MANAGE_ORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CCheckListBox m_orderList;
	afx_msg void OnBnClickedReturn();
	afx_msg void OnBnClickedConfirm();
	afx_msg void OnBnClickedOk();
	CListCtrl m_orderlist;
};
