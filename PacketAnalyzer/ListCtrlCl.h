#ifndef _LISTCTRLCL_H_INCLUDE
#define _LISTCTRLCL_H_INCLUDE

#pragma once
#include "HeaderCtrlCl.h"

// CListCtrlCl

class CListCtrlCl : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlCl)

public:
	CListCtrlCl();
	virtual ~CListCtrlCl();


	CHeaderCtrlCl m_Header;

	// �и�
	int m_nRowHeight;
	// ����߶�
	int m_FontHeight;
	// ������
	int m_FontWith;
	COLORREF m_Color;


protected:
	DECLARE_MESSAGE_MAP()

	virtual void PreSubclassWindow();

public:
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	
	CPtrList m_ptrListCol;    //��������ɫ
	CPtrList m_ptrListItem;   //����Item��ɫ��
	CPtrList m_colTextColor;  //������������ɫ
	CPtrList m_ItemTextColor; //���浥Ԫ��������ɫ
	// ���ñ�ͷ�߶�
	void SetHeaderHeight(float Height);
	void SetHeaderFontHW(int nHeight, int nWith); //���ñ�ͷ�����С
	void SetHeaderTextColor(COLORREF color);
	// Gradient - ����ϵ�������屳����,���ý�����Ϊ0
	void SetHeaderBKColor(int R, int G, int B, int Gradient);

};


#endif