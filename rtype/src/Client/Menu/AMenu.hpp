#ifndef AMENU_HPP
#define AMENU_HPP

#include <list>
#include "AState.hpp"
#include "Cursor.hpp"
#include "Packet.hpp"
#include "TCPClient.hpp"
#include "Mutex.hpp"

namespace Menu
{
  class IWidget;
  class AMenu : public App::AState
  {
  protected:
    Cursor													cursor_;
    std::list<IWidget*>							widgetList_;
		sf::Sprite											sprite_;
		sf::Sound												soundOk_;
		Network::TCPClient							*socket_;
		Thread::Mutex										mutex_;
    bool		cursorToUpdate_;
  public:
		AMenu(std::string const &imagePath);
    virtual ~AMenu() {}
    void						addWidget(IWidget *widget);
    void						removeWidget(IWidget *);
    void						draw(sf::RenderWindow *window);
    void						setCursorToUpdate(bool);
    virtual void		update(float time);
    virtual void		onPressedKey(sf::Event key) = 0;
    virtual void		update(Network::Packet const &packet) = 0;
    virtual void		activateCheatCode() = 0;
  };
}
  
#endif
