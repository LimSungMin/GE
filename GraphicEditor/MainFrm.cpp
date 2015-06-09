
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "GraphicEditor.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "GraphicEditorDoc.h"
#include "GraphicEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND(ID_LINE, &CMainFrame::OnLine)
	ON_COMMAND(ID_POLYLINE, &CMainFrame::OnPolyline)
	ON_COMMAND(ID_RECTANGLE, &CMainFrame::OnRectangle)
	ON_COMMAND(ID_ELLIPSE, &CMainFrame::OnEllipse)
	ON_COMMAND(ID_TEXT, &CMainFrame::OnText)
	ON_CBN_SELCHANGE(IDC_LineThick, &CMainFrame::OnCbnSelchangeLinethick)
	ON_CBN_SELCHANGE(IDC_LinePattern, &CMainFrame::OnCbnSelchangeLinepattern)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMainFrame::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_FONT, &CMainFrame::OnCbnSelchangeFont)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	fr_lineSize = 1;
	fr_linePattern = PS_SOLID;
	fr_fillPattern = 6;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 사용할 수 있는 다른 스타일...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // FALSE로 설정하여 탭 영역 오른쪽에 닫기 단추를 배치합니다.
	mdiTabParams.m_bTabIcons = FALSE;    // TRUE로 설정하여 MDI 탭의 문서 아이콘을 활성화합니다.
	mdiTabParams.m_bAutoColor = TRUE;    // FALSE로 설정하여 MDI 탭의 자동 색 지정을 비활성화합니다.
	mdiTabParams.m_bDocumentMenu = TRUE; // 탭 영역의 오른쪽 가장자리에 문서 메뉴를 활성화합니다.
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("메뉴 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 메뉴 모음을 활성화해도 포커스가 이동하지 않게 합니다.
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 사용자 정의 도구 모음 작업을 허용합니다.
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음 및 메뉴 모음을 도킹할 수 없게 하려면 이 다섯 줄을 삭제하십시오.
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// Visual Studio 2005 스타일 도킹 창 동작을 활성화합니다.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 스타일 도킹 창 자동 숨김 동작을 활성화합니다.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 모든 사용자 인터페이스 요소를 그리는 데 사용하는 비주얼 관리자를 설정합니다.
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 향상된 창 관리 대화 상자를 활성화합니다.
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 도구 모음 및 도킹 창 메뉴 바꾸기를 활성화합니다.
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 빠른(<Alt> 키를 누른 채 끌기) 도구 모음 사용자 지정을 활성화합니다.
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 사용자 정의 도구 모음 이미지를 로드합니다.
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}


	// 메뉴 개인 설정을 활성화합니다(가장 최근에 사용한 명령).
	// TODO: 사용자의 기본 명령을 정의하여 각 풀다운 메뉴에 하나 이상의 기본 명령을 포함시킵니다.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// 창 제목 표시줄에서 문서 이름 및 응용 프로그램 이름의 순서를 전환합니다.
	// 문서 이름이 축소판 그림과 함께 표시되므로 작업 표시줄의 기능성이 개선됩니다.
	ModifyStyle(0, FWS_PREFIXTITLE);
	/*
	if (
		!m_DockingBar.Create(
		_T("DialogBar"), this, TRUE,
		MAKEINTRESOURCE(IDD_PAINTTOOL),
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MINIMIZE |
		CBRS_LEFT | CBRS_FLOAT_MULTI,
		IDD_PAINTTOOL))
	{
		return -1;

	}

	m_DockingBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_DockingBar);
	*/

	if (!m_DockingBar.Create(this, IDD_PAINTTOOL,
		CBRS_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
		IDD_PAINTTOOL))
	{
		TRACE0("Failed to create dialog bar m_wndPaintDialog\n");
		return -1;		// fail to create
	}

	m_DockingBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_DockingBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 메뉴를 검색합니다. */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 기본 클래스가 실제 작업을 수행합니다.

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 모든 사용자 도구 모음에 사용자 지정 단추를 활성화합니다.
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


// 이것은 라인 메시지 처리기 입니다
void CMainFrame::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.	
}

// 이것은 폴리라인 메시지 처리기 입니다.
void CMainFrame::OnPolyline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

// 이것은 사각형 메시지 처리기 입니다.
void CMainFrame::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

// 이것은 타원 메시지 처리기 입니다.
void CMainFrame::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

// 이것은 텍스트 메시지 처리기 입니다.
void CMainFrame::OnText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnCbnSelchangeLinethick()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strBuf, strOut;
	CComboBox *pbox = (CComboBox*)m_DockingBar.GetDlgItem(IDC_LineThick);
	pbox->GetWindowText(strBuf);
	CT2A ascii(strBuf);
	fr_lineSize = atoi(ascii.m_psz);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChild = (CChildFrame*)pFrame->GetActiveFrame();
	CGraphicEditorDoc* pDoc = (CGraphicEditorDoc*)(pChild->GetActiveDocument());
	for (int i = 0; i < pDoc->vo.size(); i++){
		if (pDoc->vo[i]->getSelected() == TRUE){
			pDoc->vo[i]->setThick(fr_lineSize);
		}
	}
	pDoc->UpdateAllViews(NULL);
	//Invalidate(FALSE);
}


void CMainFrame::OnCbnSelchangeLinepattern()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// IDC_LinePattern
	CString strBuf, strOut;
	CComboBox *pbox = (CComboBox*)m_DockingBar.GetDlgItem(IDC_LinePattern);
	pbox->GetWindowText(strBuf);
	if (strBuf == "SOLID")
	{
		fr_linePattern = PS_SOLID;
	}
	else if (strBuf == "DASH"){
		fr_linePattern = PS_DASH;
	}else if (strBuf == "DOT"){
		fr_linePattern = PS_DOT;
	}
	else if (strBuf == "DASHDOT"){
		fr_linePattern = PS_DASHDOT;
	}
	else if (strBuf == "DASHDOTDOT"){
		fr_linePattern = PS_DASHDOTDOT;
	}
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChild = (CChildFrame*)pFrame->GetActiveFrame();
	CGraphicEditorDoc* pDoc = (CGraphicEditorDoc*)(pChild->GetActiveDocument());
	for (int i = 0; i < pDoc->vo.size(); i++){
		if (pDoc->vo[i]->getSelected() == TRUE){
			pDoc->vo[i]->setPattern(fr_linePattern);
		}
	}
	pDoc->UpdateAllViews(NULL);
}


void CMainFrame::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strBuf, strOut;
	CComboBox *pbox = (CComboBox*)m_DockingBar.GetDlgItem(IDC_FILLPATTERN);
	pbox->GetWindowText(strBuf);
	CT2A ascii(strBuf);
	fr_fillPattern = atoi(ascii.m_psz);	
	HS_HORIZONTAL;	//0
	HS_VERTICAL;	//1
	HS_FDIAGONAL;	//2
	HS_BDIAGONAL;	//3
	HS_CROSS;		//4
	HS_DIAGCROSS;	//5
	if (strBuf == "HORIZONTAL")
	{
		fr_fillPattern = HS_HORIZONTAL;
	}
	else if (strBuf == "VERTICAL"){
		fr_fillPattern = HS_VERTICAL;
	}
	else if (strBuf == "FDIAGONAL"){
		fr_fillPattern = HS_FDIAGONAL;
	}
	else if (strBuf == "BDIAGONAL"){
		fr_fillPattern = HS_BDIAGONAL;
	}
	else if (strBuf == "CROSS"){
		fr_fillPattern = HS_CROSS;
	}
	else if (strBuf == "DIAGCROSS"){
		fr_fillPattern = HS_DIAGCROSS;
	}
	else if (strBuf == "SOLID"){
		fr_fillPattern = 6;
	}
	//
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChild = (CChildFrame*)pFrame->GetActiveFrame();
	CGraphicEditorDoc* pDoc = (CGraphicEditorDoc*)(pChild->GetActiveDocument());
	for (int i = 0; i < pDoc->vo.size(); i++){
		if (pDoc->vo[i]->getSelected() == TRUE){
			pDoc->vo[i]->setFillPattern(fr_fillPattern);
		}
	}
	pDoc->UpdateAllViews(NULL);
}


void CMainFrame::OnCbnSelchangeFont()
{
	CString strBuf, strOut;
	CComboBox *pbox = (CComboBox*)m_DockingBar.GetDlgItem(IDC_FONT);
	pbox->GetWindowText(strBuf);
	CT2A ascii(strBuf);
	fr_font = atoi(ascii.m_psz);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
