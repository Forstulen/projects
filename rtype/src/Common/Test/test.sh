
#TestStream
#`cd ../Thread && g++ testStream.cpp SafeSTDStream.cpp Linux/Mutex.cpp -I ./Linux -include Thread.hpp -include Mutex.hpp -lpthread -o ../Test/TestThread -g3 -Wall -Wextra`

#FileStream
#`g++ mainFileStream.cpp ../Network/FileSender.cpp ../Thread/MutexLinux.cpp ../Network/Packet.cpp -include ../Network/Packet.hpp -include ../Network/Protocol.hpp -include ../Thread/SafeQueue.hpp -include ../Thread/MutexLinux.hpp -include ../Thread/IThread.hpp -include ../Network/FileReceiver.hpp -I ../Thread/ -I ../Network/ -lpthread -o FileStream`

#TestServer
`g++ mainServer.cpp -I ../Network/Linux/ -I ../Network  ../Network/CodeExcept.cpp ../Network/ErrnoExcept.cpp ../Network/Packet.cpp ../Network/Linux/SocketLibrary.cpp ../Network/Linux/TCPClient.cpp ../Network/Linux/TCPServer.cpp ../Network/Linux/TCPSocket.cpp ../Network/Linux/UDPSocket.cpp -o TestServer`

#echo	"Should Take less than 2 secondes"
#time ./TestStream

#echo	"Create a file"
#./FileStream

