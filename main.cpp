//
//  main.cpp
//  classEDO
//
//  Created by José Maria Marques on 14/11/2022.
//



#include "PbCauchy.hpp"
#include "Solver.hpp"
#include "CasTest.hpp"
#include "Integrale.hpp"

#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

// fonction de 1er essay
double essay1(double t, double x){
    return -2*t*x;
}

double exact(double t, double x0, double t0){
    return x0*exp(-t*t+t0*t0);
}

// fonctioon de 2em3 essay
double essay2(double t, double x){
    return 1;
}

double exact1(double t){
    return t;
}

double integrand(double x){
	return 4*sqrt(1-x*x);
}

int main(){
    
    double a = -1.5;
	double b = 1.5;
    double x0 = 1;
    int N = 100;
    
    PbCauchy test = PbCauchy(x0, essay1);
    
    EulerExplicite schema(a, b, N, "schema_EDO_EuExp_test", test);
    schema.expor();
	
    CasTest castest = CasTest(exact, essay1, a, b, x0, 1000, 10000, 100, "schema_test_ptr_exp", "EuExp");
//	castest.calcul_d_une_erreur(7000);
//	castest.calcul_erreur_totale();
	castest.exact_export(1000);
	castest.error_export();
	castest.calcul_pente();
	
//	Integrale calculPi(0, 1, integrand, 100);
	
//	cout<<calculPi.point_milieu()<<endl;
//	cout<<calculPi.simpson()<<endl;
	
//	Solver* eul = new EulerExplicite(a, b, N, "schema_EDO_EuExp", test);
//	vector<double> sol_approch = eul->get_x_val();
//	vector<double> t = eul->get_t_val();
//	vector<double> sol_exacte = eul->get_x_val();
//	for(double i = 0; i<1000; i++){
//		cout<<t[i]<<"  "<<sol_approch[i]<<"  "<<sol_exacte[i]<<"  "<<sol_approch[i] - exact(t[i]) << endl;
	return 0;
	}
	

// Séance 13 Novembre:
/*prochaine fois : gnuplot, cas test pour le schema: constante et expo,
classe: cas test: PbCauchy et Sol exacte ou fichier test.cpp avec erreur et ordre de convergence du schema et representer l'erreur en fonction de h
 autres types de schemas
*/
