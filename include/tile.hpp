#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
using std::vector;
#include <string>
using std::string;

#include "animationHandler.hpp"

enum class TileType { VOID, HIT, MISS, SHIP, WATER, SUNK };

string tileTypeToStr(TileType type);

class Tile
{
public:
	AnimationHandler animHandler;
	sf::Sprite sprite;

	TileType tileType;

	// Tile variant allowing for different looking versions of the same tile
	int tileVariant;

	Tile() {}

	Tile(const unsigned int tileSize, const unsigned int height, sf::Texture &texture,
		const vector<Animation> &animations, const TileType tileType)
	{
		this->tileType = tileType;
		this->tileVariant = 0;

		this->sprite.setOrigin(sf::Vector2f(0.0f, tileSize*(height-1)));
		this->sprite.setTexture(texture);
		this->animHandler.frameSize = sf::IntRect(0, 0, tileSize*2, tileSize*height);
		for(auto animation : animations) {
			this->animHandler.addAnim(animation);
		}

		this->animHandler.update(0.0f);
	}

	void draw(sf::RenderWindow &window, float dt);

	void update();

};

#endif // TILE_HPP
