#include <iostream>

#include <SFML/Graphics.hpp>

#include "../include/gameStateBattle.hpp"
#include "../include/gameStateSetup.hpp"
#include "../include/gameState.hpp"
#include "../include/board.hpp"

void GameStateSetup::draw(const float dt) {

	this->game->window.clear(sf::Color::Red);
	this->game->window.draw(this->game->gamebg);
	this->game->window.draw(this->game->board);
	this->game->window.setView(this->gameView);
	return;
}

void GameStateSetup::update(const float dt) {
	return;
}


void GameStateSetup::handleInput() {
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
                	if(shipSize < 6)
                		placeShip(shipSize, event.mouseButton.x, event.mouseButton.y);
                }
                break;
            }
            case sf::Event::KeyPressed: {
            	if(event.key.code == sf::Keyboard::Return) {
					this->loadgame();
					std::cout << "Entered battle mode." << std::endl << std::endl;
				}
				if(event.key.code == sf::Keyboard::Escape) {
					this->game->window.close();
					std::cout << "Closed Game.\nGood Bye!" << std::endl;
				}
            }
			default: 
				break;
		}
	}
	return;
}

void GameStateSetup::placeShip(int n, int x, int y) {
	if(size <= n && !firstTilePlaced) {
    	// Check to see if mouse click is within bounds of game board.
    	if((x > 32 && x < 352) && (y > 32 && y < 352)) {
    	    // Finds the index of the vector that is being clicked.
    	    int index = ((x-1)/32 + ((y-1)/32)*25);
    	    originalIndex = index;
    	    if(this->game->level[index] == 0) {      // if index == water
    	        this->game->level[index] = 3;        // set index as ship
    	        std::cout << "Ship piece (" << size << "/" << shipSize << ") set." << std::endl;
    	        size++;
				placedIndex = index;
				firstTilePlaced = true;			            	        
    	        }
    	    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
				std::cout << "Board could not be loaded." << std::endl;	
		}
	}
	else if(size <= n && !secondTilePlaced) {
		// Check to see if mouse click is within bounds of game board.
    	if((x > 32 && x < 352) && (y > 32 && y < 352)) {
    	    // Finds the index of the vector that is being clicked.
    	    int index = ((x-1)/32 + ((y-1)/32)*25);
    	    if(placedIndex+1 == index || placedIndex-1 == index) {
        	    if(this->game->level[index] == 0) {      // if index == water
        	        this->game->level[index] = 3;        // set index as ship
        	        std::cout << "Ship piece (" << size << "/" << shipSize << ") set." << std::endl;
        	        size++;
					placedIndex = index;
					secondTilePlaced = true;
					horizontal = true;
        	        }
        	    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
					std::cout << "Board could not be loaded." << std::endl;
				
			}
			else if(placedIndex+25 == index || placedIndex-25 == index) {
				if(this->game->level[index] == 0) {      // if index == water
        	        this->game->level[index] = 3;        // set index as ship
        	        std::cout << "Ship piece (" << size << "/" << shipSize << ") set." << std::endl;
        	        size++;
					placedIndex = index;
					secondTilePlaced = true;
					vertical = true;
        	        }
        	    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
					std::cout << "Board could not be loaded." << std::endl;	
			}
		}
	}
	else if(size <= n && horizontal) {
		// Check to see if mouse click is within bounds of game board.
    	if((x > 32 && x < 352) && (y > 32 && y < 352)) {
    	    // Finds the index of the vector that is being clicked.
    	    int index = ((x-1)/32 + ((y-1)/32)*25);
    	    if((placedIndex+1 == index || placedIndex-1 == index) /*&& originalIndex + size > index+1) */||
    	    	(placedIndex+1 == index || placedIndex-1 == index) /*&& originalIndex - size < index+1*/)  
    	    	/*(placedIndex-size+1 == index && placedIndex+size-1 != index) ||
    	    	(placedIndex-size+1 != index && placedIndex+size-1 == index))*/ {
        	    if(this->game->level[index] == 0) {      // if index == water
        	        this->game->level[index] = 3;        // set index as ship
        	        std::cout << "horizontal index " << index << std::endl;
        	        std::cout << "Ship piece (" << size << "/" << shipSize << ") set." << std::endl;
        	        size++;
					placedIndex = index;
        	        }
        	    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
					std::cout << "Board could not be loaded." << std::endl;
				
			}
		}
	}
	else if(size <= n && vertical) {
		// Check to see if mouse click is within bounds of game board.
    	if((x > 32 && x < 352) && (y > 32 && y < 352)) {
    	    // Finds the index of the vector that is being clicked.
    	    int index = ((x-1)/32 + ((y-1)/32)*25);
    	    if(placedIndex+25 == index || placedIndex-25 == index || 
    	    	placedIndex+25-size+1 == index-size || placedIndex-25+size == index+size-1) {
        	    if(this->game->level[index] == 0) {      // if index == water
        	        this->game->level[index] = 3;        // set index as ship
        	        std::cout << "Ship piece (" << size << "/" << shipSize << ") set." << std::endl;
        	        size++;
					placedIndex = index;
        	        }
        	    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
					std::cout << "Board could not be loaded." << std::endl;
				
			}
		}
	}
	else if(size > n) {
		std::cout << "Ship of size " << size-1 << " set." << std::endl << std::endl;
		if(size-1 ==5)
			std::cout << "All ships placed. Press enter to begin. Good Luck!" << std::endl;
		if(!secondOfSize3 && size-1 ==3) {
			shipSize--;
			secondOfSize3 = true;
		}
		size = 1;

		firstTilePlaced = false;
		secondTilePlaced = false;
		vertical = false;
		horizontal = false;
		shipSize++;
		if(shipSize < 6)
			std::cout << "Please place ship of size " << shipSize << std::endl;
	}
}

GameStateSetup::GameStateSetup(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);
}

void GameStateSetup::loadgame() {
	this->game->pushState(new GameStateBattle(this->game));
	return;
}