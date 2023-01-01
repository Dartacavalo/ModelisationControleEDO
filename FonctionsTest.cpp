//
//  FonctionsTest.cpp
//  ProjetC++
//
//  Created by José Maria Marques on 01/01/2023.
//
#include <stdio.h>
#include <math.h>

//****************************************************//
//************** FCTS DU SOLVER D'EDOS ***************//
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
