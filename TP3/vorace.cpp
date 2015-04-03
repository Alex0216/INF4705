//
// Created by Alexandre on 4/1/2015.
//

#include "vorace.h"
#include "blocrotation.h"

#include <algorithm>
#include <iostream>

using namespace vorace;
using namespace std;

bool reverseSurfaceComparison(Bloc l, Bloc b);

/**
 * Place les blocs dans la premières tour possible
 */
vector<vector<Bloc>> vorace::voraceFirstFit(std::vector<Bloc>& blocs)
{
    vector<Bloc> ensemble;
    transform(begin(blocs), end(blocs), back_inserter(ensemble), [](Bloc b) -> Bloc {BlocRotations rot(b); return rot.getHighestSurface();});
    std::sort(begin(ensemble), end(ensemble), reverseSurfaceComparison);
    vector<vector<Bloc>> tours;
    tours.emplace_back();
    for(auto& b : ensemble)
    {
        bool stacked = false;

        for(auto& tour : tours)
        {
            if(tour.empty())
            {
                tour.push_back(b);
                stacked = true;
                break;
            }
            if(tour[tour.size()-1].canStack(b))
            {
                tour.push_back(b);
                stacked = true;
                break;
            }
        }

        if(stacked == false)
        {
            tours.emplace_back();
            tours[tours.size()-1].push_back(b);
        }
    }
    return tours;

}

vector<vector<Bloc>> vorace::voraceInsertFirstFit(std::vector<Bloc>& blocs)
{
    vector<Bloc> ensemble;
    transform(begin(blocs), end(blocs), back_inserter(ensemble), [](Bloc b) -> Bloc {BlocRotations rot(b); return rot.CritereAlex();});
    std::sort(begin(ensemble), end(ensemble), reverseSurfaceComparison);
    vector<vector<Bloc>> tours;
    tours.emplace_back();
    for(auto& b : ensemble)
    {
        bool stacked = false;

        for(auto& tour : tours)
        {
            if(tour.empty())
            {
                tour.push_back(b);
                stacked = true;
                break;
            }
            else
            {
                int i = 0;
                while(i < tour.size() && tour[i].canStack(b))
                    ++i;

                if(i == tour.size() && tour[i-1].canStack(b))
                {
                    tour.push_back(b);
                    stacked = true;
                    break;
                }

                if(tour[i-1].canStack(b) && b.canStack(tour[i]))
                {
                    tour.insert(begin(tour)+i, b);
                    stacked = true;
                    break;
                }
            }
        }

        if(stacked == false)
        {
            tours.emplace_back();
            tours[tours.size()-1].push_back(b);
        }
    }
    return tours;

}

bool reverseSurfaceComparison(Bloc l, Bloc r)
{
    return l.getSurface() > r.getSurface();
}