#include <iostream>

#include <SFML/Graphics.hpp>

#include "../include/gameStateBattle.hpp"
#include "../include/gameStateAI.hpp"
#include "../include/gameState.hpp"
#include "../include/board.hpp"

void GameStateBattle::draw(const float dt) {

	this->game->window.clear(sf::Color::Red);
	this->game->window.draw(this->game->gamebg);
	this->game->window.draw(this->game->board);
	this->game->window.setView(this->gameView);
	return;
}

void GameStateBattle::update(const float dt) {
	return;
}

void GameStateBattle::handleInput() {
	sf::Event event;

	while(this->game->window.pollEvent(event)) {
		switch(event.type) {
			// Close the window
			case sf::Event::Closed: {
				game->window.close();
				std::cout << "Closed Game.\nGood Bye!" << std::endl;
				break;
			}

			case sf::Event::MouseButtonPressed: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    // Check to see if mouse click is within bounds of game board.
                    if((x > 448 && x < 769) && (y > 32 && y < 353)) {
                        // Finds the index of the vector that is being clicked.
                        int index = ((event.mouseButton.x-1)/32 + ((event.mouseButton.y-1)/32)*25);
                        if(this->game->level[index] == 0) {      // if index == water
                            this->game->level[index] = 1;        // set index to miss
                            std::cout << "Miss. -- Entering AI turn" << std::endl << std::endl;
                            this->loadgame();

                            }      
                        else if(this->game->level[index] == 5) { // else if index == enemy ship
                            this->game->level[index] = 2;        // set index to hit
                            std::cout << "Hit! -- Entering AI turn" << std::endl << std::endl;
                            this->loadgame();
                            }
                        if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
            				std::cout << "Board could not be loaded." << std::endl;
                    }
                }
                break;
            }
			default: 
				break;
		}
	}
	return;
}

void GameStateBattle::loadgame() {
	this->game->pushState(new GameStateAI(this->game));
	return;
}

GameStateBattle::GameStateBattle(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);
}










