#include "Player.h"
#include "Global.h"
#include "Tilemap.h"

#define PLAYER_SIZE 40.f
#define SWITCH_TIMER 3.f
#define START_TIMER 1.5f
#define PLAYER_SPEED 110.f
#define PLAYER_MUD_SPEED 50.f

Player* Player::player = 0;

Player::Player(sf::RenderWindow* window) :
	Entity(),
	Collidable(PLAYER_SIZE / 2),
	_window(window),
	_position(SCREEN_WIDTH, SCREEN_HEIGHT),
	_rotation(0.f),
	_speed(PLAYER_SPEED),
	_health(100.f),
	_currentGun(0),
	_gunSwitchCooldown(SWITCH_TIMER),
	_startCooldown(START_TIMER)
{
	_player.setPosition(_position);
	_player.setRadius(PLAYER_SIZE / 2);
	_player.setOrigin(_player.getRadius(), _player.getRadius());

	if (!_playerTexture.loadFromFile(PLAYER_TEXTURE))
		std::cout << "Failed to load: PLAYER_TEXTURE";

	_playerSprite.setTexture(_playerTexture);
	_playerSprite.setPosition(_position);
	_playerSprite.setOrigin(_player.getRadius(), _player.getRadius());
}

Player* Player::getPlayer(sf::RenderWindow* window)
{
	if (player == 0)
	{
		player = new Player(window);
	}
	return player;
}

Player::~Player()
{
	delete player;
	player = nullptr;
}

void Player::Load()
{
	_position = sf::Vector2f(0.f, 0.f);
	const Tile* tile = Tilemap::getMap()->getFirstWalkableTile();
	_position = tile->getPosition();
	_rotation = 0;
	_speed = PLAYER_SPEED;
	_health = 100.f;
	_gunSwitchCooldown = SWITCH_TIMER;
	_startCooldown = START_TIMER;
	_currentGun = 0;
	_playerRect = _player.getGlobalBounds();
	setCollisionFilter((int)EntityType::Enemy | (int)EntityType::Bullet_Player);
	
}

void Player::Update(float deltaTime)
{
	_startCooldown -= deltaTime;
	_gunSwitchCooldown -= deltaTime;
	_gunInventory[_currentGun]->setActive(true);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && _gunSwitchCooldown <= 0)
	{
		_gunInventory[_currentGun]->setActive(false);
		_currentGun = (_currentGun + 1) % (int)_gunInventory.size();
		_gunInventory[_currentGun]->setActive(true);
		_gunSwitchCooldown = SWITCH_TIMER;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _startCooldown <= 0)
	{
		_gunInventory[_currentGun]->shoot();
	}
	rotating();
	updateMovement(deltaTime);
	_player.setPosition(_position);
	_playerSprite.setPosition(_position);
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(_playerSprite);
}

void Player::Unload()
{
	_gunInventory.clear();
}

const sf::Vector2f& Player::getPosition() const
{
	return _position;
}

int Player::getType() const
{
	return (int)EntityType::Player;
}

void Player::onCollision(Collidable* collidable)
{
	_health -= 10;
	if (_health <= 0)
	{
		setCollisionFilter(0);
	}
}

float Player::getRotation()
{
	return _rotation;
}

sf::FloatRect Player::getGlobalBound()
{
	return _playerRect;
}

sf::Vector2f Player::getVelocity()
{
	return _velocity;
}

float Player::getSpeed()
{
	return _speed;
}

void Player::setPostion(sf::Vector2f position)
{
	_position = position;
}

void Player::setVelocity(sf::Vector2f velocity)
{
	_velocity = velocity;
}

void Player::rotating()
{
	sf::Vector2i mousePosWindow = sf::Mouse::getPosition(*_window);
	sf::Vector2f mousePosView = _window->mapPixelToCoords(mousePosWindow);

	float deltaX = _position.x - mousePosView.x;
	float deltaY = _position.y - mousePosView.y;

	_rotation = (atan2(-deltaX, deltaY) * 180.00000) / 3.141592;

	_playerSprite.setRotation(_rotation);
}

void Player::updateMovement(float deltaTime)
{
	_velocity = sf::Vector2f(0.f, 0.f);

	if (Tilemap::getMap()->playerInMud(_player.getGlobalBounds()))
		_speed = PLAYER_MUD_SPEED;
	else
		_speed = PLAYER_SPEED;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_velocity.y += -_speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_velocity.y += _speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_velocity.x += -_speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_velocity.x += _speed * deltaTime;
	}

	sf::Vector2f nextPosition = _position + _velocity;

	_playerRect = _player.getGlobalBounds();
	sf::FloatRect _nextHoriRect = _playerRect;
	sf::FloatRect _nextVerRect = _playerRect;
	sf::FloatRect _nextRect = _playerRect;
	_nextHoriRect.left += _velocity.x;
	_nextVerRect.top += _velocity.y;
	_nextRect.left += _velocity.x;
	_nextRect.top += _velocity.y;


	if (Tilemap::getMap()->CanMoveInDirection(_nextRect))
	{
		_position = nextPosition;
	}
	else if (Tilemap::getMap()->CanMoveInDirection(_nextHoriRect))
	{
		_position.x += _velocity.x;
	}
	else if (Tilemap::getMap()->CanMoveInDirection(_nextVerRect))
	{
		_position.y += _velocity.y;
	}

}

bool Player::isAlive()
{
	return _health <= 0;
}

void Player::addGun(Gun* gun)
{
	_gunInventory.push_back(gun);
}



