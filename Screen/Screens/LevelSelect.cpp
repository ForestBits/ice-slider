#include <fstream>
#include <cassert>
#include "ScreenList.h"
#include "../../Game/Levels.h"

using namespace ice;
using namespace ice::screen;

LevelSelect::LevelSelect(ScreenConstructionParameters parameters) : 
                                    backButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound)
{
    menuBackgroundSprite.setTexture(parameters.menuBackgroundTexture);

    backButton.setText("Menu");
    backButton.setPosition(320, 400);
    backButton.setOnClick([parameters] {parameters.control.setScreen<MainMenu>(parameters);});

    //loading what level we are on from file

    int currentLevel;

    std::fstream file;

    file.open("level.txt", std::ios::in);

    if (!file || file.peek() == std::ifstream::traits_type::eof())
    {
        //file doesn't exist yet

        file.clear();

        currentLevel = 1;

        file.open("level.txt", std::ios::out);

        file << '1';
    }
    else
    {
        //file is valid

        file >> currentLevel;
    }

    auto setLevel = [parameters] (int number) 
    {
        assert(number >= 0 && number < LevelList::getLevels().size() + 1 && "Tried to access level that does not exist");

        parameters.control.setScreen<Play>(parameters, LevelList::getLevels()[number - 1], number);
    };

    for (int x = 0; x < 4; ++x)
        for (int y = 0; y < 2; ++y)
        {
            input::LevelSelectButton button(parameters.mainFont, parameters.levelSelectInactiveTexture, parameters.levelSelectActiveTexture, parameters.levelSelectLockedTexture, parameters.clickSound);

            button.setPosition(x*100 + 140, y*70 + 100);

            button.setLocked(y*3 + x + 1 + y > currentLevel);

            button.setNumber(y*3 + x + 1 + y);

            button.setOnClick(setLevel);

            levelButtons.push_back(button);
        }

    {
        input::LevelSelectButton button(parameters.mainFont, parameters.levelSelectInactiveTexture, parameters.levelSelectActiveTexture, parameters.levelSelectLockedTexture, parameters.clickSound);

        button.setPosition(293, 250);
        button.setLocked(9 > currentLevel);
        button.setNumber(9);
        button.setOnClick(setLevel);

        levelButtons.push_back(button);
    }
}

void LevelSelect::update(ScreenUpdateParameters parameters)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        throw "(quitting application)";

    EventQueue events(parameters.window);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::Closed)
            throw "(quitting application)";
    }

    sf::Vector2i mousePosition = getMousePosition(parameters.window);

    backButton.update(events, mousePosition);

    for (auto & button : levelButtons)
        button.update(events, mousePosition);
}

void LevelSelect::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.draw(menuBackgroundSprite);

    backButton.draw(target);

    for (auto & button : levelButtons)
        button.draw(target);

    if (transition.transitioningIn || transition.transitioningOut)
    {
        if (transition.transitioningIn)
            menuBackgroundSprite.setColor(sf::Color(255, 255, 255, (1 - transition.transitionPercent)*255));
        else if (transition.transitioningOut)
            menuBackgroundSprite.setColor(sf::Color(255, 255, 255, transition.transitionPercent*255));

        target.draw(menuBackgroundSprite);

        menuBackgroundSprite.setColor(sf::Color::White);
    }
}

double LevelSelect::getTransitionInTime() {return 1;}
double LevelSelect::getTransitionOutTime() {return 1;}