#!/bin/sh
g++ mainAuthManager.cpp ../../Server/AuthManager.cpp ../Network/Packet.cpp -I ../../Server -I ../Tools/ -I ../Network/ -o AuthManager