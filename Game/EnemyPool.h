#pragma once
#include "Enemy.h"

class EnemyPool
{
public:
	void Load();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
	void Unload();
	void RenderUI(sf::RenderTarget* target);

	void EnemiesOverlap();

private:
	std::vector<Enemy*> _enemies;

};

