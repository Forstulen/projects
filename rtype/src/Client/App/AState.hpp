#ifndef ASTATE_HPP
#define ASTATE_HPP

#include <SFML/Graphics.hpp>
#include "Packet.hpp"

namespace App
{
	class AState
	{
	protected:
		AState													*nextState_;
    AState													*prevState_;
	public:
		virtual ~AState() {}
		virtual	void	initialize() = 0;
		virtual void	draw(sf::RenderWindow*) = 0;
		virtual void	onPressedKey(sf::Event) = 0;
		void	setNextState(AState*);
		void	setPrevState(AState*);
		virtual void	update(Network::Packet const&) = 0;
		virtual void  update(float) = 0;
		virtual void	activateCheatCode() = 0;
	};
}

#endif
