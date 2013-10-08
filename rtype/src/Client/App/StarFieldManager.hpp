#ifndef STARFIELDMANAGER_HPP
#define STARFIELDMANAGER_HPP

#include <list>
#include <SFML/Graphics.hpp>
#include "Singleton.hpp"

namespace App
{
	class StarFieldManager : public Tools::Singleton<StarFieldManager>
	{
		friend class Tools::Singleton<StarFieldManager>;

		struct			stars
		{
			float		posX;
			float		posY;
			sf::Color	color;
			float		speed;
		};

	private:
		sf::Randomizer				random_;
		std::list<stars>			starsList_;
		float						timer_;
	private:
		StarFieldManager();
		~StarFieldManager();
		StarFieldManager(StarFieldManager&);
		StarFieldManager& operator=(StarFieldManager&);
	public:
		void		draw(sf::RenderWindow *);
		void		initStarField(int);
		void		update(float);
	};
}

#endif