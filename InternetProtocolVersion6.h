#ifndef INTERNET_PROTOCOL_VERSION_6_HEADER
#define INTERNET_PROTOCOL_VERSION_6_HEADER

#include "InternetTypes.h"     //byte, word, dword
#include "EndianConversions.h" //SwitchEndianWord(), SwitchEndianDword()
#include <string.h>            //memcpy(), memset()
#include <stdio.h>             //printf()

class IPV6Header
{
public:
	IPV6Header();
	IPV6Header(void * location);

	void Assign(void * location);

	void Clear();

	void SwitchEndianness();

	void Print();

	dword Versions;
	word PayloadLength;
#define IPV6_TCP		0x06
#define IPV6_UDP		0x11
#define IPV6_ICMP		0x01
	byte NextProtocol;
	byte HopLimit;
	word SourceAddress[8];
	word DestinationAddress[8];
};

IPV6Header::IPV6Header()
{

}
IPV6Header::IPV6Header(void * location)
{
	Assign(location);
}
void IPV6Header::Assign(void * location)
{
	memcpy(this, location, sizeof(IPV6Header));
	SwitchEndianness();
}
void IPV6Header::Clear()
{
	memset(this, 0, sizeof(IPV6Header));
}
void IPV6Header::SwitchEndianness()
{
	SwitchEndianDword(&Versions);
	SwitchEndianWord(&PayloadLength);
	for (int i = 0; i < 8; i++)
	{
		SwitchEndianWord(&SourceAddress[i]);
		SwitchEndianWord(&DestinationAddress[i]);
	}
}
void IPV6Header::Print()
{
	byte Version = (Versions >> 28) & 0xF;
	byte DifferentiatedServicesCodePoint = (Versions >> 22) & 0x3F;
	byte ECNCapableTransport = (Versions >> 21) & 0x1;
	byte ECNCE = (Versions >> 20) & 0x1;
	dword FlowLabel = Versions & 0xFFFFF;

	printf("|-IPv6:\n");
	printf("| |-Versions: 0x%08x\n", Versions);
	printf("| | |-Version: 0x%01x\n", Version);
	printf("| | |-DSCP: 0x%02x\n", DifferentiatedServicesCodePoint);
	printf("| | |-ECT: 0x%01x\n", ECNCapableTransport);
	printf("| | |-CE: 0x%01x\n", ECNCE);
	printf("| | `-FlowLabel: 0x%05x\n", FlowLabel);
	printf("| |-PayloadLength: 0x%04x\n", PayloadLength);
	printf("| |-NextProtocol: 0x%02x\n", NextProtocol);
	printf("| |-HopLimit: 0x%02x\n", HopLimit);
	printf("| |-SourceAddress: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n", SourceAddress[0], SourceAddress[1], SourceAddress[2], SourceAddress[3], SourceAddress[4], SourceAddress[5], SourceAddress[6], SourceAddress[7]);
	printf("| `-DestinationAddress: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n", DestinationAddress[0], DestinationAddress[1], DestinationAddress[2], DestinationAddress[3], DestinationAddress[4], DestinationAddress[5], DestinationAddress[6], DestinationAddress[7]);
}

#endif