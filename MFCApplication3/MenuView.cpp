// MenuView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MenuView.h"
#include "ContentView.h"

#define MENU_ITEM_COUNT 17

// CMenuView

IMPLEMENT_DYNCREATE(CMenuView, CTreeView)

CMenuView::CMenuView()
{

}

CMenuView::~CMenuView()
{
}

BEGIN_MESSAGE_MAP(CMenuView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CMenuView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CMenuView �����Դϴ�.

#ifdef _DEBUG


void CMenuView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMenuView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMenuView �޽��� ó�����Դϴ�.

void CMenuView::SaveMenuState(CDatabase & db_menu)
{
	CRecordset recSet(&db_menu);
	recSet.Open(CRecordset::dynaset, L"select name, is_last from menu_list");
	int idx = 0;

	while (!recSet.IsEOF())
	{
		recSet.GetFieldValue(_T("NAME"), menu_board[idx][0]);
		recSet.GetFieldValue(_T("IS_LAST"), menu_board[idx][1]);
		recSet.MoveNext();
	}

	recSet.Close();
}

void CMenuView::SetMenu(CDatabase & db_menu)
{

	//Ʈ���� �����
	CRecordset recSet(&db_menu);
	HTREEITEM  htItem[MENU_ITEM_COUNT];

	TRY
	{
		CString		strSQL;
		CString		strID, strNAME, strPID, strISLAST;
		
		// �������� ���� recSet��ü�� PID�� ID�� ���ĵǾ��� ���̺��� �޾ƿ´�
		strSQL = _T("select * FROM menu_list ORDER BY parent_id, id");
		recSet.Open(CRecordset::dynaset, strSQL);

		// ��Ʈ ���� �ʱ�ȭ
		htItem[0] = GetTreeCtrl().InsertItem(L"UOS25 ������ ���� ���α׷�", 0, 0, TVI_ROOT);

		// �޾ƿ� ���̺� ���� �����Ͱ� ���� ������ ����
		while (!recSet.IsEOF())
		{
			recSet.GetFieldValue(_T("ID"), strID);
			recSet.GetFieldValue(_T("NAME"), strNAME);
			recSet.GetFieldValue(_T("PARENT_ID"), strPID);
			recSet.GetFieldValue(_T("IS_LAST"), strISLAST);

			// id, pid, islast ���� CString ���� int Ÿ������ ��ȯ���ش�
			int id = _ttoi(strID);
			int pid = _ttoi(strPID);
			int isLast = _ttoi(strISLAST);

			/*
			  �� �׸��� �������� htItem[pid]�� subItem���� �ִ´�
			  �̶� ������ �׸��� �ڽ��� id�� �ε����� ���� �迭 �ȿ� ����Ǿ��ִ�
			  ���� htItem[pid]�� �ڽ��� �θ� ���丮�� ����Ŵ
			*/
			if(isLast == 1)
				htItem[id] = GetTreeCtrl().InsertItem(strNAME, 0, 0, htItem[pid], TVI_LAST);
			else
				htItem[id] = GetTreeCtrl().InsertItem(strNAME, 0, 0, htItem[pid]);

			// ���� ���ڵ�� �̵�
			recSet.MoveNext();
		}

		recSet.Close();

	}
	CATCH(CException, e)
	{

		return;
	}
	END_CATCH

	//Ʈ���� ��ģ��
	for (int i = 0; i < MENU_ITEM_COUNT; i++)
		GetTreeCtrl().Expand(htItem[i], TVE_EXPAND);
	
	return;
}

BOOL CMenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	/*
		PreCreateWindow() �Լ��� ������ â ���� ���� ����ȴ�.
		�̶� �Ķ���� cs�� �̿��� �ش� �������� ��Ÿ���� �������ش�.
		CTreeView�� ��ӹ޴� Ŭ������ CMenuView�� ��Ÿ����
		�Ʒ��� ���� �������� �� �ִ�.
	*/

	cs.style |= TVS_HASLINES | TVS_SHOWSELALWAYS | TVS_DISABLEDRAGDROP;

	return CTreeView::PreCreateWindow(cs);
}


void CMenuView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	
	/*
		��ť��Ʈ�� �����ų� ������ �� ȣ��Ǵ� �Լ��� �� ��ü�� �ʱ�ȭ�Ѵ�.
		Document�� OnUpdate()�Լ��� ȣ���Ͽ� ���� Ŭ���̾�Ʈ ������ �ٽ� �׸����� �Ѵ�.
	*/

	// �����ͺ��̽����� ����
	// CDatabase db_menu;
	if (!db_menu.IsOpen())
	{
		TRY
		{
			db_menu.OpenEx(_T("DSN=UOS25;UID=UOS25;PWD=l27094824"));
		}
			CATCH(CException, e)
		{
			TCHAR errMSG[255];

			e->GetErrorMessage(errMSG, 255);
			AfxMessageBox(errMSG, MB_ICONERROR);


		}
		END_CATCH

	}
	
	// �޴��� ǥ���ϰ� ����� ���� �ݾ��ش�
	SetMenu(db_menu);
	// SaveMenuState(db_menu);
	db_menu.Close();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

/*
	CMenuView�� Ʈ�� ������ ��ȭ�� ���� CRightContainerView�� ��ȭ
	
	Ʈ�� �������� ���� ���ΰ� ��ȭ�ϸ� TVN_SELCHANGED �޽����� �߻��Ѵ�.
	�̶� �߻��ϴ� �޼����� �Ʒ��� OnTvnSelchanged �Լ��� �ٷ�� �ȴ�.
	�� �Լ����� ��ť��Ʈ�� UpdateAllViews �Լ��� ȣ���Ͽ�
	CRightContainerView Ŭ������ OnUpdate �Լ����� ����Ʈ�䰡 ���ŵǾ�� ���� �˸� ��
	����� �����͸� ����Ʈ�信 �����ش�.
*/
void CMenuView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>( pNMHDR );
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.



	// ���õ� �������� selectedItem ��ü�� ����
	HTREEITEM selectedItem = pNMTreeView->itemNew.hItem;

	// ���õ� �������� �̸��� ��´�
	CString selectedItem_name = GetTreeCtrl().GetItemText(selectedItem);
	CString menu_board[16][2] = {
		L"�ֹ� ��ǰ ����",L"0",  L"�ֹ� ����", L"1",L"��ǰ ����" ,L"1",L"�Ǹ� ����",L"1",
		L"��� ����",L"0", L"�԰� ����", L"1",L"��� ����" ,L"1",L"ǰ�� ����", L"0",L"��ǰ ���",L"1",
		L"��ǰ ����", L"1",L"�ڱ� ����",L"0", L"���� ����" ,L"1",L"���� ����",L"1", L"�η� ����",L"0",
		L"���� ���",L"1", L"���� �ذ�", L"1"
	};
	CString MENU[11] = { L"�ֹ� ����", L"��ǰ ����" ,L"�Ǹ� ����"
		L"�԰� ����", L"��� ����" ,L"��ǰ ���"
		L"��ǰ ����", L"���� ����" ,L"���� ����"
		L"���� ���", L"���� �ذ�" };


	// is_last	:	Ʈ���� �� ������ ���� ���������� ���θ� ����
	if (selectedItem_name == L"UOS25 ������ ���� ���α׷�")
		GetDocument()->UpdateAllViews(this, 0, (CObject*) (LPCTSTR) selectedItem_name);


	CString is_last;

	for (int i = 0; i < 16; i++)
	{
		if (selectedItem_name == menu_board[i][0] && menu_board[i][1] == '1')
		{
			is_last = '1';
		}
	}

	// Ʈ���� �� ������ ���� �������� ������ ��쿡�� view�� ������Ʈ�Ѵ�
	if (is_last == '1')
	{
		for (int i = 0; i < 11; i++)
		{
			if (selectedItem_name == MENU[i])
			{
				GetDocument()->UpdateAllViews(this, i + 1, (CObject*) (LPCTSTR) selectedItem_name);
				break;
			}
		}
	}
	
	*pResult = 0;
}
