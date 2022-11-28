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

    // Discretisation de l'espace
    double const a, b;    // Intervalle d'etude [a;b]
    unsigned long long N; // Nombre d'intervalles de temps (il est change dans les cast tests, donc pas constant !)
    double dt;            // Longueur du pas de temps
    vector<double> x_val; // Stocke les valeurs des coordonnees *** Ajouter leur taille
    vector<double> t_val; // Stocke les valeurs du temps *** Ajouter leur taille

    // Stockage des valeurs
    double nouvelle_sol; // Nouvelle sol : au temps n+1
    double ancienne_sol; // Ancienne sol : au temps n

    string nom; // nom à donner au fichier

    // Temps
    double t;

    // Constructeur
    Solver(double _a, double _b, unsigned long long _N, string nom, PbCauchy _EDO);

    // Calcule la sol
    virtual void calcul(){};

    // Exporte la sol dans un fichier a donner a gnu, mais ne change que le nom de l'export
    void expor();

    // *** Rajouter un destructeur
};

class EulerExplicite : public Solver
{
  public:
    EulerExplicite(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
        : Solver(_a, _b, _N, _nom, _EDO){};

    void calcul_pas();
    void calcul();
};

class RungeKutta : public Solver
{
  public:
    double k, k1, k2, k3, k4;
    RungeKutta(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
        : Solver(_a, _b, _N, _nom, _EDO){};

    void maj_k();
    void calcul_pas();
    void calcul();
};

#endif /* Solver_hpp */

// Q : est-ce qu'il vaut le coup d'avoir toutes ces methodes virtuelles ex: calcul_pas et set_condi_ini
// A faire : Euler implicite et CrankNicholson : Chercher des biblis pour l'inversion de syst lineaires
