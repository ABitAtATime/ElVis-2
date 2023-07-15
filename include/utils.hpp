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

const auto AlgorithmList = {
    "BubbleSort",
    "InsertionSort"
};