#include <iostream>
#include <fstream>
#include <ctime>

void selectionSort(int* array, int size);
void getArray(std::string file, int* array, int size);

int main(int argc, char* argv[])
{

    std::string file = argv[1];
    int size = atoi(argv[2]);

    int* array = new int[size];
    getArray(file, array,size);

    std::clock_t    start;

    start = std::clock();

    selectionSort(array, size);

    std::cout <<  (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << std::endl;

    return 0;
}

void selectionSort(int* array, int size)
{
    int min;

    for(int i = 0; i < size; ++i)
    {
        min = i;
        for(int j = i+1; j < size; ++j)
        {
            if(array[j] < array[min])
            {
                min = j;
            }
        }

        if(min != i)
        {
            int temp = array[min];
            array[min] = array[i];
            array[i] = temp;
        }
    }

}

void getArray(std::string filename, int* array, int size)
{
    std::fstream file(filename);
    if(file.is_open())
    {
        for(int i = 0; i < size; ++i)
        {
            file >> array[i];
        }
    }
}