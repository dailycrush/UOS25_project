#pragma once
#include "afxwin.h"


// NewOrder ��ȭ �����Դϴ�.

class NewOrder : public CDialogEx
{
	DECLARE_DYNAMIC(NewOrder)

public:
	NewOrder(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NewOrder();
	CDatabase db_neworder;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NEW_ORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void ShowData(CDatabase & db_neworder);
	CCheckListBox m_neworderList;
	afx_msg void OnBnClickedOrder();
	afx_msg void OnBnClickedOk();
};
