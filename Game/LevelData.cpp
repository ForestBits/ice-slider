#include <cassert>
#include "LevelData.h"

using namespace ice;

LevelData::LevelData(int x, int y) : LevelData(sf::Vector2i(x, y)) {}
LevelData::LevelData(sf::Vector2i dimensions) : startPosition(1, 1), endPosition(1, 2), size(dimensions)
{
    assert(dimensions.x > 0 && dimensions.y > 0 && "Levels must have positive dimensions");

    tiles.resize(dimensions.x);

    for (int i = 0; i < dimensions.x; ++i)
        tiles[i].resize(dimensions.y);

    for (int x = 0; x < dimensions.x; ++x)
        for (int y = 0; y < dimensions.y; ++y)
        {
            tiles[x][y].block = Block::ICE;
            tiles[x][y].visual.textureRectangle = sf::IntRect(0, 0, 32, 32);
        }
}

Block LevelData::getBlockType(int x, int y) const {return getBlockType({x, y});}
Block LevelData::getBlockType(sf::Vector2i coordinates) const
{
    assert(coordinates.x >= 0 && coordinates.y >= 0 && coordinates.x < size.x && coordinates.y < size.y && "coordinates must be inbounds");

    return tiles[coordinates.x][coordinates.y].block;
}

VisualTile  LevelData::getVisualTile(int x, int y) const {return getVisualTile({x, y});}
VisualTile  LevelData::getVisualTile(sf::Vector2i coordinates) const
{
    assert(coordinates.x >= 0 && coordinates.y >= 0 && coordinates.x < size.x && coordinates.y < size.y && "coordinates must be inbounds");

    return tiles[coordinates.x][coordinates.y].visual;
}

sf::Vector2i LevelData::getStartPosition() const {return startPosition;}
sf::Vector2i LevelData::getEndPosition() const {return endPosition;}

sf::Vector2i LevelData::getSize() const {return size;}

const std::string & LevelData::getTitle() const {return title;}

void LevelData::setBlockType(int x, int y, Block type) {setBlockType({x, y}, type);}
void LevelData::setBlockType(sf::Vector2i coordinates, Block type)
{
     assert(coordinates.x >= 0 && coordinates.y >= 0 && coordinates.x < size.x && coordinates.y < size.y && "coordinates must be inbounds");

     tiles[coordinates.x][coordinates.y].block = type;
}

void LevelData::setVisualTile(int x, int y, VisualTile visual) {setVisualTile({x, y}, visual);}
void LevelData::setVisualTile(sf::Vector2i coordinates, VisualTile visual)
{
     assert(coordinates.x >= 0 && coordinates.y >= 0 && coordinates.x < size.x && coordinates.y < size.y && "coordinates must be inbounds");

     tiles[coordinates.x][coordinates.y].visual = visual;
}

void LevelData::setStartPosition(int x, int y) {setStartPosition({x, y});}
void LevelData::setStartPosition(sf::Vector2i coordinates) {startPosition = coordinates;}

void LevelData::setEndPosition(int x, int y) {setEndPosition({x, y});}
void LevelData::setEndPosition(sf::Vector2i coordinates) {endPosition = coordinates;}

void LevelData::setTitle(const std::string & title) {this->title = title;}
