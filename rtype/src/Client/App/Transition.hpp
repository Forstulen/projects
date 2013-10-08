#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include "AState.hpp"

namespace App
{
  class Transition : public AState
  {
    sf::Sprite sprite_;
    float speed_;

    public:
    Transition(float speed);
    ~Transition();

		void	initialize();
    void draw(sf::RenderWindow*);
    void onPressedKey(sf::Event)
    {}
    void update(Network::Packet const& p)
    {
			this->nextState_->update(p);
		}
    void update(float);
    void activateCheatCode()
    {}
  };
}

#endif
