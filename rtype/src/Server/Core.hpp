#ifndef CORE_HPP
# define  CORE_HPP

# include <vector>
# if __i386
#   include <sys/types.h>
# endif

# include "ISocket.hpp"
# include "TCPServer.hpp"
# include "Singleton.hpp"
# include "Player.hpp"
# include "AuthManager.hpp"
# include "RoomManager.hpp"
# include "UDPSocket.hpp"

class Core : public Tools::Singleton<Core>
{
  friend class Tools::Singleton<Core>;

  Network::TCPServer          socket_;
  Connection::AuthManager     am_;
  Room::RoomManager           rm_;
  std::vector<Game::Player *> waiters_;
  std::vector<Game::Player *> players_;
  fd_set                      readSet_;
  fd_set                      writeSet_;
  struct timeval              timeout_;
  int                         nbChangeFd_;
  Network::UDPSocket	      socketUDP_;
private:
  Core();
  ~Core();

private:
  Core(Core const &);
  Core & operator=(Core const &);

private:
  void			      removeUnexpQuit(Network::TCPSocket* sock, Game::Player *player);
  void			      manageWaitersRequest(Network::TCPSocket* sock, Game::Player *player);
  void			      listenClientsInRooms();
  bool			      isExistingLogin(Network::Packet &packet, std::string const &name) const;

private:
  void                        initFdSetWrite();
  void                        initFdSetRead();
  void                        reinitTimer(int const sec, int const usec);
  void                        doSelect();
  void                        accept();
  void                        listenClient();
  void			      writeClient();

public:
  void                        run();
  bool                        set(std::string const& port);
};

# ifdef LINUX
#  define			INVALID_SOCKET -1
# endif

#endif				/* ! SELECT_HPP */
