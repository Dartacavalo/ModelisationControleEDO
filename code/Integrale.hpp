/*

Déclaration d'une classe de calcul d'intégrale avec deux méthodes :
celle du point milieu et celle de simpson

*/

#ifndef Integrale_hpp
#define Integrale_hpp

#include <functional>

using namespace std;

class Integrale
{
  private:
    double a, b;                             // Intervalle d'intégration numérique
    function<double(double)> fct_integrande; // Fonction à intégrer
    unsigned long long N;                    // Nombre d'intervalles d'intégration
    double h;                                // Pas d'integration

  public:
    // Constructeur de la classe integrale
    Integrale(double _a, double _b, function<double(double)> fct_integrande, unsigned long long _N);

    // Méthodes d'integration
    double point_milieu() const; // Méthode du point milieu
    double simpson() const;      // Méthode de Simpson
};

#endif /* Integrale_hpp */
