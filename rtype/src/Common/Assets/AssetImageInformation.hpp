#ifndef		__ASSETIMAGEINFORMATION__
#define		__ASSETIMAGEINFORMATION__

#include	<SFML/Graphics.hpp>
#include	<vector>
#include	<string>

#include	"Functor.hpp"
#include	"AssetInformation.hpp"

namespace	Asset
{

  class AssetImageInformation :	public AssetInformation<sf::Rect<int> >
  {
  private:
    sf::Image				*image_;

  public:
    AssetImageInformation();
    ~AssetImageInformation();

  public:
    void			setImage(sf::Image *);

  public:
    sf::Image			&getImage() const;
  };
}

#endif	//	__ASSETIMAGEINFORMATION__

