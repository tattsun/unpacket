#include "TCPPacket.h"

TCPPacket::TCPPacket(IPPacketPtr ip)
  : ip(std::move(ip))
  , tcp(reinterpret_cast<const struct tcphdr*>(ip->data())) {
}

unsigned short TCPPacket::src_port() {
  return tcp->th_sport;
}

unsigned short TCPPacket::dst_port() {
  return tcp->th_dport;
}
