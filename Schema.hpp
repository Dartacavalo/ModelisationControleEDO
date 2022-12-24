/*

Construction d'une classe de solveurs, c'est à dire l'implémentation de méthodes du type
Euler Explicite et Runge Kutta d'ordre 4.

*/

#ifndef Solver_hpp
#define Solver_hpp

#include <string>
#include <vector>

#include "PbCauchy.hpp" 


using namespace std;

class Schema
{
  public:
    PbCauchy EDO; // Le probleme de Cauchy a resoudre
    string nom;   // Nom à donner au fichier

    // Discretisation de l'espace
    double const a, b;    // Intervalle d'etude [a;b]
    unsigned long long N; // Nombre d'intervalles de temps (il est change dans les cast tests, donc pas constant !)
    double dt;            // Longueur du pas de temps
	double t;             // Temps
    vector<double> x_val; // Stocke les valeurs des coordonnees *** Ajouter leur taille
    vector<double> t_val; // Stocke les valeurs du temps *** Ajouter leur taille

    // Stockage des valeurs
    double nouveau_point; // Nouvelle sol : au temps n+1
    double ancien_point;  // Ancienne sol : au temps n

    // Constructeur de la classe
    Schema(PbCauchy _EDO, string _nom, double _a, double _b, unsigned long long _N);

    virtual void solve(){}; // Calcule la solution approchee
    void plot();           // Exporte la sol dans un fichier a donner a gnu, mais ne change que le nom de l'export
    
    virtual ~Schema(){};  // Rajouter un destructeur virtuel qui appelle le destructeur de par défaut de chaque classe
};

class EulerExplicite : public Schema
{
  public:
	// Constructeur de la classe fille pour le schema d'Euler
    EulerExplicite(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
        : Schema(_EDO, _nom, _a, _b, _N){};

    void solve();  // Calcul de la solution avec le schema d'Euler
};

class RungeKutta : public Schema
{
  public:
    double k, k1, k2, k3, k4; // Les arguments specifiques au calcul du schema
	
	// Constructeur de la classe fille pour le schema Runge-Kutta d'odre 4
    RungeKutta(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
        : Schema(_EDO, _nom, _a, _b, _N){};

    void maj_k();  // mise a jour de k pour chaque pas de la methode de Runge Kutta
    void solve();  // Calcul de la solution avec le schema de Runge Kutta
};

#endif /* Solver_hpp */

