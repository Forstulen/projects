#ifndef			SOUNDMANAGER
#define			SOUNDMANAGER

#include		<vector>
#include		"AssetManager.hpp"
#include		"AssetSoundInformation.hpp"
#include		"Singleton.hpp"
#include		"AGameObject.hpp"

namespace		Sound
{

class			SoundManager : public Tools::Singleton<SoundManager>
{

	friend class	Tools::Singleton<SoundManager>;

	Asset::AssetManager	&				resources_;
	sf::Sound							music_;
	sf::Sound							charge_;
	std::vector<sf::Sound>				sound_;

	SoundManager();
	SoundManager (const SoundManager&);
	SoundManager& operator=(const SoundManager &);

	void			initSoundSettings();

public:
	~SoundManager();
	void			initMusic(const std::string &);
	void			playSound(const std::string &);
	void			playCharge(const std::string &);
	void			stopCharge();
};
}
#endif		/*	SOUNDMANAGER	*/
