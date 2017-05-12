#ifndef _IPGRAM_H_INCLUDE
#define _IPGRAM_H_INCLUDE
/*
IP���ݰ���ʽ   ͷ��
0       4       8        16    19                   31        
++++++++++++++++++++++++++++++++++++++++++++++++++++
|  �汾 |�ײ�����|�������� |      ���ݱ��ܳ���         |          
|        ��ʶ            | ��־ |     Ƭƫ��         |
|   ����ʱ��     |  Э��  |       �ײ�У���          |
|                     ԴIP��ַ                       |  
|                    Ŀ��IP��ַ                      |
|                      IPѡ��                       |
+++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
#pragma once
//����IP���ݰ�
class IPGram
{
public:
	int	 nVersion;	       //�汾
	int  nIHL;	           //ͷ������
	int  nServiceType;	   //�������� type of service
	int  nPrecedence;	   //���ȼ�
	bool bDelay;	       //�ӳ�
	bool bThroughtPut;	   //������
	bool bReliability;	   //�ɿ���
	bool bCost;            //��ͳɱ�
	UINT uiTotallen;	   //�ܳ�total length
	int  nIdentification;  //��ʶ
	bool bDF;	           //��Ҫ�ֶ�
	bool bMF;	           //���н�һ���ķֶ�
	int  nFragmentOffset;  //��Ƭƫ��fragment offset
	int  nTTL;	           //������time to live
	int  nProtocol;	       //Э��,��TCP,UDP
	UINT uiChecksum;	   //ͷ��У���
	long lSrcAddr;	       //ԴIP��ַ
	long lDestAddr;	       //Ŀ��IP��ַ
	int  nOptionLen;	   //ѡ���
	byte *pOptions;	       //ѡ������
	int  nDataLen;	       //���ݳ���
	byte *pData;	       //��������

	IPGram();
	IPGram(const byte* pBuffer, UINT uiBufferLen);
	virtual ~IPGram();
	CString GetService();
	void GetSrcAddr(char * str);
	CString GetSrcAddr();
	void GetDestAddr(char * str);
	CString GetDestAddr();
	CString GetID();
};

#endif // !_IPGRAM_H_INCLUDE

