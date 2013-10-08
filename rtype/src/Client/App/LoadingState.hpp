#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "AState.hpp"
#include "Thread.hpp"

namespace App
{
	class LoadingState : public AState
	{
	private:
		Thread::IThread			*loadingThread_;
		sf::Image						image_;
		sf::Sprite					sprite_;
		sf::Sprite					bg_;
		sf::Image					bgImage_;
		bool								isLoadingFinished_;
	public:
		LoadingState();
		~LoadingState();
	private:
		LoadingState(LoadingState&);
		LoadingState& operator=(LoadingState&);
	public:
		void	initialize();
		void	draw(sf::RenderWindow*);
		void	onPressedKey(sf::Event);
		void	update(Network::Packet const&);
		void  update(float);
		void	activateCheatCode();
		void	loadFinished();
	};
}

#endif
