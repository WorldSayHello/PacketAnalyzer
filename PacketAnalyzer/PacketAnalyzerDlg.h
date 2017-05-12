#ifndef _PACKETANALYZERDLG_H_INCLUDE
#define _PACKETANALYZERDLG_H_INCLUDE

// PacketAnalyzerDlg.h : ͷ�ļ�
//

#pragma once
#include"ListCtrlCl.h"
#include "afxwin.h"
#include "IPGram.h"
#include "ARPGram.h"
#include "RARPGram.h"
//#include "EtherHead.h"

UINT RecvPackThreaddProc(LPVOID lParam);

// CPacketAnalyzerDlg �Ի���
class CPacketAnalyzerDlg : public CDialogEx
{
	// ����
public:
	CPacketAnalyzerDlg(CWnd* pParent = NULL);	// ��׼���캯��

	struct packet_info {
		pcap_pkthdr pkt_hdr;
		u_char* ppkt_data;
	};

												// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PACKETANALYZER_DIALOG };
#endif

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
	afx_msg void OnNetwork();
	afx_msg LRESULT OnPacketRecv(WPARAM wParam, LPARAM lParam);
	void ReleasePacket();
	
	DECLARE_MESSAGE_MAP()

public:

	CBitmap m_BkBmp;
	CFont   m_Font;

	CEdit m_CtlEdtDetailPack;  //�Ҳ����ϸ��Ϣ
	CEdit m_CtlEdtCurPack;     //���Ϸ���������Ϣ
	CListCtrlCl m_CtlList;     //���°�Item
	CMenu m_Menu;
	BOOL  m_bStart;


	pcap_if_t* m_alldevs;
	pcap_if_t* m_dev;
	CArray <packet_info*, packet_info*> m_apkts;

	afx_msg void OnStart();
	CString ParsePacket(const packet_info & pkti);
protected:
	
public:
	afx_msg void OnLvnItemchangedListPacketes(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


#endif // !_PACKETANALYZERDLG_H_INCLUDE


