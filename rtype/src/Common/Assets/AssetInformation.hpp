#ifndef		ASSETINFORMATION_HPP
#define		ASSETINFORMATION_HPP

#include	<vector>
#include	<string>

namespace	Asset
{
  enum		eAnimType
    {
      LOOP,
      LINEAR,
      STATIC
    };

  template <typename T>
  class				AssetInformation
  {
    std::string			name_;
    std::vector<T>		itemsVector_;
    std::vector<const T	&(AssetInformation::*)(unsigned int &, bool &) const> ptr_;
    int				width_;
    int				height_;
    float			interval_;
    unsigned int		startIndex_;
    eAnimType			behavior_;

  public:
    AssetInformation()
      : name_(""),
	width_(0),
	height_(0),
	interval_(0),
	startIndex_(0)
    {
      ptr_.push_back(&AssetInformation::getLinear);
      ptr_.push_back(&AssetInformation::getLoop);
      ptr_.push_back(&AssetInformation::getStatic);
    }

    ~AssetInformation()
    {
    }

  public:
    void			setStartIndex(unsigned int ind)
    {
      this->startIndex_ = ind;
    }

    void			setItems(const T rect)
    {
      this->itemsVector_.push_back(rect);
    }

    void			setName(const std::string & name)
    {
      this->name_ = name;
    }

    void			setInterval(float const interval)
    {
      this->interval_ = interval;
    }

    void			setWidth(int width)
    {
      this->width_ = width;
    }

    void			setHeight(int height)
    {
      this->height_ = height;
    }

    void			setAnimType(eAnimType type)
    {
      this->behavior_ = type;
    }

  public:
    const T &			getItems(unsigned int index) const
    {
      if (index > this->itemsVector_.size() - 1)
	return this->itemsVector_.at(this->itemsVector_.size() - 1);
      return this->itemsVector_.at(index);
    }

    const T &			getNextItems(unsigned int &index, bool &direction) const
    {
      return (this->*(this->ptr_[this->behavior_]))(index, direction);
    }

    int				getStartIndex() const
    {
      return this->startIndex_;
    }

    const std::string &		getName() const
    {
      return this->name_;
    }

    float			getInterval() const
    {
      return this->interval_;
    }

    int				getWidth() const
    {
      return this->width_;
    }

    int				getHeight() const
    {
      return this->height_;
    }

    eAnimType		getAnimType() const
    {
      return this->behavior_;
    }

  private:
    const T&			getLinear(unsigned int &index, bool &direction) const
    {
      if (!direction)
		index = !index ? this->startIndex_: index - 1;
      else
		index = index + 1 > this->itemsVector_.size() - 1 ? this->startIndex_ : index + 1;
	  if (index >= this->itemsVector_.size())
		  return this->itemsVector_.at(this->itemsVector_.size() - 1);
      return this->itemsVector_.at(index);
    }

    const T&			getLoop(unsigned int &index, bool &direction) const
    {
      if ((!index && !direction) || ((index >= this->itemsVector_.size() - 1) && direction))
			direction = !direction;
      index = direction ? index + 1 : index - 1;
		if (index >= this->itemsVector_.size())
		  return this->itemsVector_.at(this->itemsVector_.size() - 1);
      return this->itemsVector_.at(index);
    }

    const T&			getStatic(unsigned int &index, bool &direction) const
    {
      if (!direction)
		index = !index ? index: index - 1;
      else
		index = index + 1 >= this->itemsVector_.size() ? index : index + 1;
	  if (index >= this->itemsVector_.size())
		  return this->itemsVector_.at(this->itemsVector_.size() - 1);
      return this->itemsVector_.at(index);
    }
  };
}

#endif				/* ASSETINFORMATION_HPP */
