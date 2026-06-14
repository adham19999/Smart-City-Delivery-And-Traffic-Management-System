#include "../../Headers/Models/TrafficEvent.h"

TrafficEvent::TrafficEvent() : id(0), roadId(0), severity(0), density(0.0), timestamp("") {}

TrafficEvent::TrafficEvent(int id, int roadId, int severity, double density, string timestamp)
    : id(id), roadId(roadId), severity(severity), density(density), timestamp(timestamp) {}

void TrafficEvent::display() const
{
    cout << "Traffic Event " << id << ": Road=" << roadId << ", Severity=" << severity 
         << ", Density=" << density << ", Time=" << timestamp << "\n";
}

bool TrafficEvent::isHighSeverity() const
{
    return severity >= 7;
}
