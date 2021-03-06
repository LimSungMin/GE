#pragma once
#include "afxwin.h"


// ControlEdit 대화 상자입니다.

class ControlEdit : public CDialog
{
	DECLARE_DYNAMIC(ControlEdit)

public:
	ControlEdit(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ControlEdit();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PAINTTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedLinecolor();
//	afx_msg void OnBnClickedLinecolor();
	CComboBox m_combofont;
	int m_fontnumb;
//	afx_msg void OnCbnSelchangeFont();
	virtual BOOL OnInitDialog();

	CComboBox m_linethick;
	CComboBox m_linepattern;
	CComboBox m_fillpattern;
};
