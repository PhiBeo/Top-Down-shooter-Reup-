#include "Enemy.h"
#include "Global.h"
#include "Player.h"
#include "Tilemap.h"
#include <sstream>

#define ENEMY_SIZE 40.f
#define ENEMY_SPEED 150.f
#define RESPAWN_TIME 2.f

Enemy::Enemy() :
	Entity(),
	Collidable(ENEMY_SIZE / 2),
	_position(0.f,0.f),
	_velocity(0.f, 0.f),
	_health(100.f),
	_speed(ENEMY_SPEED),
	respawnTime(RESPAWN_TIME)
{
	_enemy.setFillColor(sf::Color::White);
	_enemy.setRadius(ENEMY_SIZE / 2);
	_enemy.setOrigin(_enemy.getRadius(), _enemy.getRadius());
	_enemy.setPosition(_position);

	_player = Player::getPlayer(nullptr);
}

Enemy::~Enemy()
{
}

void Enemy::Load()
{
	_position = sf::Vector2f(0.f, 0.f);
	_velocity = sf::Vector2f(0.f, 0.f);
	_speed = ENEMY_SPEED;
	_health = 100.f;
	respawnTime = RESPAWN_TIME;
	_enemyRect = _enemy.getGlobalBounds();
	_enemyRect.left = _position.x - _enemy.getRadius();
	_enemyRect.top = _position.y - _enemy.getRadius();
	setCollisionFilter((int)EntityType::Player | (int)EntityType::Bullet_Player);
}

void Enemy::Update(float deltaTime)
{
	if (isAlive())
	{
		_velocity = (_player->getPosition() - _position) / sqrtf(pow(_player->getPosition().x - _position.x, 2) + pow(_player->getPosition().y - _position.y, 2));
		_position += _velocity * _speed * deltaTime;

		_enemyRect.left += _velocity.x * _speed * deltaTime;
		_enemyRect.top += _velocity.y * _speed * deltaTime;

		_enemy.setPosition(_position);
	}
	else if (!isAlive())
	{
		respawnTime -= deltaTime;
		if (respawnTime <= 0)
		{
			respawn();
		}
	}
	
}

void Enemy::Render(sf::RenderTarget* target)
{
	if (isAlive())
	{
		target->draw(_enemy);
	}
}

void Enemy::Unload()
{
}

void Enemy::RenderUI(sf::RenderTarget* target)
{
}

const sf::Vector2f& Enemy::getPosition() const
{
	return _position;
}

int Enemy::getType() const
{
	return (int)EntityType::Enemy;
}

void Enemy::onCollision(Collidable* collidable)
{
	if (collidable->getType() == (int)EntityType::Player)
	{
		_health -= 20.f;
	}
	else if (collidable->getType() == (int)EntityType::Bullet_Player)
	{
		_health -= 50.f;
	}
	if (_health <= 0)
	{
		setCollisionFilter(0);
	}
}

void Enemy::setPosition(sf::Vector2f position)
{
	_position = position;
	_defaultPos = position;
}

sf::FloatRect Enemy::getEnemyRect()
{
	return _enemyRect;
}

bool Enemy::isAlive()
{
	return _health > 0;
}

void Enemy::respawn()
{
	_health = 100.f;
	_position = _defaultPos;
	respawnTime = RESPAWN_TIME;
	setCollisionFilter((int)EntityType::Player | (int)EntityType::Bullet_Player);
}
