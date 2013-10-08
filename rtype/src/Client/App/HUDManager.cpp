#include <iostream>
#include "HUDManager.hpp"
#include "Conversions.hpp"


namespace App
{
	HUDManager::HUDManager() {}

	HUDManager::~HUDManager() {}

	void	HUDManager::draw(sf::RenderWindow * window)
	{
		if (window)
		{
			window->Draw(this->beamLevel_);
			window->Draw(this->mask_);
			window->Draw(this->p1ScoreFrame_);
			window->Draw(this->playerScoreMap_[0]);
			window->Draw(this->p2ScoreFrame_);
			window->Draw(this->playerScoreMap_[1]);
			window->Draw(this->p3ScoreFrame_);
			window->Draw(this->playerScoreMap_[2]);
			window->Draw(this->p4ScoreFrame_);
			window->Draw(this->playerScoreMap_[3]);
		}
	}

	void	HUDManager::initHUD(float width, float height)
	{

		this->p1ScoreFrame_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation("scorep1").getImage());
			this->p1ScoreFrame_.SetSubRect(Asset::AssetManager::getInstance().getAssetImageInformation("scorep1").getItems(Asset::AssetManager::getInstance().getAssetImageInformation("scorep1").getStartIndex()));
			this->p1ScoreFrame_.SetPosition(0, height - this->p1ScoreFrame_.GetSize().y);

			this->p2ScoreFrame_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation("scorep2").getImage());
			this->p2ScoreFrame_.SetSubRect(Asset::AssetManager::getInstance().getAssetImageInformation("scorep2").getItems(Asset::AssetManager::getInstance().getAssetImageInformation("scorep2").getStartIndex()));
			this->p2ScoreFrame_.SetPosition(this->p1ScoreFrame_.GetPosition().x + this->p1ScoreFrame_.GetSize().x - 10, height - this->p2ScoreFrame_.GetSize().y);

			this->beamLevel_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation("hudpart1").getImage());
			this->beamLevel_.SetSubRect(Asset::AssetManager::getInstance().getAssetImageInformation("hudpart1").getItems(Asset::AssetManager::getInstance().getAssetImageInformation("hudpart1").getStartIndex()));
			this->beamLevel_.SetPosition(this->p2ScoreFrame_.GetPosition().x + this->p2ScoreFrame_.GetSize().x, height - this->beamLevel_.GetSize().y);

			this->p3ScoreFrame_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation("scorep3").getImage());
			this->p3ScoreFrame_.SetSubRect(Asset::AssetManager::getInstance().getAssetImageInformation("scorep3").getItems(Asset::AssetManager::getInstance().getAssetImageInformation("scorep3").getStartIndex()));
			this->p3ScoreFrame_.SetPosition(this->beamLevel_.GetPosition().x + this->beamLevel_.GetSize().x, height - this->p3ScoreFrame_.GetSize().y);

			this->p4ScoreFrame_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation("scorep4").getImage());
			this->p4ScoreFrame_.SetSubRect(Asset::AssetManager::getInstance().getAssetImageInformation("scorep4").getItems(Asset::AssetManager::getInstance().getAssetImageInformation("scorep4").getStartIndex()));
			this->p4ScoreFrame_.SetPosition(this->p3ScoreFrame_.GetPosition().x + this->p3ScoreFrame_.GetSize().x - 10, height - this->p4ScoreFrame_.GetSize().y);


		this->font_.LoadFromFile(App::fontPath);
		this->playerScoreMap_[0].SetText("0");
		this->playerScoreMap_[0].SetScale(0.5f, 0.5f);
		this->playerScoreMap_[0].SetColor(sf::Color(255, 255, 255));
		this->playerScoreMap_[0].Move(this->p1ScoreFrame_.GetPosition().x + this->p1ScoreFrame_.GetSize().x / 2, height - (this->p1ScoreFrame_.GetSize().y / 2) - 10);

		this->playerScoreMap_[1].SetText("0");
		this->playerScoreMap_[1].SetScale(0.5f, 0.5f);
		this->playerScoreMap_[1].SetColor(sf::Color(255, 255, 255));
		this->playerScoreMap_[1].Move(this->p2ScoreFrame_.GetPosition().x + this->p1ScoreFrame_.GetSize().x / 2, height - (this->p2ScoreFrame_.GetSize().y / 2) - 10);

		this->playerScoreMap_[2].SetText("0");
		this->playerScoreMap_[2].SetScale(0.5f, 0.5f);
		this->playerScoreMap_[2].SetColor(sf::Color(255, 255, 255));
		this->playerScoreMap_[2].Move(this->p3ScoreFrame_.GetPosition().x + this->p1ScoreFrame_.GetSize().x / 2, height - (this->p3ScoreFrame_.GetSize().y / 2) - 10);

		this->playerScoreMap_[3].SetText("0");
		this->playerScoreMap_[3].SetScale(0.5f, 0.5f);
		this->playerScoreMap_[3].SetColor(sf::Color(255, 255, 255));
		this->playerScoreMap_[3].Move(this->p4ScoreFrame_.GetPosition().x + this->p4ScoreFrame_.GetSize().x / 2, height - (this->p4ScoreFrame_.GetSize().y / 2) - 10);

	}

	void	HUDManager::resetHUD()
	{
		this->playerScoreMap_[0].SetText("0");
		this->playerScoreMap_[1].SetText("0");
		this->playerScoreMap_[2].SetText("0");
		this->playerScoreMap_[3].SetText("0");
	}

	void	HUDManager::updateBeam(float time)
	{
			if (time <= 1.2f)
				this->mask_ = sf::Shape::Rectangle(this->beamLevel_.GetPosition().x + 6.0f, this->beamLevel_.GetPosition().y + 6.0f, 
											this->beamLevel_.GetPosition().x + 5 +(212.0f / 1.2f) * time, this->beamLevel_.GetPosition().y + 15.0f, sf::Color(16, 78, 139), 0, sf::Color(214, 214, 214));
			else
				this->mask_ = sf::Shape::Rectangle(this->beamLevel_.GetPosition().x + 6.0f, this->beamLevel_.GetPosition().y + 6.0f, 
											this->beamLevel_.GetPosition().x + 216.0f, this->beamLevel_.GetPosition().y + 15.0f, sf::Color(16, 78, 139), 0, sf::Color(214, 214, 214));
	}

	void	HUDManager::updateScore(const Network::Packet & data)
	{
		const Protocol::ScoringData		*content = data.getData<const Protocol::ScoringData*>();
	
		if (this->playerScoreMap_.find(content->id) != this->playerScoreMap_.end())
		{
			std::string						conversion;

			Conversions::toString(content->score, conversion);

			this->playerScoreMap_[content->id].SetText(conversion);
		}
	}

	const std::string		HUDManager::getPlayerScore(int player) const
	{
		std::string			tmp("0");

		if (player < this->playerScoreMap_.size())
			tmp = this->playerScoreMap_.at(player).GetText();
		return tmp;
	}

	void					HUDManager::setPlayerDisconnection(const Network::Packet &data)
	{
		const unsigned int	player = data.getData<const unsigned int>();

		if (player < this->playerScoreMap_.size())
			this->playerScoreMap_[player].SetText("Offline");
	}
}
