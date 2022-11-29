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
double x(double t, double x0, double a)
{
    return x0 * exp(-(t * t - a * a));
}

// F2(t, y) = 1
double F2(double t, double y)
{
    return 1;
}

// y(t) = t
double y(double t, double x0, double a)
{
    return x0 * (t - a);
}

int main()
{
    double const a = -1.5;
    double const b = 1.5;
    double x0 = 1;
    unsigned long long N = 100;

    PbCauchy pbcauchy_gaussien = PbCauchy(x0, F1);

    EulerExplicite schema_euler_gaussien(a, b, N, "schema_EDO_EuExp", pbcauchy_gaussien);
    schema_euler_gaussien.calcul();
    schema_euler_gaussien.expor();

    CasTest erreur_gaussienne = CasTest(pbcauchy_gaussien, x, a, b, 100, 10000, 100, "schema_test_ptr_exp_RK", "EuExp");
    erreur_gaussienne.error_export();

    //	Solver* eul = new EulerExplicite(a, b, N, "schema_EDO_EuExp", test);
    //	vector<double> sol_approch = eul->get_x_val();
    //	vector<double> t = eul->get_t_val();
    //	vector<double> sol_exacte = eul->get_x_val();
    //	for(double i = 0; i<1000; i++){
    //		cout<<t[i]<<"  "<<sol_approch[i]<<"  "<<sol_exacte[i]<<"  "<<sol_approch[i] - exact(t[i]) << endl;
}

//	delete eul;

//	castest.maj_schema(100);
//	castest.calcul();
//	castest.exacte(100);
//    castest.error_export();

//    RungeKutta schema_RK(a, b, N, "schema_EDO_RK", test);
//    schema_RK.expor();
//
//    RungeKutta schema1_RK = RungeKutta(a, b, N, "schema_EDO_RK", test);
//    CasTest castest_RK(exact, essay1, schema1_RK, 100, 10000, 100);
//    castest_RK.exact_export();

//	cout<<castest.calcul_pente()<<endl;
//	cout<<castest_RK.calcul_pente()<<endl;
////    castest_RK.error_export();
//
//    EulerExplicite schema2 = EulerExplicite(a, b, 100, test);
//    CasTest castest1(exact, essay1, schema2, 1000, 10000, 100);
//    castest.exact_export();
//    castest.error_export();
//
//    return 0;
//}
// Séance 13 Novembre:
/*prochaine fois : gnuplot, cas test pour le schema: constante et expo,
classe: cas test: PbCauchy et Sol exacte ou fichier test.cpp avec erreur et ordre de convergence du schema et
representer l'erreur en fonction de h autres types de schemas
*/
