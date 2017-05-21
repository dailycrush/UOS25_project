// ContentView.cpp : 구현 ?�일?�니??
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "ContentView.h"
#include "ManageOrder.h"
#include "NewOrder.h"
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


// CContentView 진단?�니??

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


// CContentView 메시지 처리기입?�다.

BOOL CContentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ?�기???�수?�된 코드�?추�? �??�는 기본 ?�래?��? ?�출?�니??

	/*
	main contents가 ?�시?�는 CRightContainerView??
	기본?�으�?listview???�태�??�다
	*/
	//cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;

	
	return CListView::PreCreateWindow(cs);
}

void CContentView::DeleteContent(CListCtrl * m_list)
{
	/*
		컨텐�??�면???��? 지?�다
	*/

	// 리스????��??지?�다

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
	// TODO: ?�기???�수?�된 코드�?추�? �??�는 기본 ?�래?��? ?�출?�니??

	CUR_CONTENT = lHint;
	m_list = &GetListCtrl();

	// ?�이?�베?�스???�결
	CDatabase db_content;
	CRecordset recSet(&db_content);

	TRY
	{
		db_content.OpenEx(_T("DSN=UOS25;UID=UOS25;PWD=0000"));
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
		case 1:	
		{
			// 주문 관�?
			// m_list = &GetListCtrl();

			m_list->ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 0);
			m_list->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

			if (m_list->GetItemCount() > 0)
				DeleteContent(m_list);

			int idx = 1;
			recSet.Open(CRecordset::dynaset, L"select distinct order_date, order_id from order_list order by order_id");
			// recSet.Open(CRecordset::dynaset, L"select distinct ORDER_CODE from _ORDER order by ORDER_CODE");

			// m_list->InsertColumn(idx, L"주문 ?�짜", LVCFMT_CENTER, 400);
			m_list->InsertColumn(idx, L"주문 목록", LVCFMT_CENTER, 400);
			// m_list->InsertColumn(idx, L"주문 ?�량", LVCFMT_CENTER, 400);

			while (!recSet.IsEOF())
			{
				CString order_date = L" ", order_list;
				recSet.GetFieldValue(_T("ORDER_DATE"), order_date);
				AfxExtractSubString(order_date, order_date, 0, ' ');
				order_list.Format(L"주문번호 %d | %s", idx+1000, order_date);

				m_list->InsertItem(idx, order_list, 30);
				m_list->SetItemText(idx, 0, order_list);
				idx++;
				recSet.MoveNext();
			
				/*
				CString order_code = L" ", order_date;
				recSet.GetFieldValue(_T("ORDER_CODE"), order_code);;
				order_date = order_code.Left(8); //주문 코드?�서 주문?�짜 추출
				list_itm.Format(L"주문?�짜 %s | %s", order_date, order_code);

				m_list->InsertItem(idx, list_itm, 30);
				m_list->SetItemText(idx, 0, list_itm);
				idx++;
				recSet.MoveNext();
				*/
			}

			recSet.Close();
			m_list->InsertItem(idx, L"+ ??주문 ?�기", 30);
			m_list->SetItemText(idx, 0, L"+ ??주문 ?�기");
			break;
		}
		case 2:
		{
			// 반품 관�?
		
			// ?�면 ?��???지??
			m_list->ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 0);
			m_list->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

			// ?�면 ?�리??
			if (m_list->GetItemCount() > 0)
				DeleteContent(m_list);

			int idx = 1;
			recSet.Open(CRecordset::dynaset, L"select distinct order_date, order_id from order_list order by order_id");
			// recSet.Open(CRecordset::dynaset, L"select distinct RETURN_CODE, RETURN_AMOUNT from RETURN order by RETURN_CODE");


			m_list->InsertColumn(idx, L"반품 목록", LVCFMT_CENTER, 400);

			while (!recSet.IsEOF())
			{
				CString order_date = L" ", order_list;
				recSet.GetFieldValue(_T("ORDER_DATE"), order_date);
				AfxExtractSubString(order_date, order_date, 0, ' ');
				order_list.Format(L"주문번호 %d | %s", idx + 1000, order_date);

				m_list->InsertItem(idx, order_list, 30);
				m_list->SetItemText(idx, 0, order_list);
				idx++;
				recSet.MoveNext();
			}

			recSet.Close();
			m_list->InsertItem(idx, L"+ ??반품 ?�기", 30);
			m_list->SetItemText(idx, 0, L"+ ??반품 ?�기");
			break;
		
			break;
		}
		case 3:
		{
			// ?�매 관�?


			if (m_list->GetItemCount() > 0)
				DeleteContent(m_list);

			break;
		}
		case 4:
		{
			// ?�금 관�?

			if (m_list->GetItemCount() > 0)
				DeleteContent(m_list);

			break;
		}
		case 6:
		{
			// ?�재 직원
			if (m_list->GetItemCount() > 0)
				DeleteContent(m_list);

			break;
		}
		case 7:
		{
			// 직원 ?�력
			if (m_list->GetItemCount() > 0)
				DeleteContent(m_list);

			// m_list->ModifyStyle(LVS_TYPEMASK, 0);

			break;
		}
		case 8:
		{
			// 물품 관�?
			if (m_list->GetItemCount() > 0)
				DeleteContent(m_list);

			break;
		}
		default:
		{
			// UOS25 로고?�면

			CClientDC pDC(this);//?�재 ?�이?�로그의 ?�?��?바�? ?�외???�역???�는??
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

			memDC.CreateCompatibleDC(&pDC);//CDC?� CClinetDC�??�결?�주??구문

			CBitmap m_bitMain;
			m_bitMain.LoadBitmapW(IDB_LOGO);
			CBitmap *oldbm = memDC.SelectObject(&m_bitMain);
			//	pDC.StretchBlt(17, 23, 300, 300, &memDC, 0, 0, 350, 350, SRCCOPY);
			pDC.BitBlt(150, 100, 888, 396, &memDC, 0, 0, SRCCOPY);
			//bitblt?�수�??�용?�여 ?�제 bmp그림?�일???�면??출력?�다.
			//좌표 10,10?�치??300*300???�기�?그림??그린??
			//?�본그림???�쪽 ???�인?��? 0,0?�로 ?�정?�다.
			//bmp?�일???�용?��?�?모든 출력?� ?��???기�??�로 ?�다.

			break;
		}
	}

	return;
}


void CContentView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: ?�기???�수?�된 코드�?추�? �??�는 기본 ?�래?��? ?�출?�니??
	
	//m_list = &GetListCtrl();
	//m_list->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	
	// 컬럼??보이지 ?�도�??�는 ?��???
	//m_list->ModifyStyle(0, LVS_NOCOLUMNHEADER);
}

/*
	리스?��? ?�블?�릭??경우 ?�이지???�라 ?�요???�이?�로�??�운??
*/
void CContentView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>( pNMHDR );
	// TODO: ?�기??컨트�??�림 처리�?코드�?추�??�니??

	switch (CUR_CONTENT)
	{
		case 1:
		{
			if (pNMItemActivate->iItem != -1)
			{
				// ?�릭?????�버값을 받아?�다
				NM_LISTVIEW * pNMListView = (NM_LISTVIEW*) pNMHDR;
				int cur_idx = pNMListView->iItem;

			
				// idx번째 ?�의 �???값을 받아?� ?�시 ?�트링으�??�??
				// ?�택????��??CString값을 받아?�는 코드?�니??
				CString tmp_str;
				tmp_str = m_list->GetItemText(cur_idx, 0);

				if (tmp_str == "+ ??주문 ?�기")
				{
					//??주문?�기 ??�� ?�택 ??
					dlg_new_order = new NewOrder();
					dlg_new_order->Create(NewOrder::IDD);
					dlg_new_order->ShowWindow(SW_SHOW);
					break;
				}

				// current_date = m_list->GetItemText(cur_idx, 0);
			
				// ?�이?�로�??�성
				dlg_manage_order = new CManageOrder(this, cur_idx);
				dlg_manage_order->Create(CManageOrder::IDD);
				dlg_manage_order->ShowWindow(SW_SHOW);

			}
			else
			{

			}
			break;
		}
		case 2:
		{
			//반품 관�??�택

			break;
		}
		case 3:
		{
			// ?�매 관�??�택
		}
		case 4:
		{
			// ?�금 관�??�택
		}
		case 6:
		{
			// 직원 관�??�택
		}
		case 7:
		{
			// 직원 ?�력 ?�택
		}
		case 8:
		{
			// 물품 관�??�택
		}
	default:
		break;
	}

	*pResult = 0;
}
