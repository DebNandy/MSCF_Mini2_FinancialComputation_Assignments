
// File: FCII_HW1_3.cpp
// Author(s): PALLAV RAJ, AVINASH SHRIVASTAVA, DEBAJYOTI NANDY


#include <iostream>
#include <string>
using namespace std;

// Employee.h contents

class Employee {
public:
    Employee(int i, const string& n, double r);
    virtual void print() const; // part (b)
    void set_rate(double r);
    double get_rate() const { return rate; };
    // const int id;    // ID -- okay to be public
	int get_id() const { // part (c)
		return id;
	};
private:
	int id; // part (c)
	string name;     // name (arbitrary size)
    double rate;     // hourly rate
    Employee();      // no default Employees
    Employee(const Employee&);    // no clones
    Employee& operator=(const Employee&);
};

// Employee.cpp contents

const double MINWAGE = 11.25;

Employee::Employee(int i, const string& n, double r)
: id(i), name(n), rate(r > MINWAGE ? r : MINWAGE)
{}

void Employee::print() const {
    cout << "Employee # " << id << ", name: "
         << name << ", rate: " << rate << '\n';
}

void Employee::set_rate(double r)
{ rate = (r > MINWAGE ? r : MINWAGE); }

// Manager.h contents

// a Manager is a kind of Employee
class Manager : public Employee {
public:
    Manager(int i, const string& n, double r,
            const string& t, double b);
    virtual void print() const;  // override base class print
    void set_budget(double b);
    double get_budget() const { return budget; }
private:
    string title;
    double budget;
    Manager();      // no default Managers
    Manager(const Manager&);    // no clones
    Manager& operator=(const Manager&);
};

// Manager.cpp contents

const double DEFAULT_BUDGET = 500000.0;

Manager::Manager(int i, const string& n, double r,
        const string& t, double b)
: Employee(i, n, r),  // base class constructor
  title(t), budget(b > 0.0 ? b : DEFAULT_BUDGET)
{}

void Manager::set_budget(double b)
{ budget = (b > 0.0 ? b : DEFAULT_BUDGET); }

void Manager::print() const
{
    cout << "Manager information:\n";
    Employee::print();
    cout << "title: " << title << '\n';
    cout << "budget: " << budget << '\n';
}


// main function

int main()
{
    Employee alex(1, "Alex", 57.25);
    Employee bob(2, "Bob", 63.10);
    Manager carl(3, "Carl", 66.75, "Boss", 0.0);
    // Employee dave;    // error!  private default
    // Manager ed(carl); // error!  private copy
    // bob = alex;       // error!  private assignment

    cout << "Alex's ID: " << alex.get_id() << '\n';
    // alex.id = 123;       // error!  access violation
    bob.set_rate(6.31);     // 90% pay cut!  Ouch!
    bob.print();            // Employee::print()
    carl.set_rate(77.7);    // Employee::set_rate()
                            //     via inheritance
    carl.print();           // Employee::print()
	cout << "\n Part (b) print Carl as Employee \n";
	carl.Employee::print(); // part (b) print Carl as Employee
    
	cout << "\n";
	cout << "Carl's budget: " << carl.get_budget()
                              << '\n';
    // alex.get_budget()    // error!  An Employee is
                            // not a kind of Manager

    Employee *p(&alex);
    p->print();
    p = &carl;
    p->print();

    /* part (c) */
    Employee gene(10, "Gene", 68.25);
    const Employee hank(12, "Hank", 67.0);
    Manager ian(13, "Ian", 71.75, "Boss", 250000.0);

    cout << "Gene's id: " << gene.get_id() << '\n';
    cout << "Hank's id: " << hank.get_id() << '\n';
    cout << "Ian's id: " << ian.get_id() << '\n';
    
	
    /* part (d)*/
    p = &gene;
    p->print();

    //p = &hank; //cannot convert from 
	//'const Employee *' to 'Employee *'
    // p->print();

    p = &ian;
    p->print();
    

    /* part (f)
    CEO joe(15, "Joe", 120.0,
                            // joe's title will be "CEO"
             100000000.0,   // budget
               4000000.0,   // profit target
                   250.0);  // bonus percentage
    joe.print();
    cout << "Joe's id: " << joe.get_id() << '\n';
    cout << "Joe's rate: " << joe.get_rate() << '\n';
    cout << "Joe's title: " << joe.get_title() << '\n';
    cout << "Joe's budget: " << joe.get_budget() << '\n';
    cout << "Joe's profit target: "
         << joe.get_profit_target() << '\n';
    cout << "Joe's bonus percentage: "
         << joe.get_bonus_percentage() << '\n';

    // 10% raise
    joe.set_rate(joe.get_rate() * 1.1);
    // 20% budget increase
    joe.set_budget(joe.get_budget() * 1.2);
    // 10% profit target reduction
    joe.set_profit_target(
              joe.get_profit_target() * 0.90);
    // 30% increase in bonus percentage
    joe.set_bonus_percentage(
              joe.get_bonus_percentage() * 1.3);

    p = &joe;
    p->print();
    */


}

