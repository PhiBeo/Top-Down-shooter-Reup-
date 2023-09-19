#include "EnemyPool.h"
#include "Tilemap.h"
#include "Global.h"
#include "GameManager.h"

void EnemyPool::Load()
{
	std::vector<Tile*> enemyTile;
	enemyTile = Tilemap::getMap()->getEnemyTile();

	int numberOfEnemies = (int)enemyTile.size();

	for (int i = 0; i < numberOfEnemies; i++)
	{
		Enemy* newEnemy = new Enemy();
		newEnemy->Load();
		newEnemy->setPosition(enemyTile[i]->getPosition());
		_enemies.push_back(newEnemy);
		GameManager::getGame(nullptr)->addColliable(newEnemy);
	}
}

void EnemyPool::Update(float deltaTime)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->Update(deltaTime);
	}

	//EnemiesOverlap();
}

void EnemyPool::Render(sf::RenderTarget* target)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->isAlive())
		{
			_enemies[i]->Render(target);
		}	
	}
}

void EnemyPool::Unload()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		delete _enemies[i];
		_enemies[i] = nullptr;
	}

	_enemies.clear();
}

void EnemyPool::RenderUI(sf::RenderTarget* target)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->RenderUI(target);
	}
}

void EnemyPool::EnemiesOverlap()
{
	for (int i = 0; i < _enemies.size() - 1; i++)
	{
		for (int j = 1; j < _enemies.size(); j++)
		{
			if (i != j)
			{
				if (_enemies[i]->getEnemyRect().intersects(_enemies[j]->getEnemyRect()))
				{
					float minX = std::min(_enemies[i]->getEnemyRect().left + _enemies[i]->getEnemyRect().width, _enemies[j]->getEnemyRect().left + _enemies[j]->getEnemyRect().width);
					float minY = std::min(_enemies[i]->getEnemyRect().top + _enemies[i]->getEnemyRect().height, _enemies[j]->getEnemyRect().top + _enemies[j]->getEnemyRect().height);

					float maxX = std::max(_enemies[i]->getEnemyRect().left, _enemies[j]->getEnemyRect().left);
					float maxY = std::max(_enemies[i]->getEnemyRect().top, _enemies[j]->getEnemyRect().top);

					float distHoriz = minX - maxX;
					float distVert = minY - maxY;

					if (abs(distHoriz) <= _enemies[i]->getEnemyRect().width / 2)
					{
						_enemies[i]->setPosition(sf::Vector2f(_enemies[i]->getPosition().x - distHoriz, _enemies[i]->getPosition().y));
					}
					else if (abs(distVert) <= _enemies[i]->getEnemyRect().height / 2)
					{
						_enemies[i]->setPosition(sf::Vector2f(_enemies[i]->getPosition().x, _enemies[i]->getPosition().y - distVert));
					}
					//std::cout << "enemy " << i << " Colide with " << j << std::endl;
				}
			}
		}
	}
}
