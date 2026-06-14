#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "../Models/Location.h"
#include "../Models/Vehicle.h"
#include "../Models/Customer.h"
#include "../Models/Delivery.h"
#include "../DataStructures/HashTable.h"
#include <iostream>
#include <vector>
using namespace std;

// Component 2: Location & Entity Manager (Hash-based)
// O(1) average insert/lookup for all entity types
class EntityManager
{
private:
    HashTable<int, Location>  locationDB;
    HashTable<int, Vehicle>   vehicleDB;
    HashTable<int, Customer>  customerDB;
    HashTable<int, Delivery>  deliveryDB;

    int nextLocationId;
    int nextVehicleId;
    int nextCustomerId;
    int nextDeliveryId;

public:
    EntityManager();

    // Location operations
    void addLocation(const Location& loc);
    Location* getLocation(int id);
    bool removeLocation(int id);
    vector<Location> getAllLocations() const;

    // Vehicle operations
    void addVehicle(const Vehicle& vehicle);
    Vehicle* getVehicle(int id);
    bool removeVehicle(int id);
    vector<Vehicle> getAllVehicles() const;
    vector<Vehicle> getAvailableVehicles() const;

    // Customer operations
    void addCustomer(const Customer& customer);
    Customer* getCustomer(int id);
    bool removeCustomer(int id);
    vector<Customer> getAllCustomers() const;

    // Delivery operations
    void addDelivery(const Delivery& delivery);
    Delivery* getDelivery(int id);
    bool removeDelivery(int id);
    bool updateDeliveryStatus(int id, const string& status);
    vector<Delivery> getAllDeliveries() const;
    vector<Delivery> getPendingDeliveries() const;

    // ID generators
    int generateLocationId();
    int generateVehicleId();
    int generateCustomerId();
    int generateDeliveryId();

    void displayAll() const;
    void displayStats() const;
};

#endif // ENTITYMANAGER_H
