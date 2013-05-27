//#include "Adaboost.hpp"
#ifndef _ADABOOST_H_
#define _ADABOOST_H_

#include <vector>

using namespace std;


class Adaboost
{
private:
    vector<double> weight;
    vector<int> targetvec;
    vector<vector<int> > datavec;
    vector<double> alphas;
    vector<int> classifiers;
    int NofClassifier;
    int NofData;
    double updateweight(int classifier);
    int weaklearn();
public:
    Adaboost(const vector<int> target, const vector<vector<int> > data);
    pair< vector<int>,vector<double> > calc(int n); 
      //return all classifiers' indexes and weights
};


#endif //_ADABOOST_H_
