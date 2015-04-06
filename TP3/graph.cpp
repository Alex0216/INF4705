//
// Created by Alexandre on 4/4/2015.
//

#include "graph.h"
#include "BlocNode.h"
#include "blocrotation.h"

#include <memory>
#include <algorithm>
#include <iostream>
#include <thread>
#include <iterator>

using namespace std;

void initNodeList(vector<BlocNode>& nodeList, int begin, int end);

void ::Graph::buildGraph(std::vector<Bloc> blocs)
{
    vector<Bloc> ensemble;
    transform(begin(blocs), end(blocs), back_inserter(ensemble), [](Bloc b) -> Bloc {BlocRotations rot(b); return rot.CritereAlex();});
    std::sort(begin(ensemble), end(ensemble), [](Bloc a, Bloc b) -> bool {return a.getSurface() > b.getSurface();});

    vector<BlocNode> nodeList;
    vector<BlocNode> copyNode;
    for(Bloc bloc : ensemble)
    {
        nodeList.emplace_back(bloc);
        copyNode.emplace_back(bloc);
    }
    int nbThread = 100;
    int begin = 0;
    int increment = nodeList.size() / nbThread;
    vector<thread> threads(nbThread);

    auto start_time = chrono::system_clock::now();
    //initNodeList(copyNode, 0, copyNode.size());
    auto end_time = chrono::system_clock::now();

    cout << "1 threads: " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << endl;

    start_time = chrono::system_clock::now();
    for(int i = 0; i < nbThread; ++i)
    {
        threads[i] = thread([begin, increment, &nodeList](){initNodeList(nodeList, begin, begin+increment);});
        begin += increment;

    }

    for(int i=0; i < nbThread; ++i)
        threads[i].join();

    end_time = chrono::system_clock::now();

    cout << nbThread << " threads: " << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << endl;

    for(int i = 0; i < nodeList.size(); ++i)
    {
        //if(copyNode[i].getNbIncoming() != nodeList[i].getNbIncoming())
            //cout << "ERROR" << endl;
    }

    /*for(auto& node : nodeList)
    {
        cout << *node << endl;
    }
*/
}

void initNodeList(vector<BlocNode>& nodeList, int begin, int end)
{
    int size = (nodeList.size()< end) ? nodeList.size() : end;

    for(int i = begin; i < size; ++i)
    {
        for(int j = i; j < nodeList.size(); ++j)
        {
            if(nodeList[i].getBloc().canStack(nodeList[j].getBloc()))
            {
                nodeList[i].addOutgoingEdges(j);
                nodeList[j].addIncomingEdges(i);
            }
            else if(nodeList[j].getBloc().canStack(nodeList[i].getBloc()))
            {
                nodeList[j].addOutgoingEdges(i);
                nodeList[i].addIncomingEdges(j);
            }
        }
    }
}
