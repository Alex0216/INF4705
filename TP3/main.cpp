#include <iostream>
#include <fstream>
#include <vector>

#include "bloc.h"
#include "vorace.h"
#include "dynamique.h"
#include "graph.h"
#include "MetaHeuristique.h"

#include <chrono>

using namespace std;

vector<Bloc> getDataSet(string filename);
bool test(std::vector<std::vector<Bloc>> tours, int n);
void boxStacking(std::vector<std::vector<Bloc>>(*vorace)(vector<Bloc>&), vector<Bloc>& blocs, int size, bool print);

int main(int argc, char* argv[]) {

    auto blocs = getDataSet(argv[2]);
    int size = (int)blocs.size();

	boxStacking(&vorace::insertFirstFit, blocs, size, (argc >= 4 && argv[4] == "-p"));
   
    return 0;
}

void boxStacking(std::vector<std::vector<Bloc>>(*vorace)(vector<Bloc>&), vector<Bloc>& blocs, int size, bool print)
{
	auto start_time = chrono::system_clock::now();
	auto tours = vorace(blocs);
	MetaHeuristique::recuitSimule(tours, size);
	auto end_time = chrono::system_clock::now();

	cout << "Temps: " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << endl;

	cout << "Test: " << boolalpha << test(tours, size) << endl;

	cout << "NB tours: " << tours.size() << endl;

	if (print)
	{

		for (auto& tour : tours)
		{
			for (auto& b : tour)
				cout << b << endl;
			cout << "========" << endl;
		}

	}
}

vector<Bloc> getDataSet(string filename)
{
    std::fstream file(filename);
    if(file.is_open())
    {
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

	return vector<Bloc>();
}

bool test(std::vector<std::vector<Bloc>> tours, int n)
{
    size_t nbBloc = 0;
    for(auto& tour : tours)
    {
        nbBloc += tour.size();
        for(int i = 0; i < tour.size()-1; ++i)
            if(!tour[i].canStack(tour[i+1]))
                return false;
    }
    return nbBloc == n;
}