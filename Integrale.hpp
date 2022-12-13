//
//  Integrale.hpp
//  ProjetC++
//
//  Created by José Maria Marques on 29/11/2022.
//

#ifndef Integrale_hpp
#define Integrale_hpp

#include <stdio.h>
#include <functional>

using namespace std;

class Integrale{
	public :
	double a, b;								// Les bornes de l'integrale
	function<double(double)> fct_integrande;	// La fonction a integrer
	unsigned long long N;						// Le nombre de divisions de l'intervalle [a,b]
	
	double h; 									// Le pas d'integration
	
	// Le constructeur de la classe integrale
	Integrale(double _a, double _b, function<double(double)> _fct_integrande, unsigned long long _N);
	
	double point_milieu();	// Integrale par la methode du point milieu
	double simpson();		// Integrale par la methode de Simpson
};


#endif /* Integrale_hpp */
