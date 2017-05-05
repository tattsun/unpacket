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

void PacketCapturer::capture(pcap_pkthdr** header, const unsigned char** packet) {
  const unsigned char* pkt = NULL;
  pcap_pkthdr* hdr = new pcap_pkthdr;

  while(1) {
    pkt = pcap_next(handle, hdr);

    if(pkt == NULL)
      continue;

    if(hdr->len < sizeof(struct ether_header) + sizeof(struct ip))
      continue;

    break;
  }

  *header = hdr;
  *packet = pkt;
}


