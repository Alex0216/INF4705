//
// Created by Alexandre on 4/3/2015.
//

#ifndef TP3_DYNAMIQUE_H
#define TP3_DYNAMIQUE_H

#include <vector>

#include "bloc.h"

namespace dynamique {

	struct BlocDyn
	{
		Bloc bloc;
		int id;
		int previous;
		int hauteur;

		BlocDyn(Bloc b, int i) :bloc(b), id(i), previous(-1), hauteur(1)
		{
		}

		bool canStack(BlocDyn up)
		{
			return bloc.canStack(up.bloc) && id != up.id;
		}
	};

	std::vector<Bloc> plusGrandTour(std::vector<Bloc>& blocs);
}

#endif //TP3_DYNAMIQUE_H
