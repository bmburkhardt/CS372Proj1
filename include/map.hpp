#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;

#include "tile.hpp"

class Map 
{

public:
	unsigned int width;
	unsigned int height;

	vector<Tile> tiles;

	// Resource map
	vector<int> resources;

	unsigned int tileSize;
	unsigned int numSelected;
	unsigned int numRegions[1];

	// Load map from disk
	void load(const string &filename, unsigned int width, unsigned int height, map<string, Tile> &tileAtlas);

	// Save map to disk
	void save(const string &filename);

	// Draw the map
	void draw(sf::RenderWindow &window, float dt);

	// Checks if one position in the map is connected to another by
	// only traversing tiles in the whitelist
	void findConnectedRegions(vector<TileType> whitelist, int regionType);

	// Update the direction of directional tiles so that they face the 
	// correct way. Used to orient water, ships, hits, misses, etc.
	void updateDirection(TileType tileType);

	// Blank map ctor
	Map() 
	{
		this->tileSize = 8;
		this->width = 0;
		this->height = 0;
		this->numRegions[0] = 1;
	}

	// Load map from file ctor
	Map(const string &filename, unsigned int width, unsigned int height, map<string, Tile> &tileAtlas) {
		this->tileSize = 8;
		load(filename, width, height, tileAtlas);
	}

private:
	void depthfirstsearch(vector<TileType> &whitelist, sf::Vector2i pos, int label, int type);
};







#endif // MAP_HPP