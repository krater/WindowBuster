// windowDlg.h : header file
//

#if !defined(AFX_WINDOWDLG_H)
#define AFX_WINDOWDLG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWindowDlg dialog

class CWindowDlg : public CDialog
{
// Construction
public:
	CWindowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWindowDlg)
	enum { IDD = IDD_WINDOW_DIALOG };
	CTreeCtrl	m_windowtreectrl;
	CString	m_ButtonText;
	CString	m_Parent;
	CString	m_Number;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWindowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnListWindows();
	afx_msg void OnEnable();
	afx_msg void OnDisable();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangedWindowTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeText();
	afx_msg void OnMinimize();
	afx_msg void OnSetParent();
	afx_msg void OnSetTextLimit();
	afx_msg void OnGetText();
	afx_msg void OnWMTimer();
	afx_msg void OnInject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWDLG_H)
