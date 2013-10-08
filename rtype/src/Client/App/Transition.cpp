#include <iostream>
#include "StarFieldManager.hpp"
#include "EventManager.hpp"
#include "AssetManager.hpp"
#include "StateManager.hpp"
#include "Transition.hpp"

namespace App
{
Transition::Transition(float speed):
  speed_(speed)
{
	this->sprite_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation("backgroundConnection").getImage());
  this->sprite_.SetX(0);
  this->sprite_.SetY(0);
}

Transition::~Transition()
{
}

void	Transition::initialize()
{
	App::EventManager::getInstance().setToProcess(false);
}

void Transition::update(float time)
{
  StarFieldManager::getInstance().update(time);
  this->sprite_.Move(this->speed_ * time, 0);
  if (this->sprite_.GetPosition().x > 800)
	{
		this->sprite_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation("backgroundRoomList").getImage());
		this->sprite_.SetX(400);
		this->sprite_.SetY(0);
		speed_ = -speed_;
	}
	else if (this->sprite_.GetPosition().x < 0)
	{
    StateManager::getInstance().changeState(this->nextState_);
	}
}

void Transition::draw(sf::RenderWindow* window)
{
  StarFieldManager::getInstance().draw(window);
  window->Draw(this->sprite_);
}
}
