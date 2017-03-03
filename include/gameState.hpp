#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <iostream>

#include "game.hpp"

class GameState
{

public: 	
	Game* game;

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;
		
			
};




#endif // GAMESTATE_HPP