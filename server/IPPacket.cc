#include "IPPacket.h"

#include <iostream>
#include <arpa/inet.h>
#include <net/ethernet.h>

IPPacket::IPPacket(struct pcap_pkthdr* header, const unsigned char* packet)
  : header(header)
  , packet(packet)
  , ip(reinterpret_cast<const struct ip*>(packet + sizeof(struct ether_header))) {
}

std::string IPPacket::ip_src() {
  const char* c_str = inet_ntoa(ip->ip_src);
  return std::string(c_str);
}

std::string IPPacket::ip_dst() {
  const char* c_str = inet_ntoa(ip->ip_dst);
  return std::string(c_str);
}
