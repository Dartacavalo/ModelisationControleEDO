#include "CasTest.hpp"
#include "PbCauchy.hpp"
#include "Solver.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>

using namespace std;

Solver *CasTest::def_schema(unsigned long long n)
{
    if (type_schema == "EuExp")
    {
        EulerExplicite *schema = new EulerExplicite(a, b, n, nom_schema, pbcauchy);
        schema->calcul();
        return schema;
    }
    else /*if (type_schema == "RK")*/
    {
        RungeKutta *schema = new RungeKutta(a, b, n, nom_schema, pbcauchy);
        schema->calcul();
        return schema;
    }
}

void CasTest::calcul_erreur_L2(unsigned long long n)
{
    double err = 0;
    Solver *schema = def_schema(n);
    h.push_back(schema->dt);
    for (unsigned long long i = 0; i <= n; i++)
    {
        err += (fct_sol_exacte(schema->t_val[i]) - schema->x_val[i]) *
               (fct_sol_exacte(schema->t_val[i]) - schema->x_val[i]);
    }

    erreur_L2.push_back(sqrt(err));
    delete schema;
}

void CasTest::calcul_erreur_max(unsigned long long n)
{
    double err = 0;
    Solver *schema = def_schema(n);
    // h.push_back(schema->dt) trouver une solution alternative à ce commentaire
    for (unsigned long long i = 0; i <= n; i++)
    {
        err = max(err, abs(fct_sol_exacte(schema->t_val[i]) - schema->x_val[i]));
    }

    erreur_max.push_back(err);
    delete schema;
}

void CasTest::calcul_erreur_totale()
{
    for (unsigned long long n = N_min_erreurs + 1; n < N_max_erreurs; n += pas_erreurs)
    {
        calcul_erreur_L2(n);
        calcul_erreur_max(n);
    }
    // c'est un peut dodgy de faire ça comme ça, faut vérifier que h et erreur_L2 ont la même taille
    // c'est le cas mais bon, à revoir
}

double CasTest::calcul_pente_max()
{
    return (log(erreur_max[h.size() - 1]) - log(erreur_max[0])) / (log(h[h.size() - 1]) - log(h[0]));
}

double CasTest::calcul_pente_L2()
{
    return (log(erreur_L2[h.size() - 1]) - log(erreur_L2[0])) / (log(h[h.size() - 1]) - log(h[0]));
}

void CasTest::error_export()
{
    ofstream erreur_schema_max;
    ofstream erreur_schema_L2;
    string nom_erreur_max = nom_schema + "_erreur_schema_max.txt";
    string nom_erreur_L2 = nom_schema + "_erreur_schema_L2.txt";
    erreur_schema_max.open(nom_erreur_max);
    erreur_schema_L2.open(nom_erreur_L2);
    calcul_erreur_totale();
    // cout << calcul_pente_max() << endl;
    for (unsigned long long i = 0; i < h.size(); i++)
    {
        erreur_schema_max << h[i] << " " << erreur_max[i] << " " << log(erreur_max[i]) << endl;
        erreur_schema_L2 << h[i] << " " << erreur_L2[i] << " " << log(erreur_L2[i]) << endl;
    }
    erreur_schema_max.close();
    erreur_schema_L2.close();

    double hmin = *min_element(h.begin(), h.end());
    double hmax = *max_element(h.begin(), h.end());

    ofstream gnuplot_input_file;
    string gnuplot_namefile = "gnuplot_" + nom_schema + "erreur_L2.bat";
    gnuplot_input_file.open(gnuplot_namefile);
    gnuplot_input_file << "plot [" << hmin << ":" << hmax << "] '" << nom_erreur_L2 << "' with lines" << endl;
    // system("gnome-terminal -x sh -c 'gnuplot; load gnuplot_input_file.txt; exec bash'");
    string command = "gnuplot -p " + gnuplot_namefile;
    system(command.c_str());
    // ajouter les kwargs pour de plus jolis plots, à tester aussi !!
    gnuplot_input_file.close();

    ofstream gnuplot_input_file2;
    string gnuplot_namefile2 = "gnuplot_" + nom_schema + "erreur_max.bat";
    gnuplot_input_file2.open(gnuplot_namefile2);
    gnuplot_input_file2 << "plot [" << hmin << ":" << hmax << "] '" << nom_erreur_max << "' with lines" << endl;
    // system("gnome-terminal -x sh -c 'gnuplot; load gnuplot_input_file.txt; exec bash'");
    string command2 = "gnuplot -p " + gnuplot_namefile2;
    system(command2.c_str());
    // ajouter les kwargs pour de plus jolis plots, à tester aussi !!
    gnuplot_input_file2.close();
}

// void CasTest::exact_export(double n){
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

// PbCauchy CasTest::set_pbCauchy(){
//	PbCauchy EDO_test = PbCauchy( fct_sol_exacte(a), fct_second_membre);
//	return EDO_test;
//}
//
// Solver CasTest::set_schema(double n){
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
// void CasTest::maj_schema(double n){
//	N = n;
//	calcul();
//	for(double i =0; i<n; i++){
////		cout<<x_val[i]<<endl;
//	}
//}
//
// void CasTest::tps(double n){
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
// void CasTest::exacte(double n){
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
// void CasTest::approx(double n){
////	sol_approch.resize(n);
//	maj_schema(n);
////	sol_approch = schema.x_val;
//	for(double i = 0; i<n; i++){
////		cout<<x_val[i]<<endl;
//		sol_approch.push_back(x_val[i]);
//	}
//}
//
// void CasTest::erreur(double n){
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
// void CasTest::calcul_error(){
//    for(double n= N_min; n<= N_max; n+=pas){
//        maj_schema(n);
//        erreur(n);
//		h.push_back(dt);
//    }
//}
//

//
// void CasTest::exact_export(double n){
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
// void CasTest::error_export(){
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
