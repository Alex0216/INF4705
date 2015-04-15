#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

#include "bloc.h"
#include "vorace.h"
#include "dynamique.h"
#include "graph.h"
#include "MetaHeuristique.h"

#include <chrono>

using namespace std;

vector<Bloc> getDataSet(string filename);
bool test(std::vector<std::vector<Bloc>> tours, std::vector<Bloc> setDepart);
void boxStacking(std::vector<std::vector<Bloc>>(*vorace)(vector<Bloc>&), vector<Bloc>& blocs, int size, bool print);

int main(int argc, char* argv[]) {

    auto blocs = getDataSet(argv[2]);
    int size = (int)blocs.size();

	boxStacking(&vorace::insertFirstFit, blocs, size, (argc >= 4 && argv[4] == "-p"));
   
    return 0;
}

void boxStacking(std::vector<std::vector<Bloc>>(*vorace)(vector<Bloc>&), vector<Bloc>& blocs, int size, bool print)
{
	std::vector<Bloc> blocsDepart(blocs);
	ofstream data;
	data.open("param.csv");
	auto start_time = chrono::system_clock::now();
	for (double t = 0.01; t < 100; t += 0.01)
	{
		for (double c = 0.01; c < 10; c += 0.01)
		{
			vector<vector<Bloc>> solution;
			auto tours = MetaHeuristique::recuitSimuleIteratif(blocs, t, c);
			//auto tours = dynamique::plusGrandTour(blocs);
			auto end_time = chrono::system_clock::now();
			data << t << ";" << c << ";" << tours.size() << endl;
			cout << t << ";" << c << ";" << tours.size() << endl;
		}
	}

	vector<vector<Bloc>> solution;
	auto tours = MetaHeuristique::recuitSimuleIteratif(blocs, 0, 0);
	//auto tours = dynamique::plusGrandTour(blocs);
	auto end_time = chrono::system_clock::now();

	cout << "Temps: " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << endl;
	cout << "NB tours: " << tours.size() << endl;

	cout << "Test: " << boolalpha << test(tours, blocsDepart) << endl;


	if (print)
	{

		for (auto& tour : tours)
		{
			cout << tour.size() << endl;
			for (auto& b : tour)
				cout << b << endl;
			
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

bool test(std::vector<std::vector<Bloc>> tours, std::vector<Bloc> setDepart)
{
	vector<Bloc> blocsFin;
	blocsFin.reserve(setDepart.size());
    for(auto& tour : tours)
    {
		for (int i = 0; i < tour.size() - 1; ++i)
		{
			blocsFin.push_back(tour[i]);
			if (!tour[i].canStack(tour[i + 1]))
				return false;
		}

		blocsFin.push_back(tour[tour.size() - 1]);
    }

    return std::is_permutation(begin(blocsFin), end(blocsFin), begin(setDepart));
}