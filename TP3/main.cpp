#include <iostream>
#include <fstream>
#include <vector>

#include "bloc.h"
#include "vorace.h"

using namespace std;

vector<Bloc> getDataSet(string filename);

int main(int argc, char* argv[]) {

    auto blocs = getDataSet(argv[2]);
    auto tours = vorace::voraceFirstFit(blocs);

    cout << "NB tours: " << tours.size();
    if(argc >= 4 && argv[3])
    {
        for(auto& tour : tours)
        {
            for(auto& b : tour)
                cout << b << endl;
            cout << "========" << endl;
        }
    }

    return 0;
}

vector<Bloc> getDataSet(string filename)
{
    std::fstream file(filename);
    if(file.is_open())
    {
        int x;
        int size;
        file >> size;
        vector<Bloc> blocs;
        blocs.reserve(size);
        for(int i = 0; i < size; ++i)
        {
            int h, l, p;
            file >> h;
            file >> l;
            file >> p;
            Bloc b(h, l ,p);
            blocs.push_back(b);
        }

        return blocs;
    }
}