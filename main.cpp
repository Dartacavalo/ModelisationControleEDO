//
//  main.cpp
//  classEDO
//
//  Created by José Maria Marques on 14/11/2022.
//



#include "PbCauchy.hpp"
#include "Solver.hpp"
#include "CasTest.hpp"

#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

// fonction de 1er essay
double essay1(double t, double x){
    return -2*t*t;
}

double exact(double t){
    return exp(-t*t);
}

// fonctioon de 2em3 essay
double essay2(double t, double x){
    return 1;
}

double exact1(double t){
    return t;
}


int main(){
    
    double a = 0;
	double b = 10;
    double x0 = exact(a);
    int N = 1000;
    
    PbCauchy test = PbCauchy(x0, essay1);
    
    EulerExplicite schema(a, b, N, "schema_EDO_EuExp", test);
    schema.calcul();
	
    CasTest castest = CasTest(exact, essay1, a, b, 10, 1000, 10, "schema_test_ptr_exp_RK", "RK");
	castest.error_export();
	
	
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
classe: cas test: PbCauchy et Sol exacte ou fichier test.cpp avec erreur et ordre de convergence du schema et representer l'erreur en fonction de h
 autres types de schemas
*/
