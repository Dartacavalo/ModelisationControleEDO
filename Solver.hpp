/*

Construction d'une classe de solveurs, c'est à dire l'implémentation de méthodes du type
Euler Explicite et Runge Kutta d'ordre 4.

*/

#ifndef Solver_hpp
#define Solver_hpp

#include "PbCauchy.hpp"
#include <functional>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Solver
{
  public:
    PbCauchy EDO;
    string nom; // nom à donner au fichier

    // Discretisation de l'espace
    double const a, b;    // Intervalle d'etude [a;b]
    unsigned long long N; // Nombre d'intervalles de temps (il est change dans les cast tests, donc pas constant !)
    double dt;            // Longueur du pas de temps
    vector<double> x_val; // Stocke les valeurs des coordonnees *** Ajouter leur taille
    vector<double> t_val; // Stocke les valeurs du temps *** Ajouter leur taille

    // Stockage des valeurs
    double nouveau_point; // Nouvelle sol : au temps n+1
    double ancien_point;  // Ancienne sol : au temps n

    // Temps
    double t;

    // Constructeur
    Solver(PbCauchy _EDO, string _nom, double _a, double _b, unsigned long long _N);

    // Calcule la sol
    virtual void calcul(){};

    // Exporte la sol dans un fichier a donner a gnu, mais ne change que le nom de l'export
    void expor();

    // Rajouter un destructeur virtuel qui appelle le destructeur de par défaut de chaque classe
    virtual ~Solver(){};
};

class EulerExplicite : public Solver
{
  public:
    EulerExplicite(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
        : Solver(_EDO, _nom, _a, _b, _N){};

    void calcul_pas();
    void calcul();
};

class RungeKutta : public Solver
{
  public:
    double k, k1, k2, k3, k4;
    RungeKutta(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
        : Solver(_EDO, _nom, _a, _b, _N){};

    void maj_k();
    void calcul_pas();
    void calcul();
};

#endif /* Solver_hpp */

// Q : est-ce qu'il vaut le coup d'avoir toutes ces methodes virtuelles ex: calcul_pas et set_condi_ini
// A faire : Euler implicite et CrankNicholson : Chercher des biblis pour l'inversion de syst lineaires
