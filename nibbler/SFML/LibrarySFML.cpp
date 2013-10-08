//
// LibrarySFML.cpp for  in /home/tholim_r//nibbler-2014-benram_s/SFML
//
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
//
// Started on  Sat Mar 12 16:58:30 2011 romain tholimet
// Last update Sun Mar 20 19:51:53 2011 romain tholimet
//

#include		<cstdlib>
#include		"LibrarySFML.hh"

LibrarySFML::LibrarySFML()
  :_window(NULL),
   _width(0),
   _height(500),
   _pause(false),
   _gameOver(false),
   _imageWidth(15),
   _imageHeight(15)
{
  this->_name = "SFML";
}

LibrarySFML::~LibrarySFML()
{
}

// load the sprites into a map
void		LibrarySFML::initImages()
{
  std::ostringstream	oss;

  for (unsigned int count = 0; count <= 20; ++count)
    {
      std::ostringstream	oss;

      oss << "./resources/SFML/" << this->_core->getName() << "images/elem" << count << ".png";
      sf::Image	elem;
      elem.LoadFromFile(oss.str());
      elem.SetSmooth(false);
      this->_images[count] = elem;
    }
  oss << "./resources/SFML/" << this->_core->getName() << "images/score.png";
  this->_imageScore.LoadFromFile(oss.str());
}

// On charge les sprites dans un vector avec un vector correspondant de valeurs
// Ainsi on peut verifier si un sprite a change de valeur en cours de partie
// et ne reactualiser que ceux qui ont modifie (ex : les murs ne changent pas ...) // -> Romain il parle pas anglais
void		LibrarySFML::initSprites()
{
  Grid			*game;

  game = this->_core->getGrid();
  for (unsigned int lines = 0; lines < game->getSizeX(); ++lines)
    for (unsigned int cols = 0; cols < game->getSizeY(); ++cols)
      {
  	sf::Sprite	sprite;

  	sprite.SetImage(this->_images[game->getPoint(lines, cols)]);
  	sprite.SetPosition(lines * this->_imageWidth + this->_paddingLeft, cols * this->_imageHeight + this->_paddingTop);
	this->_sprites.push_back(sprite);
	this->_values.push_back(game->getPoint(lines, cols));
	this->_window->Draw(sprite);
      }
}

//On set la taille de l'ecran en fonction de la grille
void		LibrarySFML::setScreenSize(const Grid * const grid)
{

  this->_width = 50 + (grid->getSizeX() * this->_imageWidth) + 180;
  if (50 + (grid->getSizeY() * this->_imageHeight) > this->_height)
    this->_height = 50 + (grid->getSizeY() * this->_imageHeight);
}

//Settings de la window
void		LibrarySFML::initWindow()
{
  this->_window->SetFramerateLimit(60);
  this->_window->ShowMouseCursor(false);
  this->_window->SetPosition(0, 0);
  this->_window->EnableKeyRepeat(true);
  this->_window->UseVerticalSync(false);
  this->_window->Clear(sf::Color::Black);
}

//n initialise la fenetre, le jeu a charge, les images et sprites
int		LibrarySFML::init(ACore * const game, int ac, char **av)
{
  this->_core = game;
  this->setScreenSize(this->_core->getGrid());
  if (!(this->_window = new sf::RenderWindow(sf::VideoMode(this->_width, this->_height, 32), this->_core->getTitle(), sf::Style::Close)))
    throw nibblerException("Cannot create a Window SFML !");
  this->_paddingLeft = ((this->_width - 180 - (this->_imageWidth * this->_core->getGrid()->getSizeX())) / 2);
  this->_paddingTop = ((this->_height - (this->_imageHeight * this->_core->getGrid()->getSizeY())) / 2);
  this->initImages();
  this->initWindow();
  this->initSprites();
  this->setDescription();
  return (0);
}

//On detruit les objets instancies;
void		LibrarySFML::destroy()
{
  this->_window->Close();

  if (this->_window)
    delete this->_window;
}

//On effectue un refresh des sprites sur ceux qui ont ete modifie pour augmenter la fluidite
void		LibrarySFML::refreshSprite()
{
  Grid			*game;
  unsigned int		count = 0;

  game = this->_core->getGrid();
  for (unsigned int lines = 0; lines < game->getSizeX(); ++lines)
    for (unsigned int cols = 0; cols < game->getSizeY(); ++cols)
      {
  	sf::Sprite	sprite;

	if (this->_values[count] != game->getPoint(lines, cols))
	  {
	    sprite.SetImage(this->_images[game->getPoint(lines, cols)]);
	    sprite.SetPosition(lines * this->_imageWidth + this->_paddingLeft, cols * this->_imageHeight + this->_paddingTop);
	    this->_values[count] = game->getPoint(lines, cols);
	    this->_sprites[count] = sprite;
	    this->_window->Draw(this->_sprites[count]);
	  }
	++count;
      }
}


//On set le score
void		LibrarySFML::setScore(bool bestScore, size_t posY, sf::String & Score)
{
  std::ostringstream	oss;
  std::string		tmp;

  if (!bestScore)
    oss << this->_core->getScore();
  else
    oss << this->_core->getBestScore();
  tmp = oss.str();
  Score.SetText(tmp);
  Score.SetSize(18);
  Score.SetColor(sf::Color::Black);
  Score.SetX(this->_width - 120);
  Score.SetY(posY);
}

void		LibrarySFML::setDescription()
{
  sf::String	Description;

  Description.SetText(this->_core->getDescription());
  Description.SetSize(12);
  Description.SetColor(sf::Color::White);
  Description.SetX(this->_width - 190);
  Description.SetY(180);
  this->_window->Draw(Description);
}

void		LibrarySFML::setGameBoySprite(sf::Sprite & gameBoy)
{
  gameBoy.SetImage(this->_imageScore);
  gameBoy.SetPosition(this->_width - 180, 50);
}

//On refresh la fenetre et son score
void		LibrarySFML::refresh()
{
  sf::String		Score;
  sf::String		BestScore;
  sf::Sprite		gameBoy;

  this->_frameRate = this->_core->getSpeed() / 1000.0f;
  this->refreshSprite();
  this->setScore(false, 80, Score);
  this->setScore(true, 137, BestScore);
  this->setGameBoySprite(gameBoy);
  this->_window->Draw(gameBoy);
  this->_window->Draw(Score);
  this->_window->Draw(BestScore);
  this->_window->Display();
}

void		LibrarySFML::restartScreen()
{
  this->_gameOver = false;
  this->_core->restartGame();
  this->initWindow();
  this->_window->Clear(sf::Color::Black);
  this->setDescription();
  this->initSprites();
  this->refreshSprite();
}

//Methode de gameOver
void		LibrarySFML::gameOver()
{
  sf::String		gameOver;

  gameOver.SetText("GAME OVER !\n");
  gameOver.SetColor(sf::Color::White);
  gameOver.SetSize(18);
  gameOver.SetPosition(this->_width - 170, 10);
  this->_window->Draw(gameOver);
  this->_window->Display();
}

//Gestion de touches
KeyGame::eKeyCode	LibrarySFML::getKey(sf::Key::Code code)
{
  KeyGame::eKeyCode	currentKey = KeyGame::NONE;

  switch (code)
    {
    case sf::Key::Escape :
      this->_window->Close();
      break ;
    case sf::Key::Up :
      currentKey = KeyGame::UP;
      break ;
    case sf::Key::Down :
      currentKey = KeyGame::DOWN;
      break ;
    case sf::Key::Left :
      currentKey = KeyGame::LEFT;
      break ;
    case sf::Key::Right :
      currentKey = KeyGame::RIGHT;
      break ;
    case sf::Key::Space :
      currentKey = KeyGame::SPACE;
      break ;
    case sf::Key::P :
      {
	if (this->_pause)
	  this->_pause = false;
	else
	  this->_pause = true;
	break ;
      }
    case sf::Key::R :
      {
	this->_gameOver = false;
	this->restartScreen();
      }
    }
  return currentKey;
}

//La methode clef du jeu, elle recuperer les inputs et les communique au core pour traitement et joue les sons
int		LibrarySFML::run()
{
  sf::Clock		timer;
  KeyGame::eKeyCode	currentKey = KeyGame::NONE;
  bool			gameOver = false;
  int			action = 0;

  while (this->_window->IsOpened())
    {
      sf::Event event;
      while (this->_window->GetEvent(event))
	{
	  if (event.Type == sf::Event::Closed)
	    this->_window->Close();
	  if (event.Type == sf::Event::KeyPressed)
	    currentKey = getKey(event.Key.Code);
	}
      if (timer.GetElapsedTime() >= this->_frameRate && !this->_pause && !this->_gameOver)
	{
	  if ((action = this->_core->move(currentKey)) == -1)
	    {
	      this->gameOver();
	      this->_gameOver = true;
	    }
	  else
	    {
	      currentKey = KeyGame::NONE;
	      this->refresh();
	      timer.Reset();
	    }
	}
    }
}

//La fonction demanglee pour avoir un point d'entree avec dlopen
extern "C" ALibrary*	entry()
{
  return (new LibrarySFML);
}
