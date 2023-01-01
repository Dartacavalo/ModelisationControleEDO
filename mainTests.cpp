//
//  mainTests.cpp
//  ProjetC++
//
//  Created by José Maria Marques on 01/01/2023.
//
#include "CasTest.hpp"
#include "Controle.hpp"

#include <math.h>

using namespace std;

//****************************************************//
//******* FCTS POUR TESTER LES SOLVERS D'EDOS ********//
//****************************************************//

double fct_sol_exacte_Gaussienne(double t, double x0, double a)
{
	return x0 * exp(-(t * t - a * a));
}

double fct_sol_exacte_EDO2(double t, double x0, double t0)
{
	return 1/(1/x0 - t - t0);
}

double fct_sol_exacte_EDO3(double t, double t0, double x0)
{
	return cos(t)*(x0/cos(t0)-2*cos(t)+2*cos(t0));
}


int mainTests()
{
	//****** Parametres pour la resolution de l'EDO gaussienne *******//
	double const a = -1.5;
	double const b = 2;
	double const b1 = 5;
	double const x0 = 1;
	const unsigned long long N = 100;
	double const cible = 6;
	const unsigned long long N_min = 100;
	const unsigned long long N_max = 1000;
	const unsigned long long pas_erreurs = 100;
	
	
	
	return 0;
}
