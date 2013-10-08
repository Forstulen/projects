#ifndef CORE_HPP
#define CORE_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ICore.hpp"
#include "Singleton.hpp"
#include "TCPClient.hpp"
#include "UDPSocket.hpp"
#include "ObserverSocket.hpp"
#include "IThread.hpp"

namespace App
{
	const float					SIXTY_FPS = 0.016f;
	const float					WIDTH = 800;
	const float					HEIGHT = 480;

	class CoreRTYPE : public ICore, public Tools::Singleton<App::CoreRTYPE>
	{
		friend class Tools::Singleton<App::CoreRTYPE>;
	private:
		sf::Clock									clock_;
		sf::RenderWindow					window_;
		Network::ObserverSocket		*observerSocketTCP_;
		Network::ObserverSocket		*observerSocketUDP_;
		Thread::IThread						*LoadingThread_;
		unsigned int							playerId_;
		std::string								login_;
		std::string								currentRoom_;
		std::string								ipServer_;
		unsigned int							UDPPortServer_;
	private:
		CoreRTYPE();
		CoreRTYPE(CoreRTYPE&);
		CoreRTYPE& operator=(CoreRTYPE&);
		~CoreRTYPE();
	public:
		Network::TCPClient				*socketTCP_;
		Network::UDPSocket				*socketUDP_;
		bool								run();
		void								quit();
		void								disconnectFromServer();
		void								closeUDPSocket();
		void								startObserverSocketTCP();
		void								startObserverSocketUDP();
		sf::RenderWindow		*getWindow();
		unsigned int				getPlayerId() const;
		void								setPlayerId(unsigned int);
		std::string const & getLogin() const;
		void								setLogin(std::string const&);
		std::string const & getRoom() const;
		void								setRoom(std::string const&);
		Network::TCPClient	*getTCPSocket();
		Network::UDPSocket	*getUDPSocket();
		std::string const		&getIpServer() const;
		void								setIpServer(std::string const &);
		unsigned int				getUDPPortServer() const;
		void								setUDPPortServer(unsigned int);
		unsigned int				bindUDPSocket();
	private:
		void	displayFPS();
	};
}

#endif
