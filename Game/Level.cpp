#include <SFML/Window/Keyboard.hpp>
#include <cassert>
#include "Level.h"

using namespace ice;

Player::Player() : Player(sf::Vector2i(0, 0)) {}
Player::Player(int x, int y) : Player(sf::Vector2i(x, y)) {}
Player::Player(sf::Vector2i position) : rate(5.5), blockPosition(position), position(position.x, position.y) {}

sf::Vector2i Player::getEndPosition(Direction direction, const std::vector<std::vector<Block>> & blocks, sf::Vector2i goalPosition)
{
    sf::Vector2i endPosition;

    auto getPosition = [] (sf::Vector2i position, Direction direction) 
    {
        switch (direction)
        {
        case Direction::LEFT:
            --position.x;

            break;

        case Direction::RIGHT:
            ++position.x;

            break;

        case Direction::DOWN:
            ++position.y;

            break;

        case Direction::UP:
            --position.y;

            break;
        }

        return position;
    };

    sf::Vector2i newPosition = getPosition(blockPosition, direction);

    if (newPosition == goalPosition)
        return newPosition;

    //if the move goes out of the level, we cannot move
    if (newPosition.x < 0 || newPosition.y < 0 || newPosition.x >= blocks.size() || newPosition.y >= blocks[0].size())
        return blockPosition;

    Block newType = blocks[newPosition.x][newPosition.y];

    switch (newType)
    {
    case Block::WALL:
        return blockPosition; //running into walls hurts

        break;

    case Block::GROUND:
        return newPosition;

        break;

    case Block::ICE:
        //we slide untill we hit a wall, or reach the ground

        sf::Vector2i finalIcePosition;

        sf::Vector2i currentIcePosition = newPosition;

        while (true)
        {
            currentIcePosition = getPosition(currentIcePosition, direction);

            if (currentIcePosition == goalPosition)
                return currentIcePosition;

            if (currentIcePosition.x < 0 || currentIcePosition.y < 0 || currentIcePosition.x >= blocks.size() || currentIcePosition.y >= blocks[0].size()
                || blocks[currentIcePosition.x][currentIcePosition.y] == Block::WALL)
            {
                if (direction == Direction::RIGHT)
                    finalIcePosition = getPosition(currentIcePosition, Direction::LEFT);

                if (direction == Direction::LEFT)
                    finalIcePosition = getPosition(currentIcePosition, Direction::RIGHT);

                if (direction == Direction::UP)
                    finalIcePosition = getPosition(currentIcePosition, Direction::DOWN);

                if (direction == Direction::DOWN)
                    finalIcePosition = getPosition(currentIcePosition, Direction::UP);

                break;
            }


            if (blocks[currentIcePosition.x][currentIcePosition.y] == Block::GROUND)
            {
                finalIcePosition = currentIcePosition;

                break;
            }
        }

        return finalIcePosition;
    }
}

PlayerMoveResult Player::move(const std::vector<std::vector<Block>> & blocks, sf::Vector2i goalPosition)
{
    if (moving)
    {
        Direction moveDirection;

        if (endPosition.x > blockPosition.x)
            moveDirection = Direction::RIGHT;
        else if (endPosition.x < blockPosition.x)
            moveDirection = Direction::LEFT;
        else if (endPosition.y > blockPosition.y)
            moveDirection = Direction::UP;
        else if (endPosition.y < blockPosition.y)
            moveDirection = Direction::DOWN;

        int totalDistance = std::abs((blockPosition.x - endPosition.x) + (blockPosition.y - endPosition.y));

        double timeMoveTakes = totalDistance/rate;

        double movePercent = clock.getElapsedTime().asSeconds()/timeMoveTakes;

        if (movePercent >= 1)
        {
            moving = false;

            blockPosition = endPosition;

            position.x = blockPosition.x;
            position.y = blockPosition.y;

            if (blockPosition == goalPosition)
                return PlayerMoveResult::REACHED_END;
        }
        else
        {
            switch (moveDirection)
            {
            case Direction::LEFT:
                position.x = blockPosition.x - totalDistance*movePercent;

                break;

            case Direction::RIGHT:
                position.x = blockPosition.x + totalDistance*movePercent;

                break;

            case Direction::DOWN:
                position.y = blockPosition.y - totalDistance*movePercent;

                break;

            case Direction::UP:
                position.y = blockPosition.y + totalDistance*movePercent;
            }
        }

        return PlayerMoveResult::DID_NOT_MOVE;
    }
    else
    {
        Direction moveDirection;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            moveDirection = Direction::UP;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            moveDirection = Direction::DOWN;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            moveDirection = Direction::LEFT;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            moveDirection = Direction::RIGHT;
        else
            return PlayerMoveResult::DID_NOT_MOVE;

        endPosition = getEndPosition(moveDirection, blocks, goalPosition);

        //if we haven't moved
        if (endPosition == blockPosition)
            return PlayerMoveResult::DID_NOT_MOVE;

        moving = true;

        clock.restart();

        return PlayerMoveResult::DID_NOT_REACH_END;
    }
}

sf::Vector2f Player::getPosition() {return position;}

void Player::setPosition(int x, int y) {setPosition({x, y});}
void Player::setPosition(sf::Vector2i position) 
{
    blockPosition = position;

    this->position.x = position.x;
    this->position.y = position.y;
}

void Player::setRate(double rate) {this->rate = rate;}

Level::Level(const sf::Texture & spriteSheet, const std::unordered_map<std::string, sf::IntRect> & textureRectangles)
{
    sprite.setTexture(spriteSheet);

    playerSubRect = textureRectangles.at("player");
}

void Level::setData(const LevelData & data)
{
    size = data.getSize();
    title = data.getTitle();
    startPosition = data.getStartPosition();
    endPosition = data.getEndPosition();

    blocks.resize(data.getSize().x);
    visuals.resize(data.getSize().x);

    for (int i = 0; i < size.x; ++i)
    {
        blocks[i].resize(data.getSize().y);
        visuals[i].resize(data.getSize().y);
    }

    for (int x = 0; x < size.x; ++x)
        for (int y = 0; y < size.y; ++y)
        {
            blocks[x][y] = data.getBlockType(x, y);
            visuals[x][y] = data.getVisualTile(x, y);
        }

    player.setPosition(startPosition);
}

void Level::setOnMove(const std::function<void ()> & function) {onMove = function;}
void Level::setOnFinish(const std::function<void ()> & function) {onFinish = function;}

void Level::update() 
{
    switch (player.move(blocks, endPosition))
    {
    case PlayerMoveResult::DID_NOT_REACH_END:
        if (onMove)
            onMove();

        break;

    case PlayerMoveResult::REACHED_END:
        if (onMove)
            onMove();

        if (onFinish)
            onFinish();

        break;

    case PlayerMoveResult::DID_NOT_MOVE:
        ;

        break;
    }
}

void Level::draw(sf::RenderTarget & target, sf::FloatRect bounds)
{
    assert(bounds.left >= 0 && bounds.top >= 0 && bounds.left + bounds.width <= 1 && bounds.top + bounds.height <= 1 && "drawing rectangle must all be in screen");

    sf::View oldView = target.getView();

    sf::View newView;

    newView.setViewport(bounds);

    newView.setSize(32*size.x, 32*size.y);

    newView.setCenter(16*size.x, 16*size.y);

    target.setView(newView);

    //update animations

    for (int x = 0; x < size.x; ++x)
        for (int y = 0; y < size.y; ++y)
            if (visuals[x][y].animation != nullptr)
                visuals[x][y].textureRectangle = visuals[x][y].animation->getCurrentFrameRectangle();

    for (int x = 0; x < size.x; ++x)
        for (int y = 0; y < size.y; ++y)
        {
            sf::IntRect rectangle = visuals[x][y].textureRectangle;

            sprite.setTextureRect(rectangle);

            sprite.setPosition(x*32, y*32);

            target.draw(sprite);
        }

    sprite.setTextureRect(playerSubRect);

    sprite.setPosition(player.getPosition().x*32, player.getPosition().y*32);

    target.draw(sprite);

    target.setView(oldView);
}