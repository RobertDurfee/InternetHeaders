#ifndef INTERNET_PROTOCOL_VERSION_4_HEADER
#define INTERNET_PROTOCOL_VERSION_4_HEADER

#include "InternetTypes.h"     //byte, word
#include "EndianConversions.h" //SwitchEndianWord()
#include <string.h>            //memcpy(), memset()
#include <stdio.h>             //printf()

class IPV4Header
{
public:
	IPV4Header();
	IPV4Header(void * location);

	void Assign(void * location);

	void Clear();

	void SwitchEndianness();

	void Print();

	byte Versions;
	byte DifferentiatedServicesField;
	word TotalLength;
	word Identification;
	word FragmentFlags;
	byte TimeToLive;
#define IPV4_TCP		0x06
#define IPV4_UDP		0x11
#define IPV4_ICMP		0x01
	byte NextProtocol;
	word Checksum;
	byte SourceAddress[4];
	byte DestinationAddress[4];
};

IPV4Header::IPV4Header()
{

}
IPV4Header::IPV4Header(void * location)
{
	Assign(location);
}
void IPV4Header::Assign(void * location)
{
	int index = 0; 

	//memcpy() is not used due to compiler-specific structure padding.
	

	memcpy(this, location, sizeof(IPV4Header));
	SwitchEndianness();
}
void IPV4Header::Clear()
{
	memset(this, 0, sizeof(IPV4Header));
}
void IPV4Header::SwitchEndianness()
{
	SwitchEndianWord(&TotalLength);
	SwitchEndianWord(&Identification);
	SwitchEndianWord(&FragmentFlags);
	SwitchEndianWord(&Checksum);
}
void IPV4Header::Print()
{
	byte Version = (Versions >> 4) & 0xF;
	byte HeaderLength = Versions & 0xF;
	byte DifferentiatedServicesCodePoint = (DifferentiatedServicesField >> 2) & 0x3F;
	byte ECNCapableTransport = (DifferentiatedServicesField >> 1) & 0x1;
	byte ECNCE = DifferentiatedServicesField & 0x1;
	byte DontFragment = (FragmentFlags >> 14) & 0x1;
	byte MoreFragments = (FragmentFlags >> 13) & 0x1;
	word Offset = FragmentFlags & 0x1FFF;

	printf("|-IPv4:\n");
	printf("| |-Versions: 0x%02x\n", Versions);
	printf("| | |-Version: 0x%01x\n", Version);
	printf("| | `-HeaderLength: 0x%01x\n", HeaderLength);
	printf("| |-DifferentiatedServicesField: 0x%02x\n", DifferentiatedServicesField);
	printf("| | |-DSCP: 0x%02x\n", DifferentiatedServicesCodePoint);
	printf("| | |-ECT: 0x%01x\n", ECNCapableTransport);
	printf("| | `-CE: 0x%01x\n", ECNCE);
	printf("| |-TotalLength: 0x%04x\n", TotalLength);
	printf("| |-Identification: 0x%04x\n", Identification);
	printf("| |-FragmentFlags: 0x%04x\n", FragmentFlags);
	printf("| | |-DF: 0x%01x\n", DontFragment);
	printf("| | |-MF: 0x%01x\n", MoreFragments);
	printf("| | `-Offset: 0x%04x\n", Offset);
	printf("| |-TimeToLive: 0x%02x\n", TimeToLive);
	printf("| |-NextProtocol: 0x%02x\n", NextProtocol);
	printf("| |-Checksum: 0x%04x\n", Checksum);
	printf("| |-SourceAddress: %03d.%03d.%03d.%03d\n", SourceAddress[0], SourceAddress[1], SourceAddress[2], SourceAddress[3]);
	printf("| `-DestinationAddress: %03d.%03d.%03d.%03d\n", DestinationAddress[0], DestinationAddress[1], DestinationAddress[2], DestinationAddress[3]);
}

#endif