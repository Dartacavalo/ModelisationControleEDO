//
//  PbCauchy.cpp
//  classEDO
//
//  Created by José Maria Marques on 14/11/2022.
//

#include "PbCauchy.hpp"
#include <iostream>


using namespace std;

PbCauchy::PbCauchy(double _x0, function<double(double,double)> _second_membre) : x0(_x0), second_membre(_second_membre){};


