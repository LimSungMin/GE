#pragma once
#include "afxwin.h"


// ControlEdit ��ȭ �����Դϴ�.

class ControlEdit : public CDialog
{
	DECLARE_DYNAMIC(ControlEdit)

public:
	ControlEdit(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ControlEdit();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PAINTTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
