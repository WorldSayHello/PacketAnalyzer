
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// PacketAnalyzer.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


void iptos(u_long in, char output[])
{
	u_char *p;

	p = (u_char *)&in;
	sprintf_s(output, 12,"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
}