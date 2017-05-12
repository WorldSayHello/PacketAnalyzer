#ifndef _PACKET_TYPE_H_INCLUDE
#define _PACKET_TYPE_H_INCLUDE
#pragma once

#include "Include/pcap.h"
#include <Windows.h>
#define MAX_PROTO_TEXT_LEN 16 // ��Э��������󳤶�
#define MAX_PROTO_NUM 12 // ��Э������

// �������ݰ�Э������
#define IP 0x0800
#define ARP 0x0806
#define RARP 0x8035

// ����IP��ַ�ṹ
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

// ����IP�ײ���ʽ
typedef struct ip_header
{
	u_char	ver_ihl;		// �汾���ײ�����
	u_char	tos;			// �������� 
	u_short tlen;			// �ܳ��� 
	u_short identification; // ��ʶ��
	u_short flags_fo;		// ��ƫ����
	u_char	ttl;			// ����ʱ��
	u_char	proto;			// Э��
	u_short crc;			// �ײ�У���
	DWORD	saddr;		    // ԴIP��ַ
	DWORD	daddr;		    // Ŀ�ĵ�ַ
	u_int	op_pad;			// ѡ����λ
}ip_header;

// ����TCP�ײ���ʽ
typedef struct tcp_header
{
	unsigned short th_sport;  // Դ�˿ں�        
	unsigned short th_dport;  // Ŀ�Ķ˿ں�       
	unsigned int th_seq;      // SEQ���    
	unsigned int th_ack;      // ACK���
	unsigned char th_lenres;  //  �ײ�����    
	unsigned char th_flag;    // ����λ  
	unsigned short th_win;    // ���ڴ�С        
	unsigned short th_sum;    // У���        
	unsigned short th_urp;    // ����ָ��         
}tcp_header;

// ����UDP�ײ���ʽ
typedef struct udp_header
{
	u_short sport;			// 16λԴ�˿�
	u_short dport;			// 16λĿ�Ķ˿�
	u_short len;			// 16λ����
	u_short crc;			// 16λУ���
}udp_header;

// ����ICMP�ײ���ʽ
typedef struct icmp_header
{
	BYTE i_type; // 8λ����
	BYTE i_code; // 8λ����
	unsigned short i_cksum; // 16λУ���
	unsigned short i_id; // ʶ���
	unsigned short i_seq; // �������к�
	unsigned long timestamp; // ʱ���
}icmp_header;

// ������Э��ӳ���
typedef struct _protomap
{
	int ProtoNum;
	char ProtoText[MAX_PROTO_TEXT_LEN];
}PROTOMAP;

// Ϊ��Э��ӳ���ֵ
PROTOMAP ProtoMap[MAX_PROTO_NUM] = 
{
	{ IPPROTO_IP,"IP" },
	{ IPPROTO_ICMP,"ICMP" },
	{ IPPROTO_IGMP,"IGMP" },
	{ IPPROTO_GGP,"GGP" },
	{ IPPROTO_TCP,"TCP" },
	{ IPPROTO_PUP,"PUP" },
	{ IPPROTO_UDP,"UDP" },
	{ IPPROTO_IDP,"IDP" },
	{ IPPROTO_ND,"ND" },
	{ IPPROTO_RAW,"RAW" },
	{ IPPROTO_MAX,"MAX" },
	{ NULL,"" }
};


char TcpFlag[6] = { 'F','S','R','P','A','U' }; // TCP��־λ

#endif