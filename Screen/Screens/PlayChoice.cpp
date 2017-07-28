//comes up after completing a level: you can play it again, go to the level select screen, or play the next level

#include "ScreenList.h"
#include "../../Game/Levels.h"

using namespace ice;
using namespace ice::screen;

PlayChoice::PlayChoice(ScreenConstructionParameters parameters, int currentLevelNumber) :
                                 restartButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound),
                                 levelSelectButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound),
                                 nextLevelButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound)
{
    hasNext = currentLevelNumber < 9; //9 = highest level reachable

    text.setFont(parameters.mainFont);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    text.setString("Level Complete!");
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
    text.setPosition(320, 100);

    menuBackgroundSprite.setTexture(parameters.menuBackgroundTexture);
    menuBackgroundSprite.setTextureRect(sf::IntRect(0, 0, 480, 400));
    menuBackgroundSprite.setPosition(80, 48);

    restartButton.setPosition(320, 200);
    restartButton.setText("Replay");
    restartButton.setOnClick([parameters, currentLevelNumber] {parameters.control.setScreen<Play>(parameters, LevelList::getLevels()[currentLevelNumber - 1], currentLevelNumber);});

    levelSelectButton.setPosition(320, 300);
    levelSelectButton.setText("Level Select");
    levelSelectButton.setOnClick([parameters] {parameters.control.setScreen<LevelSelect>(parameters);});

    nextLevelButton.setPosition(320, 400);
    nextLevelButton.setText("Next Level");
    nextLevelButton.setOnClick([parameters, currentLevelNumber] {parameters.control.setScreen<Play>(parameters, LevelList::getLevels()[currentLevelNumber], currentLevelNumber + 1);});

    render.create(640, 480);

    bool fullscreen = parameters.window.getSize().x == sf::VideoMode::getFullscreenModes()[0].width && parameters.window.getSize().y == sf::VideoMode::getFullscreenModes()[0].height;

    if (fullscreen)
    {
        sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0];

        backgroundTexture.create(fullscreenMode.width, fullscreenMode.height);
    }
    else
        backgroundTexture.create(640, 480);

    backgroundTexture.update(parameters.window);

    backgroundSprite.setTexture(backgroundTexture);

    //the drawn level is taken as a texture for the background of this screen
    //if it is fullscreen, however, it is that dimensions, rather than 640*480
    //the view only displays this, however, so it misses most of it
    //if fullscreen, we scale the sprite so it all displays in the window

    if (fullscreen)
        backgroundSprite.scale(640/parameters.window.getSize().x, 480/parameters.window.getSize().y);
}

void PlayChoice::update(ScreenUpdateParameters parameters)
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

    restartButton.update(events, mousePosition);
    levelSelectButton.update(events, mousePosition);
    if (hasNext) nextLevelButton.update(events, mousePosition);
}

void PlayChoice::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.draw(backgroundSprite);

    render.clear(sf::Color::Transparent);

    render.draw(menuBackgroundSprite);
    render.draw(text);

    restartButton.draw(render);
    levelSelectButton.draw(render);
    if (hasNext) nextLevelButton.draw(render);

    render.display();

    sprite.setTexture(render.getTexture());

    if (transition.transitioningIn)
    {
        sprite.setColor(sf::Color(255, 255, 255, transition.transitionPercent*255));
    }
    else
        sprite.setColor(sf::Color::White);

    target.draw(sprite);
}

double PlayChoice::getTransitionInTime() {return 1;}
double PlayChoice::getTransitionOutTime() {return 0;}