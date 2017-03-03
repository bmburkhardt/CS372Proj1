#include <iostream>

#include <SFML/Graphics.hpp>

#include "../include/gameStateSetup.hpp"
#include "../include/gameStateMenu.hpp"
#include "../include/gameStateBattle.hpp"
#include "../include/gameState.hpp"

void GameStateMenu::draw(const float dt) {
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->menubg);
	this->game->window.draw(this->game->headline);
	this->game->window.draw(this->game->prompt);

	return;
}

void GameStateMenu::update(const float dt) {}

void GameStateMenu::handleInput() {
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
				else if(event.key.code == sf::Keyboard::Return) {
					this->loadgame();
					std::cout << "Entered game setup." << std::endl;
				}
				break;
			}
			default: 
				break;
		}
	}
	return;
}

GameStateMenu::GameStateMenu(Game* game) {
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

void GameStateMenu::loadgame() {
	this->game->pushState(new GameStateSetup(this->game));
	return;
}










