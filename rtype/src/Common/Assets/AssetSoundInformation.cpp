#include "AssetSoundInformation.hpp"

namespace	Asset
{
	AssetSoundInformation::AssetSoundInformation(void)
		:sound_(0),
		name_(""),
		loop_(false)
	{
	}


	AssetSoundInformation::~AssetSoundInformation(void)
	{
	}


	sf::SoundBuffer	const		&AssetSoundInformation::getSound() const
	{
		return *this->sound_;
	}
		
	const std::string &			AssetSoundInformation::getName() const
	{
		return this->name_;
	}
		
	bool						AssetSoundInformation::getLoop() const
	{
		return this->loop_;
	}

	void						AssetSoundInformation::setSound(sf::SoundBuffer * sound)
	{
		this->sound_ = sound;
	}
		
	void						AssetSoundInformation::setName(const std::string & name)
	{
		this->name_ = name;
	}
		
	void						AssetSoundInformation::setLoop(bool opt)
	{
		this->loop_ = opt;
	}
}
