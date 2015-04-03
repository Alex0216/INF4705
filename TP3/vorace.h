//
// Created by Alexandre on 4/1/2015.
//

#ifndef TP3_ALGO_H
#define TP3_ALGO_H

#include <vector>

#include "bloc.h"

namespace vorace {

    std::vector<std::vector<Bloc>> voraceFirstFit(std::vector<Bloc>& blocs);
    std::vector<std::vector<Bloc>> voraceInsertFirstFit(std::vector<Bloc>& blocs);
}


#endif //TP3_ALGO_H
