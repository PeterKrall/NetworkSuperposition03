
// Analysis4NetworkSuperpositionDlg.h : header file
//

#pragma once


// CAnalysis4NetworkSuperpositionDlg dialog
class CAnalysis4NetworkSuperpositionDlg : public CDialogEx
{
// Construction
public:
	CAnalysis4NetworkSuperpositionDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANALYSIS4NETWORKSUPERPOSITION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
