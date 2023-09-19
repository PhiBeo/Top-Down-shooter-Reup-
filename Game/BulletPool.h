#pragma once
#include "Entity.h"
#include "Bullet.h"

class BulletPool : public Entity
{
public:
	BulletPool();
	virtual ~BulletPool();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	void Unload() override;

	std::vector<Bullet*>& getBulletMag();
	Bullet* getNextBullet(int maxAmmo);
	int getCurrentUsedBullet();

private:
	std::vector<Bullet*> _bullets;
	int _nextBulletIndex;
};

