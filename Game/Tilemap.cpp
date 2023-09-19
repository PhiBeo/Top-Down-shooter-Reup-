#include "Tilemap.h"
#include "Global.h"
#include "GameManager.h"

#include <fstream>

Tilemap* Tilemap::_tileMap = 0;

Tilemap* Tilemap::getMap()
{
	if (_tileMap == 0)
	{
		_tileMap = new Tilemap();
	}
	return _tileMap;
}

void Tilemap::Load()
{
	reloadMap();
}

void Tilemap::Update(float deltaTime)
{
	fromX = GameManager::getGame(nullptr)->getView()->getCenter().x / GRID_SIZE - 10;
	toX = GameManager::getGame(nullptr)->getView()->getCenter().x / GRID_SIZE + 11;
	fromY = GameManager::getGame(nullptr)->getView()->getCenter().y / GRID_SIZE - 8;
	toY = GameManager::getGame(nullptr)->getView()->getCenter().y / GRID_SIZE + 9;

	if (fromX < 0)
		fromX = 0;
	else if (fromX >= _rows)
		fromX = _rows - 1;

	if (toX < 0)
		toX = 0;
	else if (toX >= _rows)
		toX = _rows - 1;

	if (fromY < 0)
		fromY = 0;
	else if (fromY >= _columns)
		fromY = _rows - 1;

	if (toY < 0)
		toY = 0;
	else if (toY >= _columns)
		toY = _rows - 1;


	for (int r = fromY; r < toY; r++)
	{
		for (int c = fromX; c < toX; c++)
		{
			_tiles[r][c]->Update(deltaTime);
		}
	}
}

void Tilemap::Render(sf::RenderTarget* target)
{

	for (int r = fromY; r < toY; r++)
	{
		for (int c = fromX; c < toX; c++)
		{
			_tiles[r][c]->Render(target);
		}
	}
}

void Tilemap::Unload()
{
	_mudTile.clear();

	for (int r = 0; r < _rows; r++)
	{
		for (int c = 0; c < _columns; c++)
		{
			if (_tiles[r][c] != nullptr)
			{
				_tiles[r][c]->Unload();
				delete _tiles[r][c];
				_tiles[r][c] = nullptr;
			}
		}
	}
}

void Tilemap::reloadMap()
{
	std::fstream inputStream;
	inputStream.open("./levels/level" + std::to_string(_level) + ".lvl");

	std::vector<Tile*> tiles;
	inputStream >> _rows;
	inputStream >> _columns;

	_tiles.clear();
	int dataType = 0;

	while (inputStream >> dataType)
	{
		TileData newTileData;
		newTileData.tileType = (TileType)dataType;
		newTileData.isColliable = newTileData.tileType == TileType::Wall;
		newTileData.position = sf::Vector2f(tiles.size() * GRID_SIZE, _tiles.size() * GRID_SIZE);

		Tile* tile = new Tile(newTileData);
		tile->Load();
		if (tile->getTileType() == TileType::Goal)
			_goalTile = tile;
		else if (tile->getTileType() == TileType::Mud)
			_mudTile.push_back(tile);

		tiles.push_back(tile);

		if (tiles.size() == _rows)
		{
			_tiles.push_back(tiles);
			tiles.clear();
		}
	}

	inputStream.close();
}

bool Tilemap::CanMoveInDirection(const sf::FloatRect& obj)
{
	bool isWalkable = true;

	for (int r = fromY; r < toY; r++)
	{
		for (int c = fromX; c < toX; c++)
		{
			if (_tiles[r][c]->isColliable() && _tiles[r][c]->doesCollide(obj))
			{
				isWalkable = false;
				break;
			}
			if (!isWalkable)
				break;
		}
	}
	return isWalkable;
}

const Tile* Tilemap::getFirstWalkableTile()
{
	Tile* walkableTile = nullptr;

	for (int r = 0; r < _rows; r++)
	{
		for (int c = 0; c < _columns; c++)
		{
			if (_tiles[r][c]->getTileType() == TileType::Spawn)
			{
				walkableTile = _tiles[r][c];
				break;
			}
			if (walkableTile != nullptr)
				break;
		}
	}
	return walkableTile;
}

bool Tilemap::isCollideWithWall(const sf::FloatRect& bulletObj)
{
	bool isCollide = false;

	for (int r = fromY; r < toY; r++)
	{
		for (int c = fromX; c < toX; c++)
		{
			if (_tiles[r][c]->isColliable() && _tiles[r][c]->doesCollide(bulletObj))
			{
				isCollide = true;
				break;
			}
			if (isCollide)
				break;
		}
	}
	return isCollide;
}

bool Tilemap::playerReachGoal(const sf::FloatRect& obj)
{
	if (obj.intersects(_goalTile->getRect()))
		return true;
	return false;
}

bool Tilemap::playerInMud(const sf::FloatRect& obj)
{
	for (int i = 0; i < _mudTile.size(); i++)
	{
		if (_mudTile[i]->getRect().intersects(obj))
		{
			return true;
		}
	}
	return false;
}

const std::vector<Tile*> Tilemap::getEnemyTile()
{
	std::vector<Tile*> enemyTile;

	for (int r = 0; r < _rows; r++)
	{
		for (int c = 0; c < _columns; c++)
		{
			if (_tiles[r][c]->getTileType() == TileType::Enemy)
			{
				Tile* tile = nullptr;
				tile = _tiles[r][c];
				enemyTile.push_back(tile);
			}
		}
	}
	return enemyTile;
}

const Tile* Tilemap::getTile(sf::Vector2i tile)
{
	return _tiles[tile.x][tile.y];
}

Tilemap::Tilemap() :
	Entity(),
	_rows(0),
	_columns(0),
	_level(1),
	_goalTile(nullptr)
{

}