#pragma once


// NewOrder ��ȭ �����Դϴ�.

class NewOrder : public CDialogEx
{
	DECLARE_DYNAMIC(NewOrder)

public:
	NewOrder(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NewOrder();

// ��ȭ ���� �������Դϴ�.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_ORDER };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
