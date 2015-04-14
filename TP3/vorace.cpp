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
 * Place les blocs dans la premières tour possible
 */
vector<vector<Bloc>> vorace::firstFit(std::vector<Bloc>& blocs)
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

vector<vector<Bloc>> vorace::insertFirstFit(std::vector<Bloc>& blocs)
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
            tours[tours.size()-1].push_back(b);
        }
    }
    return tours;

}

std::vector<std::vector<Bloc>> vorace::reverserInsertFirstFit(std::vector<Bloc>& blocs)
{
	vector<Bloc> ensemble;
	transform(begin(blocs), end(blocs), back_inserter(ensemble), [](Bloc b) -> Bloc {BlocRotations rot(b); return rot.CritereAlex(); });
	std::sort(begin(ensemble), end(ensemble), [](Bloc a, Bloc b) -> bool {return a.getSurface() < b.getSurface(); });
	vector<vector<Bloc>> tours;
	tours.emplace_back();

	for (auto& b : ensemble)
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
				while (i < tour.size() && b.canStack(tour[i]))
					++i;

				if (i == tour.size() && b.canStack(tour[i - 1]))
				{
					tour.push_back(b);
					stacked = true;
					break;
				}

				if (tour[i].canStack(b))
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
	}

	for (auto& tour : tours)
	{
		std::reverse(begin(tour), end(tour));
	}

	return tours;
}

std::vector<std::vector<Bloc>> vorace::insertBestFit(std::vector<Bloc>& blocs)
{
	vector<Bloc> ensemble;
	transform(begin(blocs), end(blocs), back_inserter(ensemble), [](Bloc b) -> Bloc {BlocRotations rot(b); return rot.CritereAlex(); });
	std::sort(begin(ensemble), end(ensemble), reverseSurfaceComparison);
	vector<vector<Bloc>> tours;
	tours.emplace_back();
	for (auto& b : ensemble)
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

		std::sort(begin(tours), end(tours), [](std::vector<Bloc> a, std::vector<Bloc> b)-> bool {return a.size() > b.size(); });
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