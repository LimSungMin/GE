
// GEView.h : CGEView Ŭ������ �������̽�
//

#pragma once

#include "resource.h"


class CGEView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CGEView();
	DECLARE_DYNCREATE(CGEView)

public:
	enum{ IDD = IDD_GE_FORM };

// Ư���Դϴ�.
public:
	CGEDoc* GetDocument() const;
	CString str;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CGEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GEView.cpp�� ����� ����
inline CGEDoc* CGEView::GetDocument() const
   { return reinterpret_cast<CGEDoc*>(m_pDocument); }
#endif

