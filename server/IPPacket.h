#ifndef IPPACKET_H
#define IPPACKET_H

#include <memory>

#include <netinet/ip.h>
#include <pcap.h>

class IPPacket {
public:
  IPPacket(struct pcap_pkthdr* header, const unsigned char* packet);

  std::string ip_src();
  std::string ip_dst();
private:
  struct pcap_pkthdr* header;
  const unsigned char* packet;
  const struct ip *ip;
};

using IPPacketPtr = std::unique_ptr<IPPacket>;

#endif
