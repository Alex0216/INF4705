//
// Created by Alexandre on 3/31/2015.
//

#ifndef TP3_BLOC_H
#define TP3_BLOC_H


class Bloc {
public:
    Bloc(int h, int l, int p);
    int getHauteur() const;
    int getLargeur() const;
    int getProfondeur() const;

private:
    int hauteur_;
    int largeur_;
    int profondeur_;

};


#endif //TP3_BLOC_H
