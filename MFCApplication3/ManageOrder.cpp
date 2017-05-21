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
CManageOrder::CManageOrder(CWnd *pParent, int selected_itm)
	: CDialogEx(IDD_MANAGE_ORDER, pParent)
{
	order_id = selected_itm + 1;
	/*
	// 2017-03-09 00:00:00�� ���� ���� �޾ƿ� 09-MAR-2017 �ؽ�Ʈ�� ��ȯ���ִ� �ڵ��Դϴ�

	CString year, month, day;

	AfxExtractSubString(selected_itm, selected_itm, 0, ' ');
	AfxExtractSubString(year, selected_itm, 0, '-');
	AfxExtractSubString(month, selected_itm, 1, '-');
	AfxExtractSubString(day, selected_itm, 2, '-');

	CString Calendar[12] = { L"JAN" ,L"FEB" ,L"MAR" ,L"APR" ,L"MAY" ,L"JUN" ,L"JUL" ,L"AUG" ,L"SEP" ,L"OCT" ,L"NOV" ,L"DEC" };

	current_date.Format(L"%s-%s-%s", day, Calendar[_ttoi(month)-1], year);
	*/
}

CManageOrder::~CManageOrder()
{
}

void CManageOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_orderList);
	DDX_Control(pDX, IDC_LIST2, m_orderlist);
}


BEGIN_MESSAGE_MAP(CManageOrder, CDialogEx)
	ON_BN_CLICKED(IDC_RETURN, &CManageOrder::OnBnClickedReturn)
	ON_BN_CLICKED(IDC_CONFIRM, &CManageOrder::OnBnClickedConfirm)
	ON_BN_CLICKED(IDOK, &CManageOrder::OnBnClickedOk)
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
	CString strSQL, strNAME, strPRICE, strREMAIN, strISRETURN;

	// �������� ���� Ư�� ��¥�� �ֹ���ϸ� �޾ƿ´�
	strSQL.Format(L"SELECT * FROM order_list WHERE order_id = %d", order_id);
	recSet.Open(CRecordset::dynaset, strSQL);

	// �޾ƿ� ���̺� ���� �����Ͱ� ���� ������ ����
	while (!recSet.IsEOF())
	{
		int idx = 0;
		
		recSet.GetFieldValue(_T("PROD_NAME"), strNAME);
		recSet.GetFieldValue(_T("PROD_PRICE"), strPRICE);
		recSet.GetFieldValue(_T("PROD_REMAIN"), strREMAIN);
		recSet.GetFieldValue(_T("PROD_ISRETURN"), strISRETURN);

		CString str;
		str.Format(L"%s \t %s \t %s \t %s", strNAME, strPRICE, strREMAIN, strISRETURN);
		m_orderList.AddString(str);

		//���� ���ڵ�� �̵�
		recSet.MoveNext();
	}

	recSet.Close();

}



void CManageOrder::OnBnClickedReturn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// checkbox�� ���õ� �������� ���ֹ��Ѵ�.

	int itemNum = m_orderList.GetCount(); //����Ʈ�� �ִ� ������ ������ ���´�
	int *returnItm, returnItmCnt = 0; //��ǰ �׸��� �ε����� ������ �迭�� ���ֹ� �׸��� ����
	returnItm = new int[itemNum]; 

	for (int i = 0; i < itemNum; i++)
	{
		//����Ʈ�� ��� �������� ��ȸ�ϸ鼭 üũ�Ǿ����� Ȯ�� ��
		//üũ�� �����ۿ� ���� delete�Ѵ�

		if (m_orderList.GetCheck(i) == BST_CHECKED)
		{
			CString SQL_deleteItm, itmName, str, str1;
			m_orderList.GetText(i, itmName);
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

	MessageBox(L"���ֹ� �Ϸ�");
}


void CManageOrder::OnBnClickedConfirm()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CManageOrder::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
	db_order.Close();
}
