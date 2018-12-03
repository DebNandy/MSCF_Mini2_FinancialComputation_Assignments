
// File: Employee.h
// Author(s):

#include <string>        // string data type
using namespace std;

class Employee {
public:
    Employee(const string& n, double r);
    virtual void print() const;
    void set_rate(double r);
    double get_rate() const { return rate; };
    int get_id() const { return id; }
private:
    const int id;    // ID -- okay to be public
    string name;     // name (arbitrary size)
    double rate;     // hourly rate
    Employee();      // no default Employees
    Employee(const Employee&);    // no clones
    Employee& operator=(const Employee&);
};

