#ifndef TRANSMISSION_CONTROL_PROTOCOL_HEADER
#define TRANSMISSION_CONTROL_PROTOCOL_HEADER

#include "InternetTypes.h"     //byte, word, dword
#include "EndianConversions.h" //SwitchEndianWord(), SwitchEndianDword()
#include <string.h>            //memcpy(), memset()
#include <stdio.h>             //printf()

class TCPHeader
{
public:
	TCPHeader();
	TCPHeader(void * location);

	void Assign(void * location);

	void Clear();

	void SwitchEndianness();

	void Print();

#define TCP_FTP_DATA_PORT 20
#define TCP_FTP_CONTROL_PORT 21
#define TCP_SSH_PORT 22
#define TCP_TELNET_PORT 23
#define TCP_SMTP_PORT 25
#define TCP_DNS_PORT 53
#define TCP_BOOTPS_PORT 67
#define TCP_BOOTPC_PORT 68
#define TCP_HTTP_PORT 80
#define TCP_POP3_PORT 110
#define TCP_NNTP_PORT 119
#define TCP_NTP_PORT 123
#define TCP_NETBIOS_NS_PORT 137
#define TCP_NETBIOS_DGM_PORT 138
#define TCP_NETBIOS_SSN_PORT 139
#define TCP_IMAP4_PORT 143
#define TCP_SNMP_PORT 161
#define TCP_IRC_PORT 194
#define TCP_HTTPS_PORT 443
#define TCP_MICROSOFT_DS_PORT 445
#define TCP_SMTPS_PORT 465
#define TCP_IMAPS_PORT 993
#define TCP_IRCS_PORT 994
#define TCP_POP3S_PORT 995
	word SourcePort;
	word DestinationPort;
	dword SequenceNumber;
	dword AcknowledgementNumber;
	byte DataOffset;
	byte Flags;
#define TCP_FIN  0x01
#define TCP_SYN  0x02
#define TCP_RST  0x04
#define TCP_PUSH 0x08
#define TCP_ACK  0x10
#define TCP_URG  0x20
#define TCP_ECE  0x40
#define TCP_CWR  0x80
	word Window;
	word Checksum;
	word UrgentPointer;
};

TCPHeader::TCPHeader()
{

}
TCPHeader::TCPHeader(void * location)
{
	Assign(location);
}
void TCPHeader::Assign(void * location)
{
	memcpy(this, location, sizeof(TCPHeader));
	SwitchEndianness();
}
void TCPHeader::Clear()
{
	memset(this, 0, sizeof(TCPHeader));
}
void TCPHeader::SwitchEndianness()
{
	SwitchEndianWord(&SourcePort);
	SwitchEndianWord(&DestinationPort);
	SwitchEndianDword(&SequenceNumber);
	SwitchEndianDword(&AcknowledgementNumber);
	SwitchEndianWord(&Window);
	SwitchEndianWord(&Checksum);
	SwitchEndianWord(&UrgentPointer);
}
void TCPHeader::Print()
{
	byte FIN = Flags & 0x1;
	byte SYN = (Flags >> 1) & 0x1;
	byte RST = (Flags >> 2) & 0x1;
	byte PUSH = (Flags >> 3) & 0x1;
	byte ACK = (Flags >> 4) & 0x1;
	byte URG = (Flags >> 5) & 0x1;
	byte ECE = (Flags >> 6) & 0x1;
	byte CWR = (Flags >> 7) & 0x1;

	printf("|-TCP:\n");
	printf("| |-SourcePort: 0x%02x\n", SourcePort);
	printf("| |-DestinationPort: 0x%02x\n", DestinationPort);
	printf("| |-SeqeunceNumber: 0x%08x\n", SequenceNumber);
	printf("| |-AcknowledgementNumber: 0x%08x\n", AcknowledgementNumber);
	printf("| |-DataOffset: 0x%02x\n", DataOffset);
	printf("| |-Flags: 0x%02x\n", Flags);
	printf("| | |-FIN: 0x%01x\n", FIN);
	printf("| | |-SYN: 0x%01x\n", SYN);
	printf("| | |-RST: 0x%01x\n", RST);
	printf("| | |-PUSH: 0x%01x\n", PUSH);
	printf("| | |-ACK: 0x%01x\n", ACK);
	printf("| | |-URG: 0x%01x\n", URG);
	printf("| | |-ECE: 0x%01x\n", ECE);
	printf("| | `-CWR: 0x%01x\n", CWR);
	printf("| |-Window: 0x%04x\n", Window);
	printf("| |-Checksum: 0x%04x\n", Checksum);
	printf("| `-UrgentPointer: 0x%04x\n", UrgentPointer);
}

#endif