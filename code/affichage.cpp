/*

Fonctions qui gèrent l'affichage dans le terminal

*/

#include "affichage.hpp"
#include "Integrale.hpp"
#include "Schema.hpp"

#include <cmath>
#include <functional>
#include <ostream>

void demarrage()
{
    cout << endl
         << "Bienvenue, installez vous confortablement ..." << endl
         << endl
         << "Nous allons vous présenter notre projet de C++ qui porte sur "
         << "la réalisation d'un moteur de résolution d'EDO et "
         << "l'illustration de la théorie du contrôle linéaire." << endl;
}

void wait()
{
    cout << endl << "Veuillez appuyer sur une touche pour continuer" << endl << endl;
    cin.ignore();
}

void test_schema(string nom_schema, string snd_membre, double x0, double a, string sol_exacte)
{
    cout << "Testons le schéma " + nom_schema + " sur le problème de Cauchy :" << endl
         << "     x'(t) = " + snd_membre << endl
         << "     x(" << a << ") = " << x0 << endl
         << endl
         << "La solution exacte est x(t) = " << sol_exacte << endl;
}

void parametres(double a, double b, double x0, unsigned long long N, double cible, unsigned long long N_min,
                unsigned long long N_max, unsigned long long pas_erreurs)
{
    cout << "Les paramètres de notre discrétisation sont : " << endl
         << endl
         << "Intervalle : [" << a << ", " << b << "], nombre d'intervalles N = " << N << endl
         << "Pour l'erreur, on calcule l'erreur L2 et max pour N allant de " << endl
         << "N_min = " << N_min << ", N_max = " << N_max << " avec un pas de " << pas_erreurs << endl
         << endl
         << "Voici la sortie gnuplot :" << endl
         << endl;
}

void ordre_schema_max(string nom_schema, int ordre)
{
    cout << "Le schéma " << nom_schema << " est bien d'ordre " << ordre << " pour l'erreur max," << endl
         << "comme le prévoit l'anayse numérique de ce schéma." << endl;
}

void test_controle(double a, double b, double x0, double cible, string nom_A, string nom_B)
{
    cout << "Passons au contrôle :" << endl
         << "On considère le contrôle suivant :" << endl
         << "     x'(t) = " << nom_A << " x + " << nom_B << "u" << endl
         << "     x(" << a << ") = " << x0 << endl
         << "     x(" << b << ") = " << cible << endl;
}

void plot_controle(EulerExplicite schema, double cible)
{
    cout << "Voici la sortie gnuplot :" << endl << endl;
    schema.plot();
    double erreur_controle = abs(schema.x_val[schema.x_val.size() - 1] - cible) / cible * 100;
    cout << "L'erreur entre le dernier point du schéma contrôlé et la cible est de " << erreur_controle << "%." << endl;
}

void test_integrale(double a, double b, function<double(double)> fct_integrande, unsigned long long N,
                    string nom_integrande, double valeur_exacte)
{
    Integrale calculPi(a, b, fct_integrande, N);
    double pi_milieu = calculPi.point_milieu();
    double pi_simpson = calculPi.simpson();
    cout << "Testons maintenant l'intégration :" << endl
         << "On sait que résoudre une EDO de type :"
         << "     x'(t) = F(t, x)" << endl
         << "     x(a) = x0" << endl
         << "Reviens à calculer une intégrale, les méthodes de discrétisation des EDO et d'intégration ont donc"
         << "des ordres similaires selon les approches." << endl
         << "On va intégrer la fonction suivante :" << endl
         << "F(t) = " << nom_integrande << endl
         << endl
         << "L'intervalle est I = [" << a << ", " << b << "] avec une discrétisation N = " << N << endl
         << endl
         << "L'erreur de calcul par la méthode du point milieu est de "
         << abs(valeur_exacte - pi_milieu) / valeur_exacte * 100 << "%." << endl
         << "L'erreur du calcul par la methode de Simpson est de "
         << abs(valeur_exacte - pi_simpson) / valeur_exacte * 100 << "%." << endl
         << endl;
    Integrale calculPiPi(a, b, fct_integrande, 100 * N);
    double pipi_milieu = calculPiPi.point_milieu();
    double pipi_simpson = calculPiPi.simpson();
    double pente_milieu = (log(abs(pipi_milieu - valeur_exacte)) - log(abs(pi_milieu - valeur_exacte))) / (-log(100));
    double pente_simpson =
        (log(abs(pipi_simpson - valeur_exacte)) - log(abs(pi_simpson - valeur_exacte))) / (-log(100));
    cout << "Une pente de l'erreur en échelle log est de :" << endl
         << pente_milieu << " pour la méthode du point milieu et de " << endl
         << pente_simpson << " pour la méthode de simpson" << endl
         << endl;
}