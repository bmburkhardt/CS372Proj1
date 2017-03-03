#include <iostream>

#include <SFML/Graphics.hpp>

#include "../include/gameStateDone.hpp"
#include "../include/gameStateBattle.hpp"
#include "../include/gameState.hpp"
#include "../include/board.hpp"
#include "../include/gameStateSetup.hpp"
#include "../include/gameStateMenu.hpp"
#include "../include/game.hpp"


void GameStateDone::draw(const float dt){
	sf::Color custom(0x5B0000ff);
	this->game->window.clear(sf::Color::Red);
	this->game->window.draw(this->game->gamebg);
	this->game->window.draw(this->game->board);
	if(this->game->playerWin) {
		this->game->result.setFont(this->game->font);
		this->game->result.setString("[YOU] [WON]");
		this->game->result.setCharacterSize(144);
		this->game->result.setColor(custom);
		this->game->result.setPosition(28,380);
	}
	else {
		this->game->result.setFont(this->game->font);
		this->game->result.setString("[YOU] [LOST]");
		this->game->result.setCharacterSize(144);
		this->game->result.setColor(custom);
		this->game->result.setPosition(14,380);
	}
	this->game->window.draw(this->game->result);
	this->game->window.setView(this->gameView);
	return;
}
void GameStateDone::update(const float dt){
	return;
}

void GameStateDone::handleInput() {
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
					std::cout << "Enter new game." << std::endl << std::endl;
				}
				else if(event.key.code == sf::Keyboard::Escape) {
					game->window.close();
					std::cout << "Closed Game.\nGood Bye!" << std::endl;
					break;
				}
            }

			
			default: 
				break;
		}
	}
	return;
}

GameStateDone::GameStateDone(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);
}

void GameStateDone::loadgame() {
	this->game->level = {
    //  1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //1
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, //2
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, //3
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 4, //4
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 4, //5
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 4, //6
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 4, //7
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 4, //8
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 4, //9
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, //10
        4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 4, //11
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //12
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //13
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //14
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //15
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //16
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //17
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //18
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, //19
    };
    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
    	std::cout << "Board could not be loaded." << std::endl;
    this->game->pushState(new GameStateMenu(this->game));
	//this->game->pushState(new GameStateSetup(this->game));
	return;
}








