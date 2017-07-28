#include <fstream>
#include "ScreenList.h"
#include "../../Utility/StringNumberConvert.h"

using namespace ice;
using namespace ice::screen;

//convert time in seconds to standard format time string
static std::string getTimeAsString(int seconds)
{
    int secs = seconds;
    int mins = 0;
    int hours = 0;

    while (secs >= 3600)
    {
        ++hours;

        secs -= 3600;
    }

    while (secs >= 60)
    {
        ++mins;

        secs -= 60;
    }

    std::string time;

    if (hours != 0)
        time += toString(hours) + ":";

    if (mins == 0)
    {
        if (hours != 0)
            time += "00:";
    }
    else
        if (mins >= 10)
            time += toString(mins) + ":";
        else
            if (hours != 0)
                time += "0" + toString(mins) + ":";
            else
                time += toString(mins) + ":";

    if (secs >= 10)
        time += toString(secs);
    else
        if (mins != 0 || hours != 0)
            time += "0" + toString(secs);
        else
            time += toString(secs);

    return time;
}

Play::Play(ScreenConstructionParameters parameters, const LevelData & levelData, int levelNumber) : level(parameters.spriteSheet, parameters.textureRectangles)
{
    this->levelNumber = levelNumber;

    menuBackgroundSprite.setTexture(parameters.menuBackgroundTexture);

    level.setData(levelData);

    level.setOnMove([this] 
    {
        ++moveCount;

        moveCountText.setString(std::string("Moves: ") + toString(moveCount));
    });

    level.setOnFinish([parameters, levelNumber] 
    {
        //find level number in file: if the next level number is higher, set it to that instead

        int currentFileLevel;

        std::fstream file;

        file.open("level.txt", std::ios::in);

        if (!file || file.peek() == std::ifstream::traits_type::eof())
        {
            //file doesn't exist yet

            file.clear();

            currentFileLevel = 1;
        }
        else
        {
            //file is valid

            file >> currentFileLevel;
        }

        if (levelNumber  + 1 > currentFileLevel)
        {
            file.clear();

            file.close();

            //clearing all file contents
            file.open("level.txt", std::ios::out | std::ios::trunc);

            file << levelNumber + 1;
        }

        parameters.control.setScreen<PlayChoice>(parameters, levelNumber);
    });

    levelTitleText.setFont(parameters.mainFont);
    levelTitleText.setCharacterSize(20);
    levelTitleText.setPosition(10, 5);
    levelTitleText.setFillColor(sf::Color::White);
    levelTitleText.setString("Level " + toString(levelNumber) + ": \"" + levelData.getTitle() + "\"");

    moveCountText.setFont(parameters.mainFont);
    moveCountText.setCharacterSize(20);
    moveCountText.setPosition(400, 5);
    moveCountText.setFillColor(sf::Color::White);
    moveCountText.setString(std::string("Moves: ") + "0");

    timeText.setFont(parameters.mainFont);
    timeText.setCharacterSize(20);
    timeText.setPosition(500, 5);
    timeText.setFillColor(sf::Color::White);
    timeText.setString("Time: " + getTimeAsString(time));
}

void Play::update(ScreenUpdateParameters parameters)
{
    //useful when making levels
    //std::cout << sf::Mouse::getPosition(parameters.window).x/32 << "  " << (sf::Mouse::getPosition(parameters.window).y - 48)/29 << "\n";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        throw "(quitting application)";

    EventQueue events(parameters.window);

    bool tempPressed = false;

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::Closed)
            throw "(quitting application)";

        if (event.type == sf::Event::KeyReleased)
            pressed = false;
        else if (event.type == sf::Event::KeyPressed)
            tempPressed = true;
    }
    //change this if it no longer slides smoothly
    //if (!pressed)
        level.update();

    if (tempPressed)
        pressed = true;

    if (clock.getElapsedTime().asSeconds() >= 1)
    {
        timeRemainder += clock.restart().asSeconds();

        while (timeRemainder >= 1)
        {
            --timeRemainder;

            ++time;
        }

        timeText.setString("Time: " + getTimeAsString(time));
    }
}

void Play::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.clear(sf::Color::Black);

    target.draw(levelTitleText);
    target.draw(moveCountText);
    target.draw(timeText);

    level.draw(target, sf::FloatRect(0, 0.1, 1, 0.9));

    if (transition.transitioningIn)
    {
        menuBackgroundSprite.setColor(sf::Color(255, 255, 255, (1 - transition.transitionPercent)*255));

        target.draw(menuBackgroundSprite);
    }
}

double Play::getTransitionInTime() {return 1;}
double Play::getTransitionOutTime() {return 0;}