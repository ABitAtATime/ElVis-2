#pragma once

#include "linear.hpp"

class Button;


class ElVis
{
public:
    ElVis();
    bool isRunning();
    void update();
    void draw();
private:
    void initHomeButton();
    void initAlgoButton();
    void initUiButton();
    void handleHomeMouseEvent(int posX, int posY);
    void handleSelectorMouseEvent(int posX, int posY);
    void drawHome();
    void drawAlgorithmSelector();
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture home_backgound_texture;
    sf::Texture algoselect_texture;
    std::vector<Button> home_buttons;
    std::vector<Button> sorting_algo_buttons;
    std::vector<Button> path_algo_buttons;
    std::vector<Button> ui_buttons;
    unsigned int window_width, window_height;
    Linear linear;
    GameState state;
    std::optional<SortingAlgorithm> sorting_algo;
    std::optional<PathFindingAlgorithm>path_find_algo;
};



class Button : public sf::RectangleShape {
public:
    Button(const sf::Vector2f &size, const std::string str, sf::Font& font, float char_size_scale=0.75) : sf::RectangleShape(size) {
        text.setFont(font);
        text.setCharacterSize(static_cast<unsigned int>(size.y * char_size_scale));
        text.setFillColor(sf::Color::Black);
        text.setString(str);
        this->setFillColor(sf::Color::Green);
        this->str = str;
    }
    void setButtonPosition(const sf::Vector2f& position);
    bool isMouseOver(int posX, int posY);
    std::string getOriginalString();
    void draw(sf::RenderWindow& window);
private:
    sf::Text text;
    std::string str;
};