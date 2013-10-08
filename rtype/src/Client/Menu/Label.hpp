#ifndef LABEL_HPP
#define LABEL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "IWidget.hpp"

namespace Menu
{
  class Label : public IWidget
  {
  private:
	  sf::Image									back_;
	  sf::Sprite								background_;
	  sf::Font									font_;
	  sf::String								textToDisplay_;
	  sf::Unicode::UTF32String	textLabel_;
	  sf::Unicode::UTF32String	textEdit_;
	  unsigned int							lengthText_;
	  float											sizeFont_;
	  sf::Color									color_;
	  sf::Vector2f							position_;
	  IWidget										*nextWidget_;
	  IWidget										*prevWidget_;
		bool											hide_;
  public:

	  Label(std::string const &fontPath, std::string const &textLabel, float size, sf::Vector2f vector, 
		  unsigned int lengthText = 0, std::string const &textEdit = "", sf::Color color = sf::Color(255, 255, 255));
	  ~Label();
	  void					draw(sf::RenderWindow *window);
	  sf::Vector2f			getPosition() const;
	  void					setPosition(sf::Vector2f position);
	  void					action(sf::Event);
	  IWidget					*getNextWidget() const;
	  IWidget					*getPrevWidget() const;
	  void					setNextWidget(IWidget* widget);
	  void					setPrevWidget(IWidget* widget);
		void				setTextEdit(std::string const &);
	  void				setTextLabel(std::string const &);
	  void				setColor(sf::Color);
	  void				getTextEdit(std::string &textEdit) const;
		void				getTextLabel(std::string &textEdit) const;
	  void				update(float);
		void				rotate(float);
		float				getVerticalCenter() const;
		bool				isHide();
		void				setHide(bool);
  }; 
}

#endif
