#include <iostream>
#include "RoomMenu.hpp"
#include "Label.hpp"
#include "Protocol.hpp"
#include "Button.hpp"
#include "CoreRTYPE.hpp"
#include "StateManager.hpp"
#include "EventManager.hpp"

namespace Menu
{
	const int RoomMenu::playerNb = 4;

  RoomMenu::RoomMenu(std::string const &image)
    : AMenu(image),
			titleLabel_(Label("../../resource/defused.ttf", "Room ", 30, sf::Vector2f(100, 50))),
			readyButton_(Button<RoomMenu>(this, "../../resource/defused.ttf", "ready", 30, sf::Vector2f(70, 400), &RoomMenu::applyForm)),
			quitButton_(Button<RoomMenu>(this, "../../resource/defused.ttf", "quit", 30, sf::Vector2f(310, 400), &RoomMenu::exitMenu))
  {
		this->colors_.push_back(sf::Color(0, 82, 156));
		this->colors_.push_back(sf::Color(206, 0, 0));
		this->colors_.push_back(sf::Color(0, 165, 0));
		this->colors_.push_back(sf::Color(255, 235, 17));
		this->colors_.push_back(sf::Color(58, 255, 232));
		this->initFunctions();
		this->playerLabels_.push_back(new Label("../../resource/defused.ttf", "", 30, sf::Vector2f(70, 150)));
		this->playerLabels_.push_back(new Label("../../resource/defused.ttf", "", 30, sf::Vector2f(70, 210)));
		this->playerLabels_.push_back(new Label("../../resource/defused.ttf", "", 30, sf::Vector2f(70, 270)));
		this->playerLabels_.push_back(new Label("../../resource/defused.ttf", "", 30, sf::Vector2f(70, 330)));
		for (int i = 0; i < playerNb; i++)
			this->addWidget(this->playerLabels_[i]);
		this->addWidget(&this->titleLabel_);
		this->addWidget(&this->readyButton_);
		this->addWidget(&this->quitButton_);
    this->readyButton_.setNextWidget(&this->quitButton_);
    this->readyButton_.setPrevWidget(&this->quitButton_);
    this->quitButton_.setNextWidget(&this->readyButton_);
    this->quitButton_.setPrevWidget(&this->readyButton_);
  }

  RoomMenu::~RoomMenu()
  {
  }

	void	RoomMenu::initFunctions()
	{
		this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_PLAYERS, 
			Protocol::RT_TT_REPLY)]
		= &RoomMenu::handlePlayerList;
		this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_READY, 
			Protocol::RT_TT_ACK)]
		= &RoomMenu::readyAck;
		this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_READY, 
			Protocol::RT_TT_REPLY)]
		= &RoomMenu::readyInfo;
		this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_INFO, 
			Protocol::RT_TT_REPLY)]
		= &RoomMenu::handlePlayerInfo;
	}

  void	RoomMenu::initialize()
  {
		this->roomName_ = App::CoreRTYPE::getInstance().getRoom();
		this->titleLabel_.setTextLabel("Room " + this->roomName_);
		this->socket_ = App::CoreRTYPE::getInstance().getTCPSocket();
    this->socket_->sendPacket(Network::Packet(this->roomName_.c_str(), 
					      this->roomName_.size() + 1,
					      Protocol::RT_TYPE_ROOM,
					      Protocol::RT_TT_REQUEST,
					      Protocol::RT_SUB_PLAYERS), 0);
		this->cursor_.setCurrentWidget(&this->readyButton_);
		for (int i = 0; i < playerNb; i++)
			this->playerLabels_[i]->setColor(sf::Color(255, 255, 255));
		App::EventManager::getInstance().setToProcess(true);
  }

  void	RoomMenu::onPressedKey(sf::Event eventKey)
  {
    if (this->cursor_.getCurrentWidget() == 0)
      return;
    if (eventKey.Type == sf::Event::KeyPressed)
      {
	if (eventKey.Key.Code == 293 /* up */)
	  this->cursor_.setCurrentWidget(this->cursor_.getCurrentWidget()->getPrevWidget());
	if (eventKey.Key.Code == 294 /* down */)
	  this->cursor_.setCurrentWidget(this->cursor_.getCurrentWidget()->getNextWidget());
      }
    if (eventKey.Type == sf::Event::TextEntered)
      {
	if (eventKey.Text.Unicode == 9 /*tab*/)
	  this->cursor_.setCurrentWidget(this->cursor_.getCurrentWidget()->getNextWidget());
	else
	  this->cursor_.getCurrentWidget()->action(eventKey);
      }
  }

  void	RoomMenu::update(Network::Packet const &packet)
  {
		unsigned short opcode = Conversions::encodeToUShort(packet.getSubType(), packet.getTransactionType());
		if (packet.getType() == Protocol::RT_TYPE_ROOM)
		if (this->functions_[opcode])
			(this->*this->functions_[opcode])(packet);
  }

  void	RoomMenu::activateCheatCode()
  {
  }

  void	RoomMenu::exitMenu()
  {
		this->socket_->sendPacket(Network::Packet(this->roomName_.c_str(), this->roomName_.size() + 1,
					      Protocol::RT_TYPE_ROOM,
					      Protocol::RT_TT_REQUEST,
								Protocol::RT_SUB_LEAVE), 0);
		App::StateManager::getInstance().changeState(this->prevState_);
		this->readyButton_.setText("ready");
  }

  void	RoomMenu::applyForm()
  {
    this->socket_->sendPacket(Network::Packet("", 0,
					      Protocol::RT_TYPE_ROOM,
					      Protocol::RT_TT_REQUEST,
					      Protocol::RT_SUB_READY), 0);
    std::string str;
		this->readyButton_.getText(str);
    if (str == "ready")
      this->readyButton_.setText("unready");
    else
      this->readyButton_.setText("ready");
  }

	void	RoomMenu::handlePlayerList(Network::Packet const &packet)
	{
		for (int i = 0; i < this->playerLabels_.size(); i++)
			this->playerLabels_[i]->setTextLabel("");
		unsigned int sizeData = packet.getSize() - sizeof(Network::Header);
		std::string data;
		data.append(packet.getData<const char *>(), sizeData);
		int i = 0;
		while (data.size() > 0)
		{
			unsigned int pos = data.find('\0', 0);
			std::string name = data.substr(0, pos);
			data.erase(0, pos + 1);
			this->playerLabels_[i]->setTextLabel(name);
			i++;
		}
	}

	void	RoomMenu::readyAck(Network::Packet const &packet)
	{
	}

	void	RoomMenu::readyInfo(Network::Packet const &packet)
	{
		const Protocol::PlayerStatus *playerStatus;
		playerStatus = packet.getData<const Protocol::PlayerStatus*>();
		for (int i = 0; i < this->playerLabels_.size(); i++)
		{
			std::string name;
			this->playerLabels_[i]->getTextLabel(name);
			if (name.compare(playerStatus->login) == 0)
			{
				if (playerStatus->isReady)
					this->playerLabels_[i]->setColor(this->colors_[4]);
				else
					this->playerLabels_[i]->setColor(sf::Color(255, 255, 255));
			}
		}
	}

	void	RoomMenu::sendClientInfo(Protocol::PlayerInfo info)
	{
		unsigned int port = App::CoreRTYPE::getInstance().bindUDPSocket();
		App::CoreRTYPE::getInstance().startObserverSocketUDP();
		info.port = port;
		this->socket_->sendPacket(Network::Packet(&info, sizeof(Protocol::PlayerInfo),
			Protocol::RT_TYPE_ROOM,
			Protocol::RT_TT_REQUEST,
			Protocol::RT_SUB_INFO), 0);
	}

	void	RoomMenu::handlePlayerInfo(Network::Packet const &packet)
	{
		const Protocol::PlayerInfo *pi;
		pi = packet.getData<const Protocol::PlayerInfo*>();
		App::CoreRTYPE::getInstance().setUDPPortServer(pi->port);
		if (App::CoreRTYPE::getInstance().getLogin().compare(pi->login) == 0)
		{
			this->sendClientInfo(*pi);
			App::CoreRTYPE::getInstance().setPlayerId(pi->id);
			this->soundOk_.Play();
			App::StateManager::getInstance().changeState(this->nextState_);
			this->readyButton_.setText("ready");
			std::cout << "RoomMenu: LET'S GET READY TO RUMBLE !!!!" << std::endl;
		}
		for (int i = 0; i < this->playerLabels_.size(); i++)
		{
			std::string name;
			this->playerLabels_[i]->getTextLabel(name);
			if (name.compare(pi->login) == 0)
				this->playerLabels_[i]->setColor(this->colors_[pi->id]);
		}
	}
}
