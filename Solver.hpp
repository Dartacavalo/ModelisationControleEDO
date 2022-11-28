//
//  Solver.hpp
//  ProjetC++
//
//  Created by José Maria Marques on 22/11/2022.
//

#ifndef Solver_hpp
#define Solver_hpp

#include "PbCauchy.hpp"

#include <stdio.h>
#include <functional>
#include <vector>
#include <string>

using namespace std;

class Solver{
    public:
    PbCauchy EDO;
    
    //Discretisation de l'espace
    double const a, b; // Intervalle d'etude [a;b]
    unsigned long long N; // Nombre d'intervalles de temps (il est change dans les cast tests, donc pas constant !)
    double dt; // Longueur du pas de temps
    vector<double> x_val; // Stocke les valeurs des coordonnees *** Ajouter leur taille
    vector<double> t_val; // Stocke les valeurs du temps *** Ajouter leur taille
    
    // Stockage des valeurs
    double nouvelle_sol; // Nouvelle sol : au temps n+1
    double ancienne_sol; // Ancienne sol : au temps n
    
	string nom;
	
    // Temps
    double t;
    
    // Constructeur
    Solver(double _a, double _b, unsigned long long _N, string nom,  PbCauchy _EDO);
    
    // On cree des fonctoins que l'on va surcharge avec des classes filles represantant les differents types de schemas
//	virtual void calcul_pas();
//	virtual void set_condi_ini(); // Pourrait etre surchargee en  cas de besoin

//	double get_x_val_i(double i);
//	vector<double> get_x_val();
//	vector<double> get_t_val();
//	
    // Calcule la sol
	virtual void calcul() {};
    // Exporte la sol dans un fichier a donner a gnu, mais ne change que le nom de l'export
	void expor();

    // *** Rajouter un destructeur
};

class EulerExplicite : public Solver {
    public:
    EulerExplicite(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO);
    
    void calcul_pas();
    void set_condi_ini();
    void calcul();
};

class RungeKutta : public Solver {
    public:
    double k, k1, k2, k3, k4;
    
    RungeKutta(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO);
    
    void maj_k();
    void calcul_pas();
    void set_condi_ini();
    
    void calcul();
};

#endif /* Solver_hpp */

// Q : est-ce qu'il vaut le coup d'avoir toutes ces methodes virtuelles ex: calcul_pas et set_condi_ini
// A faire : Euler implicite et CrankNicholson : Chercher des biblis pour l'inversion de syst lineaires
