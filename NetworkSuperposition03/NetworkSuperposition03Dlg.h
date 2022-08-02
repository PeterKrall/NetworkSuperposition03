
// NetworkSuperposition03Dlg.h : header file
//

#pragma once


// CNetworkSuperposition03Dlg dialog
class CNetworkSuperposition03Dlg : public CDialogEx
{
// Construction
public:
	CNetworkSuperposition03Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETWORKSUPERPOSITION03_DIALOG };
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
	CEdit basic_stable_net_size;
	CEdit basic_stable_net_transmission_probability_strain_1;
	CEdit basic_stable_net_transmission_probability_strain_2;
	CEdit aggregated_stable_net_transmission_probability_strain_1;
	CEdit aggregated_stable_net_transmission_probability_strain_2;
	CEdit basic_net_with_fluctuation_transmission_probability_strain_1;
	CEdit basic_net_with_fluctuation_transmission_probability_strain_2;
	CEdit aggregated_net_with_fluctuation_transmission_probability_strain_1;
	CEdit aggregated_net_with_fluctuation_transmission_probability_strain_2;
	CEdit aggregated_net_with_fluctuation_size;
	CEdit aggregated_net_with_fluctuation_number;
	CEdit aggregated_stable_net_size;
	CEdit basic_net_with_fluctuation_number;
	CEdit basic_net_with_fluctuation_size;
	CEdit population_size;
	CEdit contagiosuness_begin_strain_1;
	CEdit contagiosuness_end_strain_1;
	CEdit contagiosuness_begin_strain_2;
	CEdit contagiosuness_end_strain_2;
	CEdit initial_cases_strain_1;
	CEdit initial_cases_strain_2;
	CEdit reduction_of_immunity_time;
	CEdit reduction_of_immunity_degree;
	CEdit appearance_of_strain_2;
	CEdit number_of_runs;
	CEdit output_filename_prefix;
	CEdit basic_net_with_fluctuation_fluctuation;
	CEdit random_transmission_probability_strain1;
	CEdit random_transmission_probability_strain2;
	CButton base_on_shuffled_population;
};
