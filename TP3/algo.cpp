//
// Created by Alexandre on 4/1/2015.
//

#include "algo.h"

#include <algorithm>
#include <iostream>

using namespace INF4705;
using namespace std;

bool reverseSurfaceComparison(Bloc l, Bloc b);

void INF4705::vorace(std::vector<Bloc>& blocs)
{
    Bloc::extendDataSet(blocs);
    std::sort(begin(blocs), end(blocs), reverseSurfaceComparison);
    for(auto b : blocs)
        cout << b << endl;
}

bool reverseSurfaceComparison(Bloc l, Bloc r)
{
    return l.getSurface() > r.getSurface();
}