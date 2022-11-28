/*

Classe problème de Cauchy qui construit un objet avec une
condition initale et fonction second membre

*/

#ifndef PbCauchy_hpp
#define PbCauchy_hpp

#include <fstream>
#include <functional>
#include <math.h>
#include <vector>

using namespace std;

class PbCauchy
{
  public:
    // La condition initiale
    double x0; // N'est pas constant c.f. classe Cas Test -> methode exacte
    // x0 = y(0)
    // La fonction second membre
    function<double(double, double)> second_membre;

    PbCauchy(double _x0, function<double(double, double)> _second_membre) : x0(_x0), second_membre(_second_membre){};
};

#endif /*PbCauchy_hpp*/
