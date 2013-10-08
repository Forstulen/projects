#ifndef CONNECTIONMENU_HPP
#define CONNECTIONMENU_HPP

#include <SFML/Graphics.hpp>
#include "AMenu.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "TCPClient.hpp"
#include "ConfigFile.hpp"

namespace Menu
{
  class ConnectionMenu : public AMenu
  {
  private:
    typedef void (ConnectionMenu::*RMFn)(Network::Packet const &);
    typedef std::map<unsigned short, RMFn>			tFunctionContainer;
    tFunctionContainer													functions_;
    sf::Sound								soundError_;
    Label										ipLabel_;
    Label										portLabel_;
    Label										userNameLabel_;
    Button<ConnectionMenu>	okButton_;
    Button<ConnectionMenu>	quitButton_;
    Label										errorMessage_;
    Button<ConnectionMenu>	errorButton_;
    bool										isConnected_;
    bool										disconnected_;
		App::ConfigFile					configFile_;
  public:
    ConnectionMenu(std::string const &imagePath);
    ~ConnectionMenu();
    void	initialize();
    void	onPressedKey(sf::Event);
    void	update(Network::Packet const &packet);
    void	activateCheatCode();
    void	exitMenu();
    void	applyForm();
		void	applyError();
	private:
		void	setHideGUI(bool);
		void	initFunctions();
		void	connectionSuccess(Network::Packet const &);
		void	connectionError(Network::Packet const &);
		void	handleDisconnection(Network::Packet const &);
  };
}

#endif
