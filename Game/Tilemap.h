#pragma once
#include "Entity.h"
#include "Tile.h"

class Tilemap : public Entity
{
public:
	virtual ~Tilemap() {};
	static Tilemap* getMap();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	void Unload() override;

	void reloadMap();

	bool CanMoveInDirection(const sf::FloatRect& obj);
	const Tile* getFirstWalkableTile();
	bool isCollideWithWall(const sf::FloatRect& bulletObj);
	bool playerReachGoal(const sf::FloatRect& obj);
	bool playerInMud(const sf::FloatRect& obj);

	const std::vector<Tile*> getEnemyTile();
	const Tile* getTile(sf::Vector2i tile);

private:
	static Tilemap* _tileMap;
	Tilemap();

	int _rows;
	int _columns;
	std::vector<std::vector<Tile*>> _tiles;
	int _level;

	Tile* _goalTile;
	std::vector<Tile*> _mudTile;

	int fromX = 0;
	int fromY = 0; 
	int toX = 0; 
	int toY = 0;
};

