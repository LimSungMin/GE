
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
//#include "Rectangle.h"
#include "GObject.h"
#include "GRectangle.h"
#include "GPolyline.h"
#include "GLine.h"

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
	ON_WM_CHAR()
//	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_UNDO, &CGraphicEditorView::OnEditUndo)
	ON_BN_CLICKED(IDC_LineColor, &CGraphicEditorView::OnBnClickedLinecolor)
END_MESSAGE_MAP()

// CGraphicEditorView ����/�Ҹ�



CGraphicEditorView::CGraphicEditorView()
	: CFormView(CGraphicEditorView::IDD)
	, m_stringreg(_T(""))
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
		//line.SetStart(point.x, point.y);
		pDoc->m_line = new GLine();
		
		pDoc->m_line->setStartX(point.x);
		pDoc->m_line->setStartY(point.y);
		pDoc->m_line->SetEnd(point);


		
		pos = point;
		break;
	case DrawMode::RECT:{
		
		//GRectangle* rect = new GRectangle();
		pDoc->m_rect = new GRectangle();
		pDoc->m_rect->setStartX(point.x - 10);
		pDoc->m_rect->setStartY(point.y - 10);
		pDoc->m_rect->setEndX(point.x + 10);
		pDoc->m_rect->setEndY(point.y + 10);
		// pDoc->m_shapes.Add(*rect);
		// pDoc->m_shapesCurrent = pDoc->m_shapes.GetCount() - 1;
		Invalidate();
		break;
	}

	case DrawMode::TEXT:{
		//line.SetStart(point.x, point.y);
		//line.SetEnd(point.x, point.y);
		break;
	}

	case DrawMode::POLY:{
		
		if (m_firstclick == TRUE){
			pDoc->m_poly = new GPolyline();

			m_firstclick = FALSE;
		}

		pDoc->m_poly->polypointset(point);
	}
	default:
		break;
	}

	
	CFormView::OnLButtonDown(nFlags, point);
}



void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();
	ldown = FALSE;
	GLine line;
	switch (CurrentMode)
	{
	case DrawMode::LINE:{
		pDoc->vo.push_back(pDoc->m_line);
		
		break;
	}
	case DrawMode::RECT:{
		/*line.SetEnd(point.x, point.y);
		JRectangle r(line.getstart(), line.getend());
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_COPYPEN);
		dc.Rectangle(r.getstart().x, r.getstart().y, r.getend().x, r.getend().y);*/

		//pDoc->m_rects.Add(pDoc->m_rect);
		//GRectangle rect = GRectangle(pDoc->m_rect);
		//pDoc->m_shapes.Add(rect);

		/*GRectangle* rect = new GRectangle(pDoc->m_rect);
		pDoc->m_shapes.Add(*rect);
		pDoc->m_shapesCurrent = pDoc->m_shapes.GetCount() - 1;
		*/
		pDoc->vo.push_back(pDoc->m_rect);
		Invalidate();
		break;
	}
	
	case DrawMode::TEXT:{
		
		/*
			line.SetEnd(point.x, point.y);
			//JRectangle r(line.getstart(), line.getend());
			CClientDC dc(this);
			dc.SelectStockObject(NULL_BRUSH);
			dc.SetROP2(R2_COPYPEN);
			dc.Rectangle(r.getstart().x, r.getstart().y, r.getend().x, r.getend().y);

			//m_str.Add('\0');
			m_stringreg = CString(m_str.GetData());

			CPaintDC dt(this);

			//CString test = _T("this is test of textbox");
			dc.SetBkMode(TRANSPARENT);
			
			if (r.getstart().x > r.getend().x && r.getstart().y > r.getend().y)
			{
				dc.DrawText(_T("this is test of textbox"),
					CRect(r.getend().x, r.getend().y, r.getstart().x, r.getstart().y)
					, DT_LEFT | DT_WORDBREAK );
				
			}
			else{
			dc.DrawText(m_stringreg,
				CRect(r.getstart().x, r.getstart().y, r.getend().x, r.getend().y)
				, DT_LEFT | DT_WORDBREAK);
			}

			m_str.RemoveAll();
			*/
		break;
	}
	case DrawMode::POLY:{

		pDoc->vo.push_back(pDoc->m_poly);
		Invalidate();

						}


	default:
		break;
	}
	CFormView::OnLButtonUp(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();

	if (ldown){
		switch (CurrentMode)
		{
		case DrawMode::LINE:{
			

			pDoc->m_line->SetEnd(point);

			Invalidate();
			break;
		}
		case DrawMode::RECT:{
			pDoc->m_rect->setEndX(point.x);
			pDoc->m_rect->setEndY(point.y);
			/*pDoc->m_shapes[pDoc->m_shapesCurrent].setEndX(point.x);
			pDoc->m_shapes[pDoc->m_shapesCurrent].setEndY(point.y);*/

			Invalidate();
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


void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (CurrentMode)
	{
	case DrawMode::TEXT:{

		if (nChar == _T('\b')){
			if (m_str.GetSize() > 0)
				m_str.RemoveAt(m_str.GetSize() - 1);
		}

		else {
			m_str.Add(nChar);
		}

		break;
	}

	default:
		break;
	}
	CFormView::OnChar(nChar, nRepCnt, nFlags);
	
}
int i = 0;

void CGraphicEditorView::OnDraw(CDC* pDC)
{
	
	CString str;
	CGraphicEditorDoc* pDoc = GetDocument();

	/*
	for (int i = 0; i < pDoc->m_shapes.GetCount(); i++){
		pDoc->m_shapes[i].draw(pDC);
	}
	pDoc->m_poly.draw(pDC);
	*/

	for (auto i : pDoc->vo) i->draw(pDC);
	
	switch (CurrentMode){
	case DrawMode::LINE:{
		pDoc->m_line->draw(pDC);
		
		break;
	}
	case DrawMode::RECT:{
		pDoc->m_rect->draw(pDC);
		
		break;
		}

	case DrawMode::POLY:{
		pDoc->m_poly->draw(pDC);
		break;
	}
	
	}
	
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}



void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CGraphicEditorDoc* pDoc = GetDocument();

	if ( m_firstclick == FALSE)
	pDoc->m_poly = new GPolyline();

	//pDoc->m_polypoints.Add(NULL);

	CFormView::OnLButtonDblClk(nFlags, point);
}


void CGraphicEditorView::OnEditUndo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();
	Invalidate();
	pDoc->vo.pop_back();
	Invalidate();
}


void CGraphicEditorView::OnBnClickedLinecolor() // �� �� ������ �ҷ���
{
	CColorDialog cdlg;

	if (cdlg.DoModal() == IDOK)
	{
		
	}


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
