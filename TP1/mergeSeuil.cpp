#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>

void mergeSort(std::vector<int> &array, int seuil);
void mergeSortRecursif(std::vector<int>& array, int low, int high, int seuil);
void getArray(std::string filename, std::vector<int> &array, int size);
void selectionSort(std::vector<int>::iterator begin, std::vector<int>::iterator end);

int main(int argc, char* argv[])
{

    std::string file = argv[1];
    int size = atoi(argv[2]);

    std::vector<int> array;
    array.reserve(size);
    getArray(file, array, size);

    std::clock_t start;


    start = std::clock();
    mergeSort(array, 29);

    std::cout <<  (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000) << ";";
    std::cout << std::endl;
    return 0;
}

void mergeSort(std::vector<int> &array, int seuil)
{
    mergeSortRecursif(array, 0, array.size(), seuil);
}

void mergeSortRecursif(std::vector<int>& array, int low, int high, int seuil) {
    if (high - low <= seuil)
    {
        selectionSort(std::begin(array)+low, std::begin(array)+high);
        return;
    }

    int middle = low + (high - low) / 2;

    mergeSortRecursif(array, low, middle, seuil);
    mergeSortRecursif(array, middle, high, seuil);

    std::inplace_merge(std::begin(array)+low, std::begin(array)+middle, std::begin(array)+high);
}

void selectionSort(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    std::vector<int>::iterator min;
    while (begin != end)
    {
        min = std::min_element(begin, end);
        std::iter_swap(begin, min);
        ++begin;
    }

}

void getArray(std::string filename, std::vector<int> &array, int size)
{
    std::fstream file(filename);
    if(file.is_open())
    {
        int x;
        for(int i = 0; i < size; ++i)
        {
            file >> x;
            array.push_back(x);
        }
    }
}