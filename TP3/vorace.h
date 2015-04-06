//
// Created by Alexandre on 4/1/2015.
//

#ifndef TP3_ALGO_H
#define TP3_ALGO_H

#include <vector>

#include "bloc.h"

namespace vorace {

    std::vector<std::vector<Bloc>> firstFit(std::vector<Bloc>& blocs);
    std::vector<std::vector<Bloc>> insertFirstFit(std::vector<Bloc>& blocs);
	std::vector<std::vector<Bloc>> reverserInsertFirstFit(std::vector<Bloc>& blocs);
	std::vector<std::vector<Bloc>> insertBestFit(std::vector<Bloc>& blocs);
}


#endif //TP3_ALGO_H
