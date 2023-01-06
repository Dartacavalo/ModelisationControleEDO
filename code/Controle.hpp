/*

Déclaration d'une classe de contrôle et de ses fonctions membres

*/

#ifndef Controle_hpp
#define Controle_hpp

#include "Integrale.hpp"
#include "PbCauchy.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace placeholders;

class Controle
{
  private:
    double const t0, t1; // Intervalle d'étude
    double const x0;     // Condition intiale
    double const cible;  // Point auquel on souhaite arriver au temps final

    const unsigned long long N;    // Pas d'integration
    string methode_integration;    // Méthode d'intégration choisie
    function<double(double)> A, B; // Coefficients de notre problème non autonome

  public:
    // Constructeur de la classe Controle non Autonome en 1D, avec l'exception
    Controle(double const _t0, double const _t1, double const _x0, double const _cible, const unsigned long long _N,
             string _methode_integration, function<double(double)> _A, function<double(double)> _B);

    // Méthodes responsables du calcul du contrôle (voir le README pour les détails mathématiques)
    double R(double t, double s) const;                      // Résolvante
    double gramian_integrand(double s) const;                // Fonction à intégrer
    double Gramian() const;                                  // Intégrale d'une 'matrice' gramienne
    double u(double s) const;                                // Terme de controle
    double controle_second_membre(double t, double x) const; // Nouvelle fonction second membre controlée
    PbCauchy controle_PbCauchy() const; // Nouveau problème de Cauchy avec le controle du second membre

    // Méthodes responsables du calcul de la solution exacte du problème de Cauchy controlé
    double integrande_sol_exacte(double s) const; // Intégration de la solution exacte
    double controle_sol_exacte() const;           // Solution exacte

    // Méthodes responsables du calcul de feedback par le théorème de poleshifting
    double feedback() const;
    double pole_shifting(double t,
                         double x) const; // Nouvelle fonction second membre avec le feedback par pole shifting
    PbCauchy feedback_PbCauchy() const;   // Nouveau problème de Cauchy pour le theoreme de pole shifting
};

#endif /* Controle_hpp */
