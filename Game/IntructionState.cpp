#include "IntructionState.h"
#include "Global.h"
#include "DrawText.h"

IntructionState::IntructionState(sf::RenderWindow* window) :
	State(window, GameState::Intruction),
	_return(window, sf::Vector2f(SCREEN_WIDTH - BUTTON_WIDTH / 1.5, SCREEN_HEIGHT - BUTTON_HEIGHT))
{
	if (!font.loadFromFile(DEFAULT_FONT))
		std::cout << "Fail to load: DEFAULT_FONT" << std::endl;

}

IntructionState::~IntructionState()
{
}

void IntructionState::Load()
{
	_return.setString("Back");


}

void IntructionState::Update(float deltaTime)
{
}

void IntructionState::Render(sf::RenderTarget* target)
{
	


	_return.drawButton(target);
}

GameState IntructionState::UpdateState(float deltaTime)
{
	Update(deltaTime);
	if (_return.isPressed())
		return GameState::Menu;

	return GameState::Intruction;
}

GameState IntructionState::GetState()
{
	return GameState::Intruction;
}

void IntructionState::Unload()
{
}

