#include <sstream>
#include "LevelSelectButton.h"

using namespace ice;
using namespace ice::input;

LevelSelectButton::LevelSelectButton(const sf::Font & font, const sf::Texture & inactiveTexture, const sf::Texture & activeTexture, const sf::Texture & lockedTexture, sf::Sound & clickSound) : inactiveTexture(inactiveTexture), activeTexture(activeTexture), lockedTexture(lockedTexture), clickSound(clickSound)
{
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    sprite.setTexture(inactiveTexture);
}

void LevelSelectButton::setLocked(bool locked) 
{
    this->locked = locked;

    if (locked)
        sprite.setTexture(lockedTexture);
    else
        sprite.setTexture(inactiveTexture);
}

void LevelSelectButton::setNumber(int number)
{
    this->number = number;

    std::ostringstream stream;

    stream << number;

    text.setString(stream.str());

    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);

    text.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width/2, sprite.getPosition().y + sprite.getGlobalBounds().height/2);
}

void LevelSelectButton::setPosition(int x, int y) {setPosition({x, y});}
void LevelSelectButton::setPosition(sf::Vector2i position)
{
    sprite.setPosition(position.x, position.y);

    text.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width/2, sprite.getPosition().y + sprite.getGlobalBounds().height/2);
}

void LevelSelectButton::setOnClick(const std::function<void (int number)> & function) {this->onClick = function;}

void LevelSelectButton::update(EventQueue events, sf::Vector2i mousePosition)
{
    bool contains = sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);

    if (contains && !locked && sprite.getTexture() != &activeTexture)
        sprite.setTexture(activeTexture);

    if (!contains && !locked && sprite.getTexture() != &inactiveTexture)
        sprite.setTexture(inactiveTexture);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::MouseButtonPressed)
            if (contains)
                active = true;

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (contains && active && !locked)
            {
                //click

                if (onClick)
                    onClick(number);

                clickSound.play();
            }

            active = false;
        }
    }
}

void LevelSelectButton::draw(sf::RenderTarget & target)
{
    target.draw(sprite);

    if (!locked)
        target.draw(text);
}