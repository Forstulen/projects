#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/System.hpp>
#include <string>
#include "IWidget.hpp"

namespace Menu
{
  template <typename T>
  class Button : public IWidget
  {
  private:
    typedef void (T::*funcPtr)();
		T							*parent_;
    IWidget				*prevWidget_;
    IWidget				*nextWidget_;
    funcPtr				action_;
    sf::Vector2f	position_;
    sf::Sprite		sprite_;
		sf::String		text_;
		sf::Font			font_;
		bool					hide_;
		sf::Key::Code keyPressed_;
		unsigned char keyTextEntered_;
  public:
    Button(T *parent, std::string const &fontPath, std::string const &text, float size, sf::Vector2f position, funcPtr action)
      : parent_(parent), action_(action), position_(position), text_(text),
			nextWidget_(this), prevWidget_(this), hide_(false), keyPressed_(sf::Key::Count), keyTextEntered_('\r')
    {
			this->font_.LoadFromFile(fontPath);
			this->text_.SetFont(this->font_);
			this->text_.SetSize(size);
			this->text_.SetColor(sf::Color(255, 255, 255));
			this->action_ = action;
			this->position_ = position;
			this->text_.SetPosition(this->position_);
    }
      
    ~Button()
    {}

    void		draw(sf::RenderWindow *window)
    {
      window->Draw(text_);
    }
	
		void		update(float)
		{

		}
  
    sf::Vector2f		getPosition() const
    {
      return this->position_;
    }

    void		setPosition(sf::Vector2f position)
    {
      this->position_ = position;
    }
  
    void		action(sf::Event eventKey)
    {
			if (eventKey.Key.Code == this->keyPressed_ ||
				eventKey.Text.Unicode == this->keyTextEntered_)
				(this->parent_->*action_)();
    }

    IWidget		*getNextWidget() const
    {
      return this->nextWidget_;
    }

    IWidget		*getPrevWidget() const
    {
      return this->prevWidget_;
    }

    void		setNextWidget(IWidget* widget)
    {
      this->nextWidget_ = widget;
    }

    void		setPrevWidget(IWidget* widget)
    {
      this->prevWidget_ = widget;
    }

		float			getVerticalCenter() const
		{
			return this->text_.GetRect().GetHeight() / 2;
		}

		void			getText(std::string &str) const
		{
			str = this->text_.GetText();
		}

		void			setText(std::string const& str)
		{
			this->text_.SetText(str);
		}

		bool				isHide()
		{
			return this->hide_;
		}

		void				setHide(bool value)
		{
			this->hide_ = value;
		}

		void				setKeyPressed(sf::Key::Code key)
		{
			this->keyPressed_ = key;
		}

		void				setKeyTextEntered(unsigned char key)
		{
			this->keyTextEntered_ = key;
		}
  };
}

#endif
