#include "Schema.hpp"

using namespace std;

Schema::Schema(PbCauchy _EDO, string _nom, double _a, double _b, unsigned long long _N)
    : EDO(_EDO), nom(_nom), a(_a), b(_b), N(_N)
{
    // on calcule le pas
    dt = (b - a) / static_cast<double>(N);
    x_val.reserve(N+1);
    t_val.reserve(N+1);
    // on maj les CI
    x_val.push_back(EDO.x0);
    ancien_point = EDO.x0;
    t = a;
    t_val.push_back(a);
}

void Schema::plot()
{
    ofstream schema_EDO;
    schema_EDO.open(nom + ".txt");
    solve();
    for (unsigned long long j = 0; j <= N; j++)
    {
        schema_EDO << t_val[j] << " " << x_val[j] << endl;
    }
    schema_EDO.close();

    ofstream gnuplot_input_file;
    string gnuplot_namefile = "gnuplot_" + nom + ".bat";
    gnuplot_input_file.open(gnuplot_namefile);
    gnuplot_input_file << "plot [" << a << ":" << b << "] '" << nom << ".txt' with lines" << endl;
    // system("gnome-terminal -x sh -c 'gnuplot; load gnuplot_input_file.txt; exec bash'");
    string command = "gnuplot -p " + gnuplot_namefile;
    system(command.c_str());
    // ajouter les kwargs pour de plus jolis plots, à tester aussi !!
    gnuplot_input_file.close();
}

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
	t_val[N] = b;
}

void RungeKutta::maj_k()
{
    k1 = dt * (EDO.fct_second_membre(t, ancien_point));
    k2 = dt * (EDO.fct_second_membre((t + dt / 2), (ancien_point + k1 / 2)));
    k3 = dt * (EDO.fct_second_membre((t + dt / 2), (ancien_point + k2 / 2)));
    k4 = dt * (EDO.fct_second_membre((t + dt), (ancien_point + k3)));
    k = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

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
