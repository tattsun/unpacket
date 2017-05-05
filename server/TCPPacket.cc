#include "TCPPacket.h"

TCPPacket::TCPPacket(struct pcap_pkthdr* header, const unsigned char* packet)
  : IPPacket(header, packet)
  , tcp(reinterpret_cast<const struct tcphdr*>(IPPacket::data())) {
}

unsigned short TCPPacket::src_port() {
  return tcp->th_sport;
}

unsigned short TCPPacket::dst_port() {
  return tcp->th_dport;
}
