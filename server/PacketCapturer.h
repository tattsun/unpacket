#ifndef PACKET_CAPTURER_H
#define PACKET_CAPTURER_H

#include <iostream>

#include "IPPacket.h"

class PacketCapturer {
public:
  PacketCapturer(const std::string& dev, int bufsiz);
  
  void start(std::string& err);
  IPPacketPtr capture();
private:
  const std::string dev;
  int bufsiz;

  char errbuf[1024];
  pcap_t* handle;
};

using PacketCapturerPtr = std::unique_ptr<PacketCapturer>;

#endif
