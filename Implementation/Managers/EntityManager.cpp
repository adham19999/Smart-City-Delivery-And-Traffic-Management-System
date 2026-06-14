#include "../../Headers/Managers/EntityManager.h"

EntityManager::EntityManager()
    : nextLocationId(1), nextVehicleId(1), nextCustomerId(1), nextDeliveryId(1) {}

// ========== ID GENERATORS ==========

int EntityManager::generateLocationId()  { return nextLocationId++; }
int EntityManager::generateVehicleId()   { return nextVehicleId++; }
int EntityManager::generateCustomerId()  { return nextCustomerId++; }
int EntityManager::generateDeliveryId()  { return nextDeliveryId++; }

// ========== LOCATION ==========

void EntityManager::addLocation(const Location& loc)
{
    locationDB.insert(loc.id, loc);
    cout << "EntityManager: Location " << loc.id << " (" << loc.name << ") registered.\n";
}

Location* EntityManager::getLocation(int id)
{
    return locationDB.search(id);
}

bool EntityManager::removeLocation(int id)
{
    if (locationDB.remove(id))
    {
        cout << "EntityManager: Location " << id << " removed.\n";
        return true;
    }
    cout << "EntityManager: Location " << id << " not found.\n";
    return false;
}

vector<Location> EntityManager::getAllLocations() const
{
    return locationDB.getAllValues();
}

// ========== VEHICLE ==========

void EntityManager::addVehicle(const Vehicle& vehicle)
{
    vehicleDB.insert(vehicle.id, vehicle);
    cout << "EntityManager: Vehicle " << vehicle.id << " registered.\n";
}

Vehicle* EntityManager::getVehicle(int id)
{
    return vehicleDB.search(id);
}

bool EntityManager::removeVehicle(int id)
{
    if (vehicleDB.remove(id))
    {
        cout << "EntityManager: Vehicle " << id << " removed.\n";
        return true;
    }
    cout << "EntityManager: Vehicle " << id << " not found.\n";
    return false;
}

vector<Vehicle> EntityManager::getAllVehicles() const
{
    return vehicleDB.getAllValues();
}

vector<Vehicle> EntityManager::getAvailableVehicles() const
{
    vector<Vehicle> all = vehicleDB.getAllValues();
    vector<Vehicle> available;
    for (const auto& v : all)
        if (v.available)
            available.push_back(v);
    return available;
}

// ========== CUSTOMER ==========

void EntityManager::addCustomer(const Customer& customer)
{
    customerDB.insert(customer.id, customer);
    cout << "EntityManager: Customer " << customer.id << " (" << customer.name << ") registered.\n";
}

Customer* EntityManager::getCustomer(int id)
{
    return customerDB.search(id);
}

bool EntityManager::removeCustomer(int id)
{
    if (customerDB.remove(id))
    {
        cout << "EntityManager: Customer " << id << " removed.\n";
        return true;
    }
    cout << "EntityManager: Customer " << id << " not found.\n";
    return false;
}

vector<Customer> EntityManager::getAllCustomers() const
{
    return customerDB.getAllValues();
}

// ========== DELIVERY ==========

void EntityManager::addDelivery(const Delivery& delivery)
{
    deliveryDB.insert(delivery.id, delivery);
    cout << "EntityManager: Delivery " << delivery.id << " registered.\n";
}

Delivery* EntityManager::getDelivery(int id)
{
    return deliveryDB.search(id);
}

bool EntityManager::removeDelivery(int id)
{
    if (deliveryDB.remove(id))
    {
        cout << "EntityManager: Delivery " << id << " removed.\n";
        return true;
    }
    cout << "EntityManager: Delivery " << id << " not found.\n";
    return false;
}

bool EntityManager::updateDeliveryStatus(int id, const string& status)
{
    Delivery* d = deliveryDB.search(id);
    if (d == nullptr)
    {
        cout << "EntityManager: Delivery " << id << " not found.\n";
        return false;
    }
    d->status = status;
    cout << "EntityManager: Delivery " << id << " status -> " << status << "\n";
    return true;
}

vector<Delivery> EntityManager::getAllDeliveries() const
{
    return deliveryDB.getAllValues();
}

vector<Delivery> EntityManager::getPendingDeliveries() const
{
    vector<Delivery> all = deliveryDB.getAllValues();
    vector<Delivery> pending;
    for (const auto& d : all)
        if (d.status == "Pending")
            pending.push_back(d);
    return pending;
}

// ========== DISPLAY ==========

void EntityManager::displayStats() const
{
    cout << "\n=== EntityManager Stats ===\n";
    cout << "  Locations : " << locationDB.size()  << "\n";
    cout << "  Vehicles  : " << vehicleDB.size()   << "\n";
    cout << "  Customers : " << customerDB.size()  << "\n";
    cout << "  Deliveries: " << deliveryDB.size()  << "\n";
}

void EntityManager::displayAll() const
{
    displayStats();

    cout << "\n-- Locations --\n";
    for (const auto& loc : locationDB.getAllValues())
        loc.display();

    cout << "\n-- Vehicles --\n";
    for (const auto& v : vehicleDB.getAllValues())
        v.display();

    cout << "\n-- Customers --\n";
    for (const auto& c : customerDB.getAllValues())
        c.display();

    cout << "\n-- Deliveries --\n";
    for (const auto& d : deliveryDB.getAllValues())
        d.display();
}
