#include <SFML/Graphics.hpp>
#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
using std::ofstream;

#include "../include/map.hpp"
#include "../include/tile.hpp"

// Load map from disk
	void Map::load( const string &filename, unsigned int width, unsigned int height, map<string, Tile> &tileAtlas) {
		ifstream inputFile;
		inputFile.open(filename, std::ios::in | std::ios::binary);

		this->width = width;
		this->height = height;

		for(int pos = 0; pos < this->width * this->height; ++pos)
		{
			this->resources.push_back(255);

			TileType tileType;
			inputFile.read((char*)&tileType, sizeof(int));
			switch(tileType)
			{
				default:
				case TileType::VOID:
				case TileType::WATER:
					this->tiles.push_back(tileAtlas.at("water"));
					break;
				case TileType::SHIP:
					this->tiles.push_back(tileAtlas.at("ship"));
					break;
				case TileType::HIT:
					this->tiles.push_back(tileAtlas.at("hit"));
					break;
				case TileType::MISS:
					this->tiles.push_back(tileAtlas.at("miss"));
					break;
				case TileType::SUNK:
					this->tiles.push_back(tileAtlas.at("sunk"));
					break;
			}
			Tile &tile = this->tiles.back();
			inputFile.read((char*)&tile.tileVariant, sizeof(int));
			inputFile.read((char*)&tile.regions, sizeof(int)*1);
		}
		
		inputFile.close();
		return;
	}

	// Save map to disk
	void Map::save(const string &filename) {
		ofstream outputFile;
		outputFile.open(filename, std::ios::out | std::ios::binary);

		for(auto tile : this->tiles)
		{
			outputFile.write((char*)&tile.tileType, sizeof(int));
			outputFile.write((char*)&tile.tileVariant, sizeof(int));
			outputFile.write((char*)&tile.regions, sizeof(int)*1);
		}

		outputFile.close();
		return;
	}

	// Draw the map
	void Map::draw(sf::RenderWindow &window, float dt) {
		for(int y = 0; y < this->height; ++y)
		{
			for(int x = 0; x < this->width; ++x)
			{
				// Set the position of the tile in the 2d world
				sf::Vector2f pos;
				pos.x = (x-y) * this->tileSize + this->width * this->tileSize;
				pos.y = (x+y) * this->tileSize * 0.5;
				this->tiles[y*this->width+x].draw(window, dt);
			}
		}

		return;
	}

	// Checks if one position in the map is connected to another by
	// only traversing tiles in the whitelist
	void Map::findConnectedRegions(vector<TileType> whitelist, int regionType) {
		int regions = 1;

		for(auto& tile : this->tiles)
			tile.regions[regionType] = 0;

		for(int y = 0; y < this->height; ++y) {
			for(int x = 0; x < this->width; ++x) {
				bool found = false;
				for(auto type : whitelist) {
					if(type == this->tiles[y*this->width+x].tileType) {
						found = true;
						break;
					}
				}
				if(this->tiles[y*this->width+x].regions[regionType] == 0 && found) {
					depthfirstsearch(whitelist, sf::Vector2i(x, y), regions++, regionType);
				}
			}
		}
		this->numRegions[regionType] = regions;
	}

	// Update the direction of directional tiles so that they face the 
	// correct way. Used to orient water, ships, hits, misses, etc.
	void Map::updateDirection(TileType tileType) {
		for(int y = 0; y < this->height; ++y) {
			for(int x = 0; x < this->width; ++x) {
				int pos = y*this->width+x;
				if(this->tiles[pos].tileType != tileType)
					continue;

				bool adjacentTiles[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

				// check for adjacent tiles of the same type
				if(x > 0 && y > 0)
					adjacentTiles[0][0] = (this->tiles[(y-1)*this->width+(x-1)].tileType == tileType);
				if(y > 0)
					adjacentTiles[0][3] = (this->tiles[(y-1)*this->width+(x)].tileType == tileType);
				if(x < this->width-1 && y > 0)
					adjacentTiles[0][4] = (this->tiles[(y-1)*this->width+(x+1)].tileType == tileType);
				if(x > 0)
					adjacentTiles[1][0] = (this->tiles[(y)*this->width+(x-1)].tileType == tileType);
				if(x < width-1)
					adjacentTiles[1][5] = (this->tiles[(y)*this->width+(x+1)].tileType == tileType);
				if(x > 0 && y < this->height-1)
					adjacentTiles[2][0] = (this->tiles[(y+1)*this->width+(x-1)].tileType == tileType);
				if(y < this->height-1)
					adjacentTiles[2][6] = (this->tiles[(y+1)*this->width+(x)].tileType == tileType);
				if(x < this->width-1 && y < this->height-1)
					adjacentTiles[2][7] = (this->tiles[(y+1)*this->width+(x+1)].tileType == tileType);

				// Change the tile variant depending on the tile position
            	if(adjacentTiles[1][0] && adjacentTiles[1][8] && adjacentTiles[0][9] && adjacentTiles[2][10])
                	this->tiles[pos].tileVariant = 2;
            	else if(adjacentTiles[1][0] && adjacentTiles[1][11] && adjacentTiles[0][12])
                	this->tiles[pos].tileVariant = 7;
            	else if(adjacentTiles[1][0] && adjacentTiles[1][13] && adjacentTiles[2][14])
                	this->tiles[pos].tileVariant = 8;
            	else if(adjacentTiles[0][15] && adjacentTiles[2][16] && adjacentTiles[1][0])
                	this->tiles[pos].tileVariant = 9;
            	else if(adjacentTiles[0][16] && adjacentTiles[2][17] && adjacentTiles[1][18])
                	this->tiles[pos].tileVariant = 10;
            	else if(adjacentTiles[1][0] && adjacentTiles[1][19])
                	this->tiles[pos].tileVariant = 0;
            	else if(adjacentTiles[0][20] && adjacentTiles[2][21])
                	this->tiles[pos].tileVariant = 1;
            	else if(adjacentTiles[2][22] && adjacentTiles[1][0])
                	this->tiles[pos].tileVariant = 3;
            	else if(adjacentTiles[0][23] && adjacentTiles[1][24])
                	this->tiles[pos].tileVariant = 4;
            	else if(adjacentTiles[1][0] && adjacentTiles[0][25])
                	this->tiles[pos].tileVariant = 5;
            	else if(adjacentTiles[2][26] && adjacentTiles[1][27])
                	this->tiles[pos].tileVariant = 6;
            	else if(adjacentTiles[1][0])
                	this->tiles[pos].tileVariant = 0;
            	else if(adjacentTiles[1][28])
                	this->tiles[pos].tileVariant = 0;
            	else if(adjacentTiles[0][29])   
                	this->tiles[pos].tileVariant = 1;
            	else if(adjacentTiles[2][30])
                	this->tiles[pos].tileVariant = 1;
			}
		}
		return;
	}

	void Map::depthfirstsearch(vector<TileType> &whitelist, sf::Vector2i pos, int label, int regionType=0)
	{
		if(pos.x < 0 || pos.x >= this->width) 
			return;
		if(pos.y < 0 || pos.y >= this->height)
			return;
		if(this->tiles[pos.y*this->width+pos.x].regions[regionType] != 0)
			return;
		bool found = false;

		for(auto type : whitelist)
		{
			if(type == this->tiles[pos.y*this->width+pos.x].tileType) {
				found = true;
				break;
			}
		}
		if(!found)
			return;

		this->tiles[pos.y*this->width+pos.x].regions[regionType] = label;

		depthfirstsearch(whitelist, pos + sf::Vector2i(-1, 0), label, regionType);
		depthfirstsearch(whitelist, pos + sf::Vector2i(0, 1), label, regionType);
		depthfirstsearch(whitelist, pos + sf::Vector2i(1, 0), label, regionType);
		depthfirstsearch(whitelist, pos + sf::Vector2i(0, -1), label, regionType);
		
		return;
	}








