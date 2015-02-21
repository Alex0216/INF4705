#include <iostream>
#include <fstream>
#include <ctime>

void selectionSort(int* array, int size);
void getArray(std::string file, int* array, int size);

int main(int argc, char* argv[])
{
    std::string file = argv[1];
    int size = atoi(argv[2]);

    std::vector<int> array;
    array.reserve(size);
    getArray(file, array, size);

    std::clock_t    start;

    start = std::clock();

    selectionSort(array);

    std::cout <<  (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << std::endl;

    return 0;
}

void selectionSort(std::vector<int> &array)
{
    Iterator min;
	auto begin = array.begin();
	auto end = array.end();
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