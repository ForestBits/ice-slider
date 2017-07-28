#include "ScreenList.h"
#include "../../Game/Levels.h"

using namespace ice;
using namespace ice::screen;

Instructions3::Instructions3(ScreenConstructionParameters parameters) : level(parameters.spriteSheet, parameters.textureRectangles),
                                                                                                            backButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound),
                                                                                                            previousButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound)
{
    menuBackgroundSprite.setTexture(parameters.menuBackgroundTexture);

    level.setData(LevelList::getLevels()[11]);

    backButton.setText("Menu");
    backButton.setPosition(320, 400);
    backButton.setOnClick([parameters] {parameters.control.setScreen<MainMenu>(parameters);});

    previousButton.setText("Previous");
    previousButton.setPosition(30, 240, false);
    previousButton.setOnClick([parameters] {parameters.control.setScreen<Instructions2>(parameters);});

    lessonText.setFont(parameters.mainFont);
    lessonText.setCharacterSize(20);
    lessonText.setFillColor(sf::Color::Black);
    lessonText.setString("You can change directions on snow");
    lessonText.setOrigin(lessonText.getGlobalBounds().width/2, lessonText.getGlobalBounds().height/2);
    lessonText.setPosition(320, 50);
}

void Instructions3::update(ScreenUpdateParameters parameters)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        throw "(quitting application)";

    EventQueue events(parameters.window);

    for (sf::Event event : events)
        if (event.type == sf::Event::Closed)
            throw "(quitting application)";

    sf::Vector2i mousePosition = getMousePosition(parameters.window);

    backButton.update(events, mousePosition);
    previousButton.update(events, mousePosition);

    level.update();
}

void Instructions3::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.draw(menuBackgroundSprite);
    target.draw(lessonText);

    backButton.draw(target);
    previousButton.draw(target);

    level.draw(target, sf::FloatRect(0.2, 0.2, 0.6, 0.55));

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

double Instructions3::getTransitionInTime() {return 1;}
double Instructions3::getTransitionOutTime() {return 1;}