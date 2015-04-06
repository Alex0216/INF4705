//
// Created by Alexandre on 4/2/2015.
//

#ifndef TP3_BLOCROTATIONS_H
#define TP3_BLOCROTATIONS_H


#include "bloc.h"

class BlocRotations {
public:
    BlocRotations(const Bloc& b);
    BlocRotations(int h, int l, int p);

    Bloc getHighestSurface() const;
    Bloc CritereAlex() const;

	Bloc operator[](int index);

    Bloc A;
    Bloc B;
    Bloc C;

};


#endif //TP3_BLOCROTATIONS_H
