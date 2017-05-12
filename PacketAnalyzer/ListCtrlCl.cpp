// ListCtrlCl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PacketAnalyzer.h"
#include "ListCtrlCl.h"


// CListCtrlCl

struct stColor
{
	int nRow;
	int nCol;
	COLORREF rgb;
};



IMPLEMENT_DYNAMIC(CListCtrlCl, CListCtrl)

CListCtrlCl::CListCtrlCl() : m_nRowHeight(0), m_FontHeight(12), m_FontWith(0)
{
	m_Color = RGB(0, 0, 0);//��ɫ
}

CListCtrlCl::~CListCtrlCl()
{
}


BEGIN_MESSAGE_MAP(CListCtrlCl, CListCtrl)
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()



// CListCtrlCl ��Ϣ�������


void CListCtrlCl::PreSubclassWindow()
{
	CHeaderCtrl *pHeader = GetHeaderCtrl();
	m_Header.SubclassWindow(pHeader->GetSafeHwnd());
}

void CListCtrlCl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_nRowHeight>0)
	{
		lpMeasureItemStruct->itemHeight = m_nRowHeight;
	}
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


int CListCtrlCl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat /* = LVCFMT_LEFT */, int nWidth /* = -1 */, int nSubItem /* = -1 */)
{
	m_Header.m_HChar.Add(lpszColumnHeading);
	switch (nFormat)
	{
	case LVCFMT_LEFT: m_Header.m_Format = m_Header.m_Format + L"0"; break;
	case LVCFMT_CENTER:	m_Header.m_Format = m_Header.m_Format + L"1"; break;
	case LVCFMT_RIGHT: m_Header.m_Format = m_Header.m_Format + L"2";
	default: m_Header.m_Format = m_Header.m_Format + L"1"; break;
	}
	return CListCtrl::InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth, nSubItem);
}

// Gradient - ����ϵ�������屳����,���ý�����Ϊ0
void CListCtrlCl::SetHeaderBKColor(int R, int G, int B, int Gradient) //���ñ�ͷ����ɫ
{
	m_Header.m_R = R;
	m_Header.m_G = G;
	m_Header.m_B = B;
	m_Header.m_Gradient = Gradient;
}

// ���ñ�ͷ�߶�
void CListCtrlCl::SetHeaderHeight(float Height) //���ñ�ͷ�߶�
{
	m_Header.m_Height = Height;
}

void CListCtrlCl::SetHeaderFontHW(int nHeight, int nWith) //����ͷ�������͸�
{
	m_Header.m_FontHeight = nHeight;
	m_Header.m_FontWith = nWith;
}
void CListCtrlCl::SetHeaderTextColor(COLORREF color) //����ͷ��������ɫ
{
	m_Header.m_Color = color;
}