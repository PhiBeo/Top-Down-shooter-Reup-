#include "Tile.h"
#include "Global.h"

Tile::Tile(const TileData& data) :
	Entity(),
	_tileData(data),
	_player(nullptr)
{
	_wall.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
	_wall.setFillColor(sf::Color::White);
	_wall.setPosition(_tileData.position);
	_player = Player::getPlayer(nullptr);
	
	_wallRect = _wall.getGlobalBounds();
}

Tile::~Tile()
{
}

void Tile::Load()
{
	switch (_tileData.tileType)
	{
	case TileType::Spawn: _wall.setFillColor(sf::Color::Blue); break;
	case TileType::Ground: _wall.setFillColor(sf::Color(169, 169, 169));break;
	case TileType::Wall: _wall.setFillColor(sf::Color(105, 105, 105)); break;
	case TileType::Mud: _wall.setFillColor(sf::Color(92, 64, 51)); break;
	case TileType::Enemy: _wall.setFillColor(sf::Color(169, 169, 169)); break;
	case TileType::Goal: _wall.setFillColor(sf::Color::Yellow); break;
	default:
		break;
	}
}

void Tile::Update(float deltaTime)
{
	
}

void Tile::Render(sf::RenderTarget* target)
{
	target->draw(_wall);
}

void Tile::Unload()
{
}

const sf::Vector2f& Tile::getPosition() const
{
	sf::Vector2f position = sf::Vector2f(GRID_SIZE / 2,GRID_SIZE /2) + _tileData.position;
	return position;
}

const TileType Tile::getTileType() const
{
	return _tileData.tileType;
}

const sf::FloatRect Tile::getRect() const
{
	return _wallRect;
}

bool Tile::isColliable() const
{
	return _tileData.tileType == TileType::Wall;
}

bool Tile::doesCollide(const sf::FloatRect& objRect) const
{
	return _wallRect.intersects(objRect);
}
