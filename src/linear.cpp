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
        case SortingAlgorithm::merge:
            // TODO
            std::cout << "merge not implemented here have a look at insertion sort" << std::endl;
            insertion_sort(window, width, height);
            break;
        case SortingAlgorithm::quick:
            // TODO
            std::cout << "quick not implemented here have a look at insertion sort" << std::endl;
            insertion_sort(window, width, height);
            break;
        case SortingAlgorithm::radix:
            // TODO
            std::cout << "radix not implemented here have a look at insertion sort" << std::endl;
            insertion_sort(window, width, height);
            break;
        case SortingAlgorithm::heap:
            // TODO
            // std::cout << "heap not implemented here have a look at insertion sort" << std::endl;
            heap_sort(window, width, height);
            break;
        case SortingAlgorithm::selection:
            selection_sort(window, width, height);
            break;
        default:
            std::cout << "idk how you got here but have a look at insertion sort" << std::endl;
            insertion_sort(window, width, height);
    }
}



void Linear::visualize(sf::RenderWindow& window, unsigned int width, unsigned int height) {
    if (!window.isOpen()) {
        exit(1);
    }
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


// ============ Sorting algorithms only no helper funcitons ====================================================================================================

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

void Linear::selection_sort(sf::RenderWindow& window, unsigned int width, unsigned int height) {
    int min_index;
    for (int i = 0; i < data_size - 1; i++) {
        min_index = i;
        for (int j = i + 1; j < data_size; j++) {
            if (data[j] < data[min_index]) {
                min_index = j;
            }
            visualize(window, width, height);
        }
        if (min_index != i) {
            auto temp = data[i];
            data[i] = data[min_index];
            data[min_index] = temp;
        }
    }
}



void Linear::heap_sort(sf::RenderWindow& window, unsigned int width, unsigned int height)
{
    for (int i = data_size / 2 - 1; i >= 0; i--)
    {
        heapify(window, width, height, data_size,  i);
    }
    for (int i = data_size - 1; i > 0; i--)
    {
        auto temp = data[0];
        data[0] = data[i];
        data[i] = temp;

        heapify(window, width, height, i, 0);
    }
}





// =================== sorting helper functions ======================================================================

void Linear::heapify(sf::RenderWindow& window, unsigned int width, unsigned int height, int N, unsigned int i)
{
    auto largest = i;
    auto left = 2 * i + 1;
    auto right = 2 * i + 2;
    if (left < N && data[left] > data[largest])
    {
        largest = left;
    }
    if (right < N && data[right] > data[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        auto temp = data[i];
        data[i] = data[largest];
        data[largest] = temp;
        visualize(window, width, height);
        Linear::heapify(window, width, height, N, largest);
    }
}