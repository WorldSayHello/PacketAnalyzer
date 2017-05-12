
// PacketAnalyzerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PacketAnalyzer.h"
#include "PacketAnalyzerDlg.h"
#include "afxdialogex.h"
#include "NetWorkDlg.h"
#include "EtherHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_PACKET_RECV WM_USER+100

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPacketAnalyzerDlg �Ի���



CPacketAnalyzerDlg::CPacketAnalyzerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PACKETANALYZER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_alldevs = NULL;
	m_dev = NULL;
	m_bStart = FALSE;
}

void CPacketAnalyzerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DETAILED_INFO, m_CtlEdtDetailPack);
	DDX_Control(pDX, IDC_EDIT_PACKET_INFO, m_CtlEdtCurPack);
	DDX_Control(pDX, IDC_LIST_PACKETES, m_CtlList);
}

BEGIN_MESSAGE_MAP(CPacketAnalyzerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_NETWORK, OnNetwork)
	ON_COMMAND(IDM_START, &CPacketAnalyzerDlg::OnStart)
	ON_MESSAGE(WM_PACKET_RECV, &CPacketAnalyzerDlg::OnPacketRecv)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PACKETES, &CPacketAnalyzerDlg::OnLvnItemchangedListPacketes)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

WCHAR* g_FmtEditStr = L"��ţ� %d    Э�����ͣ�%s\r\n���ȣ� %s  �ֽ�\r\nԴ��ַ��%s\r\nĿ�ĵ�ַ��%s";
// CPacketAnalyzerDlg ��Ϣ�������

BOOL CPacketAnalyzerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_Menu.LoadMenu(IDR_MENU_MAIN);
	SetMenu(&m_Menu);

	m_CtlList.SetHeaderHeight(0.8f);          //����ͷ���߶�
	m_CtlList.SetHeaderFontHW(18, 0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
	m_CtlList.SetHeaderTextColor(RGB(10, 50, 255)); //����ͷ��������ɫ
	m_CtlList.SetHeaderBKColor(130, 180, 230, 0);   //����ͷ������ɫ

	m_CtlList.SetExtendedStyle(m_CtlList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_CtlList.InsertColumn(0, L"���", LVCFMT_CENTER, 80);
	m_CtlList.InsertColumn(1, L"Э������", LVCFMT_CENTER, 110);
	m_CtlList.InsertColumn(2, L"Դ��ַ", LVCFMT_CENTER, 180);
	m_CtlList.InsertColumn(3, L"Ŀ�ĵ�ַ", LVCFMT_CENTER, 180);
	m_CtlList.InsertColumn(4, L"����", LVCFMT_CENTER, 115);


	m_BkBmp.LoadBitmap(IDB_BITMAP_BORDER);

	VERIFY(m_Font.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		L"΢���ź�"));                 // lpszFacename

	m_CtlList.SetFont(&m_Font, FALSE);
	m_CtlEdtCurPack.SetFont(&m_Font, FALSE);
	m_CtlEdtDetailPack.SetFont(&m_Font, FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPacketAnalyzerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPacketAnalyzerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPacketAnalyzerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPacketAnalyzerDlg::OnNetwork()
{
	CNetWorkDlg dlg(this);
	dlg.m_alldevs = m_alldevs;
	dlg.m_dev = m_dev;
	if (dlg.DoModal() == IDOK)
	{
		ReleasePacket();
		m_alldevs = dlg.m_alldevs;
		m_dev = dlg.m_dev;
	}
}

void CPacketAnalyzerDlg::ReleasePacket()
{
	m_CtlList.DeleteAllItems();
	int isize = m_apkts.GetSize();
	for (int i = 0; i<isize; i++)
	{
		delete[] m_apkts.GetAt(i)->ppkt_data;
		delete m_apkts.GetAt(i);
	}
	m_apkts.RemoveAll();
}

CRITICAL_SECTION g_CS;
BOOL g_bCompleted = TRUE;
void pcap_handle(u_char *user, const struct pcap_pkthdr *pkt_header, const u_char *pkt_data)
{
	if (((CPacketAnalyzerDlg*)AfxGetApp()->GetMainWnd())->m_bStart == TRUE)
	{
		// ֪ͨ�������յ���һ����
		PostMessage(((CPacketAnalyzerDlg*)AfxGetApp()->GetMainWnd())->m_hWnd,
			WM_PACKET_RECV,
			(WPARAM)pkt_header,
			(LPARAM)pkt_data);
	}
}
//��������
afx_msg LRESULT CPacketAnalyzerDlg::OnPacketRecv(WPARAM wParam, LPARAM lParam)
{
	// �����յ��İ�
	packet_info* ppkti = new packet_info;
	ppkti->pkt_hdr.caplen = ((pcap_pkthdr*)wParam)->caplen;
	ppkti->pkt_hdr.len = ((pcap_pkthdr*)wParam)->len;
	ppkti->ppkt_data = new u_char[ppkti->pkt_hdr.len];
	memcpy((void*)ppkti->ppkt_data, (u_char*)lParam, ppkti->pkt_hdr.len);
	m_apkts.Add(ppkti);

	//�����жϰ�����
	u_char* pPos = ppkti->ppkt_data;
	pPos += 12;
	int itype = (*pPos) * 0x100;
	pPos++;
	itype += (*pPos);

	// �����յ��İ�
	int index = m_apkts.GetSize() - 1;
	CString szPktInfo(""), szIndex, szType(""), szLen(""), szSrcAddr(""), szDstAddr("");
	szIndex.Format(L"%d", index);
	m_CtlList.InsertItem(index, szIndex);
	switch (itype)
	{
	//IP����
	case IP:
	{
		IPGram ip(ppkti->ppkt_data + 14, ppkti->pkt_hdr.len - 14);
		szType = ip.GetService();
		szLen.Format(L"%d", ip.uiTotallen);
		szSrcAddr = ip.GetSrcAddr();
		szDstAddr = ip.GetDestAddr();
		break;
	}
	//ARP����
	case ARP:
	{
		ARPGram arp(ppkti->ppkt_data + 14, ppkti->pkt_hdr.len - 14);
		szType = "ARP";
		szSrcAddr = arp.GetSrcPrtAddr();
		szDstAddr = arp.GetDestPrtAddr();
		break;
	}
	//RARP����
	case RARP:
	{
		RARPGram rarp(ppkti->ppkt_data + 14, ppkti->pkt_hdr.len - 14);
		szType = "RARP";
		szSrcAddr = rarp.GetSrcPrtAddr();
		szDstAddr = rarp.GetDestPrtAddr();
		break;
	}
	default:
		break;
	}
	m_CtlList.SetItemText(index, 1, szType);
	m_CtlList.SetItemText(index, 2, szSrcAddr);
	m_CtlList.SetItemText(index, 3, szDstAddr);
	m_CtlList.SetItemText(index, 4, szLen);
	szPktInfo.Format(g_FmtEditStr, index, szType, szLen, szSrcAddr, szDstAddr);
	m_CtlEdtCurPack.SetWindowText(szPktInfo);

	EnterCriticalSection(&g_CS);
	g_bCompleted = TRUE;
	LeaveCriticalSection(&g_CS);

	return 0;
}

//���հ��߳�
UINT RecvPackThreaddProc(LPVOID lParam)
{
	CPacketAnalyzerDlg* pMainDlg = (CPacketAnalyzerDlg*)lParam;
	pcap_t *p;
	char errbuf[PCAP_ERRBUF_SIZE];

	// ����Ҫ������������
	if ((p = pcap_open_live(pMainDlg->m_dev->name, 65536, 1, 1000, errbuf)) == NULL)
	{
		pMainDlg->MessageBox(L"��������ʧ��!");
		return -1;
	}
	//�����ٽ���
	InitializeCriticalSection(&g_CS);
	BOOL bCompleted;
	g_bCompleted = TRUE;
	pMainDlg->m_bStart = TRUE;
	do //����ץ��,ÿץһ��,����pcap_handle����
	{
		EnterCriticalSection(&g_CS);
		bCompleted = g_bCompleted;
		g_bCompleted = FALSE;
		LeaveCriticalSection(&g_CS);
		if (bCompleted)
		{
			pcap_loop(p, 1, pcap_handle, NULL);
		}

	} while (pMainDlg->m_bStart);
	//�˳��ٽ���
	DeleteCriticalSection(&g_CS);
	pcap_close(p);//�ر�����
	return 0;
}


void CPacketAnalyzerDlg::OnStart()
{
	// TODO: �ڴ���������������
	if (m_dev == NULL)
	{
		CNetWorkDlg dlg(this);
		dlg.m_alldevs = m_alldevs;
		dlg.m_dev = m_dev;
		if (dlg.DoModal() == IDOK)
		{
			ReleasePacket();
			m_alldevs = dlg.m_alldevs;
			m_dev = dlg.m_dev;
		}
		else
			return;
	}

	if (m_bStart == TRUE && m_apkts.GetSize() > 0)
	{
		AfxMessageBox(L"�Ѿ���ʼ�ˣ�");
		return;
	}

	m_bStart = FALSE;
	AfxBeginThread(AFX_THREADPROC(RecvPackThreaddProc), (LPVOID)this);
}


CString CPacketAnalyzerDlg::ParsePacket(const packet_info& pkti)
{
	CString retStr;
	//Init for Ether ������̫֡
	EtherHead ether(pkti.ppkt_data, 14);
	retStr = L"Ŀ��MAC��ַ:  " + ether.GetMacDestAddr();
	retStr += L"\r\nԴMAC��ַ:  " + ether.GetMacSrcAddr();
	retStr += L"\r\n��̫��֡����:  ";

	switch (ether.nType)
	{
	case IP:
	{
		IPGram ip(pkti.ppkt_data + 14, pkti.pkt_hdr.len);
		CString stripversion;
		CString stripIHL;
		CString stripprecedence;
		CString stripservicetype;
		CString striptotallen;
		CString stripid;
		CString stripfragoffset;
		CString stripTTL;
		CString stripproto;
		CString stripchecksum;
		CString stripdatalen;
		CString stripopt;
		CString strData("\r\n�������ݣ�");

		CString strTmp;
		for (int i = 0; i<ip.nDataLen; i++)
		{
			if (i % 15 == 0) strData += "\r\n";
			strTmp.Format(L"%02X ", ip.pData[i]);
			strData += strTmp;
		}

		stripversion.Format(L"%d", ip.nVersion);
		stripIHL.Format(L"%d", ip.nIHL * 4);
		stripservicetype.Format(L"%d", ip.nServiceType);
		stripprecedence.Format(L"%d", ip.nPrecedence);
		striptotallen.Format(L"%d", ip.uiTotallen);
		stripid.Format(L"%d", ip.nIdentification);
		stripopt.Format(L"%d", ip.nOptionLen);
		stripfragoffset.Format(L"%d", ip.nFragmentOffset);
		stripTTL.Format(L"%d", ip.nTTL);
		stripproto.Format(L"%d", ip.nProtocol);
		stripchecksum.Format(L"0x%X", ip.uiChecksum);
		stripdatalen.Format(L"%d", ip.nDataLen);

		retStr += L"IP��";
		retStr += L"\r\nIP�汾��:  " + stripversion;
		retStr += L"\r\nIPͷ���� :  " + stripIHL + L" Byte";
		retStr += L"\r\nIP��������:  " + stripservicetype;
		retStr += L"\r\n�ӳ�:  ";
		retStr += ip.bDelay ? L"TRUE" : L"FALSE";
		retStr += L"\r\n������:  ";
		retStr += ip.bThroughtPut ? L"TRUE" : L"FALSE";
		retStr += L"\r\n�ɿ���:  ";
		retStr += ip.bReliability ? L"TRUE" : L"FALSE";
		retStr += L"\r\nIP�ܳ���:  " + striptotallen + L" Byte";
		retStr += L"\r\nIP����ʶ:  " + stripid;
		retStr += L"\r\nIP����Ƭ��־(DF):  ";
		retStr += ip.bDF ? L"TRUE" : L"FALSE";
		retStr += L"\r\nIP����Ƭ��־(MF):  ";
		retStr += ip.bMF ? L"TRUE" : L"FALSE";
		retStr += L"\r\nIP����Ƭƫ��:  " + stripfragoffset;
		retStr += L"\r\nIP������ʱ��:  " + stripTTL + L" Second";
		retStr += L"\r\nIPЭ��: " + stripproto + L"  " + ip.GetService();
		retStr += L"\r\nIPͷ��У���:  " + stripchecksum;
		retStr += L"\r\nIP��ԴIP:  " + ip.GetSrcAddr();
		retStr += L"\r\nIP��Ŀ��IP:  " + ip.GetDestAddr();
		retStr += L"\r\nIP����:  " + stripdatalen + L" Byte\r\n";
		retStr += strData;
	}
	break;
	case ARP:
	{
		ARPGram arp(pkti.ppkt_data + 14, pkti.pkt_hdr.len - 14);
		CString strarphdwtype;
		CString strarpprttype;
		CString strarphdwaddrlen;
		CString strarpprtaddrlen;
		strarphdwtype.Format(L"%u", arp.nHdwAddrType);
		strarpprttype.Format(L"%u", arp.nPrtAddrType);
		strarphdwaddrlen.Format(L"%u", arp.nHdwAddrLen);
		strarpprtaddrlen.Format(L"%u", arp.nPrtAddrLen);
		retStr += L"ARP��";
		retStr += L"\r\nӲ����ַ����:  " + strarphdwtype;
		retStr += L"\r\nARPЭ���ַ����: " + strarpprttype + "  " + arp.GetPrtType();
		retStr += L"\r\nӲ����ַ����:  " + strarphdwaddrlen;
		retStr += L"\r\nЭ���ַ����:  " + strarpprtaddrlen;
		retStr += L"\r\n��������:  " + arp.GetOperation();
		retStr += L"\r\nARP�����ͷ�MAC:  " + arp.GetSrcHdwAddr();
		retStr += L"\r\nARP�����ͷ�IP:  " + arp.GetSrcPrtAddr();
		retStr += L"\r\nARP�����շ�MAC:  " + arp.GetDestHdwAddr();
		retStr += L"\r\nARP�����շ�IP:  " + arp.GetDestPrtAddr();
	}
	break;
	case RARP:
	{
		RARPGram rarp(pkti.ppkt_data + 14, pkti.pkt_hdr.len - 14);
		CString strrarphdwtype;
		CString strrarpprttype;
		CString strrarphdwaddrlen;
		CString strrarpprtaddrlen;
		strrarphdwtype.Format(L"%u", rarp.nHdwAddrType);
		strrarpprttype.Format(L"%u", rarp.nPrtAddrType);
		strrarphdwaddrlen.Format(L"%u", rarp.nHdwAddrLen);
		strrarpprtaddrlen.Format(L"%u", rarp.nPrtAddrType);
		retStr += L"RARP��";
		retStr += L"\r\nӲ����ַ����:  " + strrarphdwtype;
		retStr += L"\r\nRARPЭ���ַ����:  " + strrarpprttype + L"  " + rarp.GetPrtType();
		retStr += L"\r\nӲ����ַ����:  " + strrarphdwaddrlen;
		retStr += L"\r\nЭ���ַ����:  " + strrarpprtaddrlen;
		retStr += L"\r\nHardware Address Type:  " + rarp.GetOperation();
		retStr += L"\r\nRARP�����ͷ�MAC:  " + rarp.GetSrcHdwAddr();
		retStr += L"\r\nRARP�����ͷ�IP:  " + rarp.GetSrcPrtAddr();
		retStr += L"\r\nRARP�����շ�MAC:  " + rarp.GetDestHdwAddr();
		retStr += L"\r\nRARP�����շ�IP:  " + rarp.GetDestPrtAddr();
	}
	default: retStr += L"δ֪"; break;
	}

	return retStr;
}


void CPacketAnalyzerDlg::OnLvnItemchangedListPacketes(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CtlEdtDetailPack.SetWindowText(ParsePacket(*m_apkts.GetAt(pNMLV->iItem)));
	
	*pResult = 0;
}


HBRUSH CPacketAnalyzerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd == &m_CtlEdtCurPack || pWnd == &m_CtlEdtDetailPack)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
		return CreateSolidBrush(RGB(255, 255, 255));
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


BOOL CPacketAnalyzerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rcWnd;
	GetClientRect(&rcWnd);
	CDC pDCTmp;
	pDCTmp.CreateCompatibleDC(pDC);
	pDCTmp.SelectObject(m_BkBmp);

	BITMAP bm;
	m_BkBmp.GetObject(sizeof(BITMAP), &bm);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0, 0, rcWnd.Width(), rcWnd.Height(), &pDCTmp, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	return CDialogEx::OnEraseBkgnd(pDC);
}
