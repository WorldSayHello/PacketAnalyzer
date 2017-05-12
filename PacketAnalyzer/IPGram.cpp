#include "stdafx.h"
#include "IPGram.h"


IPGram::IPGram()
{
}

IPGram::IPGram(const byte *pBuffer, UINT uiBufferLen)
{
	//����һ������ָ��
	byte *pPos;

	pPos = (byte*)pBuffer;
	//���ֽڳ���16����Ϊ�汾�ţ�����Ϊ�ײ����ȣ���λ4�ֽ�
	nVersion = *pPos / 16;
	nIHL = *pPos % 16;

	//�ڶ��ֽ�Ϊ��������
	//[���ȼ�|D|T|R|C| ]
	pPos++;
	nServiceType = *pPos;
	//
	nPrecedence = (*pPos & 16) * 8 + (*pPos & 8) * 4 + (*pPos & 4) * 2 + (*pPos & 2);
	if (*pPos & 16)
		bDelay = true;            //��С�ӳ�
	else
		bDelay = false;
	if (*pPos & 8)
		bThroughtPut = true;      //���������
	else
		bThroughtPut = false;
	if (*pPos & 4)
		bReliability = true;      //��߿ɿ���
	else
		bReliability = false;
	if (*pPos & 2)
		bCost = true;             //��ͳɱ�
	else
		bCost = false;
	//���� 2�ֽ� ��λ���ֽ�
	pPos++;
	uiTotallen = (*pPos) * 256 + (*(pPos + 1));

	//��ʶ 2�ֽ�
	pPos += 2;
	nIdentification = (*pPos) * 256 + (*(pPos + 1));
	//��־ 3λ ��������Ƿ��Ƭ
	pPos += 2;
	if (*pPos & 64)
		bDF = true;     //����Ƭ
	else
		bDF = false;
	if (*pPos & 32)
		bMF = true;     //��Ƭ
	else
		bMF = false;

	//Ƭƫ�� 13λ
	nFragmentOffset = (*pPos % 32) * 256 + (*(pPos + 1));
	
	//TTL
	pPos += 2;
	nTTL = *pPos;
	//Э��
	pPos++;
	nProtocol = *pPos;
	//У���
	pPos++;
	uiChecksum = (*pPos) * 256 + (*(pPos + 1));
	//ԴIP
	pPos += 2;
	lSrcAddr = (*pPos) * 0x1000000 + (*(pPos + 1)) * 0x10000 + (*(pPos + 2)) * 0x100 + (*(pPos + 3));
	//Ŀ��IP
	pPos += 4;
	lDestAddr = (*pPos) * 0x1000000 + (*(pPos + 1)) * 0x10000 + (*(pPos + 2)) * 0x100 + (*(pPos + 3));

	//���ͷ�����ȴ���20�ֽڣ���˵���ñ�����IP��ѡ��
	if (nIHL>5) 
	{
		pPos += 4;
		//��ѡ���ֳ���
		nOptionLen = (nIHL - 5) * 4;
		//ѡ���
		pOptions = new byte[nOptionLen];
		memcpy(pOptions, pBuffer + 20, nOptionLen);
	}
	else 
	{
		nOptionLen = 0;
		pOptions = NULL;
	}
	//���ｫ����ָ��ָ��������
	pPos = (byte *)(pBuffer + nIHL * 4);
	//���ݶγ��� = ���ݱ��ܳ��� - ͷ������
	nDataLen = uiTotallen - nIHL * 4;
	if (nDataLen>0)
	{
		pData = new byte[nDataLen];
		memcpy(pData, pBuffer + nIHL * 4, nDataLen);
	}
	else
		pData = NULL;
}

IPGram::~IPGram()
{
	if (pData != NULL)
		delete[] pData;
	if (pOptions != NULL)
		delete[] pOptions;
}

//����Э������
CString IPGram::GetService()
{
	CString str;

	switch (this->nProtocol)
	{
	case 6:
		str.Format(L"TCP"); break;
	case 17:
		str.Format(L"UDP"); break;
	case 1:
		str.Format(L"ICMP"); break;
	case 89:
		str.Format(L"OSPF"); break;
	default:
		str.Format(L"%d", nProtocol);
	}

	return str;
}

//����ԴIP
void IPGram::GetSrcAddr(char *str)
{
	int temp = lSrcAddr;
	byte i0, i1, i2, i3;

	i0 = (temp & 0xff000000) / 0x1000000;
	i1 = (temp & 0x00ff0000) / 0x10000;
	i2 = (temp & 0x0000ff00) / 0x100;
	i3 = temp & 0x000000ff;
	sprintf_s(str, 1,"%u.%u.%u.%u", i0, i1, i2, i3);
}

//ԴIP
CString IPGram::GetSrcAddr()
{
	CString str;
	int temp = lSrcAddr;
	byte i0, i1, i2, i3;

	i0 = (temp & 0xff000000) / 0x1000000;
	i1 = (temp & 0x00ff0000) / 0x10000;
	i2 = (temp & 0x0000ff00) / 0x100;
	i3 = temp & 0x000000ff;
	str.Format(L"%u.%u.%u.%u", i0, i1, i2, i3);

	return str;
}

//���Ŀ��IP
void IPGram::GetDestAddr(char *str)
{
	int temp = lDestAddr;
	byte i0, i1, i2, i3;

	i0 = (temp & 0xff000000) / 0x1000000;
	i1 = (temp & 0x00ff0000) / 0x10000;
	i2 = (temp & 0x0000ff00) / 0x100;
	i3 = temp & 0x000000ff;
	sprintf_s(str,1, "%u.%u.%u.%u", i0, i1, i2, i3);
}

CString IPGram::GetDestAddr()
{
	CString str;
	int temp = lDestAddr;
	byte i0, i1, i2, i3;

	i0 = (temp & 0xff000000) / 0x1000000;
	i1 = (temp & 0x00ff0000) / 0x10000;
	i2 = (temp & 0x0000ff00) / 0x100;
	i3 = temp & 0x000000ff;
	str.Format(L"%u.%u.%u.%u", i0, i1, i2, i3);

	return str;
}

//��ñ�ʶ��ÿ��IP���ݱ���һ����ʶ����־��������IP֮�����ڽ���ͨ�ŵı���
CString IPGram::GetID()
{
	CString str;
	str.Format(L"%u", this->nIdentification);
	return str;
}