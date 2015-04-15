//
// Created by Alexandre on 4/1/2015.
//

#include "vorace.h"
#include "blocrotation.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>

using namespace vorace;
using namespace std;

bool reverseSurfaceComparison(Bloc l, Bloc b);
bool setCompare(vector<Bloc> a, vector<Bloc> b);

/**
 * Place les blocs dans la premi�res tour possible
 */
vector<vector<Bloc>> vorace::firstFit(std::vector<Bloc>& blocs)
{
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

vector<vector<Bloc>> vorace::insertFirstFit(std::vector<Bloc>& blocs)
{
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

                if(b.canStack(tour[i]))
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
            tours[tours.size()-1].push_back(BlocRotations(b).getHighestSurface());
        }
    }
    return tours;

}


std::vector<std::vector<Bloc>> vorace::insertBestFit(std::vector<Bloc>& blocs)
{
	vector<vector<Bloc>> tours;
	tours.emplace_back();
	for (auto& b : blocs)
	{
		bool stacked = false;

		for (auto& tour : tours)
		{
			if (tour.empty())
			{
				tour.push_back(b);
				stacked = true;
				break;
			}
			else
			{
				int i = 0;
				while (i < tour.size() && tour[i].canStack(b))
					++i;

				if (i == tour.size() && tour[i - 1].canStack(b))
				{
					tour.push_back(b);
					stacked = true;
					break;
				}

				if (b.canStack(tour[i]))
				{
					tour.insert(begin(tour) + i, b);
					stacked = true;
					break;
				}
			}
		}

		if (stacked == false)
		{
			tours.emplace_back();
			tours[tours.size() - 1].push_back(b);
		}

		std::sort(begin(tours), end(tours), [](vector<Bloc> a, vector<Bloc> b)-> bool {return a.size() > b.size(); });
	}
	return tours;
}

bool reverseSurfaceComparison(Bloc l, Bloc r)
{
    return l.getSurface() > r.getSurface();
}

bool setCompare(vector<Bloc> a, vector<Bloc> b)
{
	return a.size() > b.size();
}