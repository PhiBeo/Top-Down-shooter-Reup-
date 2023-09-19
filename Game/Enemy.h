#pragma once
#include "Entity.h"
#include "Collidable.h"

class Player;

class Enemy : public Entity, public Collidable
{
public:
	Enemy();
	virtual ~Enemy();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	void Unload() override;
	void RenderUI(sf::RenderTarget* target);

	const sf::Vector2f& getPosition() const override;
	int getType() const override;
	void onCollision(Collidable* collidable) override;

	void setPosition(sf::Vector2f position);

	sf::FloatRect getEnemyRect();

	bool isAlive();
	void respawn();

private:
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _defaultPos;

	float _health;
	float _speed;
	sf::FloatRect _enemyRect;

	Player* _player;

	sf::CircleShape _enemy;
	float respawnTime;
};

