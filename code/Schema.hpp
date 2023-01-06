/*

Déclaration d'une classe de solveurs, c'est à dire l'implémentation de méthodes du type
Euler Explicite et Runge Kutta d'ordre 4.

*/

#ifndef Solver_hpp
#define Solver_hpp

#include "PbCauchy.hpp"
#include <string>
#include <vector>

using namespace std;

class Schema
{
  public:
    PbCauchy EDO; // Le problème de Cauchy a résoudre
    string nom;   // Nom à donner au fichier

    // Discrétisation de l'espace
    double a, b;    // Intervalle d'étude [a;b]
    unsigned long long N; // Nombre d'intervalles de temps (il est changé dans les cast tests, donc pas constant !)
    double dt;            // Longueur du pas de temps
    double t;             // Temps
    vector<double> x_val; // Stocke les valeurs des coordonnees
    vector<double> t_val; // Stocke les valeurs du temps

    // Stockage des valeurs
    double nouveau_point; // Nouvelle sol : au temps n+1
    double ancien_point;  // Ancienne sol : au temps n

    // Constructeur de la classe
    Schema(PbCauchy _EDO, string _nom, double _a, double _b, unsigned long long _N);

    // Fonctions membres
    virtual void solve(){}; // Calcule la solution approchée
    void plot();            // Exporte la sol dans un fichier a donner a gnuplot, mais ne change que le nom de l'export

    // Destructeur virtuel qui appelle le destructeur par défaut de chaque classe
    virtual ~Schema(){};
};

class EulerExplicite : public Schema
{
  public:
    // Constructeur de la classe fille pour le schéma d'Euler
    EulerExplicite(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
        : Schema(_EDO, _nom, _a, _b, _N){};

    void solve(); // Calcul de la solution avec le schéma d'Euler
};

class RungeKutta : public Schema
{
  public:
    double k, k1, k2, k3, k4; // Pentes de la méthode de Runge-Kutta

    // Constructeur de la classe fille pour le schema Runge-Kutta d'ordre 4
    RungeKutta(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
        : Schema(_EDO, _nom, _a, _b, _N){};

    void maj_k(); // Mise à jour de k pour chaque pas de la méthode de Runge Kutta
    void solve(); // Calcul de la solution avec le schéma de Runge Kutta
};

#endif /* Solver_hpp */
