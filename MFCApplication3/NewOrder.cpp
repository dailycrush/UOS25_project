// NewOrder.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "NewOrder.h"
#include "afxdialogex.h"


// NewOrder ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(NewOrder, CDialogEx)

NewOrder::NewOrder(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEW_ORDER, pParent)
{

}

NewOrder::~NewOrder()
{
}

void NewOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewOrder, CDialogEx)
END_MESSAGE_MAP()


// NewOrder �޽��� ó�����Դϴ�.
