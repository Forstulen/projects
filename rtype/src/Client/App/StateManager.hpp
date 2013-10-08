#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <SFML/Window.hpp>
#include <list>
#include "AState.hpp"
#include "Singleton.hpp"
#include "IListener.hpp"
#include "Packet.hpp"
#include "ObserverSocket.hpp"
#include "ISocket.hpp"

namespace App
{
	class StateManager : public Network::IListener, public Tools::Singleton<StateManager>
  {
		friend class Tools::Singleton<StateManager>;
  private:
		std::list<AState*>			stateList_;
		AState									*beginState_;
		AState									*currentState_;
	private:
    StateManager();
		~StateManager();
    StateManager(StateManager&);
    StateManager& operator=(StateManager&);
  public:
    void	addState(AState*);
    void	delState(AState*);
		void	setBeginState(AState*);
    void	changeState(AState*);
    void	onPressedKey(sf::Event);
    void	update(Network::Packet const &);
    void	activateCheatCode();
		AState*	getCurrentState();
  };
}  

#endif
