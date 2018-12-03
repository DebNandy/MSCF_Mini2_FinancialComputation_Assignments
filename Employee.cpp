
// File: Employee.cpp
// Author(s):

#include <iostream> // cout, <<
#include <string>   // string data type
#include <iomanip>  // setw()
using namespace std;
#include "Employee.h"

const double MINWAGE = 11.25;

Employee::Employee(const string& n, double r)
: id(next_id++), name(n), rate(r > MINWAGE ? r : MINWAGE)
{}

void Employee::print() const {
    cout << "Employee # " << id << ", name: "
         << name << ", rate: " << fixed << setprecision(2) << rate << '\n';
}

void Employee::set_rate(double r)
{ rate = (r > MINWAGE ? r : MINWAGE); }

