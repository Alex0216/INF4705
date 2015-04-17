//
// Created by Alexandre on 3/31/2015.
//

#ifndef TP3_BLOC_H
#define TP3_BLOC_H

#include <iostream>
#include <vector>

class Bloc {
public:
    Bloc() = default;
    Bloc(int h, int l, int p);
    Bloc(const Bloc&) = default;
    int getHauteur() const;
    int getLargeur() const;
    int getProfondeur() const;
    int getSurface() const;

    bool canStack(const Bloc& up) const;


    /**
     * Un bloc est plus petit qu'un autre seulement si sa largeur et sa profondeur sont strictement
     * plus petite que l'autre bloc
     */
    inline bool operator<(const Bloc& r){return largeur_ < r.largeur_ && profondeur_ < r.profondeur_;}
    inline bool operator>(const Bloc& r){return largeur_ > r.largeur_ && profondeur_ > r.profondeur_;}

	bool operator==(const Bloc& r);

    friend std::ostream& operator<<(std::ostream& os, const Bloc& bloc);

    static void extendDataSet(std::vector<Bloc> blocs);

private:
    int hauteur_;
    int largeur_;
    int profondeur_;

};


#endif //TP3_BLOC_H
