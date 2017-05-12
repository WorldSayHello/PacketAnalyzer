#ifndef _RARPGRAM_H_INCLUDE
#define _RARPGRAM_H_INCLUDE

#pragma once
/*
RARP���ݱ���ʽ


*/

class RARPGram
{
public:
	RARPGram();
	RARPGram(const byte * pBuffer, UINT uiBufferLen);
	~RARPGram();

	CString GetSrcHdwAddr();

	CString GetSrcPrtAddr();

	CString GetDestHdwAddr();

	CString GetDestPrtAddr();

	CString GetOperation();

	CString GetPrtType();


	int  nHdwAddrType;         //Ӳ����ַ����
	int  nPrtAddrType;         //Э���ַ����
	int  nHdwAddrLen;          //Ӳ����ַ����
	int  nPrtAddrLen;          //Э���ַ����
	int  nOperation;           //��������
	BYTE SrcHdwAddr[6];        //����վ��Ӳ����ַ
	int  nSrcPrtAddr;          //����վ��Э���ַ
	BYTE DestHdwAddr[6];       //Ŀ��վ��Ӳ����ַ
	int  nDestprtAddr;         //Ŀ��վ��Э���ַ
};


#endif // !_RARPGRAM_H_INCLUDE



