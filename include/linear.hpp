
#pragma once

#include "utils.hpp"

class Linear {
public:
    Linear();
    Linear(unsigned int size);
    void newData(unsigned int size);
    void visualAlgo(SortingAlgorithm algo, sf::RenderWindow& window, unsigned int width, unsigned int height);
private:
    void generateRandomData();
private:
    void insertion_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
    void bubble_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
    void visualize(sf::RenderWindow& window, unsigned int width, unsigned int height);
    std::vector<int> data;
    unsigned int data_size;
    int max;
};