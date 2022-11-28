//
//  Solver.cpp
//  ProjetC++
//
//  Created by José Maria Marques on 22/11/2022.
//

#include "PbCauchy.hpp"
#include "Solver.hpp"

#include <iostream>
#include <stdio.h>
#include <functional>
#include <vector>
#include <string>

using namespace std;

Solver::Solver(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO): a(_a), b(_b), N(_N), nom(_nom), EDO(_EDO){
	nom += ".txt";
	
	// on calcule le pas
	dt = (b-a)/static_cast<double>(N);
	
	// on maj les CI
	x_val.push_back(EDO.x0);
	ancienne_sol = EDO.x0;
	t = a;
	t_val.resize(N);
	t_val.push_back(a);
}


void Solver::expor(){
	ofstream schema_EDO;
	schema_EDO.open(nom);
	calcul();
	for(double j=0; j<= N; j++){
		schema_EDO << t_val[j]<<" "<<x_val[j]<<endl;
//		cout<< t_val[j]<<" "<<x_val[j]<<endl;
	}
	schema_EDO.close();
	
//    ofstream gnuplot_input_file;
//    gnuplot_input_file.open("gnuplot_input_fileE.txt");
//    char line[100];
//    int change = sprintf(
//        line, "plot [%i:%i] 'schema_EDO.txt' with lines", (int)a, (int)b);
//    gnuplot_input_file << line << endl;
//    // system("gnome-terminal -x sh -c 'gnuplot; load gnuplot_input_file.txt; exec bash'");
//    system("gnuplot -p gnuplot_input_fileE.txt");
//    // system("load gnuplot_input_file.txt");
}


EulerExplicite::EulerExplicite(double _a, double _b,unsigned long long _N, string _nom, PbCauchy _EDO): Solver(_a, _b, _N, _nom, _EDO){
//    calcul_pas();
//    set_condi_ini();
}

//void EulerExplicite::calcul_pas(){
//    dt = (b-a)/static_cast<double>(N);
//}
//
//void EulerExplicite::set_condi_ini(){
////	x_val.resize(N);
//    x_val.push_back(EDO.x0);
//    ancienne_sol = EDO.x0;
//    t = a;
////	t_val.resize(N);
//    t_val.push_back(a);
//}

void EulerExplicite::calcul() {
    for(double i = 1; i<= N; i++){
        nouvelle_sol = ancienne_sol+dt*(EDO.second_membre(t,ancienne_sol));
        x_val.push_back(nouvelle_sol);
        ancienne_sol = nouvelle_sol;
        t += dt;
        t_val.push_back(t);
        if(i==N){ /////// A corriger
			t_val.push_back(b);
        }
//		cout<<x_val[i]<<endl;
    }
}


RungeKutta::RungeKutta(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO): Solver(_a, _b, _N, _nom, _EDO){
//    calcul_pas();
//    set_condi_ini();
}

//void RungeKutta::calcul_pas(){
//    dt = (b-a)/static_cast<double>(N);
//}

//void RungeKutta::set_condi_ini(){
////	x_val.resize(N);
//	x_val.push_back(EDO.x0);
//	ancienne_sol = EDO.x0;
//	t = a;
////	t_val.resize(N);
//	t_val.push_back(a);
//}

void RungeKutta::maj_k(){
    k1 = dt*(EDO.second_membre(t, ancienne_sol));
    k2 = dt*(EDO.second_membre((t+dt/2), (ancienne_sol+k1/2)));
    k3 = dt*(EDO.second_membre((t+dt/2), (ancienne_sol+k2/2)));
    k4 = dt*(EDO.second_membre((t+dt), (ancienne_sol+k3)));
    k = (k1+2*k2+2*k3+k4)/6;
}

void RungeKutta::calcul(){
    for(double i = 1; i<=N; i++){
        maj_k();
        nouvelle_sol = ancienne_sol+k;
        x_val.push_back(nouvelle_sol);
        ancienne_sol = nouvelle_sol;
        t += dt;
        t_val.push_back(t);
        if(i==N){ /////// A corriger
            t_val[N] = b;
        }
    }
}

//
//double Solver::get_x_val_i(double i) {
//	calcul_pas();
//	set_condi_ini();
//	calcul();
//	return x_val[i];
//}
//
//vector<double> Solver::get_x_val() {
//	calcul_pas();
//	set_condi_ini();
//	calcul();
//	return x_val;
//}
//
//vector<double> Solver::get_t_val() {
//	calcul();
//	return t_val;
//}
