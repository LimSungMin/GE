
// GEView.h : CGEView 適掘什税 昔斗凪戚什
//

#pragma once

#include "resource.h"


class CGEView : public CFormView
{
protected: // serialization拭辞幻 幻級嬢増艦陥.
	CGEView();
	DECLARE_DYNCREATE(CGEView)

public:
	enum{ IDD = IDD_GE_FORM };

// 働失脊艦陥.
public:
	CGEDoc* GetDocument() const;
	CString str;
	CString lwjstけいしけいしr;
// 拙穣脊艦陥.
public:

// 仙舛税脊艦陥.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 走据脊艦陥.
	virtual void OnInitialUpdate(); // 持失 板 坦製 硲窒鞠醸柔艦陥.

// 姥薄脊艦陥.
public:
	virtual ~CGEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 持失吉 五獣走 己 敗呪
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GEView.cpp税 巨獄益 獄穿
inline CGEDoc* CGEView::GetDocument() const
   { return reinterpret_cast<CGEDoc*>(m_pDocument); }
#endif

