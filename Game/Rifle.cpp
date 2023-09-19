#include "Rifle.h"

Rifle::Rifle(BulletPool* magazine) :
	Gun(1, 0.1, 25),
	_currentlyUse(false),
	_magazine(magazine),
	_position(0.f, 0.f),
	_rotation(0.f),
	_bulletCoolDown(getFireRate())
{
	_gun.setFillColor(sf::Color::Black);
	_gun.setSize(sf::Vector2f(6, 30));
	_gun.setPosition(_position);
	_gun.setRotation(_rotation);
	_gun.setOrigin(_gun.getSize().x / 2, -_gun.getSize().y / 3);

	_player = Player::getPlayer(nullptr);
}

Rifle::~Rifle()
{
}

void Rifle::Load()
{
	_position = sf::Vector2f(0.f, 0.f);
	_rotation = 0.f;
	_bulletCoolDown = getFireRate();
}

void Rifle::Update(float deltaTime)
{
	if (isUse())
	{
		_position = _player->getPosition();
		_rotation = _player->getRotation();
		_gun.setPosition(_position);
		_gun.setRotation(_rotation + 180);
		_bulletCoolDown -= deltaTime;
	}
}

void Rifle::Render(sf::RenderTarget* target)
{
	if (isUse())
	{
		target->draw(_gun);
	}
}

void Rifle::Unload()
{
}

bool Rifle::isUse()
{
	return _currentlyUse;
}

void Rifle::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Rifle::setRotation(float rotation)
{
	_rotation = rotation;
}

void Rifle::setActive(bool active)
{
	_currentlyUse = active;
}

void Rifle::shoot()
{
	Bullet* bullet = _magazine->getNextBullet(getMaxAmmo());
	if (bullet != nullptr)
	{
		if (_bulletCoolDown <= 0)
		{
			bullet->setActive(_position, _rotation, EntityType::Player, 0.5);
			_bulletCoolDown = getFireRate();
		}
	}
}
