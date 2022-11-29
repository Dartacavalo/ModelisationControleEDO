//
//  Integrale.cpp
//  ProjetC++
//
//  Created by José Maria Marques on 29/11/2022.
//

#include "Integrale.hpp"

Integrale::Integrale(double _a, double _b, function<double(double)> _fct_integrande, unsigned long long _N) : a(_a), b(_b), fct_integrande(_fct_integrande), N(_N){
	h = (b-a)/N;
}

double Integrale::point_milieu(){
	double res = 0;
	for(unsigned long long i = 0; i<N; i++){
		res +=fct_integrande(a+(i+0.5)*h);
	}
	return res*h;
}

double Integrale::simpson(){
	double res = fct_integrande(a)+fct_integrande(b)+4*fct_integrande(a+h/2);
	for(unsigned long long i=1; i<N; i++){
		res+=2*fct_integrande(a + i*h)+4*fct_integrande(a+(i+0.5)*h);
	}
	return res*h/6;
}
