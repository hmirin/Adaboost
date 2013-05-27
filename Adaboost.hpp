//#include "Adaboost.h"
#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include <vector>

using namespace std;

class Adaboost
{
public:
    Adaboost(const vector<int> target, const vector<vector<int> > data);
    pair< vector<int>,vector<double> > calc(int n); 
      //return all classifiers' indexes and weights
};


#endif	// _ADABOOST_H_
