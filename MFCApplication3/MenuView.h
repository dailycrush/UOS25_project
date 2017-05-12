#pragma once
#define MENU_COUNT 16

// CMenuView ���Դϴ�.

class CMenuView : public CTreeView
{
	DECLARE_DYNCREATE(CMenuView)

protected:
	CMenuView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMenuView();

/*
	Attributes
*/
public:
	CDatabase db_menu;
	CString menu_board[MENU_COUNT][2];
/*
	Operations
*/
public:

	void SaveMenuState(CDatabase & db_menu);
	void SetMenu(CDatabase & db_menu);

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


