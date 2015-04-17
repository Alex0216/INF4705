#include "MetaHeuristique.h"

#include <algorithm>
#include <random>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <math.h>
#include <chrono>


#include "bloc.h"
#include "blocrotation.h"
#include "vorace.h"

using namespace std;

void MetaHeuristique::recuitSimule(std::vector<std::vector<Bloc>>& tours, int nbBlocs, double t, double c)
{
	int Kmax = 70;
	double temp = t;
	int palier = 50;
	double coeff = c;


	//trier les tours en ordre de nb de bloc decroissant
	std::sort(begin(tours), end(tours), [](vector<Bloc> a, vector<Bloc> b)->bool {return a.size() > b.size(); });

	vector<vector<Bloc>> meilleur(tours);
	vector<vector<Bloc>> solutionCourante(tours);
	cout << "start: " << tours.size() << endl;
	for (int i = 0; i < Kmax-1; ++i)
	{
		for (int j = 1; j < palier; ++j)
		{
			vector<vector<Bloc>> nouveau;
			if (j%2 == 0)
				nouveau = voisinPlusPetiteTour(solutionCourante);
			else
				nouveau = voisinTourHasard(solutionCourante);


			double delta = (int)solutionCourante.size() - (int)nouveau.size();
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

std::vector<std::vector<Bloc>> MetaHeuristique::recuitSimuleIteratif(std::vector<Bloc>& bloc, double t, double c)
{
	vector<Bloc> ensemble;
	std::transform(begin(bloc), end(bloc), back_inserter(ensemble), [](Bloc a) -> Bloc {return BlocRotations(a).CritereAlex(); });
	std::sort(begin(ensemble), end(ensemble), [](const Bloc& a, const Bloc& b) -> bool {return a.getSurface() > b.getSurface(); });
	vector<vector<Bloc>> meilleur;
	vector<vector<Bloc>> solution;

	auto start_time = chrono::system_clock::now();
	int iteration = 0;
	//while(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start_time).count() < 60000 && ensemble.size() > 0)
	while(iteration++ < 10)
	{

		vector<Bloc> maxTour;
		//Générer une solution
		auto toursVorace = vorace::insertFirstFit(ensemble);
		//Faire un recuit simule
		recuitSimule(toursVorace, (int)ensemble.size(), t, c);

		if (toursVorace.size() <= meilleur.size() || meilleur.empty())
			meilleur = toursVorace;

		//Prendre la tour avec le plus grand nombre de bloc et l'ajouter à la solution
		auto maxTourIt = std::max_element(begin(meilleur), end(meilleur), [](vector<Bloc>& a, vector<Bloc>& b) -> bool {return a.size() < b.size(); });
		maxTour = *maxTourIt;
		meilleur.erase(maxTourIt);
		solution.push_back(maxTour);

		//enlever les blocs de la grande tour de l'ensemble des blocs de depart
		for (auto& b : maxTour)
		{
			for (int i = 0; i < ensemble.size(); ++i)
			{
				if (b == ensemble[i])
				{
					ensemble.erase(begin(ensemble) + i);
					break;
				}
			}
		}
		//Melanger les blocs legerement pour la prochaine iteration
		shuffleBloc(ensemble);
	}

	for (auto& tour : meilleur)
		solution.push_back(tour);

	return solution;
}


std::vector<std::vector<Bloc>> MetaHeuristique::voisinPlusPetiteTour(std::vector<std::vector<Bloc>>& tours)
{
	vector<vector<Bloc>> toursVoisin(tours);
	//balanceTower(toursVoisin);

	//Prendre la plus petite tour
	auto minTourIt = std::min_element(begin(toursVoisin), end(toursVoisin), [](vector<Bloc> a, vector<Bloc> b) -> bool {return a.size() < b.size(); });
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

void MetaHeuristique::insertBloc(std::vector<Bloc>& blocs, std::vector<std::vector<Bloc>>& tours)
{
	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(blocs.begin(), blocs.end(), std::default_random_engine(seed));

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
			tours[tours.size() - 1].push_back(rot.getHighestSurface());
		}
	}
}

bool MetaHeuristique::critereMetropolis(double delta, double temperature)
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


void MetaHeuristique::shuffleBloc(std::vector<Bloc>& blocs)
{
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> uniform(-5, 5);

	for (int i = 5; i < blocs.size()-5; i += 1)
	{
		int index = uniform(eng);
		std::swap(blocs[i], blocs[i + index]);
	}
}

