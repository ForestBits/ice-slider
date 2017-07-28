#include "ScreenList.h"

using namespace ice;
using namespace ice::screen;

Credits::Credits(ScreenConstructionParameters parameters) : backButton(parameters.mainFont, parameters.activeButtonTexture, parameters.inactiveButtonTexture, parameters.clickSound)
{
    menuBackgroundSprite.setTexture(parameters.menuBackgroundTexture);

    musicText.setFont(parameters.mainFont);
    musicText.setCharacterSize(20);
    musicText.setFillColor(sf::Color::Black);
    musicText.setString("Music: \"Mining by Moonlight\", by Kevin Macleod");
    musicText.setOrigin(musicText.getGlobalBounds().width/2, musicText.getGlobalBounds().height/2);
    musicText.setPosition(320, 50);

    fontText.setFont(parameters.mainFont);
    fontText.setCharacterSize(20);
    fontText.setFillColor(sf::Color::Black);
    fontText.setString("Font: \"Pacifico\", by Vernon Adams");
    fontText.setOrigin(fontText.getGlobalBounds().width/2, fontText.getGlobalBounds().height/2);
    fontText.setPosition(320, 100);

    sfmlLogoSprite.setTexture(parameters.sfmlLogoTexture);
    sfmlLogoSprite.setOrigin(sfmlLogoSprite.getGlobalBounds().width/2, sfmlLogoSprite.getGlobalBounds().height/2);
    sfmlLogoSprite.setPosition(320, 240);

    backButton.setText("Menu");
    backButton.setPosition(320, 400);
    backButton.setOnClick([parameters] {parameters.control.setScreen<MainMenu>(parameters);});
}

void Credits::update(ScreenUpdateParameters parameters)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        throw "(quitting application)";

    EventQueue events(parameters.window);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::Closed)
            throw "(quitting application)";
    }

    backButton.update(events, getMousePosition(parameters.window));
}

void Credits::draw(sf::RenderTarget & target, const TransitionInfo & transition)
{
    target.draw(menuBackgroundSprite);
    target.draw(musicText);
    target.draw(fontText);
    target.draw(sfmlLogoSprite);

    backButton.draw(target);

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

double Credits::getTransitionInTime() {return 1;}
double Credits::getTransitionOutTime() {return 1;}