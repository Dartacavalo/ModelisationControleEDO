//
//  PbCauchy.hpp
//  classEDO
//
//  Created by José Maria Marques on 14/11/2022.
//

#ifndef PbCauchy_hpp
#define PbCauchy_hpp


#include <vector>
#include <fstream>
#include <math.h>
#include <functional>

using namespace std;

class PbCauchy{
    public:
    // La condition initiale
    double x0; // N'est pas constant c.f. classe Cas Test -> methode exacte
    // La fonction second membre
    function<double(double,double)> second_membre;

    PbCauchy(double _x0, function<double(double,double)> _second_membre);
};

#endif /*PbCauchy_hpp*/
