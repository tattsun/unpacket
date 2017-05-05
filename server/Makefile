CXX = g++
TARGET = unpacket_server
CXXFLAGS = -Wall -O2 -std=c++11 -lpcap
SRCS = ./main.cc PacketCapturer.cc IPPacket.cc TCPPacket.cc

$(TARGET): $(SRCS)
	$(CXX) -o $@ $(SRCS) $(CXXFLAGS)
