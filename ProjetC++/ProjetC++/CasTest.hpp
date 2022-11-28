//
//  CasTest.hpp
//  ProjetC++
//
//  Created by José Maria Marques on 20/11/2022.
//

#ifndef CasTest_hpp
#define CasTest_hpp

#include <stdio.h>
#include <functional>
#include <vector>
#include <iostream>
#include <math.h>

#include "PbCauchy.hpp"
#include "Solver.hpp"

using namespace std;

class CasTest{
    public:
    function<double(double)> fct_sol_exacte; // La solution exacte du probleme de Cauchy
    vector<double> sol_exacte;  // Vecteur qui stocke le calcul de l'erreur *** Ajouter sa taille
    vector<double> error_tot;  // Vecteur qui stocke le calcul de l'erreur totale *** Ajouter sa taille
    vector<double> h; // Les abscices
//    PbCauchy* EDO_test; // Le pb de Cauchy dont solution exacte connue est a tester;
//    Solver* schema; // Le schema de Cauchy a tester
	function<double(double, double)> fct_second_membre;
	double x0;
	double const a, b;
    double const N_min, N_max; // Le range de nos tests
    double const pas; // Le pas
	string nom_schema;
	string type_schema;
	
    // Arguments intermediaires qui changeront de taille avec chaque nouveau calcul d erreur
    vector<double> tps;
    vector<double> sol_approch;
    
    // Le constructeur de CasTest
	CasTest(function<double(double)> _sol_exacte, function<double(double, double)> _fct_second_membre, double const _a, double const _b, double const _N_min, double const _N_max, double const _pas, string _nom_schema, string _type_schema);
    
	Solver* def_schema(double n);
	
//	void set_tps(Solver* schema);
//	void set_sol_approch(Solver* schema);
	void set_sol_exacte(double n);
	void calcul_d_une_erreur(double n);
	void calcul_erreur_totale();
	void error_export();
	double calcul_pente();
//    // Mise a jour des vecteurs et schema intermediaires dans le calcul de l'erreur
////    void maj_CI();
//    void maj_vects(double n);
//    void maj_schema(double n);
//    void exacte(double n);
//
//    // Le calcul de l'erreur
//    void erreur(double n); // Calcul de n'erreur pout une iteration
//    void calcul_error();  // Boucle iterant sur le calcul d'erreur
//	double calcul_pente(); // Calcule la pente de l'erreur, a utiliser que pour Euler Explicite et RungeKutta
//
//    // L'exportation de l'erreur
//    void error_export();
//
//    // L'exportation de la solution exacte pour superposer à la solution approchee
//    void exact_export();
    
    // *** Rajouter un destructeur
    
};

#endif /* CasTest_hpp */
