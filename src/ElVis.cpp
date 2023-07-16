#include <stdexcept>
#include <filesystem>
#include <iostream>
#include "ElVis.hpp"

ElVis::ElVis() {
    window_width = 1600;
    window_height = 900;
    window.create(sf::VideoMode(window_width, window_height), "ElVis The Algorithm Visualizer", sf::Style::Titlebar | sf::Style::Close);
    linear.newData(1000);
    state = GameState::Home;

    if (!font.loadFromFile("res/fonts/Tektur.ttf")) {
        // /std::cerr << std::filesystem::current_path() << std::endl;
        throw std::runtime_error("Failed to laod font from res/fonts/Tektur.ttf");
    }

    if (!home_backgound_texture.loadFromFile("res/backgounds/home_backgound.jpg")) {
        throw std::runtime_error("Failed to load home backgound image");
    }

    if (!algoselect_texture.loadFromFile("res/backgounds/algoselectbg.jpg")) {
        throw std::runtime_error("Failed to load algorithm selector backgound image");
    }

    initHomeButton();
    initAlgoButton();
}

bool ElVis::isRunning() {
    return window.isOpen();
}

void ElVis::update() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (state == GameState::Home) {
                handleHomeMouseEvent(event.mouseButton.x, event.mouseButton.y);
            } else if(state == GameState::Selector) {
                handleSelectorMouseEvent(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
}

void ElVis::drawHome() {
    // std::cout << "testhome" << std::endl;
    window.clear();

    sf::Sprite background_sprite;
    background_sprite.setTexture(home_backgound_texture);
    background_sprite.setScale(window.getSize().x / background_sprite.getLocalBounds().width, window.getSize().y / background_sprite.getLocalBounds().height);


    sf::Text home_text;
    home_text.setFont(font);
    home_text.setString("ElVis The Algorithm Visualizer");

    home_text.setFillColor(sf::Color::Red);
    home_text.setCharacterSize(50);
    home_text.setPosition((window_width - home_text.getLocalBounds().width) / 2, 100);


    window.draw(background_sprite);
    window.draw(home_text);
    for (auto& btn : home_buttons) {
        btn.draw(window);
    }


    window.display();
}

void ElVis::drawAlgorithmSelector() {
    // std::cout << "test" << std::endl;
    window.clear();

    sf::Sprite background_sprite;
    background_sprite.setTexture(algoselect_texture);
    background_sprite.setScale(window.getSize().x / background_sprite.getLocalBounds().width, window.getSize().y / background_sprite.getLocalBounds().height);

    window.draw(background_sprite);
    for (auto& btn : algo_buttons) {
        btn.draw(window);
    }

    window.display();
}

void ElVis::draw() {
    switch (state) {
        case GameState::Home:
            drawHome();
            break;
        case GameState::Selector:
            drawAlgorithmSelector();
            break;
        default:
            window.close();
    }
}



void ElVis::initHomeButton() {
    const auto button_size = sf::Vector2f(window_width / 4, 70);
    const auto button_texts = {"Algorithms", "Options", "Quit"};
    unsigned int i = 0;
    for (auto text : button_texts) {
        home_buttons.emplace_back(Button(button_size, text, font));
        home_buttons[i].setButtonPosition(sf::Vector2f(window_width / 2 - button_size.x / 2, 200 + i * 100));
        i++;
    }

}


void ElVis::initAlgoButton() {
    const auto button_size = sf::Vector2f(window_width / 4, 70);
    const float padWidth = 6.25;
    const float padHeight = 20.0;
    unsigned int i = 0;
    for (const auto& text : AlgorithmList) {
        algo_buttons.emplace_back(Button(button_size, text, font));
        algo_buttons[i].setButtonPosition(sf::Vector2f( (i % 3) * (padWidth + button_size.x), (i / 3) * (padHeight + button_size.y) ));
        i++;
    } 
}

void ElVis::handleHomeMouseEvent(int posX, int posY) {
    // std::cout << "Handle called" << std::endl;
    for (auto& btn: home_buttons) {
        if (btn.isMouseOver(posX, posY)) {
            auto btn_str = btn.getOriginalString();
            if (btn_str == "Quit") {
                window.close();

            } else if (btn_str == "Options") {
                // TODO options
                // std::cout << "No options available for now" << std::endl;
            } else if (btn_str == "Algorithms") {
                // std::cout << "Entering algorithm selector" << std::endl;
                state = GameState::Selector;
            }
        }
    }
}

void ElVis::handleSelectorMouseEvent(int posX, int posY) {

} 


// =========== Button ======================================================================================================================

void Button::setButtonPosition(const sf::Vector2f& position) {
    setPosition(position);
    sf::FloatRect buttonBounds = getGlobalBounds();
    sf::Vector2f textPosition(buttonBounds.left + buttonBounds.width / 2 - text.getLocalBounds().width / 2,
                              buttonBounds.top + buttonBounds.height * 0.05f);
    text.setPosition(textPosition);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(*this);
    window.draw(text);
}

bool Button::isMouseOver(int posX, int posY) {
    return getGlobalBounds().contains(static_cast<float>(posX), static_cast<float>(posY));
}

std::string Button::getOriginalString() {
    return str;
}
