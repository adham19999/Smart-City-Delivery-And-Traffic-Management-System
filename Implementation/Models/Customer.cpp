#include "../../Headers/Models/Customer.h"

Customer::Customer() : id(0), name(""), address(""), phone("") {}

Customer::Customer(int id, string name, string address, string phone)
    : id(id), name(name), address(address), phone(phone) {}

void Customer::display() const
{
    cout << "Customer " << id << ": " << name << ", Address: " << address << ", Phone: " << phone << "\n";
}
