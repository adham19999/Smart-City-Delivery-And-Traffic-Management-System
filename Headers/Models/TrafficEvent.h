#ifndef TRAFFICEVENT_H
#define TRAFFICEVENT_H

#include <iostream>
#include <string>

using namespace std;

class TrafficEvent
{
public:
    int id;
    int roadId;
    int severity;
    double density;
    string timestamp;

    TrafficEvent();
    TrafficEvent(int id, int roadId, int severity, double density, string timestamp);
    
    void display() const;
    bool isHighSeverity() const;
};

#endif
