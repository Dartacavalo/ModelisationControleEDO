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
    wait();
    double const x0 = get_x0(a);
    double const b1 = 5;
    double const cible = 6;
    // main_schema();
    //****** Resolution de l'EDO gaussienne *******//
    test_schema("Euler Explicite", "-2 x t", x0, a, "une gaussienne");
    wait();
    PbCauchy gauss(x0, Gaussienne);
    EulerExplicite schema_euler_gaussienne(a, b, N, "gaussienne", gauss);
    schema_euler_gaussienne.plot();
    wait();

    //****** Controle en temps fini de l'EDO gaussienne *******//
    Controle gaussienne(a, b, x0, cible, N, "Simpson", A, B);
    EulerExplicite schema_euler_gaussien_controle(a, b, N, "controle_gaussienne", gaussienne.controle_PbCauchy());
    schema_euler_gaussien_controle.plot();
    wait();

    //****** Controle de l'EDO gaussienne par poleshifting *******//
    EulerExplicite schema_euler_gaussien_feedback(a, b1, N, "poleshifitng", gaussienne.feedback_PbCauchy());
    schema_euler_gaussien_feedback.plot();
    wait();

    //*****************************************************//

    //****** Resolution de l'EDO 2 *******//
    PbCauchy schema2(x0, EDO2);
    RungeKutta schema_RK_inverse(a, b, N, "Inverse", schema2);
    schema_RK_inverse.plot();
    wait();

    //*****************************************************//

    //****** Resolution de l'EDO3 *******//
    PbCauchy schemaEDO3(x0, EDO3);
    RungeKutta schema_euler_EDO3(a, b, N, "cosinusoidale", schemaEDO3);
    schema_euler_EDO3.plot();
    wait();

    //****** Controle en temps fini de l'EDO3 *******//
    Controle controle_EDO3(a, b, x0, cible, N, "PtMilieu", A_EDO3, B);
    RungeKutta schema_euler_EDO3_controle(a, b, N, "controle_codinusoidale", controle_EDO3.controle_PbCauchy());
    schema_euler_EDO3_controle.plot();
    wait();

    //****** Controle de l'EDO3 *******//
    EulerExplicite schema_euler_EDO3_feedback(a, b1, N, "poleshifitng_cossinusoidale",
                                              controle_EDO3.feedback_PbCauchy());
    schema_euler_gaussien_feedback.plot();
    wait();

    return 0;
}
