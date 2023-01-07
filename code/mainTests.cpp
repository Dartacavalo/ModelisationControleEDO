/*

Tests unitaires des résultats de la théorie du contrôle linéaire implémentés en C++

*/

#include "CasTest.hpp"
#include "Controle.hpp"
#include "FonctionsTest.hpp"
#include "Schema.hpp"
#include "affichage.hpp"
#include <cmath>

using namespace std;

int main()
{
    //****** Paramètres pour la résolution de l'EDO gaussienne *******//
    double const a = -1.5;
    double const b = 2;
    double const x0 = 1;
    const unsigned long long N = 100;
    double const cible = 6;
    const unsigned long long N_min = 100;
    const unsigned long long N_max = 1000;
    const unsigned long long pas_erreurs = 100;

    //*********** Tests Schemas Numériques ***************//

    demarrage();
    wait();
    test_schema("Euler Explicite", "-2 x t", x0, a, "exp(-x^2) ");
    wait();
    parametres(a, b, x0, N, cible, N_min, N_max, pas_erreurs);
    PbCauchy gauss(x0, Gaussienne);
    CasTest erreur_gaussienne_Euler_explicite = CasTest(gauss, fct_sol_exacte_Gaussienne, a, b, N_min, N_max,
                                                        pas_erreurs, "test_erreur_Euler_Explicite", "EuExp");
    erreur_gaussienne_Euler_explicite.error_export();
    ordre_schema_max("Euler Explicite", 1);
    wait();

    test_schema("Runge-Kutta d'ordre 4", "-2 x t", x0, a, "exp(-x^2) ");
    CasTest erreur_gaussienne_RK =
        CasTest(gauss, fct_sol_exacte_Gaussienne, a, b, N_min, N_max, pas_erreurs, "test_erreur_RK", "RK");
    wait();
    erreur_gaussienne_RK.error_export();
    ordre_schema_max("Runge-Kutta 4", 4);
    wait();

    //********* Tests Controle ****************************//

    Controle gaussienne(a, b, x0, cible, N, "Simpson", A, B);
    EulerExplicite schema_euler_gaussien_controle(a, b, N, "controle_gaussienne", gaussienne.controle_PbCauchy());
    test_controle(a, b, x0, cible, "- 2 t", "");
    wait();
    plot_controle(schema_euler_gaussien_controle, cible);
    wait();

    //*********** Tests Méthodes Intégration ***************//
    test_integrale(0, 1, integrand, 100, "4*sqrt(1-t^2)", M_PI);
    return 0;
}
