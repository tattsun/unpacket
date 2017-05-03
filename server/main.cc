#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>

#include <pcap.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

using namespace std;

struct IPPacket {
  struct pcap_pkthdr header;
  const unsigned char* packet;
};

class PacketReceiver {
public:
  PacketReceiver(const string& dev)
    : dev(dev) {
  }

  void start(string& err) {
    if((handle = pcap_open_live(dev.c_str(), bufsiz, 1, 1000, errbuf)) == NULL) {
      ostringstream st;
      st << "couldn't open device " << dev << errbuf;
      err = st.str();
      return;
    }

    if(pcap_datalink(handle) != DLT_EN10MB) {
      ostringstream st;
      st << "device not support " << dev;
      err = st.str();
      return;
    }
  }

  unique_ptr<IPPacket> recv() {
    unique_ptr<IPPacket> pkt(new IPPacket());
    while((pkt->packet = pcap_next(handle, &pkt->header)) == NULL) {
      if(pkt->header.len < sizeof(struct ether_header)+sizeof(struct ip)) {
        continue;
      }
    }
    return pkt;
  }
private:
  static int bufsiz;
    
  string dev;
  char errbuf[1024];
  
  pcap_t* handle;
};
int PacketReceiver::bufsiz = 1024;

int main() {
  string err;
  
  unique_ptr<PacketReceiver> receiver(new PacketReceiver("en0"));
  receiver->start(err);
  if(!err.empty()) {
    cerr << "ERR: " << err << endl;
    abort();
  }

  unique_ptr<IPPacket> pkt;
  while(1) {
    pkt = receiver->recv();
    cout << "Received" << endl;
  }
}
