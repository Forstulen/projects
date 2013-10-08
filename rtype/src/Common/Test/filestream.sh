#!/bin/sh
g++ mainFileStream.cpp ../Network/FileSender.cpp ../Thread/MutexLinux.cpp ../Network/Packet.cpp -include ../Network/Packet.hpp -include ../Network/Protocol.hpp -include ../Thread/SafeQueue.hpp -include ../Thread/MutexLinux.hpp -include ../Thread/IThread.hpp -include ../Network/FileReceiver.hpp -I ../Thread/ -I ../Network/ -lpthread -o FileStream
