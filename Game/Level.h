//the goal of a level is to go from the start to the finish
//it is a puzzle; you slide around, trying to get in the correct position

#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "Animation.h"
#include "GameEnums.h"
#include "LevelData.h"

namespace sf {class RenderTarget;}

namespace ice {

enum class PlayerMoveResult
{
    REACHED_END,
    DID_NOT_REACH_END,
    DID_NOT_MOVE
};

class Player
{
    sf::Vector2i blockPosition;
    sf::Vector2i endPosition; //destination square being moved to
    sf::Vector2f position;

    bool moving = false;

    //blocks per second
    double rate;

    sf::Clock clock;

    //where do you end up if you move direction from current block position?
    sf::Vector2i getEndPosition(Direction direction, const std::vector<std::vector<Block>> & blocks, sf::Vector2i goalPosition);

public:
    Player();
    Player(int x, int y);
    Player(sf::Vector2i position);

    PlayerMoveResult move(const std::vector<std::vector<Block>> & blocks, sf::Vector2i goalPosition);

    sf::Vector2f getPosition();

    void setPosition(int x, int y);
    void setPosition(sf::Vector2i position);

    //blocks per second
    void setRate(double rate);
};

class Level
{
    Player player;

    sf::Vector2i size;
    sf::Vector2i startPosition;
    sf::Vector2i endPosition;

    std::string title;

    std::vector<std::vector<Block>> blocks;
    std::vector<std::vector<VisualTile>> visuals;

    sf::IntRect playerSubRect;
    sf::IntRect snowRect;

    sf::Sprite sprite;

    std::function<void ()> onMove;
    std::function<void ()> onFinish;

public:
    Level(const sf::Texture & spriteSheet, const std::unordered_map<std::string, sf::IntRect> & textureRectangles);

    void setData(const LevelData & data);

    void setOnMove(const std::function<void ()> & function);
    void setOnFinish(const std::function<void ()> & function);

    Block getTypeAdjacent(int x, int y);
    Block getTypeAdjacent(sf::Vector2i position);

    void update();

    //functions like SFML's viewrect; proportions of window size
    void draw(sf::RenderTarget & target, sf::FloatRect bounds);
};

}

#endif