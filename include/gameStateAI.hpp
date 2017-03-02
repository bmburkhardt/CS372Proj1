#ifndef GAMESTATEAI_HPP
#define GAMESTATEAI_HPP

#include <SFML/Graphics.hpp>

#include "gameState.hpp"

class GameStateAI : public GameState
{

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	GameStateAI(Game* game);

private:

	sf::View gameView;
	void loadgame();
};




#endif // GAMESTATEAI_HPP