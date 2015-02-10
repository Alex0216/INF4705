#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int> &array);
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
    countingSort(array);

    std::cout << std::endl;

    std::cout <<  (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << std::endl;

    return 0;
}

void countingSort(std::vector<int> &array)
{
    int max = *std::max_element(begin(array),end(array)) +1 ;

    std::vector<int> count(max, 0);

    for(int i = 0; i < array.size(); ++i)
    {
        count[array[i]]++;
    }
    std::cout << count.size() << std::endl;
    //calcule des indexes
    int total = 0;
    int oldcount = 0;
    for(int i = 0; i < max; ++i)
    {
        oldcount = count[i];
        count[i] = total;
        total += oldcount;
    }

    std::vector<int> output(array.size(), 0);

    for(int x : array)
    {
        output[count[x]] = x;
        count[x] += 1;
    }



    for(int i  = 0; i < output.size(); ++i)
        array[i] = output[i];


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