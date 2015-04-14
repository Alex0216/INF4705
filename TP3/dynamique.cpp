//
// Created by Alexandre on 4/3/2015.
//

#include "dynamique.h"
#include "blocrotation.h"

#include <algorithm>
#include <math.h>
#include <iterator>

using namespace std;

int calculerHauteur(vector<dynamique::BlocDyn>& ensemble, int currentIndex);
vector<Bloc> getTour(int top, std::vector<dynamique::BlocDyn>& blocs);

vector<Bloc> dynamique::plusGrandTour(std::vector<Bloc> &blocs)
{
    std::vector<dynamique::BlocDyn> ensemble;
    std::vector<std::vector<Bloc>> solution;
    
	//Etendre l'ensemble de bloc initial pour avoir les 3 rotations
	int id = 0;
	for (auto& bloc : blocs)
	{
		BlocRotations rot(bloc);
		ensemble.emplace_back(rot.A, id);
		ensemble.emplace_back(rot.B, id);
		ensemble.emplace_back(rot.C, id);

		id++;
	}

	std::sort(begin(ensemble), end(ensemble), [](dynamique::BlocDyn& a, dynamique::BlocDyn& b) -> bool {return a.bloc.getSurface() > b.bloc.getSurface(); });

	int maxHauteur = 0;
	int maxIndex =0;

    for(int i = 0; i < ensemble.size(); ++i)
    {
        auto res = calculerHauteur(ensemble, i);
		if (res > maxHauteur)
		{
			maxHauteur = res;
			maxIndex = i;
		}

    }

	return getTour(maxIndex, ensemble);;
}

vector<Bloc> getTour(int top, std::vector<dynamique::BlocDyn>& blocs)
{
    vector<Bloc> tour;
	int index = top;
	bool done = false;
	do
	{
		tour.push_back(blocs[index].bloc);
		if (index == blocs[index].previous)
			done = true;
		index = blocs[index].previous;
	} while (! done);

	std::reverse(begin(tour), end(tour));
	return tour;
}

int calculerHauteur(vector<dynamique::BlocDyn>& ensemble, int currentIndex)
{
    if(ensemble[currentIndex].previous >= 0)
        return ensemble[currentIndex].hauteur;

    int maxHauteur = 0;
    int maxIndex = currentIndex;
	dynamique::BlocDyn bloc = ensemble[currentIndex];
    for(int i = 0; i < currentIndex; ++i)
    {
        if(ensemble[i].canStack(bloc))
        {
            int result = calculerHauteur(ensemble, i);
            if(result> maxHauteur)
            {
                maxHauteur = result;
                maxIndex = i;
            }
        }
    }

    if(maxHauteur > 0)
    {
        ensemble[currentIndex].hauteur = maxHauteur + 1;
		ensemble[currentIndex].previous = maxIndex;
    }
    else
    {
        ensemble[currentIndex].hauteur = 1;
        ensemble[currentIndex].previous = currentIndex;
    }
    vector<int> resultat = {maxHauteur, currentIndex};
    return ensemble[currentIndex].hauteur;
}