//
// Created by Alexandre on 3/31/2015.
//

#ifndef TP3_BLOC_H
#define TP3_BLOC_H

#include <iostream>
#include <vector>

class Bloc {
public:
    Bloc(int h, int l, int p);
    Bloc(const Bloc&) = default;
    int getHauteur() const;
    int getLargeur() const;
    int getProfondeur() const;
    int getSurface() const;
    void rotate();
    Bloc getRotation() const;
    inline bool operator<(const Bloc& r){return getSurface() < r.getSurface();}
    friend std::ostream& operator<<(std::ostream& os, const Bloc& bloc);

    static void extendDataSet(std::vector<Bloc> blocs);

private:
    int hauteur_;
    int largeur_;
    int profondeur_;

};


#endif //TP3_BLOC_H
