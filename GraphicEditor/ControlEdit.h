#pragma once


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
};
