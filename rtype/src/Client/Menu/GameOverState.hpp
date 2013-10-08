#ifndef			GAMEOVERSTATE
#define			GAMEOVERSTATE

#include <SFML/Graphics.hpp>
#include "EventManager.hpp"
#include "StateManager.hpp"
#include "HUDManager.hpp"
#include "AMenu.hpp"
#include "Button.hpp"
#include "Label.hpp"


namespace	Menu
{

class GameOverMenu : public AMenu
{
	Button<GameOverMenu>		okButton_;
	Label						deathMessage_;
	Label						gameOverMessage_;
	Label						p1Score_;
	Label						p2Score_;
	Label						p3Score_;
	Label						p4Score_;

public:
	GameOverMenu(const std::string &);
	virtual ~GameOverMenu(void);
	void				initialize();
	void				displayScore();
    virtual void		onPressedKey(sf::Event key) ;
    virtual void		update(Network::Packet const &packet);
    virtual void		activateCheatCode();
	void				continueGame();
};

}
#endif		//	GAMEOVERSTATE