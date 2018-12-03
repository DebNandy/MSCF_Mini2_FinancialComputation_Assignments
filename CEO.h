
// File: CEO.h
// Author(s):

#include <string>         // string data type
using namespace std;
#include "Manager.h"      // Manager class

// a CEO is a kind of Manager
class CEO : public Manager {
public:
    CEO(const string& n, double r, double b, double t, double p);
    void print() const;
    void set_profit_target(double);
    double get_profit_target() const;
    void set_bonus_percentage(double);
    double get_bonus_percentage() const;
private:
    double profit_target;
    double bonus_percentage;
    CEO();      // no default CEOs
    CEO(const CEO&);    // no clones
    CEO& operator=(const CEO&);
};

