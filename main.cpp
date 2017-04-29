// main.cpp
#include "myVector.h"
#include <iostream>
using namespace std;

int main(){

    myVector v;
    v.push_back("a");
    v.push_back("5");
    v.push_back("a");
    v.push_back("5");
    v.push_back("a");
    v.push_back("5");
    for (auto i = v.begin(); i != v.end(); i++)
        cout << *i << endl;
    return 0;
}