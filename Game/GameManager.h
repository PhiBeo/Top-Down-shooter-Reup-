#pragma once
#include "Collidable.h"
#include "Player.h"
#include "Bullet.h"
#include "Tilemap.h"
#include "EnemyPool.h"
#include "Pistol.h"
#include "Rifle.h"

class GameManager
{
public:
	static GameManager* getGame(sf::RenderWindow* window);
	virtual ~GameManager();

	void Load();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
	void Unload();

	void RenderUI(sf::RenderTarget* target);
	sf::View* getView();

	void addColliable(Collidable* collide);

	bool isOver();
	bool isReachGoal();

private:
	static GameManager* game;
	GameManager(sf::RenderWindow* window);

	sf::Font font;
	sf::RenderWindow* _window;
	sf::View* _mainView;

	Player* _player;
	Tilemap* _map;
	Pistol* _pistol;
	Rifle* _rifle;
	EnemyPool* _enemies;
	BulletPool* _bullets;

	std::vector<Collidable*> collidables;
};

