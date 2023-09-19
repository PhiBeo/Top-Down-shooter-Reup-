#include "Bullet.h"
#include "Global.h"
#include "Tilemap.h"

#define DEFAULT_LIFE_TIME 2.f
#define SPEED 1000.f
#define BULLET_WIDTH 3
#define BULLET_HEIGHT 10

Bullet::Bullet() :
	Entity(),
	Collidable(BULLET_WIDTH / 2),
	_position(0.f,0.f),
	_rotation(0.f),
	_lifeTime(0),
	_speed(SPEED),
	_type(EntityType::Bullet_Player)
{
	_bullet.setFillColor(sf::Color::Yellow);
	_bullet.setPosition(_position);
	_bullet.setRotation(_rotation);
	_bullet.setSize(sf::Vector2f(BULLET_WIDTH, BULLET_HEIGHT));
	_bullet.setOrigin(_bullet.getSize().x / 2, _bullet.getSize().y / 2);

	_bulletRect = _bullet.getGlobalBounds();
}

Bullet::~Bullet()
{
}

void Bullet::Load()
{
	_position = sf::Vector2f(0.f, 0.f);
	_rotation = 0.f;
	_lifeTime = 0;
	_speed = SPEED;

}

void Bullet::Update(float deltaTime)
{
	if (isActive())
	{
		_lifeTime -= deltaTime;
		float radians = (3.1415926536 / 180.f) * ((float)_rotation + 90);
		_position -= deltaTime * _speed * sf::Vector2f(cos(radians), sin(radians));
		_bulletRect.left = _position.x;
		_bulletRect.top = _position.y;

		if (Tilemap::getMap()->isCollideWithWall(_bulletRect))
			_lifeTime = 0;
	}
	else
		setCollisionFilter(0);
}

void Bullet::Render(sf::RenderTarget* target)
{
	if (isActive())
	{
		_bullet.setPosition(_position);
		

		target->draw(_bullet);
	}
}

void Bullet::Unload()
{
}

const sf::Vector2f& Bullet::getPosition() const
{
	return _position;
}

int Bullet::getType() const
{
	return (int) EntityType::Bullet_Player;
}

void Bullet::onCollision(Collidable* collidable)
{
	_lifeTime = 0;
	setCollisionFilter(0);
}

void Bullet::setActive(sf::Vector2f position, float rotation, EntityType type, float lifeTime)
{
	_position = position;
	_rotation = rotation;
	_lifeTime = lifeTime;
	switch (type)
	{
	case EntityType::Player:
		_type = EntityType::Bullet_Player;
		setCollisionFilter((int)EntityType::Enemy | (int)EntityType::Bullet_Enemy);
		break;
	case EntityType::Enemy:
		_type = EntityType::Bullet_Enemy;
		setCollisionFilter((int)EntityType::Player | (int)EntityType::Bullet_Player);
		break;
	default:
		break;
	}
	_bullet.setRotation(_rotation + 180);
}

bool Bullet::isActive()
{
	return _lifeTime > 0;
}
