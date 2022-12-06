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
	
	Controle(double const _t0, double const _t1, double const _x0, double const _cible, const unsigned long long _N, string _methode_integration):  t0(_t0), t1(_t1), x0(_x0), cible(_cible), N(_N), methode_integration(_methode_integration){
		C = 2*exp(t1)*(cible-x0*exp(t1-t0))/(exp(2*(t1-t0))-1.);
//		y =
	}
	
	double utest(double t, double x){ return C*exp(-t);}
	
	double R(double t, double s){
		Integrale int_A(s, t, A, N);
		if( methode_integration == "Simpson"){
			return exp(int_A.simpson());
		}
		else{
			return exp(int_A.point_milieu());
		}
	}
	
	double gramian_integrand(double s){
		return R(t1, s)*R(t1, s)*B(s)*B(s);
	}
	
	double Gramian(){
		function<double(double)> gramian_int = bind(&Controle::gramian_integrand, this, placeholders::_1);
		Integrale gramian(t0, t1, gramian_int, N);
		if( methode_integration == "Simpson"){
			return gramian.simpson();
		}
		else{
			return gramian.point_milieu();
		}
	}
	
	double u(double s){
		double y = 1/Gramian()*(cible- R(t1,t0)*x0);
		return B(s)*R(t1,t0)*y;
	}

	double controle_second_membre(double t, double x){
		return A(t)*x + B(t)*u(t);
	}
	
	PbCauchy controle_PbCauchy(){
		function<double(double, double)> contole_scd_mb = bind(&Controle::controle_second_membre, this, placeholders::_1, placeholders::_2);
		return PbCauchy(x0, contole_scd_mb);
	};
	
	double integrande_sol_exacte(double s){
		return R(t1, s)*B(s)*u(s);
	}
	
	double controle_sol_exacte(){
		function<double(double)> integ_sol_exacte = bind(&Controle::integrande_sol_exacte, this, placeholders::_1);
		Integrale terme(t0, t1, integ_sol_exacte, N);
		return R(t1, t0)*x0 + terme.simpson();
	}
		
};




#endif /* Controle_hpp */

//On commence avec un pb de cauchy, puis on change en un schema, pour avoir acces au a et b
