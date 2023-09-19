#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Enums.h"
#include "Collidable.h"

class Bullet : public Entity, public Collidable
{
public :
	Bullet();
	virtual ~Bullet();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	void Unload() override;

	const sf::Vector2f& getPosition() const override;
	int getType() const override;
	void onCollision(Collidable* collidable) override;

	void setActive(sf::Vector2f position, float rotation, EntityType type, float lifeTime = 2.f);
	bool isActive();

private:
	sf::Vector2f _position;
	float _rotation;
	float _lifeTime;
	float _speed;
	EntityType _type;

	sf::FloatRect _bulletRect;

	sf::RectangleShape _bullet;
};

