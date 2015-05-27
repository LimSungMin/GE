
// LeftView.h : CLeftView Ŭ������ �������̽�
//


#pragma once

class CGraphicEditorDoc;

class CLeftView : public CTreeView
{
protected: // serialization������ ��������ϴ�.
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Ư���Դϴ�.
public:
	CGraphicEditorDoc* GetDocument();

// �۾��Դϴ�.
public:

// �������Դϴ�.
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // LeftView.cpp�� ����� ����
inline CGraphicEditorDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

