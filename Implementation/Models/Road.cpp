#include "../../Headers/Models/Road.h"

Road::Road() : from(0), to(0), weight(0.0) {}

Road::Road(int from, int to, double weight)
    : from(from), to(to), weight(weight) {}

void Road::display() const
{
    cout << "Road: " << from << " -> " << to << " (weight=" << weight << ")\n";
}
