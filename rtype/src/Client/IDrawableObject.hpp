#ifndef IDRAWABLEOBJECT_HPP
#define IDRAWABLEOBJECT_HPP

class IDrawableObject
{
public:
  virtual ~IDrawableObject() {}
  virtual void					draw(sf::RenderWindow *window) = 0;
  virtual sf::Vector2f			getPosition() const = 0;
  virtual void					update(float) = 0;
  virtual void					setPosition(sf::Vector2f position) = 0;
};

#endif
