// CtrlSpace.h : main header file for the CTRLSPACE application
//

#if !defined(AFX_CTRLSPACE_H__1A6C8FFF_1D3E_4C13_9977_B0188D1A40C3__INCLUDED_)
#define AFX_CTRLSPACE_H__1A6C8FFF_1D3E_4C13_9977_B0188D1A40C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "WinAppEx.h"

/////////////////////////////////////////////////////////////////////////////
// CCtrlSpaceApp:
// See CtrlSpace.cpp for the implementation of this class
//

class CCtrlSpaceApp : public CWinAppEx
{
public:
	CCtrlSpaceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtrlSpaceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CCtrlSpaceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRLSPACE_H__1A6C8FFF_1D3E_4C13_9977_B0188D1A40C3__INCLUDED_)
