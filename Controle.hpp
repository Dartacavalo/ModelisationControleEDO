//
//  Controle.hpp
//  ProjetC++
//
//  Created by José Maria Marques on 02/12/2022.
//

#ifndef Controle_hpp
#define Controle_hpp


#include <stdio.h>
#include <functional>
#include <math.h>
#include <string>

#include "PbCauchy.hpp"
#include "Integrale.hpp"

using namespace std;
using namespace placeholders;

class Controle{
public:
	double const x0; // La condition intiale
	double const cible; // Le point auquel on souhaite arriver au temps final
	double const t0, t1; // L'intervalle d'etude
	double C; // Les constangtes de la fonction de controle
	string const methode_integration; // La methode d'inetegration choisie
	function<double(double)> A, B; // Les coefficients non autonomes de notre probleme
	const unsigned long long N; // Le pas d'integration
	
	Controle(double const _t0, double const _t1, double const _x0, double const _cible, const unsigned long long _N, string _methode_integration, function<double(double)> _A, function<double(double)> _B):  t0(_t0), t1(_t1), x0(_x0), cible(_cible), N(_N), methode_integration(_methode_integration), A(_A), B(_B) {}
	
	
	double R(double t, double s);
	double gramian_integrand(double s);
	double Gramian();
	double u(double s);
	double controle_second_membre(double t, double x);
	PbCauchy controle_PbCauchy();
	double integrande_sol_exacte(double s);
	double controle_sol_exacte();
	
	double feedback();
	double pole_shifting(double t, double x);
	PbCauchy feedback_PbCauchy();
	
};




#endif /* Controle_hpp */

//On commence avec un pb de cauchy, puis on change en un schema, pour avoir acces au a et b
