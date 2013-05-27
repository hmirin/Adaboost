#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Adaboost.h"
using namespace std;

int main(){
  ifstream input("testtarget");
  ifstream input2("testdata");
  string str;
  vector<int> target;
  vector<vector<int> > data;

  stringstream ss;
  while(input && getline(input,str)){
    ss.clear();
    ss << str;
    while(!ss.eof()){
      int test;
      ss >>  test;
      target.push_back(test);
    }
  }
  while(input2 && getline(input2,str)){
    ss.clear();
    ss << str;
    vector<int> tmp;
    while(!ss.eof()){
      int test;
      ss >> test;
      tmp.push_back(test);
    }
    data.push_back(tmp);
  }

  Adaboost ada(target,data);
  int n=3;
  pair< vector<int>,vector<double> > result = ada.calc(n);
  for(int i=0; i<n; i++) { cout << result.first[i] << " ";}
  cout << endl;
  for(int i=0; i<n; i++) { cout << result.second[i] << " ";}
  cout << endl;
  return 0;
}


