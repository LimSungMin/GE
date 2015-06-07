
// GraphicEditor.h : GraphicEditor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

#include "GObject.h"
#include "GRectangle.h"
#include "GPolyline.h"
#include "GLine.h"
#include "GEllipse.h"
#include "GGroup.h"
#include "GTextBox.h"
// CGraphicEditorApp:
// �� Ŭ������ ������ ���ؼ��� GraphicEditor.cpp�� �����Ͻʽÿ�.
//

class CGraphicEditorApp : public CWinAppEx
{
public:
	CGraphicEditorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphicEditorApp theApp;
