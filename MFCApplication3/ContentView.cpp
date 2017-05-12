// ContentView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "ContentView.h"
#include "ManageOrder.h"
#include "NewOrder.h"
#include "SalesView.h"
// CContentView

IMPLEMENT_DYNCREATE(CContentView, CListView)

CContentView::CContentView()
{

}

CContentView::~CContentView()
{
}

BEGIN_MESSAGE_MAP(CContentView, CListView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CContentView::OnNMDblclk)
END_MESSAGE_MAP()


// CContentView �����Դϴ�.

#ifdef _DEBUG
void CContentView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CContentView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CContentView �޽��� ó�����Դϴ�.


BOOL CContentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	/*
	main contents�� ǥ�õǴ� CRightContainerView��
	�⺻������ listview�� ���¸� ���
	*/
	//cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;

	
	return CListView::PreCreateWindow(cs);
}

void CContentView::DeleteContent(CListCtrl * m_list)
{
	/*
		������ ȭ���� ���� �����
	*/

	// ����Ʈ �׸��� �����

	CHeaderCtrl *p_headerCtrl;

	p_headerCtrl = m_list->GetHeaderCtrl();
	int columnCnt = 0;
	columnCnt = p_headerCtrl->GetItemCount();

	if (columnCnt > 0)
	{
		m_list->DeleteAllItems();
		for (int i = 0; i < columnCnt; i++)
			m_list->DeleteColumn(0);
	}

}

void CContentView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CUR_CONTENT = lHint;
	m_list = &GetListCtrl();

	// �����ͺ��̽��� ����
	CDatabase db_content;
	CRecordset recSet(&db_content);

	TRY
	{
		db_content.OpenEx(_T("DSN=UOS25;UID=UOS25;PWD=l27094824"));
	}
		CATCH(CException, e)
	{
		TCHAR errMSG[255];

		e->GetErrorMessage(errMSG, 255);
		AfxMessageBox(errMSG, MB_ICONERROR);


		if (db_content.IsOpen())
			db_content.Close();

	}
	END_CATCH

	

	switch (lHint)
	{
	case 0:
	{
		// UOS25 �ΰ�ȭ��
		
		CClientDC pDC(this);//���� ���̾�α��� Ÿ��Ʋ�ٸ� ������ ������ ��´�.
		CDC memDC;
		CPen pen;
		CBrush brush;
		pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		brush.CreateSolidBrush(RGB(255, 255, 255));

		CPen *p = pDC.SelectObject(&pen);
		CBrush *b = pDC.SelectObject(&brush);

		pDC.Rectangle(0, 0, 1500, 800);
		pDC.SelectObject(p);
		pDC.SelectObject(b);
		
		memDC.CreateCompatibleDC(&pDC);//CDC�� CClinetDC�� �������ִ� ����

		CBitmap m_bitMain;
		m_bitMain.LoadBitmapW(IDB_LOGO);
		CBitmap *oldbm = memDC.SelectObject(&m_bitMain);
		//	pDC.StretchBlt(17, 23, 300, 300, &memDC, 0, 0, 350, 350, SRCCOPY);
		pDC.BitBlt(150, 100, 888, 396, &memDC, 0, 0, SRCCOPY);
		//bitblt�Լ��� ����Ͽ� ���� bmp�׸������� ȭ�鿡 ����Ѵ�.
		//��ǥ 10,10��ġ�� 300*300�� ũ��� �׸��� �׸���.
		//�����׸��� ���� �� ����Ʈ�� 0,0���� �����Ѵ�.
		//bmp������ ����ϹǷ� ��� ����� �ȼ��� �������� �Ѵ�.

		break;
	}
	case 1:	
	{
		// �ֹ� ����
		// m_list = &GetListCtrl();
		m_list->ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 0);
		m_list->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


		int idx = 1;
		recSet.Open(CRecordset::dynaset, L"select distinct order_date, order_id from order_list order by order_id");

		if(m_list->GetItemCount() > 0)
			DeleteContent(m_list);

		m_list->InsertColumn(idx, L"�ֹ� ��¥", LVCFMT_CENTER, 400);

		while (!recSet.IsEOF())
		{
			CString order_date = L" ", order_list;
			recSet.GetFieldValue(_T("ORDER_DATE"), order_date);
			AfxExtractSubString(order_date, order_date, 0, ' ');
			order_list.Format(L"�ֹ���ȣ %d | %s", idx+1000, order_date);

			m_list->InsertItem(idx, order_list, 30);
			m_list->SetItemText(idx, 0, order_list);
			idx++;
			recSet.MoveNext();
		}

		recSet.Close();
		m_list->InsertColumn(idx, L"+ �� �ֹ� �ϱ�", LVCFMT_LEFT, 400);
		break;
	}
	case 2:
	{
		// ��ǰ ����
		if (m_list->GetItemCount() > 0)
			DeleteContent(m_list);

		m_list->ModifyStyle(LVS_TYPEMASK, 0);
		
		// Create Button
		//CButton * btn1;
		//btn1->Create(L"My Button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(300, 300, 300, 300), pSender, 103);
		//btn1->ShowWindow(SW_SHOW);
		
		break;
	}
	case 3:
	{
		// �Ǹ� ����
		//sales_view = new CSalesView();
		//sales_view->Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), pSender, 200, this);
		break;
	}
	case 4:
	{
		// �԰� ����
		break;
	}
	case 5:
	{
		// ��� ����
		break;
	}
	case 6:
	{
		// ��ǰ ���
		break;
	}
	case 7:
	{
		// ��ǰ ����
		break;
	}
	case 8:
	{
		// ���� ����
		break;
	}
	case 9:
	{
		// ���� ����
		break;
	}
	case 10:
	{
		// ���� ���
		break;
	}
	case 11:
	{
		// ���� �ذ�
		break;
	}
	default:
		break;
	}

	return;
}


void CContentView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	//m_list = &GetListCtrl();
	//m_list->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	
	// �÷��� ������ �ʵ��� �ϴ� ��Ÿ��
	//m_list->ModifyStyle(0, LVS_NOCOLUMNHEADER);
}

/*
	����Ʈ�� ����Ŭ���� ��� �������� ���� �ʿ��� ���̾�α� ����
*/
void CContentView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>( pNMHDR );
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	switch (CUR_CONTENT)
	{
	case 1:
	{
		if(pNMItemActivate->iItem)
		if (pNMItemActivate->iItem != -1)
		{
			// Ŭ���� �� �ѹ����� �޾ƿ´�
			NM_LISTVIEW * pNMListView = (NM_LISTVIEW*) pNMHDR;
			int cur_idx = pNMListView->iItem;

			
			// idx��° ���� �� �� ���� �޾ƿ� ���� ��¥ ��ü�� ����
			// ���õ� �׸��� CString���� �޾ƿ��� �ڵ��Դϴ�

			// current_date = m_list->GetItemText(cur_idx, 0);
			
			// ���̾�α� ����
			dlg_manage_order = new CManageOrder(this, cur_idx);
			dlg_manage_order->Create(CManageOrder::IDD);
			dlg_manage_order->ShowWindow(SW_SHOW);

		}
		else
		{
			dlg_new_order = new NewOrder();
			dlg_new_order->Create(NewOrder::IDD);
			dlg_new_order->ShowWindow(SW_SHOW);
		}
		break;
	}

	default:
		break;
	}

	*pResult = 0;
}