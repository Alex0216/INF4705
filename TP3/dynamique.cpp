//
// Created by Alexandre on 4/3/2015.
//

#include "dynamique.h"
#include "blocrotation.h"

#include <algorithm>
#include <math.h>
#include <iterator>

using namespace std;

vector<int> calculerHauteur(vector<Bloc>& ensemble, int currentIndex, std::vector<std::vector<int>>& tableau );
vector<Bloc> getTour(vector<int> top, vector<Bloc>& blocs);

std::vector<std::vector<int>> dynamique::dynamique(std::vector<Bloc> &blocs)
{
    std::vector<std::vector<int>> tableau(blocs.size(), std::vector<int>(2, 0));
    std::vector<Bloc> ensemble;
    std::vector<std::vector<Bloc>> solution;
    transform(begin(blocs), end(blocs), back_inserter(ensemble), [](Bloc b) -> Bloc {BlocRotations rot(b); return rot.CritereAlex();});
    std::sort(begin(ensemble), end(ensemble), [](Bloc a, Bloc b) -> bool {return a.getSurface() > b.getSurface();});

    vector<int> maxResult = {0,0};

    for(int i = 0; i < ensemble.size(); ++i)
    {
        auto res = calculerHauteur(ensemble, i, tableau);
        if(res[0] > maxResult[0])
            maxResult = res;
    }

	return null;
}

vector<Bloc> getTour(vector<int> top, vector<Bloc>& blocs)
{
    vector<Bloc> tour;
    int index = top[1];
    tour.push_back(blocs[index]);

}

vector<int> calculerHauteur(vector<Bloc>& ensemble, int currentIndex, std::vector<std::vector<int>>& tableau )
{
    if(tableau[currentIndex][0] != 0)
        return tableau[currentIndex];

    int maxHauteur = 0;
    int maxIndex = currentIndex;
    Bloc bloc = ensemble[currentIndex];
    for(int i = 0; i < currentIndex; ++i)
    {
        if(ensemble[i].canStack(bloc))
        {
            vector<int> result = calculerHauteur(ensemble, i, tableau);
            if(result[0] > maxHauteur)
            {
                maxHauteur = result[0];
                maxIndex = i;
            }
        }
    }

    if(maxHauteur > 0)
    {
        tableau[currentIndex][0] = maxHauteur + 1;
        tableau[currentIndex][1] = maxIndex;
    }
    else
    {
        tableau[currentIndex][0] = 1;
        tableau[currentIndex][1] = currentIndex;
    }
    vector<int> resultat = {maxHauteur, currentIndex};
    return resultat;
}