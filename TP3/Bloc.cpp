//
// Created by Alexandre on 3/31/2015.
//

#include "Bloc.h"

Bloc::Bloc(int h, int l, int p):hauteur_(h), largeur_(l), profondeur_(p)
{
}

int Bloc::getHauteur() const {return hauteur_; }

int Bloc::getLargeur() const {return largeur_; }
int Bloc::getProfondeur() const {return profondeur_; }


