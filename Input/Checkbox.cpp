#include "Checkbox.h"

using namespace ice;
using namespace ice::input;

Checkbox::Checkbox(const sf::Font & font, const sf::Texture & boxTexture, const sf::Texture & activeBoxTexture, const sf::Texture & checkTexture, sf::Sound & clickSound) : inactiveBackground(boxTexture), activeBackground(activeBoxTexture), clickSound(clickSound)
{
    label.setFont(font);
    label.setCharacterSize(20);
    label.setFillColor(sf::Color::Black);

    boxSprite.setTexture(boxTexture);
    checkSprite.setTexture(checkTexture);

    recalculate();
}

void Checkbox::recalculate()
{
    boxSprite.setPosition(position.x, position.y);
    
    checkSprite.setPosition(position.x, position.y);

    label.setPosition(position.x - (label.getGlobalBounds().width + 5), (position.y + boxSprite.getGlobalBounds().height/2) - label.getGlobalBounds().height/2);
}

bool Checkbox::getChecked() {return checked;}

void Checkbox::setChecked(bool checked) {this->checked = checked;}

void Checkbox::setPosition(int x, int y) {setPosition({x, y});}
void Checkbox::setPosition(sf::Vector2i position)
{
    this->position = position;

    recalculate();
}

void Checkbox::setText(const std::string & string) 
{
    label.setString(string);

    recalculate();
}

void Checkbox::setOnClick(const std::function<void (bool checked)> & function) {onClick = function;}

void Checkbox::update(EventQueue events, sf::Vector2i mousePosition)
{
    bool contains = boxSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);

    if (contains && boxSprite.getTexture() != &activeBackground)
        boxSprite.setTexture(activeBackground);
    
    if (!contains && boxSprite.getTexture() != &inactiveBackground)
        boxSprite.setTexture(inactiveBackground);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (contains)
                active = true;
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (active && contains)
            {
                //toggled

                checked = !checked;

                clickSound.play();

                if (onClick)
                    onClick(checked);
            }

            active = false;
        }
    }
}

void Checkbox::draw(sf::RenderTarget & target)
{
    target.draw(boxSprite);
    target.draw(label);

    if (checked)
        target.draw(checkSprite);
}