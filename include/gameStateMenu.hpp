#ifndef GAMESTATEMENU_HPP
#define GAMESTATEMENU_HPP

#include <SFML/Graphics.hpp>
#include "gameState.hpp"

class GameStateMenu : public GameState
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateMenu(Game* game);

private:
	sf::View view;
	void loadgame();
};

#endif // GAMESTATEMENU_HPP
