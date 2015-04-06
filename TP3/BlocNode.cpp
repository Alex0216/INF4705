//
// Created by Alexandre on 4/4/2015.
//

#include "BlocNode.h"

#include <thread>

BlocNode::BlocNode(Bloc bloc):bloc_(bloc)
{

}

BlocNode::BlocNode(BlocNode &&node):bloc_(std::move(node.getBloc()))
{

}

Bloc BlocNode::getBloc() const
{
    return bloc_;
}

void BlocNode::addIncomingEdges(int index)
{
    std::lock_guard<std::mutex> lock(inMutex_);
    incomingEdges_++;
}

void BlocNode::addOutgoingEdges(int index)
{
    std::lock_guard<std::mutex> lock(outMutex_);
    outgoingEdges_++;
}

std::ostream& operator<<(std::ostream& os, const BlocNode& bloc)
{
    os << "Bloc (" << bloc.getBloc() << "): In: " << bloc.getNbIncoming() << ", Out: " << bloc.getNbOutgoing();
    return os;
}


