#include "GameWinState.h"
#include "Global.h"
#include "DrawText.h"

GameWinState::GameWinState(sf::RenderWindow* window) :
	State(window, GameState::Gamewin),
	_restart(window, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + BUTTON_HEIGHT * 2 + TEXT_SIZE * 2)),
	_mainMenu(window, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + BUTTON_HEIGHT * 2))
{
	if (!font.loadFromFile(GAME_FONT))
		std::cout << "fail to load: GAME_FONT" << std::endl;
}

GameWinState::~GameWinState()
{
}

void GameWinState::Load()
{
	_restart.setString("Restart");
	_mainMenu.setString("Main Menu");
}

void GameWinState::Update(float deltaTime)
{
}

void GameWinState::Render(sf::RenderTarget* target)
{
	_window->setView(_window->getDefaultView());
	drawText("You had escaped!", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_OFFSET * 2), 25, target, font);
	_restart.drawButton(target);
	_mainMenu.drawButton(target);
}

GameState GameWinState::UpdateState(float deltaTime)
{
	Update(deltaTime);

	if (_restart.isPressed())
		return GameState::Run;
	else if (_mainMenu.isPressed())
		return GameState::Menu;

	return GameState::Gamewin;
}

GameState GameWinState::GetState()
{
	return GameState::Gamewin;
}

void GameWinState::Unload()
{
}