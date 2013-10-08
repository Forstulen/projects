#ifndef		__ASSETSOUNDINFORMATION__
#define		__ASSETSOUNDINFORMATION__

#include	<SFML/Audio.hpp>

namespace	Asset
{
	class AssetSoundInformation
	{

		sf::SoundBuffer		*sound_;
		std::string				name_;
		bool							loop_;


	public:
		AssetSoundInformation();
		~AssetSoundInformation();

		sf::SoundBuffer	const &getSound() const;
		const std::string &	getName() const;
		bool				getLoop() const;

		void				setSound(sf::SoundBuffer *);
		void				setName(const std::string &);
		void				setLoop(bool);
	};
}

#endif	//	__ASSETSOUNDINFORMATION__