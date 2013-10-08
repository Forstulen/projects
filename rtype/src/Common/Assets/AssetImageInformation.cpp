#include	<iostream>
#include	"AssetImageInformation.hpp"

namespace	Asset
{
  AssetImageInformation::AssetImageInformation(void)
    : image_(0)
  {
  }

  AssetImageInformation::~AssetImageInformation(void)
  {
  }

  void				AssetImageInformation::setImage(sf::Image * image)
  {
    this->image_ = image;
  }

  sf::Image			&AssetImageInformation::getImage() const
  {
    return *this->image_;
  }
}
