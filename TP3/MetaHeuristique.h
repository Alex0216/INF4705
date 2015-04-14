#pragma once

#include "Bloc.h"
#include <vector>

namespace MetaHeuristique
{
	void recuitSimule(std::vector<std::vector<Bloc>>& tours, int nbBlocs);
	std::vector<std::vector<Bloc>> recuitSimuleRecursif(std::vector<Bloc>& Bloc, int depth);

	std::vector<std::vector<Bloc>> voisin(std::vector<std::vector<Bloc>>& tours);
	std::vector<std::vector<Bloc>> voisinPlusPetiteTour(std::vector<std::vector<Bloc>>& tours);
	std::vector<std::vector<Bloc>> voisinRotation(std::vector<std::vector<Bloc>>& tours);
	std::vector<std::vector<Bloc>> voisinTourHasard(std::vector<std::vector<Bloc>>& tours);

	void insertBloc(std::vector<Bloc>& blocs, std::vector<std::vector<Bloc>>& tours);

	bool critereMetropolis(double delta, double temperature);
	void balanceTower(std::vector<std::vector<Bloc>>& tours);
	double calculeMoyenneHauteur(std::vector<std::vector<Bloc>> tours);

	bool test(std::vector<std::vector<Bloc>> tours, int n);
};

