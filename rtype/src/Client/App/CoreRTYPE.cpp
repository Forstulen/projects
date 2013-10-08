#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "AState.hpp"
#include "CoreRTYPE.hpp"
#include "StateManager.hpp"
#include "AssetManager.hpp"
#include "StarFieldManager.hpp"
#include "TCPClient.hpp"
#include "MapManager.hpp"
#include "Exception.hpp"
#include "EventManager.hpp"
#include "LoaderManager.hpp"
#include "RoomListMenu.hpp"

#include "LoadingState.hpp"

namespace App
{
	CoreRTYPE::CoreRTYPE()
		: window_(sf::VideoMode(static_cast<unsigned int>(WIDTH), static_cast<unsigned int>(HEIGHT), 32), "R-Type", sf::Style::Resize)
			, socketTCP_(new Network::TCPClient()), socketUDP_(new Network::UDPSocket(4252))
	{
	}

	CoreRTYPE::~CoreRTYPE()
	{}

	bool	CoreRTYPE::run()
	{
		try
		{
          sf::Clock cl;
		this->window_.SetFramerateLimit(60);
		this->window_.UseVerticalSync(true);
		this->window_.ShowMouseCursor(false);
		AState	*loadingState = new App::LoadingState();
		App::StateManager::getInstance().changeState(loadingState);
		App::EventManager::getInstance().setWindow(&this->window_);

                  cl.Reset();
			while (this->window_.IsOpened())
			{
				EventManager::getInstance().processEvent();
				StateManager::getInstance().getCurrentState()->update(cl.GetElapsedTime());
                                cl.Reset();
				this->window_.Clear();
				StateManager::getInstance().getCurrentState()->draw(&this->window_);
				/*this->displayFPS();*/
				this->window_.Display();
			}
		}
		catch (const Exception & e)
		{
			std::cerr << "Error Assets :" << e.what() << std::endl;
			this->quit();
		}
		catch (...)
		{
			std::cerr << "Program Error : Your program is corrupted." << std::endl;
			this->quit();
		}
		return true;
	}

	void		CoreRTYPE::startObserverSocketTCP()
	{
		this->observerSocketTCP_ = new Network::ObserverSocket(this->socketTCP_);
		this->observerSocketTCP_->registerListener(static_cast<Network::IListener*>(&App::StateManager::getInstance()));
	}

	void		CoreRTYPE::startObserverSocketUDP()
	{
		this->observerSocketUDP_= new Network::ObserverSocket(this->socketUDP_);
		this->observerSocketUDP_->registerListener(static_cast<Network::IListener*>(&App::StateManager::getInstance()));
	}

	void		CoreRTYPE::displayFPS()
	{
		sf::String	fpsString;
		float frameRate = 1.f / this->window_.GetFrameTime();
		std::string fps;
		Conversions::toString(frameRate, fps);
		fpsString.SetText(fps);
		this->window_.Draw(fpsString);
	}

	void		CoreRTYPE::quit()
	{
		if (this->observerSocketTCP_)
			delete this->observerSocketTCP_;
		delete(this->observerSocketUDP_);
		delete(this->socketUDP_);
		delete(this->socketTCP_);
		this->window_.Close();
	}

	void		CoreRTYPE::disconnectFromServer()
	{
		delete(this->observerSocketTCP_);
		this->observerSocketTCP_ = 0;
		delete(this->socketTCP_);
		this->socketTCP_ = 0;
		this->socketTCP_ = new Network::TCPClient();
	}

	void		CoreRTYPE::closeUDPSocket()
	{
		delete this->observerSocketUDP_;
		this->observerSocketUDP_ = 0;
		delete this->socketUDP_;
		this->socketUDP_ = new Network::UDPSocket(4252);
	}

	sf::RenderWindow	*CoreRTYPE::getWindow()
	{
		return &this->window_;
	}

	unsigned int			CoreRTYPE::getPlayerId() const
	{
		return this->playerId_;
	}

	void							CoreRTYPE::setPlayerId(unsigned int id)
	{
		this->playerId_ = id;
	}

	std::string const & CoreRTYPE::getLogin() const
	{
		return this->login_;
	}

	void								CoreRTYPE::setLogin(std::string const& login)
	{
		this->login_ = login;
	}

	std::string const & CoreRTYPE::getRoom() const
	{
		return this->currentRoom_;
	}

	void								CoreRTYPE::setRoom(std::string const& room)
	{
		this->currentRoom_ = room;
	}

	Network::TCPClient	*CoreRTYPE::getTCPSocket()
	{
		return this->socketTCP_;
	}

	Network::UDPSocket	*CoreRTYPE::getUDPSocket()
	{
		return this->socketUDP_;
	}

	std::string const &CoreRTYPE::getIpServer() const
	{
		return this->ipServer_;
	}
	void							CoreRTYPE::setIpServer(std::string const &str)
	{
		this->ipServer_ = str;
	}

	unsigned int			CoreRTYPE::getUDPPortServer() const
	{
		return this->UDPPortServer_;
	}

	void							CoreRTYPE::setUDPPortServer(unsigned int port)
	{
		this->UDPPortServer_ = port;
	}

	unsigned int				CoreRTYPE::bindUDPSocket()
	{
		return this->socketUDP_->bindSocket();
	}
}
