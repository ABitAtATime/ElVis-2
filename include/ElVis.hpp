#pragma once

#include <SFML/Graphics.hpp>

#include "linear.hpp"

class Button;


class ElVis
{
public:
    ElVis();
    bool isRunning();
    void update();
    void draw();
    void drawHome();
private:
    void initHomeButton();
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture home_backgound_texture;
    std::vector<Button> home_buttons;
    unsigned int window_width, window_height;
    Linear linear;
    GameState state;

};



class Button : public sf::RectangleShape {
public:
    Button(const sf::Vector2f &size, const std::string& str, sf::Font& font) : sf::RectangleShape(size) {
        text.setFont(font);
        text.setCharacterSize(static_cast<unsigned int>(size.y * 0.75));
        text.setFillColor(sf::Color::Black);
        text.setString(str);
        this->setFillColor(sf::Color::Green);
    }
    void setButtonPosition(const sf::Vector2f& position);

    void draw(sf::RenderWindow& window);
private:
    sf::Text text;
};