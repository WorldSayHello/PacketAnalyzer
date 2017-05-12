#ifndef _NETWORKDLG_H_INCLUDE
#define _NETWORKDLG_H_INCLUDE
#pragma once


#include "afxwin.h"
#include "PacketType.h"
#include "Include/pcap.h"
#include "PacketAnalyzerDlg.h"
// CNetWorkDlg �Ի���

class CNetWorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNetWorkDlg)

public:
	CNetWorkDlg(CPacketAnalyzerDlg* pParent = NULL);   // ��׼���캯��
	virtual ~CNetWorkDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NETWORK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	


public:
	CPacketAnalyzerDlg* m_ParentDlg;

	CEdit m_CtlEditAdapter;
	CComboBox m_Combo;

	pcap_if_t* m_dev; //��ǰ������
	pcap_if_t* m_alldevs;//������������Ϣ

	CBitmap    m_BkBmp;
	char m_errbuf[PCAP_ERRBUF_SIZE];

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonCancle();
	afx_msg void OnCbnSelchangeComboSelect();
};


#endif // !_NETWORKDLG_H_INCLUDE


