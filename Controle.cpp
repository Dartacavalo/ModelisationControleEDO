//
//  Controle.cpp
//  ProjetC++
//
//  Created by José Maria Marques on 02/12/2022.
//

#include "Controle.hpp"

double Controle::R(double t, double s){
	Integrale int_A(s, t, A, N);
	if( methode_integration == "Simpson"){
		return exp(int_A.simpson());
	}
	else{
		return exp(int_A.point_milieu());
	}
}

double Controle::gramian_integrand(double s){
	return R(t1, s)*R(t1, s)*B(s)*B(s);
}

double Controle::Gramian(){
	function<double(double)> gramian_int = bind(&Controle::gramian_integrand, this, placeholders::_1);
	   Integrale gramian(t0, t1, gramian_int, N);
	   if( methode_integration == "Simpson"){
		   return gramian.simpson();
	   }
	   else{
		   return gramian.point_milieu();
	   }
   }

double Controle::u(double s){
	double y = 1./Gramian()*(cible- R(t1,t0)*x0);
	   return B(s)*R(t1,s)*y;
   }

double Controle::controle_second_membre(double t, double x){
	return A(t)*x + B(t)*u(t);
   }

PbCauchy Controle::controle_PbCauchy(){
	function<double(double, double)> controle_scd_mb = bind(&Controle::controle_second_membre, this, placeholders::_1, placeholders::_2);
	return PbCauchy(x0, controle_scd_mb);
};

double Controle::integrande_sol_exacte(double s){
	return R(t1, s)*B(s)*u(s);
}

double Controle::controle_sol_exacte(){
	function<double(double)> integ_sol_exacte = bind(&Controle::integrande_sol_exacte, this, placeholders::_1);
	Integrale terme(t0, t1, integ_sol_exacte, N);
	return R(t1, t0)*x0 + terme.simpson();
}

double Controle::feedback(){
	double f = 0.;
	double dt = (t1-t0)/N;
	for(double t=t0; t<=t1; t+=dt){
		f = -max(A(dt), A(t-dt))/min(B(t), B(t-dt));
	}
	return f;
}

double Controle::pole_shifting(double t, double x){
	double f = feedback();
	double d = -cible*(A(t)+B(t)*f);
	return (A(t)+B(t)*f)*x  + d;
}

PbCauchy Controle::feedback_PbCauchy(){
	function<double(double, double)> f = bind(&Controle::pole_shifting, this, placeholders::_1, placeholders::_2);
	return PbCauchy(x0, f);
};
