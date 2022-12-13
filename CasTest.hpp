#ifndef CasTest_hpp
#define CasTest_hpp

#include "Schema.hpp"

using namespace std;

class CasTest
{
  public:
    // les dépendances évidentes
    PbCauchy pbcauchy; // Le pb de Cauchy dont solution exacte connue est a tester;
    function<double(double, double, double)> fct_sol_exacte; // La solution exacte du probleme de Cauchy

    // les paramètres de test
    double a, b;                         					// l'intervalle de calcul
    const unsigned long long N_min_erreurs, N_max_erreurs;  // Le range de nos tests
    const unsigned long long pas_erreurs;                   // Le pas
    string nom_schema;										// Le nom du schema pour le fichier d'export
    string type_schema;										// Le type de schema numerique

    // les nouveaux objets à construire
    vector<double> erreur_max; // Vecteur qui stocke le calcul de l'erreur totale en norme infinie
    vector<double> erreur_L2;  // Vecteur qui stocke le calcul de l'erreur totale en norme infinie
    vector<double> h;          // Les abscisses

    // Le constructeur de CasTest
    CasTest(PbCauchy _pbcauchy, function<double(double, double, double)> _fct_sol_exacte, const double _a,
            const double _b, double const _N_min, double const _N_max, double const _pas, string _nom_schema,
            string _type_schema)
        : pbcauchy(_pbcauchy), fct_sol_exacte(_fct_sol_exacte), a(_a), b(_b), N_min_erreurs(_N_min),
          N_max_erreurs(_N_max), pas_erreurs(_pas), nom_schema(_nom_schema), type_schema(_type_schema){};

    Schema *def_schema(unsigned long long n) const; // Definition d'un schema numerique en tant que pointeur, donc methode constante

	
	// Methodes virtuelles pour les calculs de l'erreur dans les differents schemas
    void calcul_erreur(unsigned long long n); // Calcul de l'erreur pour un seul schema et stockage dans un vecteur
    void calcul_erreur_totale(); // Calcul de l'erreur totale sur l'ensemble des schema

    double calcul_pente_max() const; // Calcul de la pente de l'erreur en norme sup
    double calcul_pente_L2() const;  // Calcul de la pente de l'erreur en norme 2
	
    void error_export();			// Export de l'erreur
    void exact_export(double n) const;	// Export de la solution exacte
    
};

#endif /* CasTest_hpp */
