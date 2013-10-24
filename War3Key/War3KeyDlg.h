// War3KeyDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "shortkeyedit.h"


// CWar3KeyDlg �Ի���
class CWar3KeyDlg : public CDialog
{
// ����
public:
	CWar3KeyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WAR3KEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void UpdateListControl(void);
	KeyMappingInformation *lpMapping;
	CListCtrl mKeyList;
public:
	afx_msg void OnBnClickedButtonhook();
public:
	CButton mBtnHook;
public:
	CButton mBtnUnhook;
public:
	afx_msg void OnBnClickedButtonlistdelete();
public:
	afx_msg void OnBnClickedButtonunhook();
public:
	afx_msg void OnLvnItemActivateKeylist(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedButtonlistadd();
};
