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
                	for(int i=0; i<4; ++i) {
                		bool firstTilePlaced = false;
                		int size = 0;
                		int gindex;
                		// set Destroyer 2
                		if(i == 0) {
                			while (size < 2) {
                				if(firstTilePlaced == false) {
					            	int x = event.mouseButton.x;
					            	int y = event.mouseButton.y;
					            	// Check to see if mouse click is within bounds of game board.
					            	if((x > 32 && x < 352) && (y > 32 && y < 352)) {
					            	    // Finds the index of the vector that is being clicked.
					            	    int index = ((event.mouseButton.x-1)/32 + ((event.mouseButton.y-1)/32)*25);
					            	    if(this->game->level[index] == 0) {      // if index == water
					            	        this->game->level[index] = 3;        // set index as ship
					            	        std::cout << "Ship set." << std::endl;
					            	        }      
					            	    std::cout << "The left button was pressed" << std::endl;
					            	    std::cout << "Mouse x: " << event.mouseButton.x << std::endl;
					            	    std::cout << "Mouse y: " << event.mouseButton.y << std::endl;
					            	    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
					    					std::cout << "Board could not be loaded." << std::endl;
					    				size++;
					    				gindex = index;
					    				firstTilePlaced = true;
					    			}
					    			if(firstTilePlaced == true && size < 2) {
					    				// Check to see if mouse click is within bounds of game board.
						            	if((x > 32 && x < 352) && (y > 32 && y < 352)) {
						            	    // Finds the index of the vector that is being clicked.
						            	    int index = ((event.mouseButton.x-1)/32 + ((event.mouseButton.y-1)/32)*25);
						            	    if(gindex+1 == index || gindex-1 == index 
						            	    	|| gindex+25 == index || gindex-25 == index) {
							            	    if(this->game->level[index] == 0) {      // if index == water
							            	        this->game->level[index] = 3;        // set index as ship
							            	        std::cout << "Ship set." << std::endl;
							            	        }      
							            	    std::cout << "The left button was pressed" << std::endl;
							            	    std::cout << "Mouse x: " << event.mouseButton.x << std::endl;
							            	    std::cout << "Mouse y: " << event.mouseButton.y << std::endl;
							            	    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
							    					std::cout << "Board could not be loaded." << std::endl;
							    				size++;
					    						gindex = index;
							    			}
					    				}
			    					}
		    					}
		    					// set Submarine 3
		    					if(i == 1) {

		    					}
		    				}
                    	}
                	}
                }
                break;
            }
            case sf::Event::KeyPressed: {
            	if(event.key.code == sf::Keyboard::Return) {
					this->loadgame();
					std::cout << "Entered battle mode." << std::endl;
				}
            }
			
			/*
				Possible add resize function
			*/
			
			default: 
				break;
		}
	}
	return;
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