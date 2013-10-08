#include "GameOverState.hpp"

namespace	Menu
{

GameOverMenu::GameOverMenu(const std::string & image)
	:AMenu(image),
	okButton_(this, "../../resource/defused.ttf", "Press Escape", 30, sf::Vector2f(190, 420), &GameOverMenu::continueGame),
	deathMessage_("../../resource/defused.ttf", "Ennemies are stronger than you expected Noob !", 22, sf::Vector2f(0, 0), 0),
	p1Score_("../../resource/defused.ttf", "Player1 Score : ", 30, sf::Vector2f(170, 200), 9),
	gameOverMessage_("../../resource/defused.ttf", "Game Over", 40, sf::Vector2f(200, 100), 0),
	p2Score_("../../resource/defused.ttf", "Player2 Score : ", 30, sf::Vector2f(170, 250), 9),
	p3Score_("../../resource/defused.ttf", "Player3 Score : ", 30, sf::Vector2f(170, 300), 9),
	p4Score_("../../resource/defused.ttf", "Player4 Score : ", 30, sf::Vector2f(170, 350), 9)
{
	this->okButton_.setKeyPressed(sf::Key::Escape);
	p1Score_.setColor(sf::Color(0, 82, 156));
	p2Score_.setColor(sf::Color(206, 0, 0));
	p3Score_.setColor(sf::Color(255, 235, 17));
	p4Score_.setColor(sf::Color(0, 165, 0));

	this->addWidget(&this->okButton_);
	this->addWidget(&this->deathMessage_);
	this->addWidget(&this->gameOverMessage_);
	this->addWidget(&this->p1Score_);
	this->addWidget(&this->p2Score_);
	this->addWidget(&this->p3Score_);
	this->addWidget(&this->p4Score_);

	this->okButton_.setNextWidget(&this->okButton_);
	this->okButton_.setPrevWidget(&this->okButton_);
}

GameOverMenu::~GameOverMenu(void)
{
}

void	GameOverMenu::initialize()
{
	this->cursor_.setCurrentWidget(&this->okButton_);
	this->displayScore();
	App::EventManager::getInstance().setToProcess(true);
}

void	GameOverMenu::onPressedKey(sf::Event key)
{
	if (key.Type == sf::Event::KeyPressed && key.Key.Code == sf::Key::Escape)
		this->cursor_.getCurrentWidget()->action(key);
}

void	GameOverMenu::update(Network::Packet const &packet)
{

}

void	GameOverMenu::displayScore()
{
	if (!App::HUDManager::getInstance().getPlayerScore(0).empty())
		this->p1Score_.setTextEdit(App::HUDManager::getInstance().getPlayerScore(0));
	if (!App::HUDManager::getInstance().getPlayerScore(1).empty())
		this->p2Score_.setTextEdit(App::HUDManager::getInstance().getPlayerScore(1));
	if (!App::HUDManager::getInstance().getPlayerScore(2).empty())
		this->p3Score_.setTextEdit(App::HUDManager::getInstance().getPlayerScore(2));
	if (!App::HUDManager::getInstance().getPlayerScore(3).empty())
		this->p4Score_.setTextEdit(App::HUDManager::getInstance().getPlayerScore(3));
}

void	GameOverMenu::activateCheatCode()
{

}

void	GameOverMenu::continueGame()
{
	App::StateManager::getInstance().changeState(this->nextState_);
}
	
}
