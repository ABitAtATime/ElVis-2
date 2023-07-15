#include <thread>

#include "ElVis.hpp"

ElVis::ElVis() {
    window_width = 1200;
    window_height = 900;
    window.create(sf::VideoMode(window_width, window_height), "ElVis The Algorithm Visualizer");
    linear.newData(1000);
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

void ElVis::draw() {
    linear.visualAlgo(SortingAlgorithm::insertion, window, window_width, window_height);
}