
// GEView.cpp : CGEView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GE.h"
#endif

#include "GEDoc.h"
#include "GEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGEView

IMPLEMENT_DYNCREATE(CGEView, CFormView)

BEGIN_MESSAGE_MAP(CGEView, CFormView)
END_MESSAGE_MAP()

// CGEView ����/�Ҹ�

CGEView::CGEView()
	: CFormView(CGEView::IDD)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CGEView::~CGEView()
{
}

void CGEView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CGEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CGEView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CGEView ����

#ifdef _DEBUG
void CGEView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGEView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGEDoc* CGEView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGEDoc)));
	return (CGEDoc*)m_pDocument;
}
#endif //_DEBUG


// CGEView �޽��� ó����
