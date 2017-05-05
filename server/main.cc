#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>

#include <pcap.h>
#include <stdlib.h>

#include "IPPacket.h"
#include "PacketCapturer.h"

int main() {
  std::string err;

  PacketCapturerPtr p = std::unique_ptr<PacketCapturer>(new PacketCapturer("en0", 1024));
  p->start(err);
  if(!err.empty()) {
    std::cerr << "err: " << err << std::endl;
    std::abort();
  }

  pcap_pkthdr** header = NULL;
  const unsigned char** packet = NULL;
  while(1) {
    p->capture(header, packet);
    pkt = p->capture();
    std::cout
      << "SRC: " << pkt->ip_src()
      << "\t\tDST: " << pkt->ip_dst()
      << "\t\tPRT: " << to_string(pkt->protocol())
      << std::endl;
  }
}
