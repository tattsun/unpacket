#include <netinet/tcp.h>

#include "IPPacket.h"

class TCPPacket : public IPPacket {
public:
  TCPPacket(struct pcap_pkthdr* header, const unsigned char* packet);

  unsigned short src_port();
  unsigned short dst_port();
private:
  const struct tcphdr* tcp;
};

using TCPPacketPtr = std::unique_ptr<TCPPacket>;
