#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include "Button.h"

class GameWinState : public State
{
public:
	GameWinState(sf::RenderWindow* window);
	virtual ~GameWinState();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	GameState UpdateState(float deltaTime) override;
	GameState GetState() override;
	void Unload() override;

private:
	Button _mainMenu;
	Button _restart;

	sf::Font font;
};

