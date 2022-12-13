//
//  Controle.hpp
//  ProjetC++
//
//  Created by José Maria Marques on 02/12/2022.
//

#ifndef Controle_hpp
#define Controle_hpp

#include <stdio.h>
#include <string>

#include "PbCauchy.hpp"
#include "Integrale.hpp"

using namespace std;
using namespace placeholders;

class Controle{
public:
	double const x0; 				  // La condition intiale
	double const cible; 			  // Le point auquel on souhaite arriver au temps final
	double const t0, t1; 			  // L'intervalle d'etude
	string const methode_integration; // La methode d'inetegration choisie
	function<double(double)> A, B;    // Les coefficients non autonomes de notre probleme
	const unsigned long long N;       // Le pas d'integration
	
	// Le constructeur de la classe controle non Autonome en 1D
	Controle(double const _t0, double const _t1, double const _x0, double const _cible, const unsigned long long _N, string _methode_integration, function<double(double)> _A, function<double(double)> _B):  t0(_t0), t1(_t1), x0(_x0), cible(_cible), N(_N), methode_integration(_methode_integration), A(_A), B(_B) {}
	
	// Methodes responsables du calcul du controle (voir le README pour les details mathematiques)
	double R(double t, double s) const; 				     // La resolvante
	double gramian_integrand(double s) const;			  	 // La fonction a integrer
	double Gramian() const;								     // L'integrale d'une 'matrice' gramienne
	double u(double s) const;							     // Le terme de controle
	double controle_second_membre(double t, double x) const; // La nouvelle fonction second membre controlee
	PbCauchy controle_PbCauchy() const;						 // Le nouveau probleme de Cauchy avec le controle du second membre
	
	// Methodes responsables du calcul de la solution exacte du probleme de Cauchy controle
	double integrande_sol_exacte(double s) const;  // Integration de la solution exacte
	double controle_sol_exacte() const;			   // Solution exacte
	
    // Methodes responsables du calcul de feedback par le theoreme de poleshifting
	double feedback() const;
	double pole_shifting(double t, double x) const;	 // La nouvelle fonction second membre avec le feedback par pole shifting
	PbCauchy feedback_PbCauchy() const;				 // Le nouveau probleme de Cauchy pour le theoreme de pole shifting
	
};




#endif /* Controle_hpp */

//On commence avec un pb de cauchy, puis on change en un schema, pour avoir acces au a et b
