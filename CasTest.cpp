#include <algorithm>
#include <math.h>

#include "CasTest.hpp"

using namespace std; 

Schema *CasTest::def_schema(unsigned long long n)
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

void CasTest::calcul_erreur(unsigned long long n)
{
    double err = 0;
    double err_max = 0;
    double ft = 0;
    double fx = 0;
    Schema *schema = def_schema(n);
    h.push_back(schema->dt);
    // cout << "t size = " << schema->t_val.size() << endl;
    for (unsigned long long i = 0; i < schema->t_val.size(); i++)
    {
        ft = fct_sol_exacte(schema->t_val[i], schema->EDO.x0, a);
        fx = schema->x_val[i];
        err += (ft - fx) * (ft - fx);
        err_max = max(err_max, abs(ft - fx));
        // cout << "t = " << schema->t_val[i] << endl;
        // cout << "ft = " << ft << " fx = " << fx << endl;
    }
    erreur_L2.push_back(sqrt(err));
    erreur_max.push_back(err_max);
    delete schema;
}

void CasTest::calcul_erreur_totale()
{
    for (unsigned long long n = N_min_erreurs; n <= N_max_erreurs; n += pas_erreurs)
    {
        calcul_erreur(n);
    }
    cout << "pente L2 = " << calcul_pente_L2() << endl;
    cout << "pente max = " << calcul_pente_max() << endl;
    // c'est un peut dodgy de faire ça comme ça, faut vérifier que h et erreur_L2 ont la même taille
    // c'est le cas mais bon, à revoir peut être
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
    string gnuplot_namefile = "gnuplot_" + nom_schema + "_erreur_L2.bat";
    gnuplot_input_file.open(gnuplot_namefile);
    gnuplot_input_file << "set logscale xy" << endl;
    gnuplot_input_file << "plot [" << hmin << ":" << hmax << "] '" << nom_erreur_L2 << "' with lines";
    gnuplot_input_file << ", x*x with lines, x*x*x with lines, x*x*x*x with lines" << endl;
    // system("gnome-terminal -x sh -c 'gnuplot; load gnuplot_input_file.txt; exec bash'");
    string command = "gnuplot -p " + gnuplot_namefile;
    system(command.c_str());
    // ajouter les kwargs pour de plus jolis plots, à tester aussi !!
    gnuplot_input_file.close();

    ofstream gnuplot_input_file2;
    string gnuplot_namefile2 = "gnuplot_" + nom_schema + "_erreur_max.bat";
    gnuplot_input_file2.open(gnuplot_namefile2);
    gnuplot_input_file2 << "set logscale xy" << endl;
    gnuplot_input_file2 << "plot [" << hmin << ":" << hmax << "] '" << nom_erreur_max << "' with lines";
    gnuplot_input_file2 << ", x*x with lines, x*x*x with lines, x*x*x*x with lines" << endl;
    // system("gnome-terminal -x sh -c 'gnuplot; load gnuplot_input_file.txt; exec bash'");
    string command2 = "gnuplot -p " + gnuplot_namefile2;
    system(command2.c_str());
    // ajouter les kwargs pour de plus jolis plots, à tester aussi !!
    gnuplot_input_file2.close();
}

void CasTest::exact_export(double n)
{
    string nom_solution_exacte = nom_schema + "_solution_exacte.txt";
    ofstream solution_exacte;
    solution_exacte.open(nom_solution_exacte);
    Schema *schema = def_schema(n);
    for (double i = 0; i < n; i++)
    {
        solution_exacte << schema->t_val[i] << " " << fct_sol_exacte(schema->t_val[i], schema->EDO.x0, a) << endl;
        //		cout<<temps[i]<<" "<< fct_sol_exacte(temps[i])<<endl;
    }
    solution_exacte.close();
    delete schema;
}
