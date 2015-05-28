
// GraphicEditorView.cpp : CGraphicEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GraphicEditor.h"
#endif
#include "GraphicEditorDoc.h"
#include "GraphicEditorView.h"
#include "Rectangle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicEditorView

IMPLEMENT_DYNCREATE(CGraphicEditorView, CFormView)

BEGIN_MESSAGE_MAP(CGraphicEditorView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LINE, &CGraphicEditorView::OnLine)
	ON_COMMAND(ID_POLYLINE, &CGraphicEditorView::OnPolyline)
	ON_COMMAND(ID_RECTANGLE, &CGraphicEditorView::OnRectangle)
	ON_COMMAND(ID_ELLIPSE, &CGraphicEditorView::OnEllipse)
	ON_COMMAND(ID_TEXT, &CGraphicEditorView::OnText)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI(ID_TEXT, &CGraphicEditorView::OnUpdateText)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CGraphicEditorView::OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(ID_POLYLINE, &CGraphicEditorView::OnUpdatePolyline)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CGraphicEditorView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CGraphicEditorView::OnUpdateLine)
END_MESSAGE_MAP()

// CGraphicEditorView ����/�Ҹ�



CGraphicEditorView::CGraphicEditorView()
	: CFormView(CGraphicEditorView::IDD)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	//CurrentMode = DrawMode::LINE;								// �⺻���� ����

}

CGraphicEditorView::~CGraphicEditorView()
{
}

void CGraphicEditorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CGraphicEditorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CGraphicEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicEditorView ����

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditorView �޽��� ó����


void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	ldown = TRUE;
	CGraphicEditorDoc* pDoc = GetDocument();
	switch (CurrentMode)
	{
	case DrawMode::LINE:
		line.SetStart(point.x, point.y);
		pos = point;
		break;
	case DrawMode::RECT:{
		line.SetStart(point.x, point.y);
		line.SetEnd(point.x, point.y);
		//JRectangle* rect = new JRectangle(point, point);
		//pDoc->m_rects.Add(*rect);
		//pDoc->m_rectsCurrent = pDoc->m_rects.GetCount() - 1;
		break;
	}
	default:
		break;
	}
	CFormView::OnLButtonDown(nFlags, point);
}



void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	ldown = FALSE;
	switch (CurrentMode)
	{
	case DrawMode::LINE:{
		line.SetEnd(point.x, point.y);
		CClientDC dc(this);
		dc.MoveTo(pos);
		dc.LineTo(point);
		//pos = point;
		break;
	}
	case DrawMode::RECT:{
		line.SetEnd(point.x, point.y);
		JRectangle r(line.getstart(), line.getend());
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_COPYPEN);
		dc.Rectangle(r.getstart().x, r.getstart().y, r.getend().x, r.getend().y);
		break;
	}
	default:
		break;
	}
	CFormView::OnLButtonUp(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (ldown){
		switch (CurrentMode)
		{
		case DrawMode::LINE:{
			
			
			break;
		}
		case DrawMode::RECT:{
			CGraphicEditorDoc* pDoc = GetDocument();
			CClientDC dc(this);
			dc.SelectStockObject(NULL_BRUSH);
			dc.SetROP2(R2_NOT);
			dc.Rectangle(line.getstart().x, line.getstart().y, line.getend().x, line.getend().y);

			line.SetEnd(point.x, point.y);
			dc.Rectangle(line.getstart().x, line.getstart().y, line.getend().x, line.getend().y);
			/*
			dc.Rectangle(pDoc->m_rects[pDoc->m_rectsCurrent].getstart().x, 
				pDoc->m_rects[pDoc->m_rectsCurrent].getstart().y, 
				pDoc->m_rects[pDoc->m_rectsCurrent].getend().x, 
				pDoc->m_rects[pDoc->m_rectsCurrent].getend().y); // ���� ��ġ�� �簢�� �����

			//pDoc->m_rects[pDoc->m_rectsCurrent].getstart().x += point.x - pDoc->m_rects[pDoc->m_rectsCurrent].
			pDoc->m_rects[pDoc->m_rectsCurrent].SetEnd(point.x, point.y);
			dc.Rectangle(pDoc->m_rects[pDoc->m_rectsCurrent].getstart().x,
				pDoc->m_rects[pDoc->m_rectsCurrent].getstart().y,
				pDoc->m_rects[pDoc->m_rectsCurrent].getend().x,
				pDoc->m_rects[pDoc->m_rectsCurrent].getend().y); // ���� �׸���
				*/
		}

		default:
			break;
		}
		CFormView::OnMouseMove(nFlags, point);
	}
	
}
void CGraphicEditorView::OnLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CurrentMode = DrawMode::LINE;
}


void CGraphicEditorView::OnPolyline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CurrentMode = DrawMode::POLY;
}


void CGraphicEditorView::OnRectangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CurrentMode = DrawMode::RECT;
}


void CGraphicEditorView::OnEllipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CurrentMode = DrawMode::ELLP;
}


void CGraphicEditorView::OnText()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CurrentMode = DrawMode::TEXT;
}



void CGraphicEditorView::OnUpdateText(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(CurrentMode == DrawMode::TEXT);
}


void CGraphicEditorView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(CurrentMode == DrawMode::RECT);
}


void CGraphicEditorView::OnUpdatePolyline(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(CurrentMode == DrawMode::POLY);
}


void CGraphicEditorView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(CurrentMode == DrawMode::ELLP);
}


void CGraphicEditorView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(CurrentMode == DrawMode::LINE);
}
