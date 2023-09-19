#pragma once
#include "Entity.h"
#include "Collidable.h"
#include "Gun.h"

class Player : public Entity, public Collidable
{
public:
    static Player* getPlayer(sf::RenderWindow* window);
    
    virtual ~Player();

    void Load() override;
    void Update(float deltaTime) override;
    void Render(sf::RenderTarget* target) override;
    void Unload() override;

    const sf::Vector2f& getPosition() const override;
    int getType() const override;
    void onCollision(Collidable* collidable) override;

    float getRotation();
    sf::FloatRect getGlobalBound();
    sf::FloatRect getNextGlobalBound();
    sf::Vector2f getVelocity();
    float getSpeed();

    void setPostion(sf::Vector2f position);
    void setVelocity(sf::Vector2f velocity);

    void rotating();
    void updateMovement(float deltaTime);
    bool isAlive();
    void addGun(Gun* gun);

private:
    static Player* player;
    Player(sf::RenderWindow* window);

    sf::RenderWindow* _window;

    sf::Vector2f _position;
    sf::Vector2f _velocity;
    float _rotation;
    float _speed;
    float _health;
    sf::FloatRect _playerRect;
    
    sf::CircleShape _player;

    sf::Texture _playerTexture;
    sf::Sprite _playerSprite;

    int _currentGun;
    std::vector<Gun*> _gunInventory;
    float _gunSwitchCooldown;
    float _startCooldown;
};