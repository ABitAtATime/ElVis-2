#include <stdexcept>
#include <filesystem>
#include <iostream>
#include "ElVis.hpp"

ElVis::ElVis() {
    window_width = 1200;
    window_height = 900;
    window.create(sf::VideoMode(window_width, window_height), "ElVis The Algorithm Visualizer");
    linear.newData(1000);
    state = GameState::Home;

    if (!font.loadFromFile("res/fonts/Tektur.ttf")) {
        // /std::cerr << std::filesystem::current_path() << std::endl;
        throw std::runtime_error("Failed to laod font from res/fonts/Tektur.ttf");
    }

    if (!home_backgound_texture.loadFromFile("res/backgounds/home_backgound.jpg")) {
        throw std::runtime_error("Failed to load backgound image");
    }
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
    }
}

void ElVis::drawHome() {
    window.clear();

    sf::Sprite background_sprite;
    background_sprite.setTexture(home_backgound_texture);


    sf::Text home_text;
    home_text.setFont(font);
    home_text.setString("ElVis The Algorithm Visualizer");

    home_text.setFillColor(sf::Color::Red);
    home_text.setCharacterSize(50);
    home_text.setPosition((window_width - home_text.getLocalBounds().width) / 2, 100);


    Button button(sf::Vector2f(window_width / 4, 70), "Algorithms", font);
    button.setButtonPosition(sf::Vector2f((window_width - button.getSize().x) / 2, 200));


    window.draw(background_sprite);
    window.draw(home_text);
    button.draw(window);


    window.display();
}

void ElVis::draw() {
    switch (state) {
        case GameState::Home:
            // TODO state machine logic
            state = GameState::Home;
            drawHome();
            break;
    }
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
