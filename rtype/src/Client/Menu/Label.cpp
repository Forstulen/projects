#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "IWidget.hpp"
#include "Label.hpp"
#include "CoreRTYPE.hpp"

namespace Menu
{
  Label::Label(std::string const &fontPath, std::string const &textLabel, float size, sf::Vector2f vector, unsigned int lengthText, std::string const &textEdit, sf::Color color)
		: textLabel_(textLabel.begin(), textLabel.end()), textEdit_(textEdit.begin(), textEdit.end()), lengthText_(lengthText), sizeFont_(size), color_(color), position_(vector),
		prevWidget_(0), nextWidget_(0), hide_(false)
  {
		this->font_.LoadFromFile(fontPath);
		this->textToDisplay_.SetSize(size);
		this->textToDisplay_.SetFont(font_);
		if (this->lengthText_ > 0)
		{
			this->back_.Create(App::HEIGHT, 40, sf::Color(0, 0, 0, 200));
			this->background_.SetImage(this->back_);
		}
		this->textToDisplay_.SetPosition(this->position_);
		this->background_.SetPosition(this->position_);
	}
  
  Label::~Label() {}
  
  void		Label::draw(sf::RenderWindow *window)
  {
	  window->Draw(background_);
		sf::Unicode::UTF32String str;
		str.append(this->textLabel_);
		str.append(this->textEdit_);
		this->textToDisplay_.SetText(str);
		window->Draw(this->textToDisplay_);
  }

  void			Label::update(float)
  {
  }
  
  sf::Vector2f	Label::getPosition() const
  {
    return this->position_;
  }

  void		Label::setPosition(sf::Vector2f position)
  {
		this->position_ = position;
		this->textToDisplay_.SetPosition(this->position_);
		this->background_.SetPosition(this->position_);
  }
  
  void		Label::action(sf::Event eventKey)
  {
		if (eventKey.Type == sf::Event::TextEntered)
		{
			if (!this->textEdit_.empty() && eventKey.Text.Unicode == '\b')
				this->textEdit_.erase(this->textEdit_.length() - 1);
			else
			{
				if (this->textEdit_.length() < this->lengthText_
					&& eventKey.Text.Unicode > 32)
				  this->textEdit_.push_back(eventKey.Text.Unicode);
			}
		}
  }
	
  IWidget	*Label::getNextWidget() const
  {
		return this->nextWidget_;
  }

  IWidget	*Label::getPrevWidget() const
  {
	return this->prevWidget_;
  }

  void		Label::setNextWidget(IWidget* widget)
  {
	this->nextWidget_ = widget;
  }

  void		Label::setPrevWidget(IWidget* widget)
  {
	this->prevWidget_ = widget;
  }

	void		Label::setTextLabel(std::string const &text)
	{
		this->textLabel_.assign(text.begin(), text.end());
	}

	void		Label::setTextEdit(std::string const &text)
	{
		this->textEdit_.assign(text.begin(), text.end());
	}

	void		Label::setColor(sf::Color color)
	{
		this->textToDisplay_.SetColor(color);
	}

	void		Label::getTextEdit(std::string &textEdit) const
	{
		sf::Unicode::Text text(this->textEdit_);
		textEdit = text;
	}

	void		Label::getTextLabel(std::string &textEdit) const
	{
		sf::Unicode::Text text(this->textLabel_);
		textEdit = text;
	}
	
	void		Label::rotate(float angle)
	{
		this->textToDisplay_.Rotate(angle);
	}

	float			Label::getVerticalCenter() const
	{
		return this->textToDisplay_.GetRect().GetHeight() / 2;
	}

	bool			Label::isHide()
	{
		return this->hide_;
	}

	void			Label::setHide(bool value)
	{
		this->hide_ = value;
	}
}
