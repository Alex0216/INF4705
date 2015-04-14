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

Bloc BlocRotations::CritereAlex() const
{
    int diffA = A.getProfondeur() - A.getLargeur();
    int diffB = B.getProfondeur() - B.getLargeur();
    int diffC = C.getProfondeur() - C.getLargeur();

    if(diffA < diffB)
    {
        if(diffC < diffA)
            return C;
        else
            return A;
    }
    if(diffB < diffC)
        return B;
    return C;
}

Bloc BlocRotations::operator[](int index)
{
	switch (index%3)
	{
	case 0:
		return A;
	case 1:
		return B;
	case 2:
		return C;
	default:
		return A;
	}
}
