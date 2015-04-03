//
// Created by Alexandre on 4/2/2015.
//

#include "blocrotation.h"

#include <assert.h>

BlocRotations::BlocRotations(const Bloc &b):
        A(b),
        B(b.getProfondeur(), b.getLargeur(), b.getHauteur()),
        C(b.getLargeur(), b.getProfondeur(), b.getHauteur()) {

}

BlocRotations::BlocRotations(int h, int l, int p):
        A(h, l, p), B(l, h, p), C(p, h, l)
{

}

Bloc BlocRotations::getHighestSurface() const
{
    if(A.getSurface() > B.getSurface())
    {
        if(A.getSurface()> C.getSurface())
            return A;
        else
            return C;
    }
    else if(B.getSurface() > C.getSurface())
        return B;
    else
        return C;
}
