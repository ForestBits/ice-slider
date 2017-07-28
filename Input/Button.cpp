#include "Button.h"

using namespace ice;
using namespace ice::input;

Button::Button(const sf::Font & font, const sf::Texture & activeTexture, const sf::Texture & inactiveTexture, sf::Sound & clickSound) : activeTexture(activeTexture), inactiveTexture(inactiveTexture), clickSound(clickSound)
{
    text.setCharacterSize(20);

    text.setFillColor(sf::Color::Black);

    text.setFont(font);
    
    sprite.setTexture(inactiveTexture);
}

void Button::recalculate()
{
    if (centered)
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
    else
        text.setOrigin(0, 0);

    text.setPosition(position.x, position.y);

    double xFactor = text.getGlobalBounds().width/sprite.getGlobalBounds().width;
    double yFactor = text.getGlobalBounds().height/sprite.getGlobalBounds().height;

    if (text.getString().isEmpty())
    {
        xFactor = 1;
        yFactor = 1;
    }

    if (xFactor < 1)
        xFactor = 1;

    if (yFactor < 1)
        yFactor = 1;

    sprite.scale(xFactor, yFactor);

    sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);

    sprite.setPosition(text.getPosition().x + text.getGlobalBounds().width/2, text.getPosition().y + text.getGlobalBounds().height/2);

    if (centered)
    {
        sf::Vector2f position = sprite.getPosition();

        position.x -= text.getGlobalBounds().width/2;
        position.y -= text.getGlobalBounds().height/2;

        sprite.setPosition(position);
    }
}

void Button::setText(std::string string)
{
    text.setString(string);

    recalculate();
}

void Button::setPosition(int x, int y, bool centered) {setPosition({x, y}, centered);}

void Button::setPosition(sf::Vector2i position, bool centered)
{
    this->position = position;
    this->centered = centered;

    recalculate();
}

void Button::setOnClick(const std::function<void ()> & function)
{
    onClick = function;
}

void Button::update(EventQueue events, sf::Vector2i mousePosition)
{
    bool contains = sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);

    if (contains && sprite.getTexture() != &activeTexture)
        sprite.setTexture(activeTexture);

    if (!contains && sprite.getTexture() != &inactiveTexture)
        sprite.setTexture(inactiveTexture);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::MouseButtonPressed && contains)
            pressed = true;

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            if (contains)
            {
                if (pressed)
                {
                    clickSound.play();

                    if (onClick)
                        onClick();
                }
            }
            else
                pressed = false;
        }
    }
}

void Button::draw(sf::RenderTarget & target)
{
    target.draw(sprite);
    target.draw(text);
}