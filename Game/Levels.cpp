#include <cassert>
#include "Levels.h"
#include "Animation.h"

using namespace ice;

std::vector<LevelData> LevelList::levels;

std::unordered_map<std::string, Animation> LevelList::animations;

bool LevelList::init = false;

const std::vector<LevelData> & LevelList::getLevels() 
{
    assert(init && "level list must be initialized before use");

    return levels;
}

void LevelList::initialize(const sf::Texture & spriteSheet, const std::unordered_map<std::string, sf::IntRect> & textureRectangles)
{
    assert(!init && "Only initialize the level list once");

    init = true;

    //setup things before creating levels (create animations, etc)

    animations["water"] = Animation(spriteSheet, {
        {textureRectangles.at("water1"), 0.1},
        {textureRectangles.at("water2"), 0.1},
        {textureRectangles.at("water3"), 0.1}
    });

    VisualTile snowTile, finishTile, iceTile, rockTile, snowmanTile, waterTile, verticalBridgeTile,
                   secretRockTile, deerTile, santaTile, treeTile;

    snowTile.textureRectangle = textureRectangles.at("snow");
    finishTile.textureRectangle = textureRectangles.at("finish");
    iceTile.textureRectangle = textureRectangles.at("ice");
    rockTile.textureRectangle = textureRectangles.at("rocks");
    snowmanTile.textureRectangle = textureRectangles.at("snowman");
    waterTile.animation = &animations["water"];
    verticalBridgeTile.textureRectangle = textureRectangles.at("verticalbridge");
    secretRockTile.textureRectangle = textureRectangles.at("secretrock");
    deerTile.textureRectangle = textureRectangles.at("deer");
    santaTile.textureRectangle = textureRectangles.at("santa");
    treeTile.textureRectangle = textureRectangles.at("tree");

    /////

    int currentLevel = 0;

    auto set = [&currentLevel] (int x, int y, std::pair<Block, VisualTile> pair) {levels[currentLevel].setBlockType(x, y, pair.first); levels[currentLevel].setVisualTile(x, y, pair.second);};

    auto ice = std::make_pair(Block::ICE, iceTile);
    auto snow = std::make_pair(Block::GROUND, snowTile);
    auto rock = std::make_pair(Block::WALL, rockTile);
    auto finish = std::make_pair(Block::GROUND, finishTile);
    auto snowman = std::make_pair(Block::WALL, snowmanTile);
    auto water = std::make_pair(Block::WALL, waterTile);
    auto verticalBridge = std::make_pair(Block::GROUND, verticalBridgeTile);
    auto secretRock = std::make_pair(Block::GROUND, secretRockTile);
    auto deer = std::make_pair(Block::WALL, deerTile);
    auto santa = std::make_pair(Block::WALL, santaTile);
    auto tree = std::make_pair(Block::WALL, treeTile);

    ///////////////

    sf::Vector2i dimensions = {20, 15};

    for (int i = 0; i < 12; ++i)
        levels.push_back(LevelData(dimensions.x, dimensions.y));

    levels[0].setTitle("Simple Sliding");
    levels[0].setStartPosition(0, 7);
    levels[0].setEndPosition(19, 7);

    for (int x = 0; x < dimensions.x; ++x)
        for (int y = 0; y < dimensions.y; ++y)
            set(x, y, ice);

    set(0, 7, snow);
    set(19, 7, finish);
    set(18, 7, rock);
    set(17, 1, rock);
    set(1, 2, rock);
    set(2, 9, rock);
    set(19, 9, rock);
    set(7, 0, rock);
    set(18, 2, rock);

    currentLevel = 1;

    levels[1].setTitle("Secret Passages");
    levels[1].setStartPosition(0, 0);
    levels[1].setEndPosition(19, 14);

    for (int x = 0; x < dimensions.x; ++x)
        for (int y = 0; y < dimensions.y; ++y)
            set(x, y, snow);

    for (int y = 0; y < 10; ++y)
        set(3, y, rock);

    set(3, 3, secretRock);

    set(19, 14, finish);

    for (int y = dimensions.y - 2; y >= 3; --y)
        set(6, y, rock);

    for (int y = dimensions.y - 1; y >= 1; --y)
        set(13, y, rock);

    set(4, 9, rock);
    set(5, 7, rock);
    set(4, 5, rock);
    set(5, 3, rock);

    for (int x = 14; x < dimensions.x; ++x)
        for (int y = 1; y < dimensions.y - 2; ++y)
            set(x, y, rock);

    set(19, 1, secretRock);
    set(19, 2, secretRock);
    set(18, 2, secretRock);
    set(18, 3, secretRock);
    set(18, 4, secretRock);
    set(17, 4, secretRock);
    set(16, 4, secretRock);
    set(15, 4, secretRock);
    set(15, 5, secretRock);
    set(15, 6, secretRock);
    set(14, 6, secretRock);
    set(14, 7, secretRock);
    set(14, 8, secretRock);
    set(14, 9, secretRock);
    set(15, 9, secretRock);
    set(16, 9, secretRock);
    set(16, 10, secretRock);
    set(16, 11, secretRock);
    set(15, 11, secretRock);
    set(14, 11, secretRock);
    set(17, 10, secretRock);
    set(18, 10, secretRock);
    set(18, 11, secretRock);
    set(18, 12, secretRock);
    set(13, 4, secretRock);
    set(14, 4, secretRock);

    currentLevel = 2;

    levels[2].setTitle("Frosty, the snowman...");
    levels[2].setStartPosition(0, 5);
    levels[2].setEndPosition(dimensions.x - 1, 8);

    for (int x = 0; x < dimensions.x; ++x)
        for (int y = 0; y < dimensions.y; ++y)
            set(x, y, ice);

    set(dimensions.x - 1, 8, finish);

    set(1, 5, snowman);
    set(2, 9, snowman);
    set(3, 0, snowman);
    set(4, 2, snowman);
    set(5, 13, snowman);
    set(6, 4, snowman);
    set(7, 14, snowman);
    set(8, 0, snowman);
    set(9, 11, snowman);
    set(10, 3, snowman);
    set(11, 6, snowman);
    set(12, 7, snowman);
    set(13, 10, snowman);
    set(14, 8, snowman);
    set(15, 3, snowman);
    set(16, 9, snowman);
    set(17, 13, snowman);
    set(18, 2, snowman);
    set(19, 6, snowman);


    currentLevel = 3;

    levels[3].setTitle("Across the River");
    levels[3].setStartPosition(0, 0);
    levels[3].setEndPosition(dimensions.x - 1, 8);

    for (int x = 0; x < dimensions.x; ++x)
        for (int y = 0; y < dimensions.y; ++y)
            set(x, y, ice);

    set(dimensions.x - 1, 8, finish);

    set(2, 0, water);
    set(2, 1, water);
    set(2, 2, water);
    set(3, 2, water);
    set(3, 3, water);
    set(3, 4, water);
    set(4, 4, water);
    set(4, 5, water);
    set(4, 6, water);
    set(5, 6, water);
    set(6, 6, water);
    set(7, 6, water);
    set(8, 6, water);
    set(9, 6, water);
    set(9, 7, water);
    set(10, 7, water);
    set(11, 7, water);
    set(12, 7, water);
    set(12, 8, water);
    set(13, 8, water);
    set(13, 9, water);
    set(13, 10, water);
    set(13, 11, water);
    set(13, 12, water);
    set(13, 13, water);
    set(13, 14, water);

    set(11, 7, verticalBridge);

    set(1, 13, rock);
    set(6, 12, rock);
    set(0, 10, rock);
    set(5, 7, rock);
    set(2, 6, rock);
    set(10, 12, rock);
    set(2, 8, rock);
    set(15, 11, rock);
    set(15, 13, rock);
    set(16, 14, rock);
    set(15, 3, rock);
    set(4, 0, rock);
    set(16, 5, rock);
    set(19, 7, rock);
    set(11, 0, snow);
    set(7, 4, rock);
    set(18, 1, rock);
    set(13, 2, rock);
    set(8, 1, rock);


    currentLevel = 4;

    levels[4].setTitle("Ho ho ho!");
    levels[4].setStartPosition(0, 14);
    levels[4].setEndPosition(19, 0);

    for (int x = 0; x < dimensions.x; ++x)
        for (int y = 0; y < dimensions.y; ++y)
            set(x, y, ice);

    for (int x = 3; x < 12; ++x)
        for (int y = 8; y < 12; ++y)
            set(x, y, snow);

    for (int x = 4; x < 10; ++x)
        for (int y = 10; y >= 9; --y)
            set(x, y, deer);

    set(10, 9, santa);

    set(19, 0, finish);
    set(18, 0, rock);
    set(19, 3, rock);
    set(6, 14, rock);
    set(2, 0, rock);
    set(3, 0, rock);
    set(11, 1, rock);
    set(10, 7, rock);
    set(15, 6, rock);
    set(14, 14, rock);
    set(19, 13, rock);
    set(11, 4, rock);
    set(1, 7, rock);
    set(4, 5, rock);
    set(14, 2, rock);
    set(5, 2, rock);
    set(16, 3, rock);


    currentLevel = 5;
    
    levels[5].setTitle("The Forest of Trees"); //because you might have a forest of gophers or something
    levels[5].setStartPosition(0, 14);
    levels[5].setEndPosition(10, 0);

    for (int x = 0; x < dimensions.x; ++x)
        for (int y = 0; y < dimensions.y; ++y)
            set(x, y, ice);

    for (int x = 0; x < dimensions.x; ++x)
        for (int y = 0; y < 6; ++y)
            set(x, y, tree);

    set(10, 5, snow);

    set(9, 6, rock);
    set(18, 6, rock);
    set(13, 14, rock);
    set(12, 10, snow);
    set(3, 10, rock);
    set(4, 13, rock);
    set(1, 12, rock);
    set(2, 7, rock);
    set(18, 8, rock);
    set(12, 8, rock);
    set(17, 14, rock);
    set(4, 6, rock);
    set(6, 12, rock);

    for (int x = 1; x < 19; ++x)
    {
        set(x, 4, snow);
        set(x, 2, snow);
    }

    set(1, 3, snow);
    set(18, 3, snow);
    set(1, 1, snow);
    set(10, 2, tree);
    set(8, 2, tree);
    set(9, 2, tree);
    set(8, 1, snow);
    set(9, 1, snow);
    set(10, 1, snow);

    for (int x = 1; x < 9; ++x)
        set(x, 0, snow);

    set(10, 0, finish);

    currentLevel = 6;

    levels[6].setTitle("Over the Pond");
    levels[6].setStartPosition(0, 0);
    levels[6].setEndPosition(19, 14);

    for (int x = 0; x < 20; ++x)
        for (int y = 0; y < 15; ++y)
            set(x, y, ice);

    set(19, 14, finish);

    for (int x = 0; x < 20; ++x)
        for (int y = 4; y < 10; ++y)
            set(x, y, water);

    for (int x = 2; x < 20; ++x)
        set(x, 3, water);

    for (int x = 0; x < 18; ++x)
        set(x, 10, water);

    for (int x = 6; x < 9; ++x)
        for (int y = 3; y < 11; ++y)
            set(x, y, verticalBridge);

    set(1, 1, rock);
    set(12, 0, rock);
    set(13, 2, rock);
    set(6, 1, rock);
    set(16, 1, rock);
    set(15, 0, rock);
    set(18, 14, rock);
    set(6, 12, rock);
    set(8, 14, rock);
    set(17, 11, rock);
    set(12, 13, rock);
    set(1, 13, rock);
    set(17, 13, rock);
    set(7, 11, rock);

    currentLevel = 7;

    levels[7].setTitle("Easy Peasy");
    levels[7].setStartPosition(0, 14);
    levels[7].setEndPosition(10, 7);

    for (int x = 0; x < 20; ++x)
        for (int y = 0; y < 15; ++y)
            set(x, y, ice);

    
    set(18, 14, rock);
    set(17, 1, rock);
    set(3, 2, rock);
    set(16, 11, rock);
    set(4, 12, rock);
    set(16, 10, rock);
    set(15, 4, rock);
    set(6, 5, rock);
    set(7, 10, rock);
    set(14, 9, rock);
    set(13, 6, rock);
    set(1, 4, rock);
    set(1, 7, rock);
    set(1, 13, rock);
    set(4, 0, rock);
    set(7, 0, rock);
    set(10, 0, rock);
    set(2, 1, rock);
    set(10, 6, rock);
    set(9, 7, rock);
    set(10, 8, rock);

    set(10, 7, finish);

    currentLevel = 8;

    levels[8].setTitle("Isle O' Woodcutters");
    levels[8].setStartPosition(19, 14);
    levels[8].setEndPosition(0, 0);

    for (int x = 0; x < 20; ++x)
        for (int y = 0; y < 15; ++y)
            set(x, y, ice);

    for (int x = 5; x < 9; ++x)
        for (int y = 5; y < 9; ++y)
            set(x, y, snow);

    for (int x = 0; x < 20; ++x)
    {
        set(x, 0, tree);
        set(x, 1, tree);

        set(x, 13, tree);
        set(x, 14, tree);
    }

    set(19, 14, snow);
    set(19, 13, snow);
    set(18, 13, snow);
    set(0, 1, snow);
    set(19, 1, snow);
    set(19, 0, snow);
    set(18, 0, snow);
    set(17, 0, snow);
    set(17, 1, snow);

    set(18, 8, rock);
    set(1, 2, rock);
    set(1, 12, rock);
    set(3, 12, rock);
    set(15, 12, rock);
    set(14, 7, rock);
    set(9, 8, rock);
    set(10, 3, rock);
    set(15, 4, rock);
    set(3, 4, rock);
    set(5, 11, rock);
    set(6, 10, rock);
    set(7, 9, rock);

    for (int y = 9; y < 13; ++y)
        set(8, y, rock);

    set(0, 0, finish);


    //////////////////////INSTRUCTIONS LEVELS///////////////////////

    currentLevel = 9;

    levels[9].setTitle("Instructions 1");
    levels[9].setStartPosition(0, 0);

    for (int x = 0; x < 20; ++x)
        for (int y = 0; y < 15; ++y)
            set(x, y, ice);


    currentLevel = 10;

    levels[10].setTitle("Instructions 2");
    levels[10].setStartPosition(0, 0);

    for (int x = 0; x < 20; ++x)
        for (int y = 0; y < 15; ++y)
            set(x, y, ice);

    set(5, 14, rock);
    set(4, 6, rock);
    set(3, 5, rock);
    set(10, 5, rock);
    set(12, 9, rock);
    set(7, 3, rock);
    set(8, 7, rock);
    set(7, 0, rock);
    set(19, 5, rock);
    set(0, 2, rock);


    currentLevel = 11;

    levels[11].setTitle("Instructions 3");
    levels[11].setStartPosition(0, 0);

    for (int x = 0; x < 20; ++x)
        for (int y = 0; y < 15; ++y)
            set(x, y, ice);

    set(3, 8, snow);
    set(10, 5, snow);
    set(11, 9, snow);
    set(7, 5, snow);
    set(3, 7, snow);
    set(4, 5, snow);
    set(19, 10, snow);
    set(0, 5, snow);
    set(0, 8, snow);
    set(11, 5, snow);
    set(14, 9, snow);
    set(3, 5, snow);
    set(9, 7, snow);
    set(10, 5, snow);
    set(19, 0, snow);
    set(1, 6, snow);
    set(10, 14, snow);
    set(0, 7, snow);
    set(19, 3, snow);

    //this ensures that all tiles have a valid visual representation
    //if a tile does not set the subrectangle or animation, this will error

    #ifndef NDEBUG

    std::vector<sf::IntRect> tileList;

    for (auto & pair : textureRectangles)
        tileList.push_back(pair.second);

    std::vector<Animation *> animationList;

    animationList.push_back(&animations["water"]);

    for (LevelData & data : levels)
        for (int x = 0; x < dimensions.x; ++x)
            for (int y = 0; y < dimensions.y; ++y)
                assert( std::find(tileList.begin(), tileList.end(), data.getVisualTile(x, y).textureRectangle) != tileList.end()
                           || std::find(animationList.begin(), animationList.end(), data.getVisualTile(x, y).animation) != animationList.end()
                           && "All the visual tiles in all levels must be set");

    #endif
}