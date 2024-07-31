#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <ctime>
#include <algorithm> // Để sử dụng std::generate
#include <random>
#include <thread>
#include <chrono>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

vector<int> generateEvenlySpacedNumbers(int count, int maxValue)
{
    vector<int> result(count);
    float a = 0;
    if (count == 0)
        return result; // Trường hợp không có số nào

    float step = float((maxValue - 1)) / (count - 1);
    for (int i = 0; i < count; ++i)
    {
        result[i] = a;
        a += step;
    }
    return result;
}

void processEvent(sf::RenderWindow &window, bool &isSorting)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            isSorting = false;
            window.close();
        }
    }
}

void drawRect(sf::RenderWindow &window, const vector<int> &arr, int low = -1, int high = -1, int pivot = -1)
{
    window.clear();
    int width = window.getSize().x / static_cast<float>(arr.size());
    for (int i = 0; i < arr.size(); ++i)
    {
        sf::RectangleShape rect(sf::Vector2f(width, arr[i]));
        rect.setPosition(i * width, window.getSize().y - arr[i]);
        if (low == -2) // change color after sorting ;
        {
            rect.setFillColor(sf::Color::Green);
        }
        else if (i == pivot)
        {
            rect.setFillColor(sf::Color::Blue);
        }
        else if (low <= i && i <= high)
        {
            rect.setFillColor(sf::Color::Red);
        }
        else
        {
            rect.setFillColor(sf::Color::White);
        }
        window.draw(rect);
    }
    window.display();
}

int partition(sf::RenderWindow &window, vector<int> &arr, int low, int high, bool &isSorting)
{
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];
    swap(arr[mid], arr[high]);

    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        processEvent(window, isSorting);

        if (arr[j] < pivot)
        {
            ++i;
            swap(arr[i], arr[j]);
            drawRect(window, arr, low, high, mid);
        }
    }
    swap(arr[i + 1], arr[high]);
    drawRect(window, arr, low, high, mid);
    return i + 1;
}

void quickSort(sf::RenderWindow &window, vector<int> &arr, int low, int high, bool &isSorting)
{
    if (low < high)
    {
        if (!isSorting)
            return; // Nếu cửa sổ bị đóng, dừng sắp xếp
        int pi = partition(window, arr, low, high, isSorting);
        quickSort(window, arr, low, pi - 1, isSorting);
        quickSort(window, arr, pi + 1, high, isSorting);
    }
}

void shuffleArray(vector<int> &arr)
{
    int n = arr.size();
    for (int i = n - 1; i > 0; --i)
    {
        int j = rand() % i;
        swap(arr[j], arr[i]);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    std::vector<sf::RectangleShape> rectangles;

    int windowWidth = 800;
    int windowHeight = 600;
    bool isSorting = true;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Visualization of sorting algorithms");

    vector<int> array = generateEvenlySpacedNumbers(windowWidth / 1, windowHeight);
    ; // Điều chỉnh kích thước của vector
    // generate(array.begin(), array.end(), [windowHeight]()
    //          { return rand() % windowHeight + 1; });
    // random_device rd;
    // mt19937 g(rd());
    // shuffle(array.begin(), array.end(), g);

    shuffleArray(array);

    drawRect(window, array);
    quickSort(window, array, 0, array.size() - 1, isSorting);

    // drawRect(window, array, -2);

    for (int i = 0; i < array.size(); ++i)
    {
        int width = window.getSize().x / static_cast<float>(array.size());
        sf::RectangleShape rect(sf::Vector2f(width, array[i]));
        rect.setPosition(i * width, window.getSize().y - array[i]);
        rectangles.push_back(rect);
    }

    // Vòng lặp chính chỉ cần kiểm tra sự kiện để giữ cửa sổ mở
    sf::Clock clock;
    int currentIndex = 0;
    while (window.isOpen())
    {
        processEvent(window, isSorting);

        if (currentIndex < rectangles.size() && clock.getElapsedTime().asMilliseconds() >= 1)
        {
            rectangles[currentIndex].setFillColor(sf::Color::Green);
            currentIndex++;
            clock.restart();
        }

        window.clear();

        for (const auto &rect : rectangles)
        {
            window.draw(rect);
        }
        window.display();
    }

    return 0;
}
