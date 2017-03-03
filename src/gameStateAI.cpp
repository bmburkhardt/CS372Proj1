#include <iostream>

#include <SFML/Graphics.hpp>

#include "../include/gameStateAI.hpp"
#include "../include/gameStateBattle.hpp"
#include "../include/gameState.hpp"
#include "../include/board.hpp"


void GameStateAI::draw(const float dt){
	this->game->window.clear(sf::Color::Red);
	this->game->window.draw(this->game->gamebg);
	this->game->window.draw(this->game->board);
	this->game->window.setView(this->gameView);
	return;
}
void GameStateAI::update(const float dt){
	return;
}

void GameStateAI::handleInput() {
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
            	if(event.key.code == sf::Keyboard::Return) {
					this->loadgame();
					std::cout << "Entered player turn." << std::endl << std::endl;
				}
            }

			
			default: 
				break;
		}
	}
	return;
}

GameStateAI::GameStateAI(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);
}

void GameStateAI::loadgame() {
	this->game->pushState(new GameStateBattle(this->game));
	return;
}