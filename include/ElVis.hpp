#pragma once

#include <SFML/Graphics.hpp>

#include "linear.hpp"


class ElVis
{
public:
    ElVis();
    bool isRunning();
    void update();
    void draw();
private:
    sf::RenderWindow window;
    unsigned int window_width, window_height;
    Linear linear;
};