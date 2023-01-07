/*

Jouons au jeu de la théorie du contrôle linéaire implémenté en C++

*/

#include "Controle.hpp"
#include "FonctionsTest.hpp"
#include "Schema.hpp"
#include "affichage.hpp"

#include <math.h>

using namespace std;

int main()
{
    demarrage();
    wait();
    get_intervalle();
    //****** Parametres pour la resolution de l'EDO gaussienne *******//
    double const a = get_a();
    double const b = get_b(a);
    const unsigned long long N = get_N(a, b);
    double const x0 = get_x0(a, b);
    double const cible = get_cible();
    double const b1 = 3 * b;
    wait(); 
    //****** Resolution de l'EDO gaussienne *******//
    test_schema("Euler Explicite", "-2 x t", x0, a, "une gaussienne");
    wait();
    PbCauchy gauss(x0, Gaussienne);
    EulerExplicite schema_euler_gaussienne(a, b, N, "gaussienne", gauss);
    plot_schema(schema_euler_gaussienne);
    wait();

    //****** Controle en temps fini de l'EDO gaussienne *******//
    test_controle(a, b, x0, cible, "- 2 t", "");
    Controle gaussienne(a, b, x0, cible, N, "Simpson", A, B);
    EulerExplicite schema_euler_gaussien_controle(a, b, N, "controle_gaussienne", gaussienne.controle_PbCauchy());
    plot_schema(schema_euler_gaussien_controle);
    wait();
    double valeur_controle = schema_euler_gaussien_controle.x_val[schema_euler_gaussien_controle.x_val.size() - 1];
    erreur_controle(valeur_controle, cible);
    wait();

    //****** Controle de l'EDO gaussienne par poleshifting *******//
    main_poleshifting();
    EulerExplicite schema_euler_gaussien_feedback(a, b1, N, "poleshifitng", gaussienne.feedback_PbCauchy());
    plot_schema(schema_euler_gaussien_feedback);
    wait();

    //*****************************************************//

    //****** Resolution de l'EDO 2 *******//
    test_schema("Runge-Kutta 4", "x^2", x0, a, "1/((a+1/x0) - x)");
    PbCauchy phcauchy2(x0, EDO2);
    RungeKutta schema_RK_inverse(a, b, N, "Inverse", phcauchy2);
    plot_schema(schema_RK_inverse);
    wait();

    //*****************************************************//

    //****** Resolution de l'EDO3 *******//
    test_schema("Runge-Kutta 4", "cos(t) * x", x0, a, "x0 * exp( - sin( t ) + sin( t0 ))");
    PbCauchy schemaEDO3(x0, EDO3);
    RungeKutta schema_euler_EDO3(a, b, N, "exponentielle_sinusoidale", schemaEDO3);
    plot_schema(schema_euler_EDO3);
    wait();

    //****** Controle en temps fini de l'EDO3 *******//
    test_controle(a, b, x0, cible, "", "");
    Controle controle_EDO3(a, b, x0, cible, N, "PtMilieu", A_EDO3, B);
    RungeKutta schema_euler_EDO3_controle(a, b, N, "controle_cosinusoidale", controle_EDO3.controle_PbCauchy());
    plot_schema(schema_euler_EDO3_controle);
    wait();

    //****** Controle de l'EDO3 *******//
    test_controle(a, b, x0, cible, "", "");
    EulerExplicite schema_euler_EDO3_feedback(a, b1, N, "poleshifitng_cossinusoidale",
                                              controle_EDO3.feedback_PbCauchy());
    plot_schema(schema_euler_gaussien_feedback);
    wait();

    return 0;
}
