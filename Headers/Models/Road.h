#ifndef ROAD_H
#define ROAD_H

#include <iostream>

using namespace std;

class Road
{
public:
    int from;
    int to;
    double weight;

    Road();
    Road(int from, int to, double weight);
    
    void display() const;
};

#endif
