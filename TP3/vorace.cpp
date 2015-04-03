//
// Created by Alexandre on 4/1/2015.
//

#include "vorace.h"

#include <algorithm>
#include <iostream>

using namespace vorace;
using namespace std;

bool reverseSurfaceComparison(Bloc l, Bloc b);

/**
 * Place les blocs dans la premières tour possible
 * Les blocs sont
 */
vector<vector<Bloc>> vorace::voraceFirstFit(std::vector<Bloc>& blocs)
{
    std::sort(begin(blocs), end(blocs), reverseSurfaceComparison);
    vector<vector<Bloc>> tours;
    tours.emplace_back();
    for(auto& b : blocs)
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

bool reverseSurfaceComparison(Bloc l, Bloc r)
{
    return l.getSurface() > r.getSurface();
}