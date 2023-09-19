#include "GameManager.h"
#include "Global.h"
#include "DrawText.h"

GameManager* GameManager::game = 0;

GameManager::GameManager(sf::RenderWindow* window) :
	_window(window),
	_player(nullptr),
	_map(nullptr),
	_mainView(nullptr),
	_pistol(nullptr),
	_rifle(nullptr),
	_enemies(nullptr),
	_bullets(nullptr)
{
	if (!font.loadFromFile(GAME_FONT))
		std::cout << "fail to load: GAME_FONT" << std::endl;
}

GameManager* GameManager::getGame(sf::RenderWindow* window)
{
	if (game == 0)
	{
		game = new GameManager(window);
	}

	return game;
}

GameManager::~GameManager()
{
	delete game;
	game = nullptr;
}

void GameManager::Load()
{
	srand(time(NULL));

	_mainView = new sf::View;
	_mainView->setSize(_window->getSize().x, _window->getSize().y);

	_player = Player::getPlayer(_window);
	addColliable(_player);
	_map = Tilemap::getMap();
	_enemies = new EnemyPool();
	_bullets = new BulletPool();
	_bullets->Load();

	_pistol = new Pistol(_bullets);
	_pistol->Load();
	_rifle = new Rifle(_bullets);
	_rifle->Load();

	_map->Load();
	_player->Load();
	_mainView->setCenter(_player->getPosition());
	_enemies->Load();

	_player->addGun(_pistol);
	_player->addGun(_rifle);
}

void GameManager::Update(float deltaTime)
{
	_window->setView(*_mainView);
	_map->Update(deltaTime);
	_player->Update(deltaTime);
	_enemies->Update(deltaTime);
	_mainView->setCenter(_player->getPosition());

	_bullets->Update(deltaTime);
	_pistol->Update(deltaTime);
	_rifle->Update(deltaTime);
	
	int numCollidable = collidables.size();

	for (int i = 0; i < numCollidable; ++i)
	{
		for (int n = i + 1; n < numCollidable; ++n)
		{
			if (collidables[i]->didCollide(collidables[n]))
			{
				collidables[i]->onCollision(collidables[n]);
				collidables[n]->onCollision(collidables[i]);
			}
		}
	}
}

void GameManager::Render(sf::RenderTarget* target)
{
	//game
	_map->Render(target);
	_bullets->Render(target);
	_player->Render(target);
	_enemies->Render(target);
	_pistol->Render(target);
	_rifle->Render(target);
	
	//UI
	RenderUI(target);
}
	
void GameManager::Unload()
{
	collidables.clear();

	_player->Unload();

	_map->Unload();

	delete _mainView;
	_mainView = nullptr;

	_enemies->Unload();
	delete _enemies;
	_enemies = nullptr;

	_pistol->Unload();
	delete _pistol;
	_pistol = nullptr;

	_rifle->Unload();
	delete _rifle;
	_rifle = nullptr;

	_bullets->Unload();
}

void GameManager::RenderUI(sf::RenderTarget* target)
{
	target->setView(_window->getDefaultView());
	_enemies->RenderUI(target);
	drawText("Press B to change weapon", sf::Vector2f(SCREEN_OFFSET * 2, SCREEN_HEIGHT - SCREEN_OFFSET), 30, target, font);
}

sf::View* GameManager::getView()
{
	return _mainView;
}

void GameManager::addColliable(Collidable* collide)
{
	collidables.push_back(collide);
}

bool GameManager::isOver()
{
	return _player->isAlive();
}

bool GameManager::isReachGoal()
{
	return Tilemap::getMap()->playerReachGoal(_player->getGlobalBound());
}
