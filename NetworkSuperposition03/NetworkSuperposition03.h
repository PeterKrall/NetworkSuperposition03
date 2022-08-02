
// NetworkSuperposition03.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CNetworkSuperposition03App:
// See NetworkSuperposition03.cpp for the implementation of this class
//

class CNetworkSuperposition03App : public CWinApp
{
public:
	CNetworkSuperposition03App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CNetworkSuperposition03App theApp;
