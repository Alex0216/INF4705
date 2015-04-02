//
// Created by Alexandre on 3/31/2015.
//

#include "Bloc.h"

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

void Bloc::rotate()
{
    int tmp = hauteur_;
    hauteur_ = profondeur_;
    profondeur_ = largeur_;
    largeur_ = tmp;
}

Bloc Bloc::getRotation() const
{
    Bloc b(*this);
    b.rotate();
    return b;
}

void Bloc::extendDataSet(std::vector<Bloc> blocs)
{
    blocs.reserve(blocs.size()*3);
    int size = blocs.size();
    for(int i = 0; i < size; ++i)
    {
        Bloc b = blocs[i].getRotation();
        Bloc c = b.getRotation();
        blocs.push_back(b);
        blocs.push_back(b.getRotation());
    }
}

std::ostream& operator<<(std::ostream& os, const Bloc& bloc)
{
    os << "H: " << bloc.hauteur_ << ", L: " << bloc.largeur_ << ", P: " << bloc.profondeur_;
    return os;
}


