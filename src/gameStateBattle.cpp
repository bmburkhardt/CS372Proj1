#include <iostream>
#include <random>
#include <time.h>

#include <SFML/Graphics.hpp>

#include "../include/gameStateBattle.hpp"
#include "../include/gameStateDone.hpp"
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
			case sf::Event::KeyPressed: {
				if(event.key.code == sf::Keyboard::Escape) {
					this->game->window.close();
					std::cout << "Closed Game.\nGood Bye!" << std::endl;
				}
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
                            this->game->level[index] = 6;        // set index to miss
                            playerShots++;
                            std::cout << "You Missed - Entering AI turn"  << std::endl;
                            this->AITurn();                            }      
                        else if(this->game->level[index] == 5) { // else if index == enemy ship
                            this->game->level[index] = 2;        // set index to hit
                            playerShots++;
                            playerHits++;
                            playerHasWon(playerHits, AIHits);
                            std::cout << "You Hit! - Entering AI turn"  << std::endl;
                            this->AITurn();
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


void GameStateBattle::AITurn() {
	bool shotSuccess = false;
	while(!shotSuccess) {
		int shootAt = (25+(rand()%12)) + (25*(rand()%10));
		if(this->game->level[shootAt] == 0) {
			this->game->level[shootAt] = 1;
			AIShots++;
			std::cout << "AI Missed." << std::endl << std::endl;
			shotSuccess = true;
		}
		else if(this->game->level[shootAt] == 3) {
			this->game->level[shootAt] = 2;
			AIShots++;
			AIHits++;
			playerHasWon(playerHits, AIHits);
			std::cout << "AI Hit" << std::endl << std::endl;
			shotSuccess = true;
		}
	}
}

void GameStateBattle::loadgame() {
	this->game->pushState(new GameStateDone(this->game));
	return;
}

GameStateBattle::GameStateBattle(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);
}

void GameStateBattle::playerHasWon(int ph, int ah) {
	if(ph == 17) {
		this->game->playerWin = true;
		std::cout << "Player won!" << std::endl;
		this->loadgame();
	}
	else if(ah == 17) {
		this->game->playerWin = false;
		std::cout << "AI won!" << std::endl;
		this->loadgame();
	}
}







