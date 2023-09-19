#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include "Button.h"

class IntructionState : public State
{
public:
	IntructionState(sf::RenderWindow* window);
	virtual ~IntructionState();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	GameState UpdateState(float deltaTime) override;
	GameState GetState() override;
	void Unload() override;

private:
	Button _return;

	sf::Font font;
};

