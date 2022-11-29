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
	double a, b;
	function<double(double)> fct_integrande;
	unsigned long long N;
	
	double h;
	
	Integrale(double _a, double _b, function<double(double)> _fct_integrande, unsigned long long _N);
	
	double point_milieu();
	double simpson();
};




#endif /* Integrale_hpp */
