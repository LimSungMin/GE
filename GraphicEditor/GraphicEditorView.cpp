
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
#include "GEllipse.h"

// ��Ʈ�� ���� �������
#include "ControlEdit.h"

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
	ON_BN_CLICKED(IDC_PaneColor, &CGraphicEditorView::OnBnClickedPanecolor)

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
	
	for (int i = 0; i < pDoc->vo.size(); i++)
		pDoc->vo[i]->setSelected(FALSE);
	
	switch (CurrentMode)
	{
	case DrawMode::LINE:
		//line.SetStart(point.x, point.y);
		pDoc->m_line = new GLine();
		
		pDoc->m_line->setStartX(point.x);
		pDoc->m_line->setStartY(point.y);
		pDoc->m_line->SetEnd(point);
		pDoc->m_line->setEndX(point.x);
		pDoc->m_line->setEndY(point.y);
		
		
		break;
		
	case DrawMode::ELLP:{
		pDoc->m_ellp = new GEllipse();
		
		pDoc->m_ellp->setStartX(point.x);
		pDoc->m_ellp->setStartY(point.y);
		pDoc->m_ellp->setEndX(point.x);
		pDoc->m_ellp->setEndY(point.y);
		pDoc->m_ellp->SetEnd(point);
	}
	
	case DrawMode::RECT:{
		
		pDoc->m_rect = new GRectangle();
		pDoc->m_rect->setPattern(PS_DOT);
		pDoc->m_rect->setStartX(point.x - 10);
		pDoc->m_rect->setStartY(point.y - 10);
		pDoc->m_rect->setEndX(point.x + 10);
		pDoc->m_rect->setEndY(point.y + 10);
		//Invalidate();
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

		break;
	}
	default:{ // DrawMode::NOTHING
		if (pDoc->vo.size()>0 && m_currentSelected >= 0){
			if ((m_changeSizePosition = pDoc->vo[m_currentSelected]->isInSizeBound(point)) >= 0){ // ũ�� ���� ��ġ�� 0~3
				/*
				if (pDoc->vo[m_currentSelected] == pDoc->m_poly){ // ���������� ��� Ư���ϹǷ� �ٲپ�ߵ�
					MessageBox(NULL, NULL, NULL);
					
					pDoc->vo[m_currentSelected]->polypointmovecheck(1);

					polypointmove = TRUE;

					break;
				}*/
				
				m_changeSize = TRUE;
				pDoc->vo[m_currentSelected]->setSelected(TRUE);
				return;
			}
		}
		for (int i = 0; i < pDoc->vo.size(); i++) // ���õǾ��� ��ü�� ���� ���� �����Ѵ�.
			pDoc->vo[i]->setSelected(FALSE);

		for (int i = pDoc->vo.size() - 1; i >= 0; i--){ // �� ���� �ִ� ������ ��� ���� �������� �˻���.
			if (pDoc->vo[i]->isInBound(point)){
				m_move = TRUE;
				pDoc->vo[i]->setSelected(TRUE);
				m_currentSelected = i;
				m_clickedPoint = point;
				break;
			}
		}
		break;
	}
		
	}

	Invalidate();
	CFormView::OnLButtonDown(nFlags, point);
}



void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();
	ldown = FALSE;
	if (m_changeSize == TRUE){
		m_changeSize = FALSE;
		m_changeSizePosition = -1;
		pDoc->vo[m_currentSelected]->setSelected(TRUE);
		return;
	}

	GLine line;
	switch (CurrentMode)
	{
	case DrawMode::LINE:{
		pDoc->m_line->setPattern(PS_SOLID);
		pDoc->m_line->setSelected(TRUE);
		pDoc->vo.push_back(pDoc->m_line);
		m_currentSelected = pDoc->vo.size() - 1;
		Invalidate();
		break;
	}
						
	case DrawMode::ELLP:{
		pDoc->m_ellp->setPattern(PS_SOLID);
		pDoc->m_ellp->setSelected(TRUE);
		pDoc->vo.push_back(pDoc->m_ellp);
		m_currentSelected = pDoc->vo.size() - 1;
		Invalidate();
		break;
	}
	case DrawMode::RECT:{
		pDoc->m_rect->setPattern(PS_SOLID);
		pDoc->m_rect->setSelected(TRUE);
		pDoc->vo.push_back(pDoc->m_rect);
		m_currentSelected = pDoc->vo.size() - 1;
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
		m_move = FALSE;
		break;
	}
	CFormView::OnLButtonUp(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();

	if (ldown){
		if (m_changeSize == TRUE){
			switch (m_changeSizePosition){
			case 0:{ // ���� ��
				pDoc->vo[m_currentSelected]->setStartX(point.x);
				pDoc->vo[m_currentSelected]->setStartY(point.y);
				break;
			}
			case 1:{ // ������ ��
				pDoc->vo[m_currentSelected]->setEndX(point.x);
				pDoc->vo[m_currentSelected]->setStartY(point.y);
				break;
			}
			case 2:{ // ���� �Ʒ�
				pDoc->vo[m_currentSelected]->setStartX(point.x);
				pDoc->vo[m_currentSelected]->setEndY(point.y);
				break;
			}
			case 3:{ // ������ �Ʒ�
				pDoc->vo[m_currentSelected]->setEndX(point.x);
				pDoc->vo[m_currentSelected]->setEndY(point.y);
				break;
			}
			default:{
				break;
			}
			}
			Invalidate();
			return;
		}
		switch (CurrentMode)
		{
		case DrawMode::LINE:{
			pDoc->m_line->SetEnd(point);
			pDoc->m_line->setEndX(point.x);
			pDoc->m_line->setEndY(point.y);
			Invalidate();
			break;
		}
		case DrawMode::ELLP:{
			pDoc->m_ellp->SetEnd(point);
			pDoc->m_ellp->setEndX(point.x);
			pDoc->m_ellp->setEndY(point.y);
			Invalidate();
			break;
		}


		case DrawMode::RECT:{
			pDoc->m_rect->setEndX(point.x);
			pDoc->m_rect->setEndY(point.y);
			Invalidate();
		}
		default:{
			if (m_move == TRUE){ // ��ü�� ���õǾ��� �� ������ ��� �����̴� ��Ȳ
				GObject* curr = pDoc->vo[m_currentSelected];

				int startX = curr->getStartX();
				int startY = curr->getStartY();
				int endX = curr->getEndX();
				int endY = curr->getEndY();

				startX += point.x - m_clickedPoint.x;
				startY += point.y - m_clickedPoint.y;
				endX += point.x - m_clickedPoint.x;
				endY += point.y - m_clickedPoint.y;

				curr->move(startX, startY, endX, endY);
				m_clickedPoint = point;

				

				Invalidate();
			}
			break;
		}
		}
		CFormView::OnMouseMove(nFlags, point);
	}

	
}
void CGraphicEditorView::OnLine()
{
	if (CurrentMode != DrawMode::LINE)
		CurrentMode = DrawMode::LINE;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnPolyline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (CurrentMode != DrawMode::POLY)
		CurrentMode = DrawMode::POLY;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnRectangle()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (CurrentMode != DrawMode::RECT)
		CurrentMode = DrawMode::RECT;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnEllipse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (CurrentMode != DrawMode::ELLP)
		CurrentMode = DrawMode::ELLP;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnText()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (CurrentMode != DrawMode::TEXT)
		CurrentMode = DrawMode::TEXT;
	else
		CurrentMode = DrawMode::NOTHING;
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

	for (auto i : pDoc->vo) i->draw(pDC);
	
	switch (CurrentMode){
	case DrawMode::LINE:{
		pDoc->m_line->draw(pDC);
		
		break;
	}
	case DrawMode::ELLP:{
		pDoc->m_ellp->draw(pDC);
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
	
	pDoc->m_poly->polypointset(point);
	m_firstclick = TRUE;
	

	//pDoc->m_poly->deletepolypointset(1);
	//pDoc->m_polypoints.Add(NULL);
	//
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
	CGraphicEditorDoc* pDoc = GetDocument();

	if (cdlg.DoModal() == IDOK)
	{
		switch (CurrentMode){
		case DrawMode::LINE:{
			pDoc->m_line->setLineColor(cdlg.GetColor());
			break;
		}
		case DrawMode::ELLP:{
			pDoc->m_ellp->setLineColor(cdlg.GetColor());
			break;
		}
		case DrawMode::RECT:{
			pDoc->m_rect->setLineColor(cdlg.GetColor());

			break;
		}

		case DrawMode::POLY:{
			pDoc->m_poly->setLineColor(cdlg.GetColor());
			break;
		}
		}
		Invalidate();
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnBnClickedPanecolor()
{
	CColorDialog cdlg;
	CGraphicEditorDoc* pDoc = GetDocument();

	if (cdlg.DoModal() == IDOK)
	{
		switch (CurrentMode){
		case DrawMode::LINE:{
			pDoc->m_line->setFillColor(cdlg.GetColor());
			break;
		}
		case DrawMode::ELLP:{
			pDoc->m_ellp->setFillColor(cdlg.GetColor());
			break;
		}
		case DrawMode::RECT:{
			pDoc->m_rect->setFillColor(cdlg.GetColor());

			break;
		}

		case DrawMode::POLY:{
			pDoc->m_poly->setFillColor(cdlg.GetColor());
			break;
		}
		}
		Invalidate();
	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}