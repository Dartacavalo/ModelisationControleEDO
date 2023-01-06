/*

Déclaration d'une classe de cas tests pour les différentes classes filles de la classe Schema :
EulerExplicite et RungeKutta

*/

#ifndef CasTest_hpp
#define CasTest_hpp

#include "Schema.hpp"

using namespace std;

class CasTest
{
  public:
    // Dépendances évidentes
    PbCauchy pbcauchy; // Pb de Cauchy dont la solution exacte connue est à tester
    function<double(double, double, double)> fct_sol_exacte; // Solution exacte du problème de Cauchy

    // Paramètres de test
    double a, b;                                     // Intervalle de calcul
    unsigned long long N_min_erreurs, N_max_erreurs; // Range de nos tests
    unsigned long long pas_erreurs;                  // Pas pour le calcul des erreurs
    string nom_schema;                               // Nom du schema pour le fichier d'export
    string type_schema;                              // Type de schema numerique

    // Nouveaux objets à construire
    vector<double> erreur_max; // Stocke le calcul de l'erreur totale en norme infinie
    vector<double> erreur_L2;  // Stocke le calcul de l'erreur totale en norme 2
    vector<double> h;          // Les abscisses

    // Constructeur de CasTest
    CasTest(PbCauchy _pbcauchy, function<double(double, double, double)> _fct_sol_exacte, double _a, double _b,
            double _N_min, double _N_max, double _pas, string _nom_schema, string _type_schema)
        : pbcauchy(_pbcauchy), fct_sol_exacte(_fct_sol_exacte), a(_a), b(_b), N_min_erreurs(_N_min),
          N_max_erreurs(_N_max), pas_erreurs(_pas), nom_schema(_nom_schema), type_schema(_type_schema)
    {
        unsigned long long size_vec = (unsigned long long)((_N_max - _N_min) / _pas);
        erreur_L2.reserve(size_vec);
        erreur_max.reserve(size_vec);
        h.reserve(size_vec);
    };

    // Fonctions membres
    Schema *def_schema(unsigned long long n) const; // Définition d'un pointeur vers un schema numerique

    // Méthodes pour les calculs de l'erreur dans les differents schemas
    void calcul_erreur(unsigned long long n); // Calcul de l'erreur pour un seul schema
    void calcul_erreur_totale();              // Calcul de l'erreur sur l'ensemble des schemas

    double calcul_pente_max() const;
    double calcul_pente_L2() const;

    void error_export(); // non constante car appelle calcul_erreur_totale qui n'est pas constante
    void exact_export(double n) const;

    // Destructeur par défaut
    ~CasTest(){};
};

#endif /* CasTest_hpp */
