#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>

using namespace std;

class Customer
{
public:
    int id;
    string name;
    string address;
    string phone;

    Customer();
    Customer(int id, string name, string address, string phone);
    
    void display() const;
};

#endif
