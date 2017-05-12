#ifndef _ARPGRAM_H_INCLUDE
#define _ARPGRAM_H_INCLUDE

#pragma once

/*
ARP���ĸ�ʽ
0           8           16           24             31
+++++++++++++++++++++++++++++++++++++++++++++++++++++
|        Ӳ������        |          Э������          |
|Ӳ����ַ����|Э���ַ����|          ��������          |
|              ����վ��Ӳ����ַ                       |
|                       |           IP��ַ           |
|                       |     ����վ��Ӳ����ַ        |
|                                                    |
|                 Ŀ��վ��IP��ַ                      |
++++++++++++++++++++++++++++++++++++++++++++++++++++++

*/


class ARPGram
{
public:
	ARPGram();
	ARPGram(const byte * pBuffer, UINT uiBufferLen);
	~ARPGram();

	CString GetSrcHdwAddr();

	CString GetSrcPrtAddr();

	CString GetDestHdwAddr();

	CString GetDestPrtAddr();

	CString GetOperation();

	CString GetPrtType();


	int  nHdwAddrType;     //Ӳ����ַ����
	int  nPrtAddrType;     //Э���ַ����
	int  nHdwAddrLen;      //Ӳ����ַ����
	int  nPrtAddrLen;      //Э���ַ����
	int  nOperation;       //��������
	BYTE SrcHdwAddr[6];    //����վ��Ӳ����ַ
	int  nSrcPrtAddr;      //����վ��IP��ַ
	BYTE DestHdwAddr[6];   //Ŀ��վ��Ӳ����ַ
	int  nDestPrtAddr;     //Ŀ��վ��IP��ַ

};

#endif