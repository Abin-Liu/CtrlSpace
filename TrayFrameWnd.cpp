////////////////////////////////////////////////////////////////////
// TrayFrameWnd.cpp
//
// CTrayFrameWnd, a CFrameWnd derived class implements system tray
// window combined with Chris Maunder's CSystemTray class.
//
// Abin (abinn32@yahoo.com)
//
// 2012-11-20
////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrayFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_TRAYNOTIFY	(WM_APP + 6835)

IMPLEMENT_DYNCREATE(CTrayFrameWnd, CFrameWnd)

CTrayFrameWnd::CTrayFrameWnd()
{
	m_pMainDlg = NULL;
}

CTrayFrameWnd::~CTrayFrameWnd()
{	
}

BEGIN_MESSAGE_MAP(CTrayFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CTrayFrameWnd)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrayFrameWnd message handlers

BOOL CTrayFrameWnd::CreateTray(HICON hIcon, LPCTSTR lpszTooltip, LPCTSTR lpszBalloonText, LPCTSTR lpszBalloonTitle, DWORD dwBalloonIcon, UINT nBalloonTimeout)
{
	return m_tray.Create(this, WM_TRAYNOTIFY, lpszTooltip, hIcon, 0, FALSE, lpszBalloonText, lpszBalloonTitle, dwBalloonIcon, nBalloonTimeout);
}

BOOL CTrayFrameWnd::CreateTray(UINT nIconResID, LPCTSTR lpszTooltip, LPCTSTR lpszBalloonText, LPCTSTR lpszBalloonTitle, DWORD dwBalloonIcon, UINT nBalloonTimeout)
{
	return CreateTray(AfxGetApp()->LoadIcon(nIconResID), lpszTooltip, lpszBalloonText, lpszBalloonTitle, dwBalloonIcon, nBalloonTimeout);
}

void CTrayFrameWnd::CmdRouteMenu(CMenu *pMenu)
{
	if (!pMenu)
	{
		ASSERT(FALSE);
		return;
	}

	CCmdUI state;
	state.m_pMenu = pMenu;
	state.m_pParentMenu = pMenu;
	state.m_nIndexMax = pMenu->GetMenuItemCount();

	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++) 
	{
		state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);

		// menu separator or invalid cmd - ignore it
		if (state.m_nID == 0)
			continue; 

		if (state.m_nID == -1)
		{
			// possibly a popup menu, route to child menu if so
			CMenu* pSub=pMenu->GetSubMenu(state.m_nIndex);
			if (pSub)
				CmdRouteMenu(pSub);
		}
		else 
		{
			// normal menu item, Auto disable if command is 
			// _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}
	}
}

BOOL CTrayFrameWnd::PopupMenu(CMenu *pMenu, int nSubMenuIndex, int nDefaultItemPos)
{
	if (!pMenu)
	{		
		pMenu = GetMenu();
		if (!pMenu)
			return FALSE;
	}

	pMenu = pMenu->GetSubMenu(nSubMenuIndex);
	if (!pMenu)
		return FALSE;

	if (nDefaultItemPos >= 0)
		pMenu->SetDefaultItem((UINT)nDefaultItemPos, TRUE);

	CmdRouteMenu(pMenu);
	POINT pt;
	::GetCursorPos(&pt);
	SetForegroundWindow();
	pMenu->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this, NULL);
	PostMessage(WM_NULL);
	return TRUE;
}

BOOL CTrayFrameWnd::PopupMenu(UINT nMenuResID, int nSubMenuIndex, int nDefaultItemPos)
{
	CMenu menu;
	if (!menu.LoadMenu(nMenuResID))
		return FALSE;

	return PopupMenu(&menu, nSubMenuIndex, nDefaultItemPos);
}

void CTrayFrameWnd::OnTrayDblClick()
{
	OnConfig();
}

void CTrayFrameWnd::OnTrayBalloonClick()
{
	OnTrayDblClick();
}

void CTrayFrameWnd::OnTrayRClick()
{
	PopupMenu(GetMenu(), 0, 0);
}

LRESULT CTrayFrameWnd::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{	
	if (lParam == WM_LBUTTONUP)
	{
		SetForegroundWindow();
		OnTrayLClick();
	}	
	else if (lParam == WM_RBUTTONUP)
	{
		SetForegroundWindow();
		OnTrayRClick();		
	}
	else if (lParam == WM_LBUTTONDBLCLK)
	{
		SetForegroundWindow();
		OnTrayDblClick();
	}
	else if (lParam == NIN_BALLOONUSERCLICK)
	{
		SetForegroundWindow();
		OnTrayBalloonClick();
	}

	return (LRESULT)0;
}

int CTrayFrameWnd::DoModal(CDialog* pDialog, int nKey, BOOL bIsMainDlg)
{
	if (!pDialog)
	{
		ASSERT(FALSE);
		return IDCANCEL;
	}

	if (nKey != KEY_IGNORED)
	{
		if (FindDialog(nKey, TRUE))
			return IDCANCEL;

		m_dlgMap.SetAt(nKey, pDialog);
	}

	if (bIsMainDlg)
		m_pMainDlg = (CWnd*)pDialog;

	int nResult = pDialog->DoModal();

	if (bIsMainDlg)
		m_pMainDlg = NULL;

	return nResult;
}

BOOL CTrayFrameWnd::SetTrayTooltipText(LPCTSTR lpszText)
{
	return m_tray.SetTooltipText(lpszText);
}

BOOL CTrayFrameWnd::SetTrayIcon(UINT nIconResID)
{
	return m_tray.SetIcon(nIconResID);
}

BOOL CTrayFrameWnd::SetTrayIcon(HICON hIcon)
{
	return m_tray.SetIcon(hIcon);
}

BOOL CTrayFrameWnd::ShowTrayBalloon(LPCTSTR lpszText, LPCTSTR lpszTitle, DWORD dwIcon, UINT nBalloonTimeout)
{
	return m_tray.ShowBalloon(lpszText, lpszTitle, dwIcon, nBalloonTimeout);
}

int CTrayFrameWnd::MessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption, UINT nType)
{
	CString sCaption;
	if (!lpszCaption)
	{
		GetWindowText(sCaption);
		lpszCaption = sCaption;
	}

	if (IsWindowVisible())
	{
		SetForegroundWindow();
		return CFrameWnd::MessageBox(lpszText, lpszCaption, nType);	
	}

	::SetForegroundWindow(::GetDesktopWindow());
	return ::MessageBox(::GetDesktopWindow(), lpszText, lpszCaption, nType);
}

void CTrayFrameWnd::OnAppHelp() 
{
	AfxGetApp()->WinHelp(0);
}

CDialog* CTrayFrameWnd::FindDialog(int nKey, BOOL bRestore) const
{
	CDialog* pDialog = NULL;
	if (!m_dlgMap.Lookup(nKey, pDialog))
		return NULL;

	if (!::IsWindow(pDialog->m_hWnd))
		return NULL;

	if (bRestore)
	{
		if (pDialog->IsIconic())
			pDialog->ShowWindow(SW_RESTORE);

		pDialog->SetForegroundWindow();
	}

	return pDialog;
}

CWnd* CTrayFrameWnd::GetPopupParent() const
{
	if (m_pMainDlg && ::IsWindow(m_pMainDlg->m_hWnd))
		return m_pMainDlg;
	return GetDesktopWindow();
}

void CTrayFrameWnd::SetClassName(LPCTSTR lpszClassName)
{
	m_sClassName = lpszClassName;
}

BOOL CTrayFrameWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!m_sClassName.IsEmpty())
	{
		WNDCLASS wndcls = { 0 };
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.hInstance = AfxGetInstanceHandle();
		wndcls.lpszClassName = m_sClassName;
		if(!AfxRegisterClass(&wndcls))
		{
			TRACE("Class Registration Failed\n");
			return FALSE; 
		}
	}	

	if(!CFrameWnd::PreCreateWindow(cs))
		return FALSE;	

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	if (m_sClassName.IsEmpty())
		cs.lpszClass = AfxRegisterWndClass(0);
	else
		cs.lpszClass = m_sClassName;

	return TRUE;
}

