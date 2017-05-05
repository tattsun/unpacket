#include "IPPacket.h"

#include <iostream>
#include <arpa/inet.h>
#include <net/ethernet.h>

std::string to_string(const IPProtocolType t) {
  switch(t) {
  case IPProtocolType::TCP:
    return "tcp";
  case IPProtocolType::UDP:
    return "udp";
  case IPProtocolType::Unknown:
    return "unknown";
  }
}

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

const unsigned char* IPPacket::data() {
  return packet + sizeof(struct ether_header) + sizeof(struct ip);
}

IPProtocolType IPPacket::protocol() {
  switch(ip->ip_p) {
  case 6:
    return IPProtocolType::TCP;
  case 17:
    return IPProtocolType::UDP;
  default:
    return IPProtocolType::Unknown;
  }
}
