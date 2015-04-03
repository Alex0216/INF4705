//
// Created by Alexandre on 3/31/2015.
//

#include "bloc.h"

Bloc::Bloc(int h, int l, int p):hauteur_(h)
{
    if(l < p)
    {
        largeur_ = l;
        profondeur_ = p;
    }
    else
    {
        largeur_ = p;
        profondeur_ = l;
    }
}

int Bloc::getHauteur() const {return hauteur_; }
int Bloc::getLargeur() const {return largeur_; }
int Bloc::getProfondeur() const {return profondeur_; }
int Bloc::getSurface() const {return largeur_ * profondeur_; }

void Bloc::extendDataSet(std::vector<Bloc> blocs)
{

}

std::ostream& operator<<(std::ostream& os, const Bloc& bloc)
{
    os << bloc.largeur_ << ", " << bloc.profondeur_ << ", " << bloc.hauteur_;
    return os;
}


bool Bloc::canStack(const Bloc &up) const
{
    return largeur_ > up.largeur_ && profondeur_ > up.profondeur_;
}
