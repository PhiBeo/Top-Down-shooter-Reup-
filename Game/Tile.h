#pragma once
#include "Entity.h"
#include "Enums.h"
#include "Player.h"

struct TileData
{
    TileType tileType = TileType::None;
    sf::Vector2f position;
    bool isColliable = false;
};

class Tile : public Entity
{
public:
    Tile(const TileData& data);
    virtual ~Tile();

    void Load() override;
    void Update(float deltaTime) override;
    void Render(sf::RenderTarget* target) override;
    void Unload() override;

    const sf::Vector2f& getPosition() const;
    const TileType getTileType() const;
    const sf::FloatRect getRect() const;

    bool isColliable() const;
    bool doesCollide(const sf::FloatRect& objRect) const;


private:
    TileData _tileData;
    sf::RectangleShape _wall;
    sf::FloatRect _wallRect;

    Player* _player;
};

