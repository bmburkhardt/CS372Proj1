#include <iostream>

#include <SFML/Graphics.hpp>

#include "../include/gameStatePlay.hpp"
#include "../include/gameState.hpp"
#include "../include/board.hpp"

void GameStatePlay::draw(const float dt) {

	this->game->window.clear(sf::Color::Red);
	this->game->window.draw(this->game->gamebg);
	this->game->window.draw(this->game->board);
	this->game->window.setView(this->gameView);
	return;
}

void GameStatePlay::update(const float dt) {
	return;
}

void GameStatePlay::handleInput() {
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
                        if(this->game->level[index] == 0)       // if index == water
                            this->game->level[index] = 1;       // set index to miss
                        else if(this->game->level[index] == 3)  // else if index == ship
                            this->game->level[index] = 2;       // set index to hit
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
            				std::cout << "Board could not be loaded." << std::endl;
                    }
                }
                break;
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

GameStatePlay::GameStatePlay(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	//this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	//this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);
}










