
// NetworkSuperposition03Dlg.cpp : implementation file
//

#include "framework.h"
#include "NetworkSuperposition03.h"
#include "NetworkSuperposition03Dlg.h"
#include "afxdialogex.h"
#include "model.h"
#include <stdexcept>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// some auxiliary functions
LPCTSTR to_wstring(unsigned int n)
{
	static TCHAR buffer[32];
	_itow_s(n, buffer, 10);
	return buffer;
}
LPCTSTR to_wstring(const std::string& str)
{
	static TCHAR buffer[1024];
	std::wstring wstr(str.begin(), str.end());
	swprintf_s(buffer, 1024, L"%s", wstr.c_str());
	return buffer;
}
unsigned int to_uint(CEdit& ed)
{
	CStringW t;
	ed.GetWindowTextW(t);
	return (unsigned int)(_wtoi(t.GetBuffer()));
}
std::string to_string(CEdit& ed)
{
	CStringW t;
	ed.GetWindowTextW(t);
	std::wstring ws(t.GetBuffer());
	std::string s(ws.begin(), ws.end());
	return s;
}
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNetworkSuperposition03Dlg dialog



CNetworkSuperposition03Dlg::CNetworkSuperposition03Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETWORKSUPERPOSITION03_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetworkSuperposition03Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ED_BASIC_STABLE_NET_SIZE, basic_stable_net_size);
	DDX_Control(pDX, ED_BASIC_STABLE_NET_TRANSMISSION_PROBABILITY_STRAIN_1, basic_stable_net_transmission_probability_strain_1);
	DDX_Control(pDX, ED_BASIC_STABLE_NET_TRANSMISSION_PROBABILITY_STRAIN_2, basic_stable_net_transmission_probability_strain_2);
	DDX_Control(pDX, ED_AGGREGATED_STABLE_NET_TRANSMISSION_PROBABILITY_STRAIN_1, aggregated_stable_net_transmission_probability_strain_1);
	DDX_Control(pDX, ED_AGGREGATED_STABLE_NET_TRANSMISSION_PROBABILITY_STRAIN_2, aggregated_stable_net_transmission_probability_strain_2);
	DDX_Control(pDX, ED_BASIC_NET_WITH_FLUCTUATION_TRANSMISSION_PROBABILITY_STRAIN_1, basic_net_with_fluctuation_transmission_probability_strain_1);
	DDX_Control(pDX, ED_BASIC_NET_WITH_FLUCTUATION_TRANSMISSION_PROBABILITY_STRAIN_2, basic_net_with_fluctuation_transmission_probability_strain_2);
	DDX_Control(pDX, ED_AGGREGATED_NET_WITH_FLUCTUATION_TRANSMISSION_PROBABILITY_STRAIN_1, aggregated_net_with_fluctuation_transmission_probability_strain_1);
	DDX_Control(pDX, ED_AGGREGATED_NET_WITH_FLUCTUATION_TRANSMISSION_PROBABILITY_STRAIN_2, aggregated_net_with_fluctuation_transmission_probability_strain_2);
	DDX_Control(pDX, ED_AGGREGATED_NET_WITH_FUCTUATION_SIZE, aggregated_net_with_fluctuation_size);
	DDX_Control(pDX, ED_AGGREGATED_NET_WITH_FUCTUATION_NUMBER, aggregated_net_with_fluctuation_number);
	DDX_Control(pDX, ED_AGGREGATED_STABLE_NET_SIZE, aggregated_stable_net_size);
	DDX_Control(pDX, ED_BASIC_NET_WITH_FUCTUATION_NUMBER, basic_net_with_fluctuation_number);
	DDX_Control(pDX, ED_BASIC_NET_WITH_FUCTUATION_SIZE, basic_net_with_fluctuation_size);
	DDX_Control(pDX, ED_POPULATION_SIZE, population_size);
	DDX_Control(pDX, ED_CONTAGEIOUSNESS_BEGIN_STRAIN_1, contagiosuness_begin_strain_1);
	DDX_Control(pDX, ED_CONTAGEIOUSNESS_END_STRAIN_1, contagiosuness_end_strain_1);
	DDX_Control(pDX, ED_CONTAGEIOUSNESS_BEGIN_STRAIN_2, contagiosuness_begin_strain_2);
	DDX_Control(pDX, ED_CONTAGEIOUSNESS_END_STRAIN_2, contagiosuness_end_strain_2);
	DDX_Control(pDX, ED_INITIAL_CASES_STRAIN_1, initial_cases_strain_1);
	DDX_Control(pDX, ED_INITIAL_CASES_STRAIN_2, initial_cases_strain_2);
	DDX_Control(pDX, ED_IMMUNITY_REDUCTION_TIME, reduction_of_immunity_time);
	DDX_Control(pDX, ED_IMMUNITY_REDUCTION_DEGREE, reduction_of_immunity_degree);
	DDX_Control(pDX, ED_APPEARANCE_STRAIN_2, appearance_of_strain_2);
	DDX_Control(pDX, ED_NUMBER_OF_RUNS, number_of_runs);
	DDX_Control(pDX, ED_OUTPUT_FILE_PREFIX, output_filename_prefix);
	DDX_Control(pDX, ED_BASIC_NET_WITH_FLUCTUATION_FLUCTUATION, basic_net_with_fluctuation_fluctuation);
	DDX_Control(pDX, ED_RANDOM_TRANSMISSION_PROBABILITY_STRAIN_3, random_transmission_probability_strain1);
	DDX_Control(pDX, ED_RANDOM_TRANSMISSION_PROBABILITY_STRAIN_4, random_transmission_probability_strain2);
	DDX_Control(pDX, IDC_EDIT1, label);
	DDX_Control(pDX, ED_AGGREGATED_STABLE_NET_SHUFFLE, aggregated_stable_net_shuffle);
}

BEGIN_MESSAGE_MAP(CNetworkSuperposition03Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNetworkSuperposition03Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNetworkSuperposition03Dlg message handlers

BOOL CNetworkSuperposition03Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	aggregated_net_with_fluctuation_transmission_probability_strain_1.SetWindowTextW(to_wstring(model::Configuration::configuration->strain_1_transmission_probability_in_aggregated_net_with_fluctuation));
	aggregated_stable_net_transmission_probability_strain_1.SetWindowTextW(to_wstring(model::Configuration::configuration->strain_1_transmission_probability_in_aggregated_stable_net));
	basic_net_with_fluctuation_transmission_probability_strain_1.SetWindowTextW(to_wstring(model::Configuration::configuration->strain_1_transmission_probability_in_basic_net_with_fluctuation));
	basic_stable_net_transmission_probability_strain_1.SetWindowTextW(to_wstring(model::Configuration::configuration->strain_1_transmission_probability_in_basic_stable_net));
	aggregated_net_with_fluctuation_transmission_probability_strain_2.SetWindowTextW(to_wstring(model::Configuration::configuration->strain_2_transmission_probability_in_aggregated_net_with_fluctuation));
	aggregated_stable_net_transmission_probability_strain_2.SetWindowTextW(to_wstring(model::Configuration::configuration->strain_2_transmission_probability_in_aggregated_stable_net));
	basic_net_with_fluctuation_transmission_probability_strain_2.SetWindowTextW(to_wstring(model::Configuration::configuration->strain_2_transmission_probability_in_basic_net_with_fluctuation));
	basic_stable_net_transmission_probability_strain_2.SetWindowTextW(to_wstring(model::Configuration::configuration->strain_2_transmission_probability_in_basic_stable_net));
	aggregated_net_with_fluctuation_number.SetWindowTextW(to_wstring(model::Configuration::configuration->aggregated_net_with_fluctuation_number));
	aggregated_net_with_fluctuation_size.SetWindowTextW(to_wstring(model::Configuration::configuration->aggregated_net_with_fluctuation_size));
	aggregated_stable_net_size.SetWindowTextW(to_wstring(model::Configuration::configuration->aggregated_stable_net_size));
	basic_net_with_fluctuation_fluctuation.SetWindowTextW(to_wstring(model::Configuration::configuration->basic_net_with_fluctuation_fluctuation));
	basic_net_with_fluctuation_number.SetWindowTextW(to_wstring(model::Configuration::configuration->basic_net_with_fluctuation_number));
	basic_net_with_fluctuation_size.SetWindowTextW(to_wstring(model::Configuration::configuration->basic_net_with_fluctuation_size));
	basic_stable_net_size.SetWindowTextW(to_wstring(model::Configuration::configuration->basic_stable_net_size));
	population_size.SetWindowTextW(to_wstring(model::Configuration::configuration-> population_size));
	random_transmission_probability_strain1.SetWindowTextW(to_wstring(model::Configuration::configuration->strain1_random_transmission_probability));
	random_transmission_probability_strain2.SetWindowTextW(to_wstring(model::Configuration::configuration->strain2_random_transmission_probability));
	aggregated_stable_net_shuffle.SetWindowTextW(to_wstring(model::Configuration::configuration->aggregated_stable_net_shuffle));
	//
	contagiosuness_begin_strain_1.SetWindowTextW(to_wstring(model::Configuration::configuration-> strain_1_contagiousness_begin));
	contagiosuness_end_strain_1.SetWindowTextW(to_wstring(model::Configuration::configuration-> strain_1_contagiousness_end));
	contagiosuness_begin_strain_2.SetWindowTextW(to_wstring(model::Configuration::configuration-> strain_2_contagiousness_begin));
	contagiosuness_end_strain_2.SetWindowTextW(to_wstring(model::Configuration::configuration-> strain_2_contagiousness_end));
	reduction_of_immunity_time.SetWindowTextW(to_wstring(model::Configuration::configuration-> immunity_reduction_time_of_strain1_for_strain_2_exposition));
	reduction_of_immunity_degree.SetWindowTextW(to_wstring(model::Configuration::configuration-> immunity_reduction_weight_of_strain1_for_strain_2_exposition));
	initial_cases_strain_1.SetWindowTextW(to_wstring(model::Configuration::configuration->initial_strain1cases));
	initial_cases_strain_2.SetWindowTextW(to_wstring(model::Configuration::configuration->initial_strain2cases));
	appearance_of_strain_2.SetWindowTextW(to_wstring(model::Configuration::configuration-> first_strain2_appearance));
	output_filename_prefix.SetWindowTextW(to_wstring(model::Configuration::configuration->output_directory));
	


	basic_stable_net_size.SetWindowTextW(to_wstring(model::Configuration::configuration->basic_stable_net_size));
	initial_cases_strain_1.SetWindowTextW(to_wstring(model::Configuration::configuration->initial_strain1cases));
	number_of_runs.SetWindowTextW(L"10");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetworkSuperposition03Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetworkSuperposition03Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetworkSuperposition03Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetworkSuperposition03Dlg::OnBnClickedOk()
{
	try 
	{
		model::Configuration::configuration = new model::Configuration
		(
 	      to_uint(aggregated_net_with_fluctuation_transmission_probability_strain_1)
		, to_uint(aggregated_stable_net_transmission_probability_strain_1)
		, to_uint(basic_net_with_fluctuation_transmission_probability_strain_1)
		, to_uint(basic_stable_net_transmission_probability_strain_1)
		, to_uint(aggregated_net_with_fluctuation_transmission_probability_strain_2)
		, to_uint(aggregated_stable_net_transmission_probability_strain_2)
		, to_uint(basic_net_with_fluctuation_transmission_probability_strain_2)
		, to_uint(basic_stable_net_transmission_probability_strain_2)
		, to_uint(aggregated_net_with_fluctuation_number)
		, to_uint(aggregated_net_with_fluctuation_size)
		, to_uint(aggregated_stable_net_size)
		, to_uint(basic_net_with_fluctuation_fluctuation)
		, to_uint(basic_net_with_fluctuation_number)
		, to_uint(basic_net_with_fluctuation_size)
		, to_uint(basic_stable_net_size)
		, to_uint(population_size)
		, to_uint(random_transmission_probability_strain1)
		, to_uint(random_transmission_probability_strain2)
		, to_uint(aggregated_stable_net_shuffle)
		//
		, to_uint(contagiosuness_begin_strain_1)
		, to_uint(contagiosuness_end_strain_1)
		, to_uint(contagiosuness_begin_strain_2)
		, to_uint(contagiosuness_end_strain_2)
		, to_uint(reduction_of_immunity_time)
		, to_uint(reduction_of_immunity_degree)
		, to_uint(appearance_of_strain_2)
		, to_string(initial_cases_strain_1).c_str()
		, to_string(initial_cases_strain_2).c_str()
		, to_string(output_filename_prefix).c_str()
		, to_string(label).c_str()
		);
	}
	catch (...)
	{
		AfxMessageBox(L"oops - what is going on here?");
	}
	try
	{
		for (unsigned int run = 0; run < to_uint(number_of_runs); ++run)
		{
			model::Model::run_model();
		}
	}
	catch (std::exception& ex)
	{
		AfxMessageBox(L"Oops! This never happened\n");
	}
	CDialogEx::OnOK();
}


