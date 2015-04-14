//
// Created by Alexandre on 4/4/2015.
//

#ifndef TP3_BLOCNODE_H
#define TP3_BLOCNODE_H

#include <memory>
#include <mutex>
#include <set>

#include "Bloc.h"

class BlocNode
{
public:
    BlocNode(Bloc bloc);
    BlocNode(BlocNode&& node);

    Bloc getBloc() const;
    void addIncomingEdges(int index);
    void addOutgoingEdges(int index);

    int getNbIncoming() const
    { return incomingEdges_;}

    int getNbOutgoing() const
    {return outgoingEdges_;}

    friend std::ostream& operator<<(std::ostream& os, const BlocNode& bloc);

private:
    Bloc bloc_;

    int incomingEdges_ = 0;
    std::mutex inMutex_;
    int outgoingEdges_ = 0;
    std::mutex outMutex_;

};


#endif //TP3_BLOCNODE_H
