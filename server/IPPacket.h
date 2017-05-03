#ifndef IPPACKET_H
#define IPPACKET_H

#include <memory>

#include <pcap.h>

class IPPacket {
public:
  IPPacket(struct pcap_pkthdr* header, const unsigned char* packet)
    : header(header), packet(packet) {
  }
private:
  struct pcap_pkthdr* header;
  const unsigned char* packet;
};

using IPPacketPtr = std::unique_ptr<IPPacket>;

#endif
