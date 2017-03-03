#include <iostream>
#include <random>

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
		this->game->quitPrompt.setFont(this->game->font);
		this->game->quitPrompt.setString("[PRESS_ENTER_TO_PLAY_AGAIN_OR_ESCAPE_TO_QUIT]");
		this->game->quitPrompt.setCharacterSize(28);
		this->game->quitPrompt.setColor(custom);
		this->game->quitPrompt.setPosition(20,550);
	}
	else {
		this->game->result.setFont(this->game->font);
		this->game->result.setString("[YOU] [LOST]");
		this->game->result.setCharacterSize(144);
		this->game->result.setColor(custom);
		this->game->result.setPosition(14,380);
		this->game->quitPrompt.setFont(this->game->font);
		this->game->quitPrompt.setString("[PRESS_ENTER_TO_PLAY_AGAIN_OR_ESCAPE_TO_QUIT]");
		this->game->quitPrompt.setCharacterSize(28);
		this->game->quitPrompt.setColor(custom);
		this->game->quitPrompt.setPosition(17,550);
	}
	this->game->window.draw(this->game->result);
	this->game->window.draw(this->game->quitPrompt);
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
	this->game->level = this->game->randomBoard(rand()%12);
    if (!this->game->board.load("../res/tiles/alltiles.png", sf::Vector2u(32, 32), this->game->level, 25, 19))
    	std::cout << "Board could not be loaded." << std::endl;
    this->game->pushState(new GameStateMenu(this->game));
	return;
}








