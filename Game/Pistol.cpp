#include "Pistol.h"
#include "Global.h"

Pistol::Pistol(BulletPool* magazine) :
	Gun(0,0.5,7),
	_currentlyUse(false),
	_magazine(magazine),
	_position(0.f,0.f),
	_rotation(0.f),
	_bulletCoolDown(getFireRate())
{
	_gun.setFillColor(sf::Color::Black);
	_gun.setSize(sf::Vector2f(5, 15));
	_gun.setPosition(_position);
	_gun.setRotation(_rotation);
	_gun.setOrigin(_gun.getSize().x / 2, -_gun.getSize().y);

	_player = Player::getPlayer(nullptr);
}

Pistol::~Pistol()
{
}

void Pistol::Load()
{
	_position = sf::Vector2f(0.f, 0.f);
	_rotation = 0.f;
	_bulletCoolDown = getFireRate();
}

void Pistol::Update(float deltaTime)
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

void Pistol::Render(sf::RenderTarget* target)
{
	if (isUse())
	{
		target->draw(_gun);
	}
}

void Pistol::Unload()
{
}

bool Pistol::isUse()
{
	return _currentlyUse;
}

void Pistol::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Pistol::setRotation(float rotation)
{
	_rotation = rotation;
}

void Pistol::setActive(bool active)
{
	_currentlyUse = active;
}

void Pistol::shoot()
{
	Bullet* bullet = _magazine->getNextBullet(getMaxAmmo());
	if (bullet != nullptr)
	{
		if (_bulletCoolDown <= 0)
		{
			bullet->setActive(_position, _rotation, EntityType::Player, 1.5);
			_bulletCoolDown = getFireRate();
		}
	}
}
