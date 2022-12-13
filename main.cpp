#include <math.h>

#include "Schema.hpp"
#include "Controle.hpp"


using namespace std;
double F1(double t, double x)
{
    return -2 * t * x;
}

double F3(double t, double x)
{
	double x0 = 1;
	double t0 = 0;
	double t1 = 1.5;
	double cible = -1;
	long double C = 2*exp(t1)*(cible-/*pbcauchy.*/x0*exp(t1-t0))/(exp(2*(t1-t0))-1.);
	
	return  x + C*exp(-t);
}

double fct_sol_exacte_F3(double t, double xo, double t0){
	double x0 = 0.22;
	double t1 = 1.5;
	double cible = 10;
	double C = -2*exp(t1)*(cible-/*pbcauchy.*/x0*exp(t1-t0))/(exp(-2*t1)-exp(-2*t0));
//	double c0 = (x0 + C/2.);
	return x0*exp(t) + C*sinh(t);
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

//double sec_membre(double t, double x){
//	return F3(t,x) + u(t,x);
//}


//******* FCTS POUR TESTER LE CONTROLE NON AUTONOME ********//

double A(double t){
	return -2*t;
//	return 1/(t*t);
}

double B(double t){
	return 1;
}

double R(double t, double s){
	double N = 100;
	Integrale int_A(s, t, A, N);
	return exp(int_A.simpson());
}

double gramian_integrand(double s){
	double t1 = 1.5;
	return R(t1, s)*R(t1, s)*B(s)*B(s);
}

double Gramian(){
	double N=100;
	double t0 = -1.5;
	double t1 = 1.5;
	Integrale gramian(t0, t1, gramian_integrand, N);
	return gramian.simpson();
}

double u(double s){
	double x0 = 1;
//	double N = 100;
	double t1 = 1.5;
	double t0 = -1.5;
	double cible = 19;
	double y = (cible-R(t1,t0)*x0)/Gramian();
	return B(s)*R(t1,s)*y;
}

double integrrande_sol_exacte(double s){
	double t1 = 1.5;
	return R(t1, s)*B(s)*u(s);
}

double controle_sol_exacte(){
	double x0 = 1;
	double N = 100;
	double t1 = 1.5;
	double t0 = -1.5;
//	double cible = 6;
	Integrale terme(t0, t1, integrrande_sol_exacte, N);
	return R(t1, t0)*x0 + terme.simpson();
}

double controle_gaussienne(double t, double x){
	return A(t)*x + B(t)*u(t);
}

//Prochaine étape définir ce pb dans une classe
//************************************************************//





int main()
{
    double const a = -1.5;
    double const b = 1.5;
	double const b1 = 5;
    double const x0 = 0;
    const unsigned long long N = 100;
	double const cible = 6;
//    const unsigned long long N_min = 1000;
//    const unsigned long long N_max = 10000;
//    const unsigned long long pas_erreurs = 100;

	Controle gaussienne(a, b, x0, cible, N, "Simpson", A, B);
    EulerExplicite schema_euler_gaussien_controle(a, b, N, "controle_gaussienne", gaussienne.controle_PbCauchy());
    schema_euler_gaussien_controle.calcul();
    schema_euler_gaussien_controle.expor();
	
	EulerExplicite schema_euler_gaussien_feedback(a, b1, N, "poleshifitng", gaussienne.feedback_PbCauchy());
	schema_euler_gaussien_feedback.calcul();
	schema_euler_gaussien_feedback.expor();
	
	return 0;

//
//
//
//	Controle controle = Controle( x0, cible, a, b);
//
//	PbCauchy pbcauchy_gaussien = PbCauchy(x0, F3);
//    EulerExplicite schema_euler_gaussien(a, b, N, "schema_EDO_EuExp", pbcauchy_gaussien);
//    schema_euler_gaussien.calcul();
//    schema_euler_gaussien.expor();

//    CasTest erreur_gaussienne =
//        CasTest(pbcauchy_gaussien, fct_sol_exacte_F3, a, b, N_min, N_max, pas_erreurs, "test_erreur_RK", "RK");
//    erreur_gaussienne.error_export();
//	erreur_gaussienne.exact_export(100);
}

double integrand(double x){
	return 4*sqrt(1-x*x);
}

// Séance 13 Novembre:
/*prochaine fois : gnuplot, cas test pour le schema: constante et expo,
classe: cas test: PbCauchy et Sol exacte ou fichier test.cpp avec erreur et ordre de convergence du schema et
representer l'erreur en fonction de h autres types de schemas
*/
