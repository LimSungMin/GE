
// GE.h : GE ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGEApp:
// �� Ŭ������ ������ ���ؼ��� GE.cpp�� �����Ͻʽÿ�.
//

class CGEApp : public CWinApp
{
public:
	CGEApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGEApp theApp;
