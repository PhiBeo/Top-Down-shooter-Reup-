#include "RunState.h"
#include "DrawText.h"

RunState::RunState(sf::RenderWindow* window) :
	State(window, GameState::Run),
	game(nullptr),
	_currentState(RunningState::Play),
	_isPress(false)
{
	if (!font.loadFromFile(GAME_FONT))
		std::cout << "fail to load: GAME_FONT" << std::endl;
	game = GameManager::getGame(window);
}

RunState::~RunState()
{
}

void RunState::Load()
{
	game->Load();
	_currentState = RunningState::Play;
	_isPress = false;
}

void RunState::Update(float deltaTime)
{
	if (_currentState == RunningState::Play)
	{
		game->Update(deltaTime);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		_isPress = false;

	if (!_isPress && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		switch (_currentState)
		{
		case RunningState::Play:
			_currentState = RunningState::Pause;
			break;
		case RunningState::Pause:
			_currentState = RunningState::Play;
			break;
		default:
			break;
		}
		_isPress = true;
	}
}

void RunState::Render(sf::RenderTarget* target)
{
	game->Render(target);	
	game->RenderUI(target);

	if (_currentState == RunningState::Pause)
	{
		sf::View view;
		view.setCenter(Player::getPlayer(_window)->getPosition());
		view.setSize(sf::Vector2f(_window->getSize().x, _window->getSize().y));
		_window->setView(view);
		drawText("Pausing", sf::Vector2f(_window->getView().getCenter().x, _window->getView().getCenter().y), 24, target, font);
	}
}

GameState RunState::UpdateState(float deltaTime)
{
	Update(deltaTime);
	if (game->isOver())
	{
		_window->setView(_window->getDefaultView());
		return GameState::Gameover;
	}
	else if (game->isReachGoal())
	{
		return GameState::Gamewin;
	}
	return GameState::Run;
}

GameState RunState::GetState()
{
	return GameState::Run;
}

void RunState::Unload()
{
	game->Unload();
}
