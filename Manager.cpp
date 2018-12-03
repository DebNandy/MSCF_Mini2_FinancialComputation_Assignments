
// File: Manager.cpp
// Author(s):

#include <iostream>  // cout, <<
#include <string>    // string data type
#include <iomanip>   // setw()
using namespace std;
#include "Employee.h"   // Employee class
#include "Manager.h"    // Manager class


const double DEFAULT_BUDGET = 500000.0;

Manager::Manager(const string& n, double r,
        const string& t, double b)
: Employee(n, r),  // base class constructor
  title(t), budget(b > 0.0 ? b : DEFAULT_BUDGET)
{}

void Manager::set_budget(double b)
{ budget = (b > 0.0 ? b : DEFAULT_BUDGET); }

void Manager::print() const
{
    cout << "Manager information:\n";
    Employee::print();
    cout << "title: " << title << '\n';
    cout << "budget: " << fixed << setprecision(2) << budget << '\n';
}

