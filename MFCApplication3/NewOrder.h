#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include <string>
using namespace std;

// NewOrder ��ȭ �����Դϴ�.

class NewOrder : public CDialogEx
{
	DECLARE_DYNAMIC(NewOrder)

public:
	NewOrder(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NewOrder();
	CDatabase db_neworder;
	vector<vector<CString> > itmData;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NEW_ORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void ShowData(CDatabase & db_neworder);
	afx_msg void OnBnClickedOrder();
	afx_msg void OnBnClickedOk();
	CListCtrl m_newOrder;
	afx_msg void OnEndlabeleditNewOrder(NMHDR *pNMHDR, LRESULT *pResult);
};
