#include "linear.hpp"

Linear::Linear() : data_size{1000}
{
    generateRandomData();
}

Linear::Linear(unsigned int size) : data_size{size}
{
    generateRandomData();
}

void Linear::newData(unsigned int size)
{
    data_size = size;
    generateRandomData();
}

void Linear::generateRandomData()
{
    data.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1500);


    //-------------------creating a file--------------------------------
    std::ofstream outputFile("notSorted.txt");
    
    for (size_t i = 0; i < data_size; ++i)
    {   
        int temp = distribution(gen);
        data.push_back(temp);
        outputFile <<temp<< std::endl;
        
    }
    outputFile.close();

    max = *max_element(data.begin(), data.end());
}

void Linear::visualAlgo(SortingAlgorithm algo, sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    switch (algo)
    {
    case SortingAlgorithm::bubble:
        bubble_sort(window, width, height);
        break;
    case SortingAlgorithm::insertion:

        insertion_sort(window, width, height);
        break;
    case SortingAlgorithm::merge:

        merge_sort(window, width, height, 0, data_size);
        break;
    case SortingAlgorithm::quick:

        quick_sort(window, width, height, 0, data_size);
        break;
    case SortingAlgorithm::radix:

        radix_sort(window, width, height);
        break;
    case SortingAlgorithm::heap:

        heap_sort(window, width, height);
        break;
    case SortingAlgorithm::selection:

        selection_sort(window, width, height);
        break;
    default:
        std::cout << "idk how you got here but have a look at heap sort" << std::endl;

        heap_sort(window, width, height);
    }
}

void Linear::visualize(sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    if (!window.isOpen())
    {
        exit(1);
    }
    const float columnWidth = static_cast<float>(width) / data_size;
    window.clear();
    for (int i = 0; i < (int)data_size; ++i)
    {
        float columnHeight = (height * 0.9) * data[i] / max;
        sf::RectangleShape column(sf::Vector2f(columnWidth, columnHeight));
        column.setPosition(i * columnWidth, height - columnHeight);
        column.setFillColor(sf::Color::Blue);
        window.draw(column);
    }
    window.display();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

// ============ Sorting algorithms only no helper funcitons ====================================================================================================

void Linear::bubble_sort(sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    for (int j = 0; j < (int)data_size - 1; j++)
    {
        for (int i = j + 1; i < (int)data_size; i++)
        {
            if (data[j] > data[i])
            {
                auto temp = data[i];
                data[i] = data[j];
                data[j] = temp;
                visualize(window, width, height);
            }
        }
    }
}

void Linear::insertion_sort(sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    for (int j = 1; j < (int)data_size; j++)
    {
        auto key = data[j];
        auto i = j - 1;
        while (i >= 0 && data[i] > key)
        {
            data[i + 1] = data[i];
            i--;
            visualize(window, width, height);
        }
        data[i + 1] = key;
        visualize(window, width, height);
    }
}
void Linear::merge_sort(sf::RenderWindow &window, unsigned int width, unsigned int height, unsigned int low, unsigned int high)
{

    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort(window, width, height, low, mid);
        merge_sort(window, width, height, mid + 1, high);
        merge(window, width, height, low, mid, high);
    }
}
void Linear ::quick_sort(sf::RenderWindow &window, unsigned int width, unsigned int height, int low, int high)
{
    if (low < high)
    {
        int pivotpos = partition(window, width, height, low, high);

        quick_sort(window, width, height, low, pivotpos - 1);
        quick_sort(window, width, height, pivotpos + 1, high);
    }
}

void Linear::selection_sort(sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    int min_index;
    for (int i = 0; i < data_size - 1; i++)
    {
        min_index = i;
        for (int j = i + 1; j < data_size; j++)
        {
            if (data[j] < data[min_index])
            {
                min_index = j;
                visualize(window, width, height);
            }
        }
        if (min_index != i)
        {
            auto temp = data[i];
            data[i] = data[min_index];
            data[min_index] = temp;
        }
    }
}

void Linear::radix_sort(sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    unsigned int m = 0;
    for (unsigned int i = 1; i <= data_size; i++)
    {
        if (data[i] > data[m])
        {
            m = i;
        }
    }
    auto max_data = data[m];
    // std::cout << max_data;

    for (int power = 1; max_data / power > 0; power *= 10)
    {
        count_sort(window, width, height, power);
    }
}

void Linear::heap_sort(sf::RenderWindow &window, unsigned int width, unsigned int height)
{
    for (int i = data_size / 2 - 1; i >= 0; i--)
    {
        heapify(window, width, height, data_size, i);
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

void Linear::merge(sf::RenderWindow &window, unsigned int width, unsigned int height, unsigned int low, unsigned int mid, unsigned int high)
{
    int arr1[data_size / 2 + 1], arr2[data_size / 2 + 1];
    int n1, n2, i, j, k;
    n1 = mid - low + 1;
    n2 = high - mid;

    for (i = 0; i < n1; i++)
        arr1[i] = data[low + i];
    for (j = 0; j < n2; j++)
        arr2[j] = data[mid + j + 1];

    arr1[n1] = 99999999;
    arr2[n2] = 99999999;

    i = 0;
    j = 0;

    for (k = low; k <= high; k++)
    {
        if (arr1[i] <= arr2[j])
        {
            data[k] = arr1[i++];
        }
        else
        {
            data[k] = arr2[j++];
        }
        visualize(window, width, height);
    }
}
int Linear::partition(sf::RenderWindow &window, unsigned int width, unsigned int height, int low, int high)
{
    int pivot = data[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (data[j] < pivot)
        {
            i++;
            auto temp = data[j];
            data[j] = data[i];
            data[i] = temp;
        }
        visualize(window, width, height);
    }
    auto temp = data[i + 1];
    data[i + 1] = data[high];
    data[high] = temp;
    return (i + 1);

} // quicksort

void Linear::heapify(sf::RenderWindow &window, unsigned int width, unsigned int height, int N, unsigned int i)
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

void Linear::count_sort(sf::RenderWindow &window, unsigned int width, unsigned int height, int ten)
{

    std::vector<int> output(data_size);
    int count[10] = {0};
    int i;
    for (i = 0; i < data_size; i++)
    {
        count[(data[i] / ten) % 10]++;
    }
    for (i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    for (i = data_size - 1; i >= 0; i--)
    {
        output[count[(data[i] / ten) % 10] - 1] = data[i];
        count[(data[i] / ten) % 10]--;
    }

    for (i = 0; i < data_size; i++)
    {
        data[i] = output[i];
        visualize(window , width , height);
    }
} // radix
