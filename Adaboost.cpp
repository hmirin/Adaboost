#include <vector>
#include <cfloat>
#include "Adaboost.h"
#include <iostream>
using namespace std;
  
double Adaboost::updateweight(int classifier){//updateweight using classifier
  // normalize err
  double mistake = 0;
  double sum = 0;
  double err;
  double alpha;
#pragma omp parallel
  {
#pragma omp for reduction(+:sum, mistake)
    for (int i =0; i < (int)datavec.size(); i++){ 
      //calculate error rate
      sum += weight.at(i);
      if(datavec[i][classifier] != targetvec[i]){
	mistake += weight.at(i);
      }
    }
#pragma omp single //err,alpha :treated as shared
    {
      //calculte log errrate
      err = mistake/sum; //alpha = log((1-err)/err); 
      alpha = (1-err)/err;
      alphas.push_back(alpha);
    }
    //update weight
#pragma omp for
    for(int i = 0; i<NofData; i++){ //for all datasets
      if(datavec[i][classifier] != targetvec[i]){ 
	weight[i] = weight[i]*alpha; // penalty
      }
    }
  }
  return err;
}
  

int Adaboost::weaklearn(){
  int minpos=-1; double minerr = DBL_MAX;
  for(int i=0; i < NofClassifier; i++){ //find minimum error classifier
    double currentclassifiererr = 0;
#pragma omp parallel for reduction(+:currentclassifiererr)
    for(int j=0; j < NofData; j++){ //for all datsets
      if(datavec[j][i] != targetvec[j]){
	currentclassifiererr += weight[j];
      }
    }
    if(minerr > currentclassifiererr){
      minpos = i;
      minerr = currentclassifiererr;
    }
  }
  classifiers.push_back(minpos);
  return minpos; //return the index of the classifier which gives minimum errorx
}
  

Adaboost::Adaboost(const vector<int> target,const vector<vector<int> > data){
  weight = vector<double>(data.size(),1./data.size()); //data.size() cant be zero
  NofClassifier = data[0].size();
  NofData = data.size();
  targetvec = target;
  datavec = data;
}

pair< vector<int>, vector<double> > Adaboost::calc(int n){
  for(int i=0; i< n; i++){
    updateweight(weaklearn());
  }
  return make_pair(classifiers, alphas);
}
