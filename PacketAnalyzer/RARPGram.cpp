#include "stdafx.h"
#include "RARPGram.h"


RARPGram::RARPGram()
{
}


RARPGram::RARPGram(const byte *pBuffer, UINT uiBufferLen)
{
	byte *pPos = (byte *)pBuffer;
	nHdwAddrType = (*pPos) * 0x100 + (*(pPos + 1));

	pPos += 2;
	nPrtAddrType = (*pPos) * 0x100 + (*(pPos + 1));

	pPos += 2;
	nHdwAddrLen = (*pPos);

	pPos++;
	nPrtAddrLen = (*pPos);

	pPos++;
	nOperation = (*pPos) * 0x100 + (*(pPos + 1));

	pPos += 2;
	for (int i = 0; i<6; i++) 
	{
		SrcHdwAddr[i] = BYTE(*pPos);
		pPos++;
	}

	nSrcPrtAddr = (*pPos) * 0x1000000 + (*(pPos + 1)) * 0x10000 + (*(pPos + 2)) * 0x100 + (*(pPos + 3));

	pPos += 4;
	for (int i = 0; i<6; i++) 
	{
		DestHdwAddr[i] = BYTE(*pPos);
		pPos++;
	}

	nDestprtAddr = (*pPos) * 0x1000000 + (*(pPos + 1)) * 0x10000 + (*(pPos + 2)) * 0x100 + (*(pPos + 3));

}

RARPGram::~RARPGram()
{
}

//���ԴӲ����ַ
CString RARPGram::GetSrcHdwAddr()
{
	CString str;
	str.Format(L"%02X:%02X:%02X:%02X:%02X:%02X",
		SrcHdwAddr[0],
		SrcHdwAddr[1],
		SrcHdwAddr[2],
		SrcHdwAddr[3],
		SrcHdwAddr[4],
		SrcHdwAddr[5]
	);
	return str;
}

//���ԴIP��ַ
CString RARPGram::GetSrcPrtAddr()
{
	CString str;
	byte *p;

	p = (byte *)&nSrcPrtAddr;
	str.Format(L"%u.%u.%u.%u", p[3], p[2], p[1], p[0]);
	return str;
}

CString RARPGram::GetDestHdwAddr()
{
	CString str;
	str.Format(L"%02X:%02X:%02X:%02X:%02X:%02X",
		DestHdwAddr[0],
		DestHdwAddr[1],
		DestHdwAddr[2],
		DestHdwAddr[3],
		DestHdwAddr[4],
		DestHdwAddr[5]
	);
	return str;
}

//���Ŀ��IP��ַ
CString RARPGram::GetDestPrtAddr()
{
	CString str;
	byte *p;

	p = (byte *)&nDestprtAddr;
	str.Format(L"%u.%u.%u.%u", p[3], p[2], p[1], p[0]);
	return str;
}

//��ò�������
CString RARPGram::GetOperation()
{
	CString str;
	switch (this->nOperation) 
	{
	case 3:
		str.Format(L"RARP Request");   //RARP������
		break; 
	case 4:
		str.Format(L"RARP Reply");     //RARP�ش���
		break;
	default:
		str.Format(L"");
	}
	return str;
}

//���Э������
CString RARPGram::GetPrtType()
{
	CString str;
	switch (nPrtAddrType)
	{
	case 0x0800:
		str.Format(L"IP");
		break;
	default:
		str.Format(L"");
	}
	return str;
}
