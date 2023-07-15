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
        throw std::runtime_error("Failed to load backgound image");
    }
    initHomeButton();
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto pos = sf::Mouse::getPosition(window);
        // std::cout << "MousePos:= X: " << pos.x << " Y: " << pos.y << std::endl;
    }
}

void ElVis::drawHome() {
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
    for (auto btn : home_buttons) {
        btn.draw(window);
    }
    // algo_button.draw(window);
    // opt_button.draw(window);
    // quit_button.draw(window);


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
