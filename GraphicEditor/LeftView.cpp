
// LeftView.cpp : CLeftView Ŭ������ ����
//

#include "stdafx.h"
#include "GraphicEditor.h"

#include "GraphicEditorDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
END_MESSAGE_MAP()


// CLeftView ����/�Ҹ�

CLeftView::CLeftView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: TreeView�� �׸����� ä�����
	//  GetTreeCtrl()�� ȣ���Ͽ� �ش� tree ��Ʈ���� ���� �׼����Ͻʽÿ�.
}


// CLeftView ����

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CGraphicEditorDoc* CLeftView::GetDocument() // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView �޽��� ó����
