/*

Classe problème de Cauchy qui construit un objet avec une
condition initale et fonction second membre

*/

#ifndef PbCauchy_hpp
#define PbCauchy_hpp

#include <functional>

using namespace std;

class PbCauchy
{
  public:
    double x0;                                          // La condition initiale
    function<double(double, double)> fct_second_membre; // La fonction second membre

    // Constructeur
    PbCauchy(double _x0, function<double(double, double)> _second_membre)
        : x0(_x0), fct_second_membre(_second_membre){};
    
    // Destructeur par défaut
    ~PbCauchy(){};
};

#endif /*PbCauchy_hpp*/
