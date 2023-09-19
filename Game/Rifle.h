#pragma once
#include "Gun.h"
#include "BulletPool.h"
#include "Player.h"

class Rifle : public Gun
{
public:
	Rifle(BulletPool* magazine);
	virtual ~Rifle();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	void Unload() override;

	bool isUse() override;
	void setPosition(sf::Vector2f position) override;
	void setRotation(float rotation) override;
	void setActive(bool active) override;
	void shoot() override;

private:
	bool _currentlyUse;

	sf::Vector2f _position;
	float _rotation;

	Player* _player;

	BulletPool* _magazine;
	float _bulletCoolDown;

	sf::RectangleShape _gun;
};

