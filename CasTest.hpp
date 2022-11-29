#ifndef CasTest_hpp
#define CasTest_hpp

#include <functional>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>

#include "PbCauchy.hpp"
#include "Solver.hpp"

using namespace std;

class CasTest
{
  public:
    // les dépendances évidentes
    PbCauchy pbcauchy; // Le pb de Cauchy dont solution exacte connue est a tester;

    // les nouveaux objets à construire
    function<double(double)> fct_sol_exacte; // La solution exacte du probleme de Cauchy
    vector<double> erreur_max;               // Vecteur qui stocke le calcul de l'erreur totale en norme infinie
    vector<double> erreur_L2;                // Vecteur qui stocke le calcul de l'erreur totale en norme infinie
    vector<double> h;                        // Les abscisses

    // les paramètres de test
    double const a, b;                         // l'intervalle du test
    double const N_min_erreurs, N_max_erreurs; // Le range de nos tests
    double const pas_erreurs;                  // Le pas
    string nom_schema;
    string type_schema;

    // Arguments intermediaires qui changeront de taille avec chaque nouveau calcul d erreur
    // vector<double> tps;
    // vector<double> sol_approch;

    // Le constructeur de CasTest
    CasTest(PbCauchy _pbcauchy, function<double(double)> _fct_sol_exacte, const double _a, const double _b,
            double const _N_min, double const _N_max, double const _pas, string _nom_schema, string _type_schema)
        : pbcauchy(_pbcauchy), fct_sol_exacte(_fct_sol_exacte), a(_a), b(_b), N_min_erreurs(_N_min),
          N_max_erreurs(_N_max), pas_erreurs(_pas), nom_schema(_nom_schema), type_schema(_type_schema){};

    Solver *def_schema(unsigned long long n);

    // void set_sol_exacte(Solver *schema, unsigned long long n);
    void calcul_erreur_L2(unsigned long long n);
    void calcul_erreur_max(unsigned long long n);
    void calcul_erreur_totale();

    double calcul_pente_max();
    double calcul_pente_L2();

    void expor();
    void error_export();


    //    // L'exportation de la solution exacte pour superposer à la solution approchee
    //    void exact_export();

    // *** Rajouter un destructeur
};

#endif /* CasTest_hpp */
