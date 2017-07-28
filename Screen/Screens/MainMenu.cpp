#include "ScreenList.h"
#include "../../Utility/EventQueue.h"

using namespace ice;
using namespace ice::screen;

MainMenu::MainMenu(ScreenConstructionParameters parameters) : 
                                playButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound), 
                                instructionsButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound),
                                optionsButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound),  
                                creditsButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound),
                                quitButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound)
{
    playButton.setOnClick([parameters] {parameters.control.setScreen<LevelSelect>(parameters);});
    playButton.setPosition(320, 96);
    playButton.setText("Play");

    instructionsButton.setOnClick([parameters] {parameters.control.setScreen<Instructions1>(parameters);});
    instructionsButton.setPosition(320, 175);
    instructionsButton.setText("Instructions");
    
    optionsButton.setOnClick([parameters] {parameters.control.setScreen<Options>(parameters);});
    optionsButton.setPosition(320, 254);
    optionsButton.setText("Options");

    creditsButton.setOnClick([parameters] {parameters.control.setScreen<Credits>(parameters);});
    creditsButton.setPosition(320, 333);
    creditsButton.setText("Credits");

    quitButton.setOnClick([] {throw "Can't catch this (da na na na)";});
    quitButton.setPosition(320, 412);
    quitButton.setText("Quit");

    if (parameters.music.getStatus() != sf::Music::Playing)
        parameters.music.play();

    menuBackgroundSprite.setTexture(parameters.menuBackgroundTexture);
}

void MainMenu::update(ScreenUpdateParameters parameters)
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

    playButton.update(events, mousePosition);
    instructionsButton.update(events, mousePosition);
    optionsButton.update(events, mousePosition);
    creditsButton.update(events, mousePosition);
    quitButton.update(events, mousePosition);
}

void MainMenu::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.draw(menuBackgroundSprite);

    playButton.draw(target);
    instructionsButton.draw(target);
    optionsButton.draw(target);
    creditsButton.draw(target);
    quitButton.draw(target);

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

double MainMenu::getTransitionInTime() {return 1;}
double MainMenu::getTransitionOutTime() {return 1;}
