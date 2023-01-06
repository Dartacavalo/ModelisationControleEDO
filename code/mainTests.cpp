/*

Tests unitaires des résultats de la théorie du contrôle linéaire implémentés en C++

*/

#include "CasTest.hpp"
#include "Controle.hpp"
#include "FonctionsTest.hpp"

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
    PbCauchy gauss(x0, Gaussienne);
    CasTest erreur_gaussienne_Euler_explicite = CasTest(gauss, fct_sol_exacte_Gaussienne, a, b, N_min, N_max,
                                                        pas_erreurs, "test_erreur_Euler_Explicite", "EuExp");
    erreur_gaussienne_Euler_explicite.error_export();

    CasTest erreur_gaussienne_RK =
        CasTest(gauss, fct_sol_exacte_Gaussienne, a, b, N_min, N_max, pas_erreurs, "test_erreur_RK", "RK");
    erreur_gaussienne_RK.error_export();

    //********* Tests Controle ****************************//
    Controle gaussienne(a, b, x0, cible, N, "Simpson", A, B);

    EulerExplicite schema_euler_gaussien_controle(a, b, N, "controle_gaussienne", gaussienne.controle_PbCauchy());
    schema_euler_gaussien_controle.solve();
    vector<double> controle_gauss = schema_euler_gaussien_controle.x_val;
    double erreur_controle = abs(controle_gauss[controle_gauss.size() - 1] - cible) / cible * 100;
    cout << "L'erreur entre le dernier point du schema controle et la cible est de  " << erreur_controle << "%."
         << endl;

    //*********** Tests Méthodes Intégration ***************//

    Integrale calculPi(0, 1, integrand, 100);

    cout << "L'erreur du calcul de Pi par integration par la methode du point milieu est de "
         << abs(M_PI - calculPi.point_milieu()) / M_PI * 100 << "%." << endl;
    cout << "L'erreur du calcul de Pi par integration par la methode de Simpson est de "
         << abs(M_PI - calculPi.simpson()) / M_PI * 100 << "%." << endl;

    return 0;
}
