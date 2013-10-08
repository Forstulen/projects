#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

#include "Protocol.hpp"
#include "Singleton.hpp"

namespace App
{
	class EventManager : public Tools::Singleton<EventManager>
	{
		friend class Tools::Singleton<EventManager>;
	private:
		typedef bool (EventManager::*ptrMF)();
		sf::RenderWindow			*window_;
		std::vector<ptrMF>		ptrFMVector_;
		static const int			shoot_interval;
		bool									toProcess_;
	private:
		EventManager();
		~EventManager();
		EventManager(EventManager&);
		EventManager& operator=(EventManager&);
	public:
		void									setWindow(sf::RenderWindow *window);
		void									processEvent();
    Protocol::eEvent			getDirection();
		void									setToProcess(bool);
	private:
		void						handleJoyMoved(sf::Event);
		void						handleJoyButtonPressed(sf::Event);
		bool						checkUpLeft();
		bool						checkUpRight();
		bool						checkDownLeft();
		bool						checkDownRight();
		bool						checkLeft();
		bool						checkRight();
		bool						checkUp();
		bool						checkDown();
	public:
		bool						checkSpace();
	};
}

#endif
