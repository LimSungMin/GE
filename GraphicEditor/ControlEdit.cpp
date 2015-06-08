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
	DDX_Control(pDX, IDC_Font, m_combofont);
}


BEGIN_MESSAGE_MAP(ControlEdit, CDialog)

	ON_CBN_SELCHANGE(IDC_Font, &ControlEdit::OnCbnSelchangeFont)
END_MESSAGE_MAP()




void ControlEdit::OnCbnSelchangeFont()
{
	m_fontnumb = m_combofont.GetCurSel();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
