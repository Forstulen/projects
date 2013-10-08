#include		<string>

#include		"FileSender.hpp"
#include		"FileReceiver.hpp"

/*
** g++ main.cpp ../Thread/MutexLinux.cpp -include Protocol.hpp -include ../Thread/SafeQueue.hpp -include ../Thread/MutexLinux.hpp -include ../Thread/IThread.hpp -I ../Thread/ -lpthread
*/

int				main()
{
  std::string			sock = "Patate";
  Network::FileSender<std::string, Thread::Mutex>	file(sock);
  Network::FileReceiver		rec;
  Network::Packet		packet("Patate", 6,
				       Protocol::RT_TYPE_ROOM,
				       Protocol::RT_TT_MODIFICATION, 0);
  Network::Packet		eo("", 0,
				   Protocol::RT_TYPE_ROOM,
				   Protocol::RT_TT_MODIFICATION, 0);

  file << "Test.txt";
  --file;
  --file;

  rec << "Patate.txt";
  rec += packet;

  rec << "TonBoule.txt";
  rec += packet;
  rec += eo;
  return (0);
}
