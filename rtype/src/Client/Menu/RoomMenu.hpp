#ifndef ROOMMENU_HPP
#define ROOMMENU_HPP

#include "Label.hpp"
#include "AMenu.hpp"
#include "Button.hpp"

namespace Menu
{
  class RoomMenu : public AMenu
  {
  private:
		typedef void (RoomMenu::*RMFn)(Network::Packet const &);
    typedef std::map<unsigned short, RMFn>			tFunctionContainer;
		tFunctionContainer													functions_;
    std::string																	roomName_;
		std::vector<sf::Color>											colors_;
		Label																				titleLabel_;
		std::vector<Label*>													playerLabels_;
		Button<RoomMenu>														readyButton_;
		Button<RoomMenu>														quitButton_;
		static const int														playerNb;
  public:
    RoomMenu(std::string const &imagePath);
    ~RoomMenu();
		void	initFunctions();
    void	initialize();
    void	onPressedKey(sf::Event);
    void	update(Network::Packet const &packet);
    void	activateCheatCode();
    void	exitMenu();
    void	applyForm();
    void	setRoomName(std::string const &);
    void	handlePlayerList(Network::Packet const &packet);
		void	readyAck(Network::Packet const &packet);
		void	readyInfo(Network::Packet const &packet);
		void	handlePlayerInfo(Network::Packet const &packet);
		void	sendClientInfo(Protocol::PlayerInfo info);
  };
}

#endif
