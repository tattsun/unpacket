#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>

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

  IPPacketPtr pkt = nullptr;
  while(1) {
    pkt = p->capture();
    std::cout << "SRC: " << pkt->ip_src() << "\t\tDST: " << pkt->ip_dst() << std::endl;
  }
}
