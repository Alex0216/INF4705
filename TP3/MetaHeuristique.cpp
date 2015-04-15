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
	int Kmax = 100;
	double temp = 1;
	int palier = 50;
	double coeff = 1.5;

	//ofstream data;
	//data.open("../moyenne50k.csv");

	double convergence = 0.0;
	//trier les tours en ordre de nb de bloc decroissant
	std::sort(begin(tours), end(tours), [](vector<Bloc> a, vector<Bloc> b)->bool {return a.size() > b.size(); });

	vector<vector<Bloc>> meilleur(tours);
	vector<vector<Bloc>> solutionCourante(tours);
	//cout << "start: " << tours.size() << endl;
	for (int i = 0; i < Kmax-1; ++i)
	{
		for (int j = 1; j < palier; ++j)
		{
			vector<vector<Bloc>> nouveau;
			if (j%2 == 0)
				nouveau = voisinPlusPetiteTour(solutionCourante);
			else
				nouveau = voisinTourHasard(solutionCourante);

			//double delta = calculeMoyenneHauteur(solutionCourante) - calculeMoyenneHauteur(nouveau);
			double nouvelMoyenne = calculeMoyenneHauteur(nouveau);
			double moyenne = calculeMoyenneHauteur(solutionCourante);
			double delta = (int)solutionCourante.size() - (int)nouveau.size();
			convergence += nouvelMoyenne - moyenne;
			if (critereMetropolis(delta, temp))
			{
				solutionCourante = nouveau;
				if (meilleur.size() > solutionCourante.size())
				{
					//cout << "Nouveau meilleur: " << nouveau.size() << endl;
					meilleur = solutionCourante;
				}
			}
		}
		temp *= coeff;

		//verifie si la solution converge
		if (false && convergence / ((i + 1)*palier) < 0.15)
		{
			cout << "Converge apres " << (i+1)*palier << " iterations" << endl;
			break;
		}
	}
	tours = meilleur;
}

std::vector<std::vector<Bloc>> MetaHeuristique::recuitSimuleIteratif(std::vector<Bloc>& bloc, double t, double c)
{
	vector<Bloc> ensemble;
	std::transform(begin(bloc), end(bloc), back_inserter(ensemble), [](Bloc a) -> Bloc {return BlocRotations(a).CritereAlex(); });
	std::sort(begin(ensemble), end(ensemble), [](Bloc& a, Bloc& b) -> bool {return a.getSurface() > b.getSurface(); });
	vector<vector<Bloc>> init = vorace::insertFirstFit(bloc);
	vector<vector<Bloc>> meilleur;
	vector<vector<Bloc>> solution;

	auto start_time = chrono::system_clock::now();

	while(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start_time).count() < 60000 && ensemble.size() > 0)
	{

		vector<Bloc> maxTour;
		//Générer une solution
		auto toursVorace = vorace::insertFirstFit(ensemble);
		//Faire un recuit simule
		recuitSimule(toursVorace, (int)ensemble.size(), t, c);

		if (toursVorace.size() < meilleur.size() || meilleur.empty())
			meilleur = toursVorace;

		//Prendre la tour avec le plus grand nombre de bloc et l'ajouter à la solution
		auto maxTourIt = std::max_element(begin(meilleur), end(meilleur), [](vector<Bloc>& a, vector<Bloc>& b) -> bool {return a.size() < b.size(); });
		maxTour = *maxTourIt;
		meilleur.erase(maxTourIt);
		solution.push_back(maxTour);

		//enlever les blocs de la grande tour de l'ensemble des blocs de depart
		for (auto& b : maxTour)
		{
			for (int i = ensemble.size() - 1; i >= 0; --i)
			{
				if (b == ensemble[i])
				{
					ensemble.erase(begin(ensemble) + i);
					break;
				}
			}
		}
	}

	for (auto& tour : meilleur)
		solution.push_back(tour);

	return solution;
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

double MetaHeuristique::calculeMoyenneHauteur(std::vector<std::vector<Bloc>> tours)
{
	int sum = std::accumulate(begin(tours), end(tours), 0, [](int total, const vector<Bloc>& tour)
	{
		return total + std::accumulate(begin(tour), end(tour), 0, [](int hauteur, const Bloc& bloc){return hauteur + bloc.getHauteur(); });
	});

	return sum / (double)tours.size();
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
