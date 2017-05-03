#include "PacketCapturer.h"

#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>

#include <sstream>

PacketCapturer::PacketCapturer(const std::string& dev, int bufsiz)
  : dev(dev), bufsiz(bufsiz) {
}

void PacketCapturer::start(std::string &err) {
  handle = pcap_open_live(dev.c_str(), bufsiz, 1, 1000, errbuf);
  if(handle == NULL) {
    std::ostringstream st;
    st << "couldn't open device " << dev << ", cause: " << errbuf;
    err = st.str();
    return;
  }

  if(pcap_datalink(handle) != DLT_EN10MB) {
    std::ostringstream st;
    st << "device not support " << dev;
    err = st.str();
    return;
  }
}

IPPacketPtr PacketCapturer::capture() {
  const unsigned char* packet = NULL;
  pcap_pkthdr* header = new pcap_pkthdr;

  while(1) {
    packet = pcap_next(handle, header);

    if(packet == NULL)
      continue;

    if(header->len < sizeof(struct ether_header) + sizeof(struct ip))
      continue;

    break;
  }

  return std::unique_ptr<IPPacket>(new IPPacket(header, packet));
}


