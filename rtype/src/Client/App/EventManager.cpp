#include <SFML/Graphics.hpp>
#include "EventManager.hpp"
#include "StateManager.hpp"
#include "CoreRTYPE.hpp"

namespace App
{
	const int EventManager::shoot_interval = 6;

	EventManager::EventManager()
		:	toProcess_(false)
	{
		this->ptrFMVector_.push_back(&EventManager::checkUpLeft);
		this->ptrFMVector_.push_back(&EventManager::checkUpRight);
		this->ptrFMVector_.push_back(&EventManager::checkDownLeft);
		this->ptrFMVector_.push_back(&EventManager::checkDownRight);
		this->ptrFMVector_.push_back(&EventManager::checkUp);
		this->ptrFMVector_.push_back(&EventManager::checkDown);
		this->ptrFMVector_.push_back(&EventManager::checkLeft);
		this->ptrFMVector_.push_back(&EventManager::checkRight);
	}

	EventManager::~EventManager() {}

	void	EventManager::setWindow(sf::RenderWindow *window)
	{
		this->window_ = window;
	}

	void	EventManager::processEvent()
	{
		sf::Event sfEvent;
		while (this->toProcess_ && this->window_->GetEvent(sfEvent))
		{
			if (sfEvent.Type == sf::Event::JoyMoved)
				handleJoyMoved(sfEvent);
			if (sfEvent.Type == sf::Event::JoyButtonPressed)
				handleJoyButtonPressed(sfEvent);
			if (sfEvent.Type == sf::Event::Closed)
				CoreRTYPE::getInstance().quit();
			if (sfEvent.Type == sf::Event::TextEntered || sfEvent.Type == sf::Event::KeyPressed)
				StateManager::getInstance().onPressedKey(sfEvent);
		}
	}

	void	EventManager::setToProcess(bool value)
	{
		this->toProcess_ = value;
	}

	void		EventManager::handleJoyMoved(sf::Event sfEvent)
	{
		if (sfEvent.JoyMove.Axis == sf::Joy::AxisPOV)
		{
			sf::Event eventKey;
			eventKey.Key = sf::Event::KeyEvent();
			eventKey.Type = sf::Event::KeyPressed;
			if (sfEvent.JoyMove.Axis == sf::Joy::AxisPOV && sfEvent.JoyMove.Position == 0)
				eventKey.Key.Code = sf::Key::Up;
			else if (sfEvent.JoyMove.Axis == sf::Joy::AxisPOV && sfEvent.JoyMove.Position == 180)
				eventKey.Key.Code = sf::Key::Down;
			else
				return ;
			StateManager::getInstance().onPressedKey(eventKey);
		}
	}

	void		EventManager::handleJoyButtonPressed(sf::Event sfEvent)
	{
		if (sfEvent.JoyButton.Button == 1)
		{
			sf::Event eventKey;
			eventKey.Key = sf::Event::KeyEvent();
			eventKey.Type = sf::Event::TextEntered;
			eventKey.Text.Unicode = 13;
			StateManager::getInstance().onPressedKey(eventKey);
		}
                else if (sfEvent.JoyButton.Button == 9)
		{
			sf::Event eventKey;
			eventKey.Key = sf::Event::KeyEvent();
			eventKey.Type = sf::Event::KeyPressed;
			eventKey.Key.Code = sf::Key::Escape;
			StateManager::getInstance().onPressedKey(eventKey);
		}
	}

	Protocol::eEvent EventManager::getDirection()
	{
		int direction = Protocol::RT_EVENT_UP_LEFT;
		for (std::vector<ptrMF>::const_iterator it = this->ptrFMVector_.begin(); it != this->ptrFMVector_.end(); ++it, direction++)
		{
			if ((this->*(*it))())
				return static_cast<Protocol::eEvent>(direction);
		}
		return Protocol::RT_EVENT_NONE;
	}

	bool		EventManager::checkUpLeft()
	{
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Up) && this->window_->GetInput().IsKeyDown(sf::Key::Left))
			|| (this->window_->GetInput().GetJoystickAxis(0, sf::Joy::AxisPOV) == 315));
	}

	bool		EventManager::checkUpRight()
	{
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Up) && this->window_->GetInput().IsKeyDown(sf::Key::Right))
			|| (this->window_->GetInput().GetJoystickAxis(0, sf::Joy::AxisPOV) == 45));
	}

	bool		EventManager::checkDownLeft()
	{
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Down) && this->window_->GetInput().IsKeyDown(sf::Key::Left))
			|| (this->window_->GetInput().GetJoystickAxis(0, sf::Joy::AxisPOV) == 225));
	}

	bool		EventManager::checkDownRight()
	{
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Down) && this->window_->GetInput().IsKeyDown(sf::Key::Right))
			|| (this->window_->GetInput().GetJoystickAxis(0, sf::Joy::AxisPOV) == 135));
	}

	bool		EventManager::checkLeft()
	{
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Left))
			|| (this->window_->GetInput().GetJoystickAxis(0, sf::Joy::AxisPOV) == 270));
	}

	bool		EventManager::checkRight()
	{
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Right))
			|| (this->window_->GetInput().GetJoystickAxis(0, sf::Joy::AxisPOV) == 90));
	}

	bool		EventManager::checkUp()
	{
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Up))
			|| (this->window_->GetInput().GetJoystickAxis(0, sf::Joy::AxisPOV) == 0));
	}

	bool		EventManager::checkDown()
	{
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Down))
			|| (this->window_->GetInput().GetJoystickAxis(0, sf::Joy::AxisPOV) == 180));
	}

	bool		EventManager::checkSpace()
	{
		static char button0 = 0;

		if (this->window_->GetInput().IsJoystickButtonDown(0, 0))
		{
			if (button0++ == shoot_interval)
				button0 = 0;
			return button0 == 0;
		}
		return ((this->window_->GetInput().IsKeyDown(sf::Key::Space))
			|| (this->window_->GetInput().IsJoystickButtonDown(0, 1)));
	}
}
