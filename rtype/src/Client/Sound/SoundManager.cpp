#include "SoundManager.hpp"

namespace	Sound
{
	SoundManager::SoundManager(void)
		:resources_(Asset::AssetManager::getInstance())
	{
		this->initSoundSettings();
	}


	SoundManager::~SoundManager(void)
	{
	}

	void		SoundManager::initSoundSettings()
	{
		this->sound_.resize(64);
		for (std::vector<sf::Sound>::iterator it = this->sound_.begin(); it != this->sound_.end(); ++it)
		{
			(*it).SetPitch(1.8f);
			(*it).SetVolume(60.0f);
		}
		this->charge_.SetLoop(true);
	}

	void		SoundManager::initMusic(const std::string & name)
	{	
		if (!name.empty())
		{
			if (this->music_.GetStatus() == sf::Sound::Stopped || this->music_.GetBuffer())
				this->music_.Stop();
			this->music_.SetBuffer(Asset::AssetManager::getInstance().getAssetSoundInformation(name).getSound());
			this->music_.SetVolume(10.0f);
			this->music_.SetLoop(Asset::AssetManager::getInstance().getAssetSoundInformation(name).getLoop());
			this->music_.Play();
		}
	}

	void		SoundManager::playCharge(const std::string & name)
	{
		if (!name.empty())
		{
			this->charge_.SetBuffer(Asset::AssetManager::getInstance().getAssetSoundInformation(name).getSound());
			this->charge_.Play();
		}
	}

	void		SoundManager::stopCharge()
	{
		if (this->charge_.GetStatus() == sf::Sound::Playing)
			this->charge_.Stop();
	}

	void		SoundManager::playSound(const std::string & name)
	{
		if (!name.empty())
			for (std::vector<sf::Sound>::iterator it = this->sound_.begin(); it != this->sound_.end(); ++it)
				if (it->GetStatus() == sf::Sound::Stopped)
				{
					it->SetBuffer(Asset::AssetManager::getInstance().getAssetSoundInformation(name).getSound());
					(*it).Play();
					break;
				}
	}
}