#pragma once
#include "Gun.h"
#include "BulletPool.h"
#include "Player.h"

class Pistol : public Gun
{
public:
	Pistol(BulletPool* magazine);
	virtual ~Pistol();

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

