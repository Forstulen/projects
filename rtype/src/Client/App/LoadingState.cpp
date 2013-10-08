#include "LoadingState.hpp"
#include "CoreRTYPE.hpp"
#include "AssetManager.hpp"
#include "StarFieldManager.hpp"
#include "Exception.hpp"
#include "HUDManager.hpp"
#include "MapManager.hpp"
#include "ConnectionMenu.hpp"
#include "GameOverState.hpp"
#include "Transition.hpp"
#include "GameClient.hpp"
#include "RoomListMenu.hpp"
#include "RoomMenu.hpp"
#include "StateManager.hpp"
#include "Sound/SoundManager.hpp"

static bool	loadGame(App::LoadingState *state)
{
	try
	{
		Asset::AssetManager::getInstance().loadAssets();
	}
	catch (...)
	{
		std::cout << "Error Assets !" << std::endl;
		App::CoreRTYPE::getInstance().quit();
	}
	App::AState	*connectionMenu = new Menu::ConnectionMenu("backgroundConnection");
	App::AState	*transState = new App::Transition(500.0f);
	App::AState	*roomListMenu = new Menu::RoomListMenu("backgroundRoomList");
	App::AState	*roomMenu = new Menu::RoomMenu("backgroundRoomList");
	App::AState	*gameOverMenu = new Menu::GameOverMenu("backgroundGameover");
	App::AState	*gameState = new App::GameClient(App::CoreRTYPE::getInstance().socketUDP_);
	App::StateManager::getInstance().addState(connectionMenu);
	App::StateManager::getInstance().setBeginState(connectionMenu);
	App::StateManager::getInstance().addState(transState);
	App::StateManager::getInstance().addState(roomListMenu);
	App::StateManager::getInstance().addState(roomMenu);
	App::StateManager::getInstance().addState(gameState);
	App::StateManager::getInstance().addState(gameOverMenu);
	state->setNextState(connectionMenu);
	connectionMenu->setNextState(transState);
	transState->setNextState(roomListMenu);
	roomListMenu->setPrevState(connectionMenu);
	roomListMenu->setNextState(roomMenu);
	roomMenu->setPrevState(roomListMenu);
	roomMenu->setNextState(gameState);
	gameState->setPrevState(roomListMenu);
	gameState->setNextState(gameOverMenu);
	gameOverMenu->setPrevState(gameState);
	gameOverMenu->setNextState(roomListMenu);
	App::StarFieldManager::getInstance().initStarField(75);
	App::HUDManager::getInstance().initHUD(App::WIDTH, App::HEIGHT);
	Sound::SoundManager::getInstance().initMusic("Starcraft");
	state->loadFinished();
	return true;
}

namespace App
{
	LoadingState::LoadingState()
		: isLoadingFinished_(false)
	{
		this->loadingThread_ = new Thread::Thread(&::loadGame, this);
		this->image_.LoadFromFile("../../resource/sprites/blueship.png");
		this->bgImage_.LoadFromFile("../../resource/sprites/loading.png");
		this->bg_.SetImage(this->bgImage_);
		this->bg_.SetPosition(0, 0);
		this->sprite_.SetImage(this->image_);
		this->sprite_.SetSubRect(sf::IntRect(0, 0, 31, 14));
		this->sprite_.SetPosition(sf::Vector2f(-this->sprite_.GetSize().x, 400.f));
		this->sprite_.Rotate(18.f);
	}

	LoadingState::~LoadingState() {}

	void	LoadingState::initialize()
	{
		
	}

	void	LoadingState::draw(sf::RenderWindow* window)
	{
		if (window)
		{
			window->Draw(this->bg_);
			window->Draw(this->sprite_);
		}
	}

	void	LoadingState::onPressedKey(sf::Event)
	{
	}

	void	LoadingState::update(Network::Packet const&)
	{
	}

	void  LoadingState::update(float time)
	{
		this->sprite_.Move(400.f * time, -100.f * time);
		if (this->sprite_.GetPosition().x > App::WIDTH)
			this->sprite_.SetPosition(-this->sprite_.GetSize().x, this->sprite_.GetPosition().y);
	 if (this->sprite_.GetPosition().y < 0)
			this->sprite_.SetPosition(this->sprite_.GetPosition().x, App::HEIGHT);
		if (this->isLoadingFinished_)
		{
			this->loadingThread_->joinThread();
			App::StateManager::getInstance().changeState(this->nextState_);
		}
	}
	
	void	LoadingState::activateCheatCode()
	{
	}

	void	LoadingState::loadFinished()
	{
		this->isLoadingFinished_ = true;
	}
}
