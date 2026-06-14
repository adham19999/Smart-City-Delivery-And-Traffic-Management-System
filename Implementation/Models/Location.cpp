#include "../../Headers/Models/Location.h"
#include <cmath>

Location::Location() : id(0), name(""), x(0.0), y(0.0), type("") {}

Location::Location(int id, string name, double x, double y, string type)
    : id(id), name(name), x(x), y(y), type(type) {}

void Location::display() const
{
    cout << "Location " << id << ": " << name << " (" << x << ", " << y << ") [" << type << "]\n";
}

double Location::distanceTo(const Location& other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}
