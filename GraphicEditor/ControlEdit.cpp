// ControlEdit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "ControlEdit.h"
#include "afxdialogex.h"
#include "GraphicEditorDoc.h"

// ControlEdit ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ControlEdit, CDialog)

ControlEdit::ControlEdit(CWnd* pParent /*=NULL*/)
	: CDialog(ControlEdit::IDD, pParent)
{

}

ControlEdit::~ControlEdit()
{
}

void ControlEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_Font, m_combofont);
	DDX_Control(pDX, IDC_LineThick, m_linethick);
	DDX_Control(pDX, IDC_LinePattern, m_linepattern);
	DDX_Control(pDX, IDC_FILLPATTERN, m_fillpattern);
	
}


BEGIN_MESSAGE_MAP(ControlEdit, CDialog)

	//ON_CBN_SELCHANGE(IDC_Font, &ControlEdit::OnCbnSelchangeFont)
END_MESSAGE_MAP()



/*
void ControlEdit::OnCbnSelchangeFont()
{
	m_fontnumb = m_combofont.GetCurSel();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
*/

BOOL ControlEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_combofont.SetCurSel(m_fontnumb);

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
