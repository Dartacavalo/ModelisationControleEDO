/*

Construction et définition des méthodes déclarées dans Schema.hpp

*/

#include "Schema.hpp"
#include "PbCauchy.hpp"

#include <fstream>

using namespace std;

// Constructeur de Solver
Schema::Schema(PbCauchy _EDO, string _nom, double _a, double _b, unsigned long long _N)
    : EDO(_EDO), nom(_nom), a(_a), b(_b), N(_N)
{
    // Calcul du pas
    dt = (b - a) / static_cast<double>(N);
    x_val.reserve(N + 1);
    t_val.reserve(N + 1);

    // Mise à jour des conditions initiales
    x_val.push_back(EDO.x0);
    ancien_point = EDO.x0;
    t = a;
    t_val.push_back(a);
}

// Définition de plot
void Schema::plot()
{
    ofstream schema_EDO;
    schema_EDO.open("gnuplot/" + nom + ".txt");
    solve();
    for (unsigned long long j = 0; j <= N; j++)
    {
        schema_EDO << t_val[j] << " " << x_val[j] << endl;
    }
    schema_EDO.close();

    ofstream gnuplot_input_file;
    string gnuplot_namefile = "gnuplot/gnuplot_" + nom + ".bat";
    gnuplot_input_file.open(gnuplot_namefile);
    gnuplot_input_file << "plot [" << a << ":" << b << "] 'gnuplot/" << nom << ".txt' with lines" << endl;
    string command = "gnuplot -p " + gnuplot_namefile;
    system(command.c_str());
    // ajouter les kwargs pour de plus jolis plots, à tester aussi !!
    gnuplot_input_file.close();
}

// Définition de la méthode d'Euler Explicite
void EulerExplicite::solve()
{
    for (unsigned long long i = 1; i <= N; i++)
    {
        nouveau_point = ancien_point + dt * (EDO.fct_second_membre(t, ancien_point));
        x_val.push_back(nouveau_point);
        ancien_point = nouveau_point;
        t += dt;
        t_val.push_back(t);
    }
}

// Mise à jour des valeurs de k à l'aide d'un tableau de Butcher
void RungeKutta::maj_k()
{
    k1 = dt * (EDO.fct_second_membre(t, ancien_point));
    k2 = dt * (EDO.fct_second_membre((t + dt / 2), (ancien_point + k1 / 2)));
    k3 = dt * (EDO.fct_second_membre((t + dt / 2), (ancien_point + k2 / 2)));
    k4 = dt * (EDO.fct_second_membre((t + dt), (ancien_point + k3)));
    k = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

// Définition de la méthode de Runge-Kutta d'ordre 4
void RungeKutta::solve()
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
