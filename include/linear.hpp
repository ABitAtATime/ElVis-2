
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


private: // sorting algorithms
    void merge_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
    void quick_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
    void radix_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
    void heap_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
    void bubble_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
    void insertion_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
    void selection_sort(sf::RenderWindow& window, unsigned int width, unsigned int height);
private: // helper functions of sorting
    void metge(); // mergesort
    void partition(); // quicksort
    void count_sort(); // radiz
    void heapify(sf::RenderWindow& window, unsigned int width, unsigned int height, int N, unsigned int i); // heap

private:
    void visualize(sf::RenderWindow& window, unsigned int width, unsigned int height);
    std::vector<int> data;
    unsigned int data_size;
    int max;
};