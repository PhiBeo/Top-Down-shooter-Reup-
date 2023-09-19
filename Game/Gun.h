#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"

class Gun
{
public:
	Gun(int id, float fireRate, int maxAmmo);
	virtual ~Gun();

	virtual void Load() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
	virtual void Unload() = 0;

	virtual bool isUse() = 0;
	virtual void setPosition(sf::Vector2f position) = 0;
	virtual void setRotation(float rotation) = 0;
	virtual void setActive(bool active) = 0;
	virtual void shoot() = 0;

	virtual int getId() const;
	virtual float getFireRate() const;
	virtual int getMaxAmmo() const;

private:
	int _id;
	float _fireRate;
	int _maxAmmo;
};

