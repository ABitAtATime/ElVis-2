#include <random>

#include "linear.hpp"

Linear::Linear() : data_size{100} {
    generateRandomData();
}

Linear::Linear(unsigned int size) : data_size{size} {
    generateRandomData();
}

void Linear::newData(unsigned int size) {
    data_size = size;
    generateRandomData();
}

void Linear::generateRandomData() {
    data.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1500);
    for (size_t i = 0; i < data_size; ++i)
    {
        data.push_back(distribution(gen));
    }

    max = *max_element(data.begin(), data.end());
}

void Linear::visualAlgo(SortingAlgorithm algo, sf::RenderWindow& window, unsigned int width, unsigned int height) {
    switch (algo) {
        case SortingAlgorithm::bubble:
            bubble_sort(window, width, height);
            break;
        case SortingAlgorithm::insertion:
            insertion_sort(window, width, height);
            break;
        default:
            insertion_sort(window, width, height);
    }
}

void Linear::bubble_sort(sf::RenderWindow& window, unsigned int width, unsigned int height) {
    for (int j=0; j<(int)data_size-1; j++) {
        for (int i=j+1; i<(int)data_size; i++) {
            if (data[j] > data[i]) {
                auto temp = data[i];
                data[i] = data[j];
                data[j] = temp;
                visualize(window, width, height);
            }
        }
    }
}

void Linear::insertion_sort(sf::RenderWindow& window, unsigned int width, unsigned int height) {
    for (int j=1; j<(int)data_size; j++) {
        auto key = data[j];
        auto i = j - 1;
        while ( i >= 0 && data[i] > key) {
            data[i+1] = data[i];
            i--;
            visualize(window, width, height);
        }
        data[i+1] = key;
        visualize(window, width, height);
    }
}

void Linear::visualize(sf::RenderWindow& window, unsigned int width, unsigned int height) {
    const float columnWidth = static_cast<float>(width) / data_size;
    window.clear();
    for (int i = 0; i < (int)data_size; ++i){
        float columnHeight = (height * 0.9) * data[i] / max;
        sf::RectangleShape column(sf::Vector2f(columnWidth, columnHeight));
        column.setPosition(i * columnWidth, height - columnHeight);
        column.setFillColor(sf::Color::Blue);
        window.draw(column);
    }
    window.display();

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
    
}