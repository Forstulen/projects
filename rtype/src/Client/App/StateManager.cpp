#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Packet.hpp"
#include	"CoreRTYPE.hpp"
#include "AState.hpp"
#include "StateManager.hpp"
#include "TCPSocket.hpp"

namespace App
{
  StateManager::StateManager()
	{}
  
	StateManager::~StateManager() {}

  void		StateManager::addState(AState* state)
  {
    this->stateList_.push_back(state);
  }

  void		StateManager::delState(AState* state)
  {
    this->stateList_.remove(state);
  }

	void		StateManager::setBeginState(AState *state)
	{
		this->beginState_ = state;
	}

  void		StateManager::changeState(AState* state)
  {
    this->currentState_ = state;
    this->currentState_->initialize();
  }

  void		StateManager::onPressedKey(sf::Event key)
  {
		this->currentState_->onPressedKey(key);
  }

  void		StateManager::update(Network::Packet const & packet)
  {
		if (packet.getType() == Protocol::RT_TYPE_CONNECTION &&
			packet.getTransactionType() == Protocol::RT_TT_REQUEST &&
			packet.getSubType() == Protocol::RT_SUB_DISC)
		{
			this->changeState(this->beginState_);
		}
    this->currentState_->update(packet);
  }

  void		StateManager::activateCheatCode()
  {
    this->currentState_->activateCheatCode();
  }
  
  AState	*StateManager::getCurrentState()
  {
    return this->currentState_;
  }
}
