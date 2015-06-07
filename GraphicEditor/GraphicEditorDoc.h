
// GraphicEditorDoc.h : CGraphicEditorDoc Ŭ������ �������̽�
//


#pragma once
#include "afxtempl.h"
#include <vector>
using namespace std;
class CGraphicEditorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditorDoc();
	DECLARE_DYNCREATE(CGraphicEditorDoc)

	// Ư���Դϴ�.
public:
	BOOL m_enableRectangle;
	CArray<GObject, GObject&> m_shapes;
	int m_shapesCurrent;
	GRectangle* m_rect;
	GPolyline* m_poly;
	GLine* m_line;
	GEllipse* m_ellp;

	COLORREF m_colorLine;
	COLORREF m_colorFill;

	vector <GObject*> vo;
	CList<GObject, GObject&> m_group;
	// �۾��Դϴ�. 
public:

	// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// �����Դϴ�.
public:
	virtual ~CGraphicEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	CArray<POINT, POINT&> m_polypoints;
	afx_msg void OnEditUndo();
	afx_msg void OnDelete();
};
