#ifndef ADDRESS_RESOLUTION_PROTOCOL_HEADER
#define ADDRESS_RESOLUTION_PROTOCOL_HEADER

#include "InternetTypes.h"     //byte, word
#include "EndianConversions.h" //SwitchEndianWord()
#include <string.h>            //memset()
#include <stdio.h>             //printf()

class ARPHeader
{
public:
	ARPHeader();
	ARPHeader(void * location);

	void Assign(void * location);

	void Clear();

	void SwitchEndianness();

	void Print();

#define ARP_ETHERNET 0x01
#define ARP_IEEE_802 0x06
#define ARP_FIBRE    0x12
#define ARP_SERIAL   0x14
#define ARP_IPV4	 0x0800
#define ARP_IPV6	 0x86DD
	word HardwareType;
	word ProtocolType;
	byte HardwareAddressLen;
	byte ProtocolAddressLen;
	word OpCode;
	byte SenderMACAddress[6];
	byte SenderIPv4Address[4];
	byte TargetMACAddress[6];
	byte TargetIPv4Address[4];
};

ARPHeader::ARPHeader()
{

}
ARPHeader::ARPHeader(void * location)
{
	Assign(location);
}
void ARPHeader::Assign(void * location)
{
	int index = 0;

	//memcpy() is not used due to compiler-specific structure padding
	HardwareType = *(word *)&((byte *)location)[index];                             index += sizeof(word);
	ProtocolType = *(word *)&((byte *)location)[index];                             index += sizeof(word);
	HardwareAddressLen = ((byte *)location)[index];                                 index += sizeof(byte);
	ProtocolAddressLen = ((byte *)location)[index];                                 index += sizeof(byte);
	OpCode = *(word *)&((byte *)location)[index];                                   index += sizeof(word);
	for (int i = 0; i < 6; i++) { SenderMACAddress[i] = ((byte *)location)[index];  index += sizeof(byte); }
	for (int i = 0; i < 4; i++) { SenderIPv4Address[i] = ((byte *)location)[index]; index += sizeof(byte); }
	for (int i = 0; i < 6; i++) { TargetMACAddress[i] = ((byte *)location)[index];  index += sizeof(byte); }
	for (int i = 0; i < 4; i++) { TargetIPv4Address[i] = ((byte *)location)[index]; index += sizeof(byte); }

	SwitchEndianness();
}
void ARPHeader::Clear()
{
	//memset() can be used as padding can be zero.
	memset(this, 0, sizeof(ARPHeader));
}
void ARPHeader::SwitchEndianness()
{
	SwitchEndianWord(&HardwareType);
	SwitchEndianWord(&ProtocolType);
	SwitchEndianWord(&OpCode);
}
void ARPHeader::Print()
{
	printf("|-ARP:\n");
	printf("| |-HardwareType: 0x%04x\n", HardwareType);
	printf("| |-ProtocolType: 0x%04x\n", ProtocolType);
	printf("| |-HardwareAddressLength: 0x%02x\n", HardwareAddressLen);
	printf("| |-ProtocolAddressLength: 0x%02x\n", ProtocolAddressLen);
	printf("| |-Opcode: 0x%04x\n", OpCode);
	printf("| |-SenderMACAddress: %02x-%02x-%02x-%02x-%02x-%02x\n", SenderMACAddress[0], SenderMACAddress[1], SenderMACAddress[2], SenderMACAddress[3], SenderMACAddress[4], SenderMACAddress[5]);
	printf("| |-SenderIPv4Addres: %d.%d.%d.%d\n", SenderIPv4Address[0], SenderIPv4Address[1], SenderIPv4Address[2], SenderIPv4Address[3]);
	printf("| |-TargetMACAddress: %02x-%02x-%02x-%02x-%02x-%02x\n", TargetMACAddress[0], TargetMACAddress[1], TargetMACAddress[2], TargetMACAddress[3], TargetMACAddress[4], TargetMACAddress[5]);
	printf("| `-TargetIPv4Addres: %d.%d.%d.%d\n", TargetIPv4Address[0], TargetIPv4Address[1], TargetIPv4Address[2], TargetIPv4Address[3]);
}

#endif