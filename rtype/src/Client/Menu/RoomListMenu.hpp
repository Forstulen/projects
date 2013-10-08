#ifndef ROOMLISTMENU_HPP
#define ROOMLISTMENU_HPP

#include "AMenu.hpp"
#include "Label.hpp"
#include "Button.hpp"

namespace Menu
{
  class RoomListMenu : public AMenu
  {
  private:
		typedef void (RoomListMenu::*RMFn)(Network::Packet const &);
    typedef std::map<unsigned short, RMFn>			tFunctionContainer;
		tFunctionContainer													functions_;
    std::string																	roomChosen_;
		Label																				listLabel_;
		std::vector<Label*>													playerLabels_;
		std::vector<Button<RoomListMenu>* >					roomButtons_;
		Button<RoomListMenu>												quitButton_;
		Label																				errorMessage_;;
		bool																				error_;
		static const	int														playerNb;
  public:
    RoomListMenu(std::string const &imagePath);
    ~RoomListMenu();
		void	initialize();
    void	onPressedKey(sf::Event);
    void	update(Network::Packet const &packet);
    void	activateCheatCode();
    void	exitMenu();
    void	applyForm();
    void	changeRoomLabel(IWidget* widget);
    void	handleRoomList(Network::Packet const &packet);
    void	handlePlayerList(Network::Packet const &packet);
		void	joinRoomSuccess(Network::Packet const &packet);
		void	joinRoomError(Network::Packet const &packet);
	private:
		void	initFunctions();
		void	setHideGUI(bool);
  };
}

#endif
