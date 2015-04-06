#include "MetaHeuristique.h"

#include "bloc.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>
#include <math.h>
#include "blocrotation.h"


using namespace std;

void MetaHeuristique::recuitSimule(std::vector<std::vector<Bloc>>& tours, int nbBlocs)
{
	int Kmax = 500;
	double temp = 100;
	int palier = 50;
	double coeff = 0.9;


	//trier les tours en ordre de nb de bloc decroissant
	std::sort(begin(tours), end(tours), [](auto a, auto b)->bool {return a.size() > b.size(); });

	vector<vector<Bloc>> meilleur(tours);
	vector<vector<Bloc>> solutionCourante(tours);
	cout << "start: " << tours.size() << endl;
	for (int i = 0; i < Kmax-1; ++i)
	{
		for (int j = 1; j < palier; ++j)
		{
			vector<vector<Bloc>> nouveau;
			if (j < palier / 2)
				nouveau = voisinPlusPetiteTour(solutionCourante);
			else
				nouveau = voisinTourHasard(solutionCourante);
			
			int delta = (int)solutionCourante.size() - (int)nouveau.size();
			if (critereMetropolis(delta, temp))
			{
				solutionCourante = nouveau;
				
				if (meilleur.size() > solutionCourante.size())
				{
					cout << "Nouveau meilleur: " << nouveau.size() << endl;
					meilleur = solutionCourante;
				}
			}
		}
		temp *= coeff;
	}
	tours = meilleur;
}

std::vector<std::vector<Bloc>> MetaHeuristique::voisin(std::vector<std::vector<Bloc>>& tours)
{
	vector<vector<Bloc>> toursVoisin(tours);

	//Prendre une tour au hasard
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> uniform(0, (int)toursVoisin.size() - 1);
	int indexTour = uniform(eng);

	//Prendre un bloc au harsard
	uniform = uniform_int_distribution<int>(0, (int)toursVoisin[indexTour].size() - 1);
	int indexBloc = uniform(eng);

	//enlever le bloc
	auto bloc = toursVoisin[indexTour][indexBloc];
	toursVoisin[indexTour].erase(toursVoisin[indexTour].begin() + indexBloc);
	

	//si la tour est vide, l'enlever aussi
	if (toursVoisin[indexTour].empty())
		toursVoisin.erase(begin(toursVoisin) + indexTour);

	//inserer le bloc dans un tours choisie au hasard
	uniform = uniform_int_distribution<int>(0, (int)toursVoisin.size() - 1);
	int tourCible = uniform(eng);
	vector<Bloc>& tour = toursVoisin[tourCible];
	int index = 0;
	while (index < tour.size() && tour[index].canStack(bloc))
		index++;
	tour.insert(begin(tour) + index, bloc);
	int insertIndex = ++index;
	while (index < tour.size() && !bloc.canStack(tour[index]))
		index++;

	vector<Bloc> blocsRemoved;
	std::copy(begin(tour) + insertIndex, begin(tour) + index, back_inserter(blocsRemoved));
	tour.erase(begin(tour) + insertIndex, begin(tour) + index);

	insertBloc(blocsRemoved, toursVoisin);

	return toursVoisin;
}

std::vector<std::vector<Bloc>> MetaHeuristique::voisinPlusPetiteTour(std::vector<std::vector<Bloc>>& tours)
{
	vector<vector<Bloc>> toursVoisin(tours);
	//balanceTower(toursVoisin);

	//Prendre la plus petite tour
	auto minTourIt = std::min_element(begin(toursVoisin), end(toursVoisin), [](auto a, auto b) -> bool {return a.size() < b.size(); });
	vector<Bloc> minTour = *minTourIt;

	toursVoisin.erase(minTourIt);


	insertBloc(minTour, toursVoisin);

	return toursVoisin;
}

std::vector<std::vector<Bloc>> MetaHeuristique::voisinTourHasard(std::vector<std::vector<Bloc>>& tours)
{
	vector<vector<Bloc>> toursVoisin(tours);
	

	//Prendre une tour au hasard
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> uniform(0, (int)toursVoisin.size() - 1);
	int indexTour = uniform(eng);
	auto minTour = toursVoisin[indexTour];

	toursVoisin.erase(begin(toursVoisin)+indexTour);


	insertBloc(minTour, toursVoisin);

	return toursVoisin;
}

std::vector<std::vector<Bloc>> MetaHeuristique::voisinRotation(std::vector<std::vector<Bloc>>& tours)
{
	vector<vector<Bloc>> toursVoisin(tours);
	balanceTower(toursVoisin);
	//Prendre une tour au hasard
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> uniform(0, (int)toursVoisin.size() - 1);
	int indexTour = uniform(eng);

	//Prendre un bloc au harsard
	uniform = uniform_int_distribution<int>(0, (int)toursVoisin[indexTour].size() - 1);
	int indexBloc = uniform(eng);

	//enlever le bloc
	auto bloc = toursVoisin[indexTour][indexBloc];
	toursVoisin[indexTour].erase(toursVoisin[indexTour].begin() + indexBloc);


	//si la tour est vide, l'enlever aussi
	if (toursVoisin[indexTour].empty())
		toursVoisin.erase(begin(toursVoisin) + indexTour);

	//Rotate le bloc
	uniform = uniform_int_distribution<int>(0, 2);
	int rotation = uniform(eng);
	bloc = BlocRotations(bloc)[rotation];

	//inserer le bloc dans un tours choisie au hasard
	uniform = uniform_int_distribution<int>(0, (int)toursVoisin.size() - 1);
	int tourCible = uniform(eng);
	vector<Bloc>& tour = toursVoisin[tourCible];
	int index = 0;
	while (index < tour.size() && tour[index].canStack(bloc))
		index++;
	tour.insert(begin(tour) + index, bloc);
	int insertIndex = ++index;
	while (index < tour.size() && !bloc.canStack(tour[index]))
		index++;

	vector<Bloc> blocsRemoved;
	std::copy(begin(tour) + insertIndex, begin(tour) + index, back_inserter(blocsRemoved));
	tour.erase(begin(tour) + insertIndex, begin(tour) + index);

	insertBloc(blocsRemoved, toursVoisin);

	return toursVoisin;
}

void MetaHeuristique::insertBloc(std::vector<Bloc>& blocs, std::vector<std::vector<Bloc>>& tours)
{
	for (auto& b : blocs)
	{
		bool stacked = false;
		BlocRotations rot(b);
		for (int j = 0; j < 3 && !stacked; ++j)
		{
			Bloc bloc = rot[j];
			for (auto& tour : tours)
			{
				if (tour.empty())
				{
					tour.push_back(bloc);
					stacked = true;
					cout << "wat" << endl;
					break;
				}
				else
				{
					int i = 0;
					while (i < tour.size() && tour[i].canStack(bloc))
						++i;

					if (i == tour.size() && tour[i - 1].canStack(bloc))
					{
						tour.push_back(bloc);
						stacked = true;
						break;
					}

					if (bloc.canStack(tour[i]))
					{
						tour.insert(begin(tour) + i, bloc);
						stacked = true;
						break;
					}
				}
			}
		}

		if (stacked == false)
		{
			tours.emplace_back();
			tours[tours.size() - 1].push_back(b);
		}
	}
}

bool MetaHeuristique::critereMetropolis(int delta, double temperature)
{
	if (delta >= 0)
		return true;

	random_device rd;
	default_random_engine eng(rd());
	uniform_real_distribution<double> uniform(0, 1);
	double unif = uniform(eng);
	double e = exp((double)delta / (double)temperature);

	if (e >= unif)
		return true;
	else
		return false;
}

void MetaHeuristique::balanceTower(std::vector<std::vector<Bloc>>& tours)
{
	for (auto& tour : tours)
	{
		if (tour.empty())
			break;
		///rotate base
		BlocRotations rot(tour[0]);


		for (int i = 1; i < tour.size()-1; ++i)
		{
			BlocRotations bloc(tour[i]);

			if (bloc.B.canStack(tour[i + 1]) && tour[i - 1].canStack(bloc.B))
			{
				tour[i] = bloc.B;
			}
			else if (bloc.C.canStack(tour[i + 1]) && tour[i - 1].canStack(bloc.C))
			{
				tour[i] = bloc.C;
			}
		}
	}
}


bool MetaHeuristique::test(std::vector<std::vector<Bloc>> tours, int n)
{
	size_t nbBloc = 0;
	for (auto& tour : tours)
	{
		nbBloc += tour.size();
		for (int i = 0; i < tour.size() - 1; ++i)
			if (!tour[i].canStack(tour[i + 1]))
				return false;
	}
	return nbBloc == n;
}
