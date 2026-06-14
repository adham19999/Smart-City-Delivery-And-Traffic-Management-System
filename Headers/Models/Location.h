#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <string>

using namespace std;

class Location
{
public:
    int id;
    string name;
    double x;
    double y;
    string type;

    Location();
    Location(int id, string name, double x, double y, string type);
    
    void display() const;
    double distanceTo(const Location& other) const;
};

#endif
