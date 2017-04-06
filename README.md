# InternetHeaders
C++ classes for parsing internet headers.

### Disclaimer
This is not production-worthy code! View this simply as a proof-of-concept. Preconditions are implicit. No error checking exists.

### Initialization
```C++
Header();
Header(void * location);
```
Any of the internet headers supplied can be initialized one of two ways:

 1. By default, setting all fields to zero.
 2. With a pointer to a sequence of bytes in big-endian configuration.

The endianness is converted by default by calling the `SwitchEndianness` method. If big-endian configuration is desired, call the `SwitchEndianness` method again after constructing a header.

### Assign
```C++
void Assign(void * location);
```
This method works in the same way as the second constructor. The endianness is converted by default by calling the `SwitchEndianness` method. If big-endian configuration is desired, call the `SwitchEndianness` method again after assigning to a header.

### Clear
```C++
void Clear();
```
This method works in the same way as the first constructor. All the fields are reset to zero.

### Switch Endianness
```C++
SwitchEndianness();
```
Since internet communication is done in big-endian configuration and clients typically run in little-endian, this method is provided to switch back and forth between endian configurations.

### To String
```C++
char * ToString();
```
It is often necessary to display the data as a string. As a result, this method is supplied to display the information in a formatted output. All fields are labeled and given in fixed-width hexadecimal base. The returned string must be freed by calling the standard `free` function.

### Ethernet
```C++
class EthernetHeader
{
	byte DestinationAddress[6];
	byte SourceAddress[6];
#define ETHERNET_IPV4 0x0800
#define ETHERNET_IPV6 0x86DD
#define ETHERNET_ARP  0x0806
	word Type;
};
```

### Address Resolution Protocol
```C++
class ARPHeader
{
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
```

### Internet Protocol Version 4
```C++
class IPV4Header
{
	byte Versions;
		byte Version;
		byte HeaderLength;
	byte DifferentiatedServicesField;
		byte DifferentiatedServicesCodePoint;
		byte ECNCapableTransport;
		byte ECNCE;
	word TotalLength;
	word Identification;
	word FragmentFlags;
		byte DontFragment;
		byte MoreFragments;
		word Offset;
	byte TimeToLive;
#define IPV4_TCP		0x06
#define IPV4_UDP		0x11
#define IPV4_ICMP		0x01
	byte NextProtocol;
	word Checksum;
	byte SourceAddress[4];
	byte DestinationAddress[4];
};
```

### Internet Protocol Version 6
```C++
class IPV6Header
{
	dword Versions;
		byte Version;
		byte DifferentiatedServicesCodePoint;
		byte ECNCapableTransport;
		byte ECNCE;
		dword FlowLabel;
	word PayloadLength;
#define IPV6_TCP		0x06
#define IPV6_UDP		0x11
#define IPV6_ICMP		0x01
	byte NextProtocol;
	byte HopLimit;
	word SourceAddress[8];
	word DestinationAddress[8];
};
```

### Transmission Control Protocol
```C++
class TCPHeader
{
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
#define TCP_FIN  0x01
#define TCP_SYN  0x02
#define TCP_RST  0x04
#define TCP_PUSH 0x08
#define TCP_ACK  0x10
#define TCP_URG  0x20
#define TCP_ECE  0x40
#define TCP_CWR  0x80
	byte Flags;
		byte FIN;
		byte SYN;
		byte RST;
		byte PSH;
		byte ACK;
		byte URG;
		byte ECE;
		byte CWR;
	word Window;
	word Checksum;
	word UrgentPointer;
};
```

### User Datagram Protocol
```C++
class UDPHeader
{
#define UDP_FTP_DATA_PORT 20
#define UDP_FTP_CONTROL_PORT 21
#define UDP_SSH_PORT 22
#define UDP_TELNET_PORT 23
#define UDP_SMTP_PORT 25
#define UDP_DNS_PORT 53
#define UDP_BOOTPS_PORT 67
#define UDP_BOOTPC_PORT 68
#define UDP_HTTP_PORT 80
#define UDP_POP3_PORT 110
#define UDP_NNTP_PORT 119
#define UDP_NTP_PORT 123
#define UDP_NETBIOS_NS_PORT 137
#define UDP_NETBIOS_DGM_PORT 138
#define UDP_NETBIOS_SSN_PORT 139
#define UDP_IMAP4_PORT 143
#define UDP_SNMP_PORT 161
#define UDP_IRC_PORT 194
#define UDP_HTTPS_PORT 443
#define UDP_MICROSOFT_DS_PORT 445
#define UDP_SMTPS_PORT 465
#define UDP_IMAPS_PORT 993
#define UDP_IRCS_PORT 994
#define UDP_POP3S_PORT 995
	word SourcePort;
	word DestinationPort;
	word Length;
	word Checksum;
};
```
### Example
An example is not provided due to complexity of implementation. View the [NetworkPacketAnalyzer](https://github.com/robertdurfee/networkpacketanalyzer) for an implementation.
