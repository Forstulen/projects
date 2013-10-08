#ifndef IWIDGET_HPP
#define IWIDGET_HPP

#include "IDrawableObject.hpp"

namespace Menu
{
  class IWidget : public IDrawableObject
  {
  public:
    virtual ~IWidget() {}
    virtual void			action(sf::Event) = 0;
    virtual IWidget			*getNextWidget() const = 0;
    virtual IWidget			*getPrevWidget() const = 0;
    virtual void			setNextWidget(IWidget*) = 0;
    virtual void			setPrevWidget(IWidget*) = 0;
		virtual float			getVerticalCenter() const = 0;
		virtual bool			isHide() = 0;
		virtual void			setHide(bool) = 0;
  };
}

#endif
