#include "routplanning.h"
#ifndef _mylagrange_H
#define _mylagrange_H

rout lagrange(long double indata[][2],int time,rout *routpoly);
void calculate(long double indata[][2],int count,int havechoice[100],long double anser[100][100],int choicenum);

#endif


