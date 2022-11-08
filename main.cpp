//
//  main.cpp
//  POO_EDO
//
//  Created by José Maria Marques on 07/11/2022.
//

#include <iostream>
#include <cmath>

class CI{
    public:
    
    //Le domaine
    double const debut;
    double const fin;
    //Les conditions initiales
    double const y0;
};

class Pb_Cauchy{
    public:
    //conditions initiales
    CI cond_init;
    //Fonction
    double F(double x, double f);
};

class Tests{
};

class Refroidissement: public Tests{
    public:
    double k;
    double T0;
    Refroidissement(double _k, double _T0, double t): k(_k), T0(_T0){};
    
    double f(double t){return -k * (t - T0);};
    
};


class Schemas{
    public:
};



//


int main(){
    return 0;
}

