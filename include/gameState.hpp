#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "game.hpp"

class GameState
{

public: 	
	Game* Game;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;
};




#endif // GAMESTATE_HPP