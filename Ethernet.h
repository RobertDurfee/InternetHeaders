#ifndef ETHERNET_HEADER
#define ETHERNET_HEADER

#include "InternetTypes.h"     //byte, word
#include "EndianConversions.h" //SwitchEndiannWord()
#include <string.h>            //memset()
#include <stdio.h>             //printf()

class EthernetHeader
{
public:
	EthernetHeader();
	EthernetHeader(void * location);

	void Assign(void * location);

	void Clear();

	void SwitchEndianness();

	void Print();

	byte DestinationAddress[6];
	byte SourceAddress[6];
#define ETHERNET_IPV4 0x0800
#define ETHERNET_IPV6 0x86DD
#define ETHERNET_ARP  0x0806
	word Type;
};
EthernetHeader::EthernetHeader()
{

}
EthernetHeader::EthernetHeader(void * location)
{
	Assign(location);
}

void EthernetHeader::Assign(void * location)
{
	int index = 0;

	//memcpy() is not used due to compiler-specific structure padding.
	for (int i = 0; i < 6; i++) { DestinationAddress[i] = ((byte *)location)[index]; index += sizeof(byte); }
	for (int i = 0; i < 6; i++) { SourceAddress[i] = ((byte *)location)[index];      index += sizeof(byte); }
	Type = *(word *)&((byte *)location)[index];                                      index += sizeof(word);

	SwitchEndianness();
}

void EthernetHeader::Clear()
{
	//memset() can be used as padding can be zero
	memset(this, 0, sizeof(EthernetHeader));
}

void EthernetHeader::SwitchEndianness()
{
	SwitchEndianWord(&Type);
}

void EthernetHeader::Print()
{
	printf("|-Ethernet:\n");
	printf("| |-DestinationAddress: %02x-%02x-%02x-%02x-%02x-%02x\n", DestinationAddress[0], DestinationAddress[1], DestinationAddress[2], DestinationAddress[3], DestinationAddress[4], DestinationAddress[5]);
	printf("| |-SourceAddress: %02x-%02x-%02x-%02x-%02x-%02x\n", SourceAddress[0], SourceAddress[1], SourceAddress[2], SourceAddress[3], SourceAddress[4], SourceAddress[5]);
	printf("| `-Type: 0x%04x\n", Type);
}

#endif