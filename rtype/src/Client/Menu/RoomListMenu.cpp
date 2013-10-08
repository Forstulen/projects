#include <string>
#include "RoomListMenu.hpp"
#include "Label.hpp"
#include "Packet.hpp"
#include "Conversions.hpp"
#include "EventManager.hpp"
#include "Button.hpp"
#include "IWidget.hpp"
#include "StateManager.hpp"
#include "CoreRTYPE.hpp"
#include "RoomMenu.hpp"
#include "ScopedLock.hpp"

namespace Menu
{
	const	int				RoomListMenu::playerNb = 4;

	RoomListMenu::RoomListMenu(std::string const &image)
		: AMenu(image),
			listLabel_("../../resource/defused.ttf", "Room List", 22, sf::Vector2f(70, 50)),
			quitButton_(this, "../../resource/defused.ttf", "quit", 30, sf::Vector2f(150, 400), &RoomListMenu::exitMenu),
			errorMessage_("../../resource/defused.ttf", "", 22, sf::Vector2f(80, 150),1),
			error_(false)
	{
		this->initFunctions();
		this->addWidget(&this->listLabel_);
		this->playerLabels_.push_back(new Label("../../resource/defused.ttf", "", 30, sf::Vector2f(400, 80)));
		this->playerLabels_.push_back(new Label("../../resource/defused.ttf", "", 30, sf::Vector2f(400, 180)));
		this->playerLabels_.push_back(new Label("../../resource/defused.ttf", "", 30, sf::Vector2f(400, 280)));
		this->playerLabels_.push_back(new Label("../../resource/defused.ttf", "", 30, sf::Vector2f(400, 380)));
		for (int i = 0; i < playerNb; i++)
			this->addWidget(this->playerLabels_[i]);
		this->addWidget(&this->quitButton_);
		this->errorMessage_.setHide(true);
		this->addWidget(&this->errorMessage_);
	}

	RoomListMenu::~RoomListMenu()
	{
	}
	
	void	RoomListMenu::initFunctions()
	{
		this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_ROOMS, 
			Protocol::RT_TT_REPLY)]
		= &RoomListMenu::handleRoomList;
		this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_PLAYERS, 
			Protocol::RT_TT_REPLY)]
		= &RoomListMenu::handlePlayerList;
		this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_JOIN, 
			Protocol::RT_TT_ACK)]
		= &RoomListMenu::joinRoomSuccess;
		this->functions_[Conversions::encodeToUShort(Protocol::RT_SUB_JOIN, 
			Protocol::RT_TT_ERROR)]
		= &RoomListMenu::joinRoomError;
	}

	void	RoomListMenu::initialize()
	{
		this->socket_ = App::CoreRTYPE::getInstance().getTCPSocket();
		this->cursor_.setHide(true);
		this->cursor_.setCurrentWidget(0);
		bool toContinue = true;
		this->socket_->sendPacket(Network::Packet("", 0, Protocol::RT_TYPE_ROOM, Protocol::RT_TT_REQUEST, Protocol::RT_SUB_ROOMS), 0);
		App::EventManager::getInstance().setToProcess(true);
	}

	void	RoomListMenu::onPressedKey(sf::Event eventKey)
	{
		if (this->cursor_.getCurrentWidget() == 0)
			return;
		if (eventKey.Type == sf::Event::KeyPressed)
		{
			if (eventKey.Key.Code == 293 /* up */)
				this->changeRoomLabel(this->cursor_.getCurrentWidget()->getPrevWidget());
			if (eventKey.Key.Code == 294 /* down */)
				this->changeRoomLabel(this->cursor_.getCurrentWidget()->getNextWidget());
		}
		if (eventKey.Type == sf::Event::TextEntered)
		{
			if (eventKey.Text.Unicode == 9 /*tab*/)
				this->changeRoomLabel(this->cursor_.getCurrentWidget()->getNextWidget());
			else if (this->cursor_.getCurrentWidget())
				this->cursor_.getCurrentWidget()->action(eventKey);
		}
	}

	void	RoomListMenu::update(Network::Packet const &packet)
	{
		unsigned short opcode = Conversions::encodeToUShort(packet.getSubType(), packet.getTransactionType());
		if (packet.getType() == Protocol::RT_TYPE_ROOM)
			if (this->functions_[opcode])
				(this->*this->functions_[opcode])(packet);
	}

	void	RoomListMenu::activateCheatCode()
	{
	}

	void	RoomListMenu::exitMenu()
	{
		this->socket_->sendPacket(Network::Packet("", 0,
			Protocol::RT_TYPE_CONNECTION,
			Protocol::RT_TT_REQUEST,
			Protocol::RT_SUB_DISC), 0);
		App::CoreRTYPE::getInstance().disconnectFromServer();
		App::StateManager::getInstance().changeState(this->prevState_);
	}

	void	RoomListMenu::applyForm()
	{
		Button<RoomListMenu> *room = dynamic_cast<Button<RoomListMenu>* >(this->cursor_.getCurrentWidget());
		if (room && room != &this->quitButton_)
		{
			room->getText(this->roomChosen_);
			this->socket_->sendPacket(Network::Packet(roomChosen_.c_str(), roomChosen_.size() + 1, Protocol::RT_TYPE_ROOM, Protocol::RT_TT_REQUEST, Protocol::RT_SUB_JOIN), 0);
		}
	}

	void	RoomListMenu::handleRoomList(Network::Packet const &packet)
	{
		unsigned int sizeData = packet.getSize() - sizeof(Network::Header);
		std::string data;
		data.append(packet.getData<const char *>(), sizeData);
		Button<RoomListMenu> *prev = 0;
		for (int i = 0; i < 10; i++)
		{
			unsigned int pos = data.find('\0', 0);
			std::string name = data.substr(0, pos);
			data.erase(0, pos + 1);
			this->roomButtons_.push_back(new Button<RoomListMenu>(this, "../../resource/defused.ttf", name, 19, sf::Vector2f(70, 80 + (i + 1) * 25), &RoomListMenu::applyForm));
			if (i != 0)
			{
				this->roomButtons_.back()->setPrevWidget(this->roomButtons_[i - 1]);
				this->roomButtons_[i - 1]->setNextWidget(this->roomButtons_[i]);
			}
			Thread::ScopedLock<Thread::Mutex> scopedLock(this->mutex_);
			this->addWidget(this->roomButtons_[i]);
		}
		this->roomButtons_[0]->setPrevWidget(&this->quitButton_);
		this->quitButton_.setPrevWidget(this->roomButtons_[9]);
		this->quitButton_.setNextWidget(this->roomButtons_[0]);
		this->roomButtons_[9]->setNextWidget(&this->quitButton_);
		this->cursor_.setCurrentWidget(this->roomButtons_[0]);
		this->changeRoomLabel(this->roomButtons_[0]);
		this->cursor_.setHide(false);
	}

	void	RoomListMenu::handlePlayerList(Network::Packet const &packet)
	{
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
			std::cout << name << std::endl;
			i++;
		}
	}

	void	RoomListMenu::joinRoomSuccess(Network::Packet const &packet)
	{
			this->soundOk_.Play();
			App::CoreRTYPE::getInstance().setRoom(this->roomChosen_);
			App::StateManager::getInstance().changeState(this->nextState_);
	}

	void	RoomListMenu::joinRoomError(Network::Packet const &packet)
	{
		this->errorMessage_.setTextLabel(packet.getData<char const *>());
		this->errorMessage_.setHide(false);
		this->error_ = true;
		this->setHideGUI(true);
	}

	void RoomListMenu::setHideGUI(bool value)
	{
		this->cursor_.setHide(value);
		this->listLabel_.setHide(value);
		this->quitButton_.setHide(value);
		for (int i = 0; i < this->playerNb; i++)
			this->playerLabels_[i]->setHide(value);
		for (int i = 0; i < this->roomButtons_.size(); i++)
			this->roomButtons_[i]->setHide(value);
	}

	void	RoomListMenu::changeRoomLabel(IWidget* widget)
	{
		if (this->error_)
		{
			this->errorMessage_.setHide(true);
			this->setHideGUI(false);
			this->error_ = false;
		}
		Label *playerLabel;
		std::string nb;
		for (int i = 0; i < playerNb; i++)
			playerLabels_[i]->setTextLabel("");
		this->cursor_.setCurrentWidget(widget);
		Button<RoomListMenu> *buttonRoom = dynamic_cast<Button<RoomListMenu>* >(widget);
		std::string roomName;
		buttonRoom->getText(roomName);
		this->socket_->sendPacket(Network::Packet(roomName.c_str(), roomName.size() + 1, Protocol::RT_TYPE_ROOM, Protocol::RT_TT_REQUEST, Protocol::RT_SUB_PLAYERS), 0);
	}
}
