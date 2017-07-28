#include <cassert>
#include "Slider.h"

using namespace ice;
using namespace ice::input;

Slider::Slider(const sf::Font & font, const sf::Texture & barTexture, const sf::Texture & sliderTexture, const sf::Texture & activeSliderTexture, sf::Sound & updateSound) : inactiveSlider(sliderTexture), activeSlider(activeSliderTexture), updateSound(updateSound)
{
    barSprite.setTexture(barTexture);
    sliderSprite.setTexture(sliderTexture);

    label.setFont(font);

    label.setFillColor(sf::Color::Black);
    label.setCharacterSize(20);

    recalculate();
}

void Slider::recalculate()
{
    barSprite.setPosition(position.x, position.y);

    label.setPosition(position.x - (label.getGlobalBounds().width + 5), (position.y + barSprite.getGlobalBounds().height/2) - label.getGlobalBounds().height/2);

    sliderSprite.setPosition(position.x + (barSprite.getGlobalBounds().width - sliderSprite.getGlobalBounds().width)*percent, (position.y + barSprite.getGlobalBounds().height/2) - sliderSprite.getGlobalBounds().height/2);
}

double Slider::getPercent()
{
    return (sliderSprite.getPosition().x - position.x)/(barSprite.getGlobalBounds().width - sliderSprite.getGlobalBounds().width);
}

void Slider::setPercent(double percent)
{
    assert(percent >= 0 && percent <= 1 && "percent must be in range [0, 1]");

    this->percent = percent;
    
    recalculate();
}

void Slider::setLabel(const std::string & string)
{
    label.setString(string);

    recalculate();
}

void Slider::setOnUpdate(const std::function<void (double percent)> & function)
{
    onUpdate = function;
}

void Slider::setPosition(int x, int y) {setPosition({x, y});}
void Slider::setPosition(sf::Vector2i position)
{
    this->position = position;

    recalculate();
}

void Slider::update(EventQueue events, sf::Vector2i mousePosition)
{
    bool contains = sliderSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);

    for (sf::Event event : events)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (contains && !active)
                active = true;
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (active)
            {
                active = false;

                updateSound.play();
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            if (active)
            {
                int newX = mousePosition.x - sliderSprite.getGlobalBounds().width/2;

                if (sliderSprite.getPosition().x == newX)
                    return;

                if (newX < position.x)
                    newX = position.x;

                if (newX > (position.x + barSprite.getGlobalBounds().width) - sliderSprite.getGlobalBounds().width)
                    newX = (position.x + barSprite.getGlobalBounds().width) - sliderSprite.getGlobalBounds().width;

                sliderSprite.setPosition(newX, sliderSprite.getPosition().y);

                percent = getPercent();

                if (onUpdate)
                    onUpdate(percent);
            }
        }
    }

    if ((active || contains) && sliderSprite.getTexture() != &activeSlider)
        sliderSprite.setTexture(activeSlider);

    if (!active && !contains && sliderSprite.getTexture() != &inactiveSlider)
        sliderSprite.setTexture(inactiveSlider);
}

void Slider::draw(sf::RenderTarget & target)
{
    target.draw(barSprite);
    target.draw(sliderSprite);
    target.draw(label);
}