/*

Déclaration des fonctions tests à utiliser depuis les autres fichiers

*/

#ifndef FonctionsTest_hpp
#define FonctionsTest_hpp

#include <math.h>

//****************************************************//
//************** FCTS DU SOLVER D'EDOS ***************//
//****************************************************//

double Gaussienne(double t, double x);
double EDO2(double t, double x);
double EDO3(double t, double x);

//****************************************************//
//* SOLUTIONS EXACTES POUR TESTER LES SOLVERS D'EDOS *//
//****************************************************//

double fct_sol_exacte_Gaussienne(double t, double x0, double a);
double fct_sol_exacte_EDO2(double t, double x0, double t0);
double fct_sol_exacte_EDO3(double t, double t0, double x0);

//******* FCTS POUR TESTER LE CONTROLE NON AUTONOME ********//

double A(double t);
double A_EDO3(double t);
double B(double t);

//************************************************************//

double integrand(double x);

#endif /* FonctionsTest_hpp */
