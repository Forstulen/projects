#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <string>
#include "IDrawableObject.hpp"
#include "AssetManager.hpp"

namespace Menu
{
	class IWidget;

	class Cursor : public IDrawableObject
	{
	private:
		IWidget							*currentWidget_;
		std::string					nameSprite_;
		sf::Vector2f				position_;
		sf::SoundBuffer			soundBuffer_;
		sf::Sound						sound_;
		unsigned int				index_;
		sf::Sprite					sprite_;
		bool								direction_;
		bool								hide_;
	public:
		Cursor(std::string const &imagePath);
		~Cursor();
		void							draw(sf::RenderWindow *window);
		void							update(float);
		sf::Vector2f			getPosition() const;
		void							setPosition(sf::Vector2f position);
		void							setCurrentWidget(IWidget *);
		IWidget						*getCurrentWidget() const;
		void							setHide(bool);
	};
}

#endif
