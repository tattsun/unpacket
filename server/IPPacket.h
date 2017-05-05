#ifndef IPPACKET_H
#define IPPACKET_H

#include <iostream>
#include <memory>

#include <netinet/ip.h>
#include <pcap.h>

enum class IPProtocolType {
  TCP,
  UDP,
  Unknown,
};
std::string to_string(const IPProtocolType t);

class IPPacket {
public:
  IPPacket(struct pcap_pkthdr* header, const unsigned char* packet);

  std::string ip_src();
  std::string ip_dst();
  const unsigned char* data();

  IPProtocolType protocol();
protected:
  struct pcap_pkthdr* header;
  const unsigned char* packet;
  const struct ip *ip;
};

using IPPacketPtr = std::unique_ptr<IPPacket>;

#endif

