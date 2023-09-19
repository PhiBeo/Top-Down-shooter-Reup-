#include "BulletPool.h"
#include "GameManager.h"

BulletPool::BulletPool() :
	Entity(),
	_nextBulletIndex(0)
{
	const int numOfBullet = 50;
	for (int i = 0; i < numOfBullet; i++)
	{
		Bullet* bullet = new Bullet();
		bullet->Load();
		_bullets.push_back(bullet);
		GameManager::getGame(nullptr)->addColliable(bullet);
	}
}

BulletPool::~BulletPool()
{
}

void BulletPool::Load()
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->Load();
	}
	_nextBulletIndex = 0;
}

void BulletPool::Update(float deltaTime)
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->Update(deltaTime);
	}
}

void BulletPool::Render(sf::RenderTarget* target)
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->Render(target);
	}
}

void BulletPool::Unload()
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->Unload();
		delete _bullets[i];
		_bullets[i] = nullptr;
	}
	_bullets.clear();
}

std::vector<Bullet*>& BulletPool::getBulletMag()
{
	return _bullets;
}

Bullet* BulletPool::getNextBullet(int maxAmmo)
{
	Bullet* nextBullet = nullptr;
	nextBullet = _bullets[_nextBulletIndex];
	_nextBulletIndex = (_nextBulletIndex + 1) % (int)_bullets.size();

	return nextBullet;
}

int BulletPool::getCurrentUsedBullet()
{
	return _nextBulletIndex;
}
