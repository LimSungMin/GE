
// GraphicEditorView.h : CGraphicEditorView Ŭ������ �������̽�
//

#pragma once

#include "resource.h"


class CGraphicEditorView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditorView();
	DECLARE_DYNCREATE(CGraphicEditorView)

public:
	enum{ IDD = IDD_GRAPHICEDITOR_FORM };

// Ư���Դϴ�.
public:
	CGraphicEditorDoc* GetDocument() const;
	enum DrawMode
	{
		NOTHING = -1, LINE, POLY, RECT, ELLP, TEXT
	};
	int CurrentMode;
	

	POINT pos;
	POINT postPos;
	BOOL ldown;
	BOOL m_move = FALSE; // ������ ��� ���� ����
	BOOL m_changeSize = FALSE; // ���� ��Ʈ�Ӹ��� ��� ũ�⸦ �����ϴ� ����
	BOOL m_textin = FALSE;
	BOOL m_firstclick = TRUE;
	CArray<TCHAR, TCHAR> m_str;
	int m_changeSizePosition = -1;
	int m_currentSelected; // ���õ� ������ m_shape index
	POINT m_clickedPoint; // ������ �������� �� Ŭ���� ���콺 �������� ��ǥ
	GGroup m_group;

	int m_fontnumb;

	int polypointindex; // ���õ� �簢�� �ӽ� ���� ��ǥ
	int m_lineSize;		// MainFrm ���κ��� �� �β��� �����ɴϴ�.
	int m_linePattern;	// MainFrm ���κ��� �� ������ �����ɴϴ�.
	int m_fillPattern;	// MainFrm ���κ��� ���� ������ �����ɴϴ�.
	BOOL polypointmove = FALSE;

// �۾��Դϴ�.
public:
	int getLineSize();
	int getLinePattern();
	int getFillPattern();
	int getFont();
// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnPolyline();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnText();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdateText(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePolyline(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	CString m_stringreg;
	virtual void OnDraw(CDC* /*pDC*/);
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
	afx_msg void OnBnClickedLinecolor();
	afx_msg void OnBnClickedPanecolor();
	afx_msg void OnDelete();
	afx_msg void OnSelect();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGroup();
	afx_msg void OnGroupdeselect();
	afx_msg void OnCbnSelchangeLinethick();
	afx_msg void OnCbnSelchangeLinepattern();
	afx_msg void OnCbnSelchangeFillpattern();
	afx_msg void OnCut();
	afx_msg void OnPaste();
	afx_msg void OnBnClickedFontcolor();
};

#ifndef _DEBUG  // GraphicEditorView.cpp�� ����� ����
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

