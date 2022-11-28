#include "Solver.hpp"
#include "PbCauchy.hpp"

#include <functional>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

vector<double> set_sol_exacte(Solver *schema, function<double(double)> f, unsigned long long n) {
    vector<double> sol;
    for (unsigned long long i = 0; i <= n; i++)
    {
        sol.push_back(f(schema->t_val[i]));
    }
    return sol;
}

Solver::Solver(double _a, double _b, unsigned long long _N, string _nom, PbCauchy _EDO)
    : a(_a), b(_b), N(_N), nom(_nom), EDO(_EDO)
{
    nom += ".txt";

    // on calcule le pas
    dt = (b - a) / static_cast<double>(N);

    // on maj les CI
    x_val.push_back(EDO.x0);
    ancien_point = EDO.x0;
    t = a;
    t_val.push_back(a);
}

void Solver::expor()
{
    ofstream schema_EDO;
    schema_EDO.open(nom);
    calcul();
    for (unsigned long long j = 0; j <= N; j++)
    {
        schema_EDO << t_val[j] << " " << x_val[j] << endl;
    }
    schema_EDO.close();

    ofstream gnuplot_input_file;
    string gnuplot_namefile = "gnuplot_" + nom;
    gnuplot_input_file.open(gnuplot_namefile);
    gnuplot_input_file << "plot [" << (int)a << ":" << (int)b << "] 'schema_EDO.txt' with lines" << endl;
    // system("gnome-terminal -x sh -c 'gnuplot; load gnuplot_input_file.txt; exec bash'");
    string command = "gnuplot -p gnuplot_" + nom;
    system(command.c_str());
    // ajouter les kwargs pour de plus jolis plots, à tester aussi !!
}

void EulerExplicite::calcul()
{
    for (unsigned long long i = 1; i <= N; i++)
    {
        nouveau_point = ancien_point + dt * (EDO.second_membre(t, ancien_point));
        x_val.push_back(nouveau_point);
        ancien_point = nouveau_point;
        t += dt;
        t_val.push_back(t);
    }
}

void RungeKutta::maj_k()
{
    k1 = dt * (EDO.second_membre(t, ancien_point));
    k2 = dt * (EDO.second_membre((t + dt / 2), (ancien_point + k1 / 2)));
    k3 = dt * (EDO.second_membre((t + dt / 2), (ancien_point + k2 / 2)));
    k4 = dt * (EDO.second_membre((t + dt), (ancien_point + k3)));
    k = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

void RungeKutta::calcul()
{
    for (unsigned long long i = 1; i <= N; i++)
    {
        maj_k();
        nouveau_point = ancien_point + k;
        x_val.push_back(nouveau_point);
        ancien_point = nouveau_point;
        t += dt;
        t_val.push_back(t);
    }
}
