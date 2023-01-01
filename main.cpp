#include <math.h>

#include "Schema.hpp"
#include "Controle.hpp"


using namespace std;

//****************************************************//
//************* FCTS  LES SOLVERS D'EDOS *************//
//****************************************************//

double Gaussienne(double t, double x)
{
    return -2 * t * x;
}

double fct_sol_exacte_Gaussienne(double t, double x0, double a)
{
    return x0 * exp(-(t * t - a * a));
}

double EDO2(double t, double x)
{
	return x*x;
}

double fct_sol_exacte_EDO2(double t, double x0, double t0)
{
	return 1/(1/x0 - t - t0);
}

double EDO3(double t, double x)
{
	return sin(2*t)-tan(t)*x;
}

double fct_sol_exacte_EDO3(double t, double t0, double x0)
{
	return cos(t)*(x0/cos(t0)-2*cos(t)+2*cos(t0));
}

//******* FCTS POUR TESTER LE CONTROLE NON AUTONOME ********//

double A(double t)
{
	return -2*t;
}

double A_EDO3(double t)
{
	return 1;
}

double B(double t)
{
	return 1;
}

//************************************************************//

int main()
{
	//****** Parametres pour la resolution de l'EDO gaussienne *******//
    double const a = -1.5;
    double const b = 2;
	double const b1 = 5;
    double const x0 = 0;
    const unsigned long long N = 100;
	double const cible = 6;
	
	//****** Resolution de l'EDO gaussienne *******//
	PbCauchy gauss(x0, Gaussienne);
	EulerExplicite schema_euler_gaussienne(a, b, N, "gaussienne", gauss);
	schema_euler_gaussienne.plot();
	
	//****** Controle en temps fini de l'EDO gaussienne *******//
	Controle gaussienne(a, b, x0, cible, N, "Simpson", A, B);
    EulerExplicite schema_euler_gaussien_controle(a, b, N, "controle_gaussienne", gaussienne.controle_PbCauchy());
    schema_euler_gaussien_controle.plot();
	
	//****** Controle de l'EDO gaussienne par poleshifting *******//
	EulerExplicite schema_euler_gaussien_feedback(a, b1, N, "poleshifitng", gaussienne.feedback_PbCauchy());
	schema_euler_gaussien_feedback.plot();

	//*****************************************************//
	
	//****** Resolution de l'EDO 2 *******//
	PbCauchy schema2(x0, EDO2);
	RungeKutta schema_RK_inverse(a, b, N, "Inverse", schema2);
	schema_RK_inverse.plot();
	
	//*****************************************************//
	
	//****** Resolution de l'EDO3 *******//
	PbCauchy schemaEDO3(x0, EDO3);
	RungeKutta schema_euler_EDO3(a, b, N, "cosinusoidale", schemaEDO3);
	schema_euler_EDO3.plot();
	
	//****** Controle en temps fini de l'EDO3 *******//
	Controle controle_EDO3(a, b, x0, cible, N, "PtMilieu", A_EDO3, B);
	RungeKutta schema_euler_EDO3_controle(a, b, N, "controle_codinusoidale", controle_EDO3.controle_PbCauchy());
	schema_euler_EDO3_controle.plot();
	
	//****** Controle de l'EDO3 *******//
	EulerExplicite schema_euler_EDO3_feedback(a, b1, N, "poleshifitng_cossinusoidale", controle_EDO3.feedback_PbCauchy());
	schema_euler_gaussien_feedback.plot();
	
	return 0;
}


