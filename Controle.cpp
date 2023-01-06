/*

Définition des fonctions membres de la classe Controle

*/

#include "Controle.hpp"

#include <math.h>

Controle::Controle(double const _t0, double const _t1, double const _x0, double const _cible,
                   const unsigned long long _N, string _methode_integration, function<double(double)> _A,
                   function<double(double)> _B)
    : t0(_t0), t1(_t1), x0(_x0), cible(_cible), N(_N), methode_integration(_methode_integration), A(_A), B(_B)
{
    if (!(_methode_integration == "Simpson" || _methode_integration == "PtMilieu"))
    {
        try
        {
            throw(_methode_integration);
        }

        catch (string meth_integration)
        {
            cout << "La méthode d'intégration doit être soit la méthode \"Simpson\"; soit la méthode : \"PtMilieu\", "
                    "au lieu de la méthode choisie \""
                 << meth_integration << "\"." << endl;
            cout << "Par défaut, la méthode choisie est la méthode \"Simpson\"" << endl;
            methode_integration = "Simpson";
        }
    }
}

double Controle::R(double t, double s) const
{
    Integrale int_A(s, t, A, N);
    if (methode_integration == "Simpson")
    {
        return x0 * exp(int_A.simpson());
    }
    else
    {
        return x0 * exp(int_A.point_milieu());
    }
}

double Controle::gramian_integrand(double s) const
{
    return R(t1, s) * R(t1, s) * B(s) * B(s);
}

double Controle::Gramian() const
{
    function<double(double)> gramian_int = bind(&Controle::gramian_integrand, this, placeholders::_1);
    Integrale gramian(t0, t1, gramian_int, N);
    if (methode_integration == "Simpson")
    {
        return gramian.simpson();
    }
    else
    {
        return gramian.point_milieu();
    }
}

double Controle::u(double s) const
{
    double y = 1. / Gramian() * (cible - R(t1, t0) * x0);
    return B(s) * R(t1, s) * y;
}

double Controle::controle_second_membre(double t, double x) const
{
    return A(t) * x + B(t) * u(t);
}

PbCauchy Controle::controle_PbCauchy() const
{
    function<double(double, double)> controle_scd_mb =
        bind(&Controle::controle_second_membre, this, placeholders::_1, placeholders::_2);
    return PbCauchy(x0, controle_scd_mb);
}

double Controle::integrande_sol_exacte(double s) const
{
    return R(t1, s) * B(s) * u(s);
}

double Controle::controle_sol_exacte() const
{
    function<double(double)> integ_sol_exacte = bind(&Controle::integrande_sol_exacte, this, placeholders::_1);
    Integrale terme(t0, t1, integ_sol_exacte, N);
    return R(t1, t0) * x0 + terme.simpson();
}

double Controle::feedback() const
{
    double f = 0.;
    double dt = (t1 - t0) / N;
    for (double t = t0; t <= t1; t += dt)
    {
        f = -max(A(dt), A(t - dt)) / min(B(t), B(t - dt));
    }
    return f;
}

double Controle::pole_shifting(double t, double x) const
{
    double f = feedback();
    double d = -cible * (A(t) + B(t) * f);
    return (A(t) + B(t) * f) * x + d;
}

PbCauchy Controle::feedback_PbCauchy() const
{
    function<double(double, double)> f = bind(&Controle::pole_shifting, this, placeholders::_1, placeholders::_2);
    return PbCauchy(x0, f);
};
