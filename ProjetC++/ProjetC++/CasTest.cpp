//
//  CasTest.cpp
//  ProjetC++
//
//  Created by José Maria Marques on 20/11/2022.
//



#include "PbCauchy.hpp"
#include "Solver.hpp"
#include "CasTest.hpp"

#include <iostream>
#include <math.h>
#include <vector>
#include <functional>
#include <stdio.h>

using namespace std;

//Solver _schema,
//Solver(double _a, double _b, int _N, PbCauchy _EDO);

CasTest::CasTest(function<double(double)> _fct_sol_exacte, function<double(double, double)> _fct_second_membre, double const _a, double const _b, double const _N_min, double const _N_max, double const _pas, string _nom_schema, string _type_schema): fct_sol_exacte(_fct_sol_exacte), fct_second_membre(_fct_second_membre), a(_a), b(_b),  N_min(_N_min), N_max(_N_max), pas(_pas), nom_schema(_nom_schema), type_schema(_type_schema){}

Solver* CasTest::def_schema(double n){
	PbCauchy pbcauchy(fct_sol_exacte(a), fct_second_membre);
	if(type_schema == "EuExp"){
		EulerExplicite* schema = new EulerExplicite(a, b, n, nom_schema, pbcauchy);
		return schema;
	}
	else /*if (type_schema == "RK")*/{
		RungeKutta* schema = new RungeKutta(a, b, n, nom_schema, pbcauchy);
		return schema;
	}
}

//void CasTest::set_tps(Solver* schema){
//	tps = schema->t_val;
//}
//
//void CasTest::set_sol_approch(Solver* schema){
//	sol_approch = schema->x_val;
//}

void CasTest::set_sol_exacte(double n){
	for(double i=0; i<= n; i++){
		sol_exacte.push_back(fct_sol_exacte(tps[i]));
	}
}

void CasTest::calcul_d_une_erreur(double n){
	double err = 0;
	Solver* schema = def_schema(n);
//	tps.empty();
//	sol_approch.empty();
//	sol_exacte.empty();
	tps = schema->t_val;
	sol_approch = schema->x_val;
	set_sol_exacte(n);
	h.push_back(schema->dt);
	for(double i = 0; i<=n; i++){
//		cout<<sol_approch[i]<<endl;
		err += (sol_exacte[i]-sol_approch[i])*(sol_exacte[i]-sol_approch[i]);
			
	}
//		cout<<err<<endl;
	
	error_tot.push_back(sqrt(err));
	delete schema;
}

void CasTest::calcul_erreur_totale(){
	for(double n = N_min+1; n< N_max; n+= pas){
		calcul_d_une_erreur(n);
	}
}

double CasTest::calcul_pente(){
	return (log(error_tot[97])-log(error_tot[0]))/(log(h[97])-log(h[0]));
}

void CasTest::error_export(){
    ofstream erreur_schema;
	string nom_erreur = nom_schema + "_erreur_schema.txt";
    erreur_schema.open(nom_erreur);
	calcul_erreur_totale();
	cout<<calcul_pente()<<endl;
    for(double i= 2; i < (N_max-N_min)/(int)pas; i++){
        erreur_schema << h[i] <<" "<<error_tot[i]<<" "<<log(error_tot[i])<<endl;
    }
    erreur_schema.close();
}


//void CasTest::exact_export(double n){
//	string nom_solution_exate = nom_schema + "_solution_exacte.txt";
//	ofstream solution_exacte;
//    solution_exacte.open(nom_solution_exate);
//	exacte(n);
//    for(double i= 0; i < n; i++){
//        solution_exacte <<temps[i] <<" "<<fct_sol_exacte(temps[i])<<endl;
////		cout<<temps[i]<<" "<< fct_sol_exacte(temps[i])<<endl;
//    }
//    solution_exacte.close();
//}



//PbCauchy CasTest::set_pbCauchy(){
//	PbCauchy EDO_test = PbCauchy( fct_sol_exacte(a), fct_second_membre);
//	return EDO_test;
//}
//
//Solver CasTest::set_schema(double n){
//	// On voit le type se schema voulu
//	if(type_schema == "EuExp"){
//		Solver schema = EulerExplicite(a, b, n, nom_schema, set_pbCauchy());
//		return schema;
//	}
//	else/*(type_schema == "RK")*/{
//		Solver schema = RungeKutta(a, b, n, nom_schema, set_pbCauchy());
//		return schema;
//	}
//		// On mettra l'exception ici
//}

//
//void CasTest::maj_schema(double n){
//	N = n;
//	calcul();
//	for(double i =0; i<n; i++){
////		cout<<x_val[i]<<endl;
//	}
//}
//
//void CasTest::tps(double n){
//	temps.clear();
//	temps.resize(n);
//	temps.push_back(a);
//	N=n;
//	calcul_pas();
//	cout<<dt<<endl;
//	for(double i = 0; i<n; i++){
//		temps.push_back(temps[i]+dt);
////		cout<<temps[i]<<endl;
//	}
//	temps.push_back(b);
//}
//
//void CasTest::exacte(double n){
////	sol_exacte.resize(n);
//	N = n;
//	tps(n);
//	calcul();
//    for(double i = 0; i<n; i++){
//        sol_exacte.push_back(fct_sol_exacte(temps[i]));
////		cout<<temps[i]<<endl;
//    }
//}
//
//void CasTest::approx(double n){
////	sol_approch.resize(n);
//	maj_schema(n);
////	sol_approch = schema.x_val;
//	for(double i = 0; i<n; i++){
////		cout<<x_val[i]<<endl;
//		sol_approch.push_back(x_val[i]);
//	}
//}
//
//void CasTest::erreur(double n){
////	Solver schema = set_schema(n);
////	maj_vects(n, schema);
//	maj_schema(n);
//    double err = 0;
//    for(double i = 0; i<n; i++){
//        err += (sol_exacte[i]-sol_approch[i])*(sol_exacte[i]-sol_approch[i]);
////		cout<<sol_approch[i]<<endl;
//    }
////	cout<<err<<endl;
//    error_tot.push_back(sqrt(err));
//}
//
//void CasTest::calcul_error(){
//    for(double n= N_min; n<= N_max; n+=pas){
//        maj_schema(n);
//        erreur(n);
//		h.push_back(dt);
//    }
//}
//

//
//void CasTest::exact_export(double n){
//	string nom_solution_exate = nom_schema + "_solution_exacte.txt";
//	ofstream solution_exacte;
//    solution_exacte.open(nom_solution_exate);
//	exacte(n);
//    for(double i= 0; i < n; i++){
//        solution_exacte <<temps[i] <<" "<<fct_sol_exacte(temps[i])<<endl;
////		cout<<temps[i]<<" "<< fct_sol_exacte(temps[i])<<endl;
//    }
//    solution_exacte.close();
//}
//
//void CasTest::error_export(){
//    ofstream erreur_schema;
//	string nom_erreur = nom_schema + "_erreur_schema.txt";
//    erreur_schema.open(nom_erreur);
//    calcul_error();
//    for(double i= 0; i <= (N_max-N_min)/pas; i++){
//        erreur_schema << h[i] <<" "<<error_tot[i]<<" "<<log(error_tot[i])<<endl;
//    }
//    erreur_schema.close();
//}

// Questions:
// - comment faire EDO->x0 = fct_sol_exacte(schema->a) ?
// - le fiichier erreur par schema ? Rajouter ligne qui indique le type de schema
