// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CtrlSpace.h"

#include "MainFrm.h"
#include "InputSimulate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CTrayFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CTrayFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTrayFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!::RegisterHotKey(m_hWnd, 0, MOD_CONTROL, VK_SPACE))
		return -1;

	CreateTray(IDR_MAINFRAME, _T("Ctrl - Space"));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CTrayFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

void CMainFrame::OnDestroy() 
{
	::UnregisterHotKey(m_hWnd, 0);
	CTrayFrameWnd::OnDestroy();	
}

LRESULT CMainFrame::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		SimulateKeyDown(VK_CONTROL);
		SimulateKeyStroke(VK_SHIFT);
	}

	return 0;
}
