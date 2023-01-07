/*

Déclaration des fonctions d'affichage

*/

#ifndef affichage_hpp
#define affichage_hpp

#include "Schema.hpp"

#include <iostream>
#include <string>

using namespace std;

void demarrage();
void wait();
void test_schema(string schema, string snd_membre, double x0, double a, string sol_exacte);
void plot_schema(Schema &schema);
void parametres(double a, double b, double x0, unsigned long long N, double cible, unsigned long long N_min,
                unsigned long long N_max, unsigned long long pas_erreurs);
void ordre_schema_max(string schema, int ordre);
void test_controle(double a, double b, double x0, double cible, string nom_A, string nom_B);
void erreur_controle(double erreur, double cible);
void test_integrale(double a, double b, function<double(double)> fct_integrande, unsigned long long N,
                    string nom_integrande, double valeur_exacte);

void get_intervalle();
double get_a();
double get_b(double a);
unsigned long long get_N(double a, double b);
double get_x0(double a, double b);
double get_cible();
void main_poleshifting();

#endif