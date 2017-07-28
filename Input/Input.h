//an input element is something such as a button or textbox

#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics/RenderTarget.hpp>
#include "../Utility/EventQueue.h"

namespace ice { namespace input {

class Input
{
public:
    virtual void update(EventQueue events, sf::Vector2i mousePosition) = 0;

    virtual void draw(sf::RenderTarget & target) = 0;
};

}}

#endif