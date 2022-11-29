#include "CasTest.hpp"
#include "PbCauchy.hpp"
#include "Solver.hpp"
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
// F1(t, x) = -2*t^2
double F1(double t, double x)
{
    return -2 * t * x;
}

// x(t) = exp(-t^2)
double fct_sol_exacte_F1(double t, double x0, double a)
{
    return x0 * exp(-(t * t - a * a));
}

// F2(t, y) = 1
double F2(double t, double y)
{
    return 1;
}

// y(t) = t
double fct_sol_exacte_F2(double t, double x0, double a)
{
    return (t - a) + x0;
}

int main()
{
    double a = -1.5;
    double const b = 1.5;
    double x0 = 1;
    unsigned long long N = 10;
    const unsigned long long N_min = 100;
    const unsigned long long N_max = 1000;
    const unsigned long long pas_erreurs = 100;

    PbCauchy pbcauchy_gaussien = PbCauchy(x0, F1);

    EulerExplicite schema_euler_gaussien(a, b, N, "schema_EDO_EuExp", pbcauchy_gaussien);
    schema_euler_gaussien.calcul();
    schema_euler_gaussien.expor();

    CasTest erreur_gaussienne =
        CasTest(pbcauchy_gaussien, fct_sol_exacte_F1, a, b, N_min, N_max, pas_erreurs, "test_erreur_RK", "RK");
    erreur_gaussienne.error_export();
}

double integrand(double x){
	return 4*sqrt(1-x*x);
}

// Séance 13 Novembre:
/*prochaine fois : gnuplot, cas test pour le schema: constante et expo,
classe: cas test: PbCauchy et Sol exacte ou fichier test.cpp avec erreur et ordre de convergence du schema et
representer l'erreur en fonction de h autres types de schemas
*/
