#ifndef HUDMANAGER_HPP
#define HUDMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "AssetManager.hpp"
#include "Singleton.hpp"
#include "Packet.hpp"

namespace App
{

	const std::string			fontPath("../../resource/defused.ttf");

	class HUDManager : public Tools::Singleton<HUDManager>
	{
		friend class Tools::Singleton<HUDManager>;

		sf::Sprite				beamLevel_;
		sf::Sprite				p1ScoreFrame_;
		sf::Sprite				p2ScoreFrame_;
		sf::Sprite				p3ScoreFrame_;
		sf::Sprite				p4ScoreFrame_;
		sf::Font				font_;
		sf::Shape				mask_;
		std::map<unsigned int, sf::String>	playerScoreMap_;

	private:
		HUDManager();
		~HUDManager();
		HUDManager(HUDManager&);
		HUDManager& operator=(HUDManager&);
	public:
		void		draw(sf::RenderWindow *);
		void		initHUD(float, float);
		void		resetHUD();
		void		updateBeam(float);
		void		updateScore(const Network::Packet &data);

		const std::string	getPlayerScore(int) const;
		void				setPlayerDisconnection(const Network::Packet &data);

	};
}

#endif	// HUDMANAGER_HPP