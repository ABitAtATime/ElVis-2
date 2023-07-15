#include <SFML/Graphics.hpp>

enum SortingAlgorithm {
    bubble,
    insertion,
};

enum GameState {
    Home,
    Selector,
    Visualization,
    VisualizationComplete
};


//TODO seperate algorithms by types
const auto AlgorithmList = {
    "BubbleSort",
    "InsertionSort"
};