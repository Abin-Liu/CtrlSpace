////////////////////////////////////////////////////////////////////
// TrayFrameWnd.h
//
// CTrayFrameWnd, a CFrameWnd derived class implements system tray
// window combined with Chris Maunder's CSystemTray class.
//
// Abin (abinn32@yahoo.com)
//
// 2012-11-20
////////////////////////////////////////////////////////////////////

#ifndef __TRAYFRAMEWND_H__
#define __TRAYFRAMEWND_H__

#include <afxtempl.h>
#include "SystemTray.h"

class CTrayFrameWnd : public CFrameWnd
{
public:	

	enum { KEY_IGNORED = -1, };

	CTrayFrameWnd();
	virtual ~CTrayFrameWnd();

	virtual BOOL CreateTray(HICON hIcon, LPCTSTR lpszTooltip, LPCTSTR lpszBalloonText = NULL, LPCTSTR lpszBalloonTitle = NULL, DWORD dwBalloonIcon = NIIF_INFO, UINT nBalloonTimeout = 10);
	virtual BOOL CreateTray(UINT nIconResID, LPCTSTR lpszTooltip, LPCTSTR lpszBalloonText = NULL, LPCTSTR lpszBalloonTitle = NULL, DWORD dwBalloonIcon = NIIF_INFO, UINT nBalloonTimeout = 10);
	virtual BOOL SetTrayIcon(UINT nIconResID);
	virtual BOOL SetTrayIcon(HICON hIcon);
	virtual BOOL SetTrayTooltipText(LPCTSTR lpszText);
	virtual BOOL ShowTrayBalloon(LPCTSTR lpszText, LPCTSTR lpszTitle, DWORD dwIcon = NIIF_INFO, UINT nBalloonTimeout = 10);

	virtual BOOL PopupMenu(CMenu* pMenu, int nSubMenuIndex = 0, int nDefaultItemPos = -1);
	virtual BOOL PopupMenu(UINT nMenuResID, int nSubMenuIndex = 0, int nDefaultItemPos = -1);
	virtual int MessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption = NULL, UINT nType = MB_ICONEXCLAMATION);

	virtual int DoModal(CDialog* pDialog, int nKey = KEY_IGNORED, BOOL bIsMainDlg = FALSE);
	virtual CWnd* GetPopupParent() const;
	virtual CDialog* FindDialog(int nKey, BOOL bRestore = FALSE) const;

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayFrameWnd)
	protected:
	//}}AFX_VIRTUAL

protected:	
	
	DECLARE_DYNCREATE(CTrayFrameWnd)
	// Generated message map functions
	//{{AFX_MSG(CTrayFrameWnd)
	//}}AFX_MSG
	LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:

	virtual void OnConfig() {}
	virtual void OnTrayLClick() {}
	virtual void OnTrayRClick();
	virtual void OnTrayDblClick();
	virtual void OnTrayBalloonClick();
	virtual void OnAppHelp();
	
	void SetClassName(LPCTSTR lpszClassName); // Only valid before "PreCreateWindow"

	CSystemTray m_tray;

private:

	void CmdRouteMenu(CMenu* pMenu);
	
	CMap<int, int, CDialog*, CDialog*> m_dlgMap;
	CWnd* m_pMainDlg;
	CString m_sClassName;
};

#endif // __TRAYFRAMEWND_H__
