
// Analysis4NetworkSuperposition.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAnalysis4NetworkSuperpositionApp:
// See Analysis4NetworkSuperposition.cpp for the implementation of this class
//

class CAnalysis4NetworkSuperpositionApp : public CWinApp
{
public:
	CAnalysis4NetworkSuperpositionApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAnalysis4NetworkSuperpositionApp theApp;
