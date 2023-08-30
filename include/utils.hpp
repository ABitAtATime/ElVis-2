#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <filesystem>
#include <random>
#include <thread>
#include <chrono>
#include <optional>
#include <iostream>
#include <fstream>

enum SortingAlgorithm {
    bubble,
    insertion,
    selection,
    merge,
    quick,
    radix,
    heap,
};

enum PathFindingAlgorithm {
    dfs,
    bfs,
    astar,
    dijkstra,
};



// //TODO seperate algorithms by types
// const auto AlgorithmList = {
//     "BubbleSort",
//     "InsertionSort",
//     "MergeSort",
//     "QuickSort",
//     "RadixSort",
//     "HeapSort",
//     "DFS",
//     "BFS",
//     "AStar",
//     "Dijkstra",
// };


const std::map<std::string, SortingAlgorithm> SortingAlgorithmMap = {
    {"BubbleSort", bubble},
    {"InsertionSort", insertion},
    {"SelectionSort", selection},
    {"MergeSort", merge},
    {"QuickSort", quick},
    {"RadixSort", radix},
    {"HeapSort", heap}
};

const std::map<std::string, PathFindingAlgorithm> PathFindingAlgorithmMap = {
    {"DFS", dfs},
    {"BFS", bfs},
    {"AStar", astar},
    {"Dijkstra", dijkstra}
};

enum GameState {
    Home,
    Selector,
    Visualization,
    VisualizationComplete
};
