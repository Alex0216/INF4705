#include <iostream>

void selectionSort(int* array, int size);

int main()
{
    int a[] = {9,8,7,6,5,4,3};

    selectionSort(a, 7);
    for(int i = 0; i < 7; ++i)
        std::cout << a[i] << " ";
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