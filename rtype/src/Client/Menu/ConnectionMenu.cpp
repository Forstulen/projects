#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TCPSocket.hpp"
#include "Cursor.hpp"
#include "AMenu.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "ConnectionMenu.hpp"
#include "StateManager.hpp"
#include "Conversions.hpp"
#include "Protocol.hpp"
#include "CoreRTYPE.hpp"
#include "EventManager.hpp"

namespace Menu
{
  ConnectionMenu::ConnectionMenu(std::string const &image)
    : AMenu(image),
			configFile_("../../resource/config.txt"),
      ipLabel_("../../resource/defused.ttf", "ip : ", 30, sf::Vector2f(120, 150), 15),
      portLabel_("../../resource/defused.ttf", "port : ", 30, sf::Vector2f(120, 200), 5),
      userNameLabel_("../../resource/defused.ttf", "username : ", 30, sf::Vector2f(120, 250), 11),
      okButton_(this, "../../resource/defused.ttf", "ok", 30, sf::Vector2f(250, 400), &ConnectionMenu::applyForm),
      quitButton_(this, "../../resource/defused.ttf", "quit", 30, sf::Vector2f(450, 400), &ConnectionMenu::exitMenu),
      errorMessage_("../../resource/defused.ttf", "Disconnected from server", 30, sf::Vector2f(80, 150)),
      errorButton_(this, "../../resource/defused.ttf", "ok", 30, sf::Vector2f(350, 200), &ConnectionMenu::applyError),
      isConnected_(false),
      disconnected_(false)
  {
    this->addWidget(&this->errorButton_);
    this->addWidget(&this->errorMessage_);
    this->errorButton_.setHide(true);
    this->errorMessage_.setHide(true);
    this->addWidget(&this->ipLabel_);
    this->addWidget(&this->portLabel_);
    this->addWidget(&this->userNameLabel_);
    this->addWidget(&this->okButton_);
    this->addWidget(&this->quitButton_);
    this->initFunctions();
    this->ipLabel_.setNextWidget(&this->portLabel_);
    this->ipLabel_.setPrevWidget(&this->quitButton_);
    this->portLabel_.setNextWidget(&this->userNameLabel_);
    this->portLabel_.setPrevWidget(&this->ipLabel_);
    this->userNameLabel_.setNextWidget(&this->okButton_);
    this->userNameLabel_.setPrevWidget(&this->portLabel_);
    this->okButton_.setNextWidget(&this->quitButton_);
    this->okButton_.setPrevWidget(&this->userNameLabel_);
    this->quitButton_.setNextWidget(&this->ipLabel_);
    this->quitButton_.setPrevWidget(&this->okButton_);
    this->soundError_.SetBuffer(Asset::AssetManager::getInstance().getAssetSoundInformation("insufficient").getSound());
    this->soundError_.SetVolume(40.f);
		this->ipLabel_.setTextEdit(this->configFile_.getHost());
		this->portLabel_.setTextEdit(this->configFile_.getPort());
		this->userNameLabel_.setTextEdit(this->configFile_.getUserName());
  }

  ConnectionMenu::~ConnectionMenu()	{}

  void	ConnectionMenu::initFunctions()
  {
    this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_AUTH, 
						 Protocol::RT_TT_ACK)]
      = &ConnectionMenu::connectionSuccess;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_AUTH, 
						 Protocol::RT_TT_ERROR)]
      = &ConnectionMenu::connectionError;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_DISC, 
						 Protocol::RT_TT_REQUEST)]
      = &ConnectionMenu::handleDisconnection;
  }

  void		ConnectionMenu::initialize()
  {
    this->setCursorToUpdate(true);
    this->isConnected_ = false;
    this->cursor_.setCurrentWidget(&this->ipLabel_);
    this->socket_ = App::CoreRTYPE::getInstance().getTCPSocket();
    App::EventManager::getInstance().setToProcess(true);
  }

  void	ConnectionMenu::onPressedKey(sf::Event eventKey)
  {
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

  void	ConnectionMenu::connectionSuccess(Network::Packet const &packet)
  {
    this->soundOk_.Play();
    App::StateManager::getInstance().changeState(this->nextState_);
    std::cout << "ConnectionMenu: connection accepted" << std::endl;
  }

  void	ConnectionMenu::connectionError(Network::Packet const &packet)
  {
    this->isConnected_ = false;
    this->disconnected_ = true;
  }

  void	ConnectionMenu::setHideGUI(bool value)
  {
    this->ipLabel_.setHide(value);
    this->portLabel_.setHide(value);
    this->userNameLabel_.setHide(value);
    this->okButton_.setHide(value);
    this->quitButton_.setHide(value);
  }

  void	ConnectionMenu::handleDisconnection(Network::Packet const &packet)
  {
    this->disconnected_ = true;
    this->setHideGUI(true);
    this->errorMessage_.setHide(false);
    this->errorButton_.setHide(false);
    this->cursor_.setCurrentWidget(&this->errorButton_);
  }

  void	ConnectionMenu::update(Network::Packet const &packet)
  {
    unsigned short opcode = Conversions::encodeToUShort(packet.getSubType(), packet.getTransactionType());
    if (packet.getType() == Protocol::RT_TYPE_CONNECTION)
      if (this->functions_[opcode])
	(this->*this->functions_[opcode])(packet);
      else
	std::cerr << "ConnectionMenu: Unknown packet received" << std::endl;
  }

  void	ConnectionMenu::activateCheatCode()
  {
  }

  void	ConnectionMenu::exitMenu()
  {
    App::CoreRTYPE::getInstance().quit();
  }

  void	ConnectionMenu::applyError()
  {
    this->errorMessage_.setHide(true);
    this->errorButton_.setHide(true);
    this->setHideGUI(false);
    this->cursor_.setCurrentWidget(&this->ipLabel_);
  }

	void	ConnectionMenu::applyForm()
  {
    std::string	host, port, username;
    this->ipLabel_.getTextEdit(host);
    this->socket_->setHost(host);
    this->portLabel_.getTextEdit(port);	
    this->socket_->setPort(Conversions::convertString<int>(port));
    this->userNameLabel_.getTextEdit(username);
    if (this->disconnected_)
      {
	App::CoreRTYPE::getInstance().disconnectFromServer();
	App::CoreRTYPE::getInstance().closeUDPSocket();
	this->socket_ = App::CoreRTYPE::getInstance().getTCPSocket();
	this->socket_->setHost(host);
	this->socket_->setPort(Conversions::convertString<int>(port));
	this->disconnected_ = false;
      }
    if (!this->isConnected_ && this->socket_->connectToServer())
      {
	this->isConnected_ = true;
	App::CoreRTYPE::getInstance().setIpServer(host);
	this->configFile_.setHost(host);
	this->configFile_.setPort(port);
	this->configFile_.setUserName(username);
	this->configFile_.writeFile();
      }
    if (this->isConnected_)
      {
	App::CoreRTYPE::getInstance().startObserverSocketTCP();
	App::CoreRTYPE::getInstance().setLogin(username);
	this->socket_->sendPacket(Network::Packet(username.c_str(), username.size() + 1, Protocol::RT_TYPE_CONNECTION, Protocol::RT_TT_REQUEST, Protocol::RT_SUB_AUTH), 0);
      }
    else
      {
	std::cerr << "ConnectionMenu: Error connection" << std::endl;
	this->soundError_.Play();
      }
  }
}
