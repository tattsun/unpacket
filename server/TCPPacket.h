#include <netinet/tcp.h>

#include "IPPacket.h"

class TCPPacket {
public:
  TCPPacket(IPPacketPtr ip);

  unsigned short src_port();
  unsigned short dst_port();
private:
  IPPacketPtr ip;
  const struct tcphdr* tcp;
};
