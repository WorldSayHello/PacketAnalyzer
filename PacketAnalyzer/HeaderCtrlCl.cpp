// HeaderCtrlCl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PacketAnalyzer.h"
#include "HeaderCtrlCl.h"


// CHeaderCtrlCl

IMPLEMENT_DYNAMIC(CHeaderCtrlCl, CHeaderCtrl)

CHeaderCtrlCl::CHeaderCtrlCl() : m_R(171), m_G(199), m_B(235), m_Gradient(8)
{
	m_Format = L"";
	m_Height = 1;
	m_FontHeight = 15;
	m_FontWith   = 0;
	m_Color      = RGB(0, 0, 0);
}

CHeaderCtrlCl::~CHeaderCtrlCl()
{
}


BEGIN_MESSAGE_MAP(CHeaderCtrlCl, CHeaderCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CHeaderCtrlCl ��Ϣ�������




void CHeaderCtrlCl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CHeaderCtrl::OnPaint()
	int nItem = 0;
	nItem = GetItemCount();//�õ��м�����Ԫ 
	for (int i = 0; i<nItem; i++)
	{
		CRect rect;                //�޶�ÿ��Item�ľ��ο�
		GetItemRect(i, &rect);     //�õ�Item�ĳߴ�
		int R = m_R, G = m_G, B = m_B;
		CRect rt(rect);            //�����ߴ絽�µ������� 
		rt.left++;                 //�����ָ��ߵĵط� 
					               //�������屳�� 
		for (int j = rect.top; j <= rect.bottom; j++)
		{
			rt.bottom = rt.top + 1;
			CBrush brush;
			brush.CreateSolidBrush(RGB(R, G, B));//������ˢ 
			dc.FillRect(&rt, &brush);            //��䱳�� 
			brush.DeleteObject();                //�ͷŻ�ˢ 
			R -= m_Gradient; G -= m_Gradient; B -= m_Gradient;
			if (R<0)R = 0;
			if (G<0)G = 0;
			if (B<0)B = 0;
			rt.top = rt.bottom;
		}
		dc.SetBkMode(TRANSPARENT);
		CFont font, *oldFont;
		
		dc.SetTextColor(m_Color);
		font.CreateFont(m_FontHeight, m_FontWith, 0, 0, 0, FALSE, FALSE, 0, 0, 0, 0, 0, 0, _TEXT("΢���ź�"));//�������� 
		oldFont = dc.SelectObject(&font);

		DWORD dwFormat = 1;
		if (m_Format[i] == L'0')
		{
			dwFormat = DT_LEFT;
			rect.left += 3;
		}
		else if (m_Format[i] == L'1')
		{
			dwFormat = DT_CENTER;
		}
		else if (m_Format[i] == L'2')
		{
			dwFormat = DT_RIGHT;
			rect.right -= 3;
		}
		TEXTMETRIC textMetric;
		dc.GetTextMetrics(&textMetric);
		int offset = 0;
		offset = rect.Height() - textMetric.tmHeight;
		rect.OffsetRect(0, offset / 2);
		dc.DrawText(m_HChar[i], &rect, dwFormat);
		dc.SelectObject(oldFont);
		font.DeleteObject(); //�ͷ����� 
	}
	//��ͷ��ʣ�ಿ��
	CRect rtRect;
	CRect clientRect;
	GetItemRect(nItem - 1, rtRect);
	GetClientRect(clientRect);
	rtRect.left = rtRect.right + 1;
	rtRect.right = clientRect.right;
	int R = m_R, G = m_G, B = m_B;
	CRect rect(rtRect);
	//�������屳�� 
	for (int j = rtRect.top; j <= rtRect.bottom; j++)
	{
		rect.bottom = rect.top + 1;
		CBrush brush;
		brush.CreateSolidBrush(RGB(R, G, B));//������ˢ 
		dc.FillRect(&rect, &brush);         //��䱳�� 
		brush.DeleteObject();                //�ͷŻ�ˢ 
		R -= m_Gradient; G -= m_Gradient; B -= m_Gradient;
		if (R<0)R = 0;
		if (G<0)G = 0;
		if (B<0)B = 0;
		rect.top = rect.bottom;
	}

}

LRESULT CHeaderCtrlCl::OnLayout(WPARAM wParam, LPARAM lParam)
{
	LRESULT   lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);
	HD_LAYOUT &hdl = *(HD_LAYOUT *)lParam;
	RECT *prc = hdl.prc;
	WINDOWPOS *pwpos = hdl.pwpos;

	//��ͷ�߶�Ϊԭ��1.5�������Ҫ��̬�޸ı�ͷ�߶ȵĻ�����1.5���һ��ȫ�ֱ��� 
	int nHeight = (int)(pwpos->cy * m_Height);
	pwpos->cy = nHeight;
	prc->top = nHeight;
	return lResult;
}
