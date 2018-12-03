
// File: CEO.cpp
// Author(s):

#include <iostream>  // cout, <<
#include <string>    // string data type
#include <iomanip>   // setw()
using namespace std;
#include "CEO.h"     // CEO class
#include "Manager.h" // Manager class

CEO::CEO(const string& n, double r, double b, double t, double p)
: Manager(n, r, "CEO", b), profit_target(t), bonus_percentage(p)
{}

void CEO::set_profit_target(double t)
{
	profit_target = t;
}

double CEO::get_profit_target() const
{
	return profit_target;
}

void CEO::set_bonus_percentage(double p)
{
	bonus_percentage = p;
}

double CEO::get_bonus_percentage() const
{
	return bonus_percentage;
}

// NOTE: added << fixed << setprecision(2) for money amounts
void CEO::print() const
{
	cout << "CEO information:\n";
	Manager::print();
	cout << "profit_target: " << fixed << setprecision(2) << profit_target << '\n';
	cout << "bonus_percentage: " << bonus_percentage << '\n';
}

