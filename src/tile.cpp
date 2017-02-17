#include <SFML/Graphics.hpp>

#include "../include/animationHandler.hpp"
#include "../include/tile.hpp"
#include <string>
using std::string;

void Tile::draw(sf::RenderWindow &window, float dt){
	// Change the sprite to reflect the tile variant
	this->animHandler.changeAnim(this->tileVariant);

	// update the animation
	this->animHandler.update(dt);

	// update the sprite
	this->sprite.setTextureRect(this->animHandler.bounds);

	// draw the tile
	window.draw(this->sprite);

	return;
}

void Tile::update() {
	/************************************************
	*												*
	*   			WE NEED TO DO this 				*
	*												*
	************************************************/
}

string tileTypeToStr(TileType type) {
	switch(type) {
		default:
		case TileType::VOID:			return "Void";
		case TileType::HIT:				return "Hit";
		case TileType::MISS:			return "Miss";
		case TileType::SHIP:			return "Ship";
		case TileType::WATER:			return "Water";
		case TileType::SUNK:			return "Sunk";
	}
}

