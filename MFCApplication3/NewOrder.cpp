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
	DDX_Control(pDX, IDC_NEW_ORDER, m_neworderList);
}



BEGIN_MESSAGE_MAP(NewOrder, CDialogEx)
	ON_BN_CLICKED(IDC_ORDER, &NewOrder::OnBnClickedOrder)
END_MESSAGE_MAP()


// NewOrder �޽��� ó�����Դϴ�.


BOOL NewOrder::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// �����ͺ��̽����� ����
	// CDatabase db_order;

	TRY
	{
		db_neworder.OpenEx(_T("DSN=UOS25;UID=UOS25;PWD=0000"));
	}
		CATCH(CException, e)
	{
		TCHAR errMSG[255];

		e->GetErrorMessage(errMSG, 255);
		AfxMessageBox(errMSG, MB_ICONERROR);


		if (db_neworder.IsOpen())
			db_neworder.Close();

	}
	END_CATCH

		ShowData(db_neworder);
	   // db_neworder.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void NewOrder::ShowData(CDatabase & db_neworder)
{
	CRecordset recSet(&db_neworder);
	CString strSQL, strCODE, strNAME, strMAKER, strPRICE, strSTOCKAMOUNT;

	// �������� ���� Ư�� ��¥�� �ֹ���ϸ� �޾ƿ´�
	strSQL.Format(L"SELECT * FROM PRODUCT");
	recSet.Open(CRecordset::dynaset, strSQL);

	// �޾ƿ� ���̺� ���� �����Ͱ� ���� ������ ����
	while (!recSet.IsEOF())
	{
		int idx = 0;

		recSet.GetFieldValue(_T("PROD_CODE"), strCODE);
		recSet.GetFieldValue(_T("PROD_NAME"), strNAME);
		recSet.GetFieldValue(_T("PROD_MAKER"), strMAKER);
		recSet.GetFieldValue(_T("PROD_PRICE"), strPRICE);
		recSet.GetFieldValue(_T("PROD_STOCK_AMOUNT"), strSTOCKAMOUNT);

		CString str;
		str.Format(L"%s \t %s \t %s \t %s \t %s", strCODE, strNAME, strMAKER, strPRICE, strSTOCKAMOUNT);
		m_neworderList.AddString(str);

		//���� ���ڵ�� �̵�
		recSet.MoveNext();
	}

	recSet.Close();

}

void NewOrder::OnBnClickedOrder()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
