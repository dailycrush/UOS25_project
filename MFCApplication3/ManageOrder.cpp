// ManageOrder.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "ManageOrder.h"
#include "afxdialogex.h"
#include "ContentView.h"

// CManageOrder ��ȭ �����Դϴ�.

/*
	�ֹ� ������ ���� ���̾�α� Ŭ����
*/

IMPLEMENT_DYNAMIC(CManageOrder, CDialogEx)

/*
CManageOrder::CManageOrder(CWnd* pParent /*=NULL)
	: CDialogEx(IDD_MANAGE_ORDER, pParent)
{

}
*/
//������ �����ε�
CManageOrder::CManageOrder(CWnd *pParent, CString selected_itm)
	: CDialogEx(IDD_MANAGE_ORDER, pParent)
{
	CTime cTime = CTime::GetCurrentTime();

	order_id = selected_itm;
}

CManageOrder::~CManageOrder()
{
}

void CManageOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RETURN_LIST, m_returnList);
	DDX_Control(pDX, IDC_REORDER_LIST, m_reorderList);
	DDX_Control(pDX, IDC_ORDER_LIST, m_orderList);
}


BEGIN_MESSAGE_MAP(CManageOrder, CDialogEx)
	ON_BN_CLICKED(IDC_RETURN, &CManageOrder::OnBnClickedReturn)
	ON_BN_CLICKED(IDC_CONFIRM, &CManageOrder::OnBnClickedConfirm)
	ON_BN_CLICKED(IDOK, &CManageOrder::OnBnClickedOk)
	ON_BN_CLICKED(IDC_REORDER, &CManageOrder::OnBnClickedReorder)
END_MESSAGE_MAP()


// CManageOrder �޽��� ó�����Դϴ�.


BOOL CManageOrder::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// �����ͺ��̽����� ����
	// CDatabase db_order;

	TRY
	{
		db_order.OpenEx(_T("DSN=UOS25;UID=UOS25;PWD=0000"));
	}
		CATCH(CException, e)
	{
		TCHAR errMSG[255];

		e->GetErrorMessage(errMSG, 255);
		AfxMessageBox(errMSG, MB_ICONERROR);


		if (db_order.IsOpen())
			db_order.Close();

	}
	END_CATCH
	
	ShowData(db_order);
	//db_order.Close();
	
	return TRUE;  
	// return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CManageOrder::ShowData(CDatabase & db_order)
{

	CRecordset recSet(&db_order);
	CString strSQL, strNAME, strPRICE, strREMAIN, strCODE, strMAKER, strORDERAMT;

	// Modify list style
	m_orderList.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 0);
	m_orderList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	// �������� ���� Ư�� ��¥�� �ֹ���ϸ� �޾ƿ´�
	// Get product code, product name, product maker, product price, order amount, product stock amount, event detail
	strSQL.Format(L"select product.prod_code, prod_name, prod_maker, prod_price, order_amount, prod_stock_amount from product inner join order_ on order_.order_code = '%s' and order_.prod_code = product.prod_code", order_id);
	recSet.Open(CRecordset::dynaset, strSQL);

	// Create Column
	m_orderList.InsertColumn(1, L"��ǰ �ڵ�", LVCFMT_CENTER, 80);
	m_orderList.InsertColumn(2, L"��ǰ��", LVCFMT_CENTER, 100);
	m_orderList.InsertColumn(3, L"������", LVCFMT_CENTER, 100);
	m_orderList.InsertColumn(4, L"��ǰ ����", LVCFMT_CENTER, 100);
	m_orderList.InsertColumn(5, L"�ֹ� ����", LVCFMT_CENTER, 50);
	m_orderList.InsertColumn(6, L"��� ����", LVCFMT_CENTER, 50);

	// �޾ƿ� ���̺� ���� �����Ͱ� ���� ������ ����
	while (!recSet.IsEOF())
	{
		int idx = 0;
		
		recSet.GetFieldValue(_T("PROD_CODE"), strCODE);
		recSet.GetFieldValue(_T("PROD_NAME"), strNAME);
		recSet.GetFieldValue(_T("PROD_MAKER"), strMAKER);
		recSet.GetFieldValue(_T("PROD_PRICE"), strPRICE);
		recSet.GetFieldValue(_T("ORDER_AMOUNT"), strORDERAMT);
		recSet.GetFieldValue(_T("PROD_STOCK_AMOUNT"), strREMAIN);

		// insert data into list
		int nListitm = m_orderList.InsertItem(0, strCODE, 0);
		m_orderList.SetItem(nListitm, 1, LVFIF_TEXT, strNAME, 0, 0, 0, NULL);
		m_orderList.SetItem(nListitm, 2, LVFIF_TEXT, strMAKER, 0, 0, 0, NULL);
		m_orderList.SetItem(nListitm, 3, LVFIF_TEXT, strPRICE, 0, 0, 0, NULL);
		m_orderList.SetItem(nListitm, 4, LVFIF_TEXT, strORDERAMT, 0, 0, 0, NULL);
		m_orderList.SetItem(nListitm, 5, LVFIF_TEXT, strREMAIN, 0, 0, 0, NULL);

		//���� ���ڵ�� �̵�
		recSet.MoveNext();
	}

	recSet.Close();
	
}



void CManageOrder::OnBnClickedReturn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// checkbox�� ���õ� �������� �ֹ������Ѵ�.
/*
	int itemNum = m_orderlist.GetItemCount(); //����Ʈ�� �ִ� ������ ������ ���´�
	int *returnItm, returnItmCnt = 0; //��ǰ �׸��� �ε����� ������ �迭�� ���ֹ� �׸��� ����
	returnItm = new int[itemNum]; 

	for (int i = 0; i < itemNum; i++)
	{
		//����Ʈ�� ��� �������� ��ȸ�ϸ鼭 üũ�Ǿ����� Ȯ�� ��
		//üũ�� �����ۿ� ���� delete�Ѵ�

		if (m_orderlist.GetCheck(i) == BST_CHECKED)
		{
			CString SQL_deleteItm, itmName, str, str1;
			m_orderlist.GetText(i, itmName);
			AfxExtractSubString(itmName, itmName, 0, ' ');
			//MessageBox(itmName);

			//üũ�� �׸� �����ͺ��̽����� ����
			SQL_deleteItm.Format(L"DELETE FROM ORDER_LIST WHERE PROD_NAME = '%s'", itmName);
			db_order.ExecuteSQL(SQL_deleteItm);

			//��ǰ �׸��� �ε��� ��ȣ �迭�� ���� �� �迭 ī��Ʈ +1
			returnItm[returnItmCnt] = i;
			returnItmCnt++;
		}
	}
	db_order.Close();
	
	//üũ�� �׸� ����Ʈȭ�鿡�� �����ϰ� �޼��� ����
	for (int i = 0; i <= returnItmCnt; i++)
		m_orderList.DeleteString(i);
		*/
	MessageBox(L"���ֹ� �Ϸ�");
}


void CManageOrder::OnBnClickedConfirm()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// �ֹ� ��� ��ü�� �����ۿ� ���� �ֹ� Ȯ��
}


void CManageOrder::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
	db_order.Close();
}


void CManageOrder::OnBnClickedReorder()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
