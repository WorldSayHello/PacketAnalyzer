#ifndef _ETHERHEAD_H_INCLUDE
#define _ETHERHEAD_H_INCLUDE

#pragma once
class EtherHead
{
public:
	EtherHead();
	EtherHead(const byte * pBuffer, UINT uiBufferLen);
	~EtherHead();

	void GetMacSrcAddr(char * str);

	CString GetMacSrcAddr();

	void GetMacDestAddr(char * str);

	CString GetMacDestAddr();

	CString GetType();

	int SrcAddr[6];     //ԴMAC��ַ
	int DestAddr[6];    //Ŀ��MAC��ַ
	int nType;           //����㱨������:IP,ARP,RARP
};


#endif // !_ETHERHEAD_H_INCLUDE




