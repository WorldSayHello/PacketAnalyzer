#ifndef _HEADERCTRLCL_H_INCLUDE
#define _HEADERCTRLCL_H_INCLUDE

#pragma once


// CHeaderCtrlCl

class CHeaderCtrlCl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CHeaderCtrlCl)

public:
	CHeaderCtrlCl();
	virtual ~CHeaderCtrlCl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	int m_R;
	int m_G;
	int m_B;
	int m_Gradient;	  // �����屳��������ϵ��
	float m_Height;   //��ͷ�߶ȣ����Ǳ���,
	int m_FontHeight; //����߶�
	int m_FontWith;   //������
	COLORREF     m_Color;
	CStringArray m_HChar;
	CString      m_Format; //��ʾ�������͵���������,0��ʾ����룬1��ʾ�м���룬2��ʾ�Ҷ���

	LRESULT OnLayout(WPARAM wParam, LPARAM lParam);
};

#endif // !_HEADERCTRLCL_H_INCLUDE