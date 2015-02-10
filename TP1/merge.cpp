#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>

void mergeSort(std::vector<int> &array);
void mergeSortRecursif(std::vector<int>& array, int low, int high);
void getArray(std::string filename, std::vector<int> &array, int size);

int main(int argc, char* argv[])
{

    std::string file = argv[1];
    int size = atoi(argv[2]);

    std::vector<int> array;
    array.reserve(size);
    getArray(file, array, size);

    std::clock_t    start;

    start = std::clock();
    mergeSort(array);
    for(auto i : array)
        std::cout << i << ' ';

    std::cout << std::endl;

    std::cout <<  (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << std::endl;

    return 0;
}

void mergeSort(std::vector<int> &array)
{
    mergeSortRecursif(array, 0, array.size());
}

void mergeSortRecursif(std::vector<int>& array, int low, int high) {
    if (high - low <= 1)
        return;

    int middle = low + (high - low) / 2;

    mergeSortRecursif(array, low, middle);
    mergeSortRecursif(array, middle, high);

    std::inplace_merge(std::begin(array)+low, std::begin(array)+middle, std::begin(array)+high);
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