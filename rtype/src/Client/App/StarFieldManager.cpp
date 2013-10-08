#include <SFML/Graphics.hpp>
#include "Packet.hpp"
#include "StarFieldManager.hpp"
#include "CoreRTYPE.hpp"

namespace App
{
	StarFieldManager::StarFieldManager() {}

	StarFieldManager::~StarFieldManager() {}

	void	StarFieldManager::draw(sf::RenderWindow *window)
	{
		for (std::list<stars>::iterator it = this->starsList_.begin(); it != this->starsList_.end(); ++it)
			window->Draw(sf::Shape::Circle((*it).posX, (*it).posY, 1, (*it).color));
	}

	void	StarFieldManager::initStarField(int number)
	{
		this->random_.SetSeed(42);
		for (int tmp = 0; tmp < number; ++tmp)
		{
			float		speed = this->random_.Random(1.0f, 3.0f);
			int			col = 255 / static_cast<int>(speed);

			stars		star = {this->random_.Random(0.0f, App::WIDTH), this->random_.Random(0.0f, App::HEIGHT),  sf::Color(col, col, col), 1.0f / speed};
			this->starsList_.push_back(star);
		}
		this->timer_ = 0;
	}


	void			StarFieldManager::update(float time)
	{
		if (this->timer_ > App::SIXTY_FPS)
          {
			for (std::list<stars>::iterator it = this->starsList_.begin(); it != this->starsList_.end(); ++it)
			{
				(*it).posX -= (*it).speed * time * 100.0f;
				if ((*it).posX <= 0)
				{
					(*it).posX = App::WIDTH;
					(*it).posY = this->random_.Random(0.0f, App::HEIGHT);
				}
			}
			this->timer_ = 0;
          }
        this->timer_ += time;
	}
}
