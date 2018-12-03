
// File: FCII_HW3_1.cpp
// Author(s):

#include <iostream>     // cout, <<
using namespace std;
#include "Employee.h"   // Employee class
#include "Manager.h"    // Manager class
#include "CEO.h"        // CEO class

int main()
{
    Employee alex("Alex", 57.25);
    Employee bob("Bob", 63.10);
    Manager carl("Carl", 66.75, "Boss", 0.0);

    cout << "Alex's ID: " << alex.get_id() << '\n';
    bob.set_rate(6.31);     // 90% pay cut!  Ouch!
    bob.print();            // Employee::print()
    carl.set_rate(77.7);    // Employee::set_rate()
                            //     via inheritance
    carl.print();           // Employee::print()
    cout << "Carl's budget: " << carl.get_budget()
                              << '\n';

    const Employee *p(&alex);
    p->print();
    p = &carl;
    p->print();

    Employee gene("Gene", 68.25);
    const Employee hank("Hank", 67.0);
    Manager ian("Ian", 71.75, "Boss", 250000.0);

    cout << "Gene's id: " << gene.get_id() << '\n';
    cout << "Hank's id: " << hank.get_id() << '\n';
    cout << "Ian's id: " << ian.get_id() << '\n';

    p = &gene;
    p->print();

    p = &hank;
    p->print();

    p = &ian;
    p->print();

    CEO joe("Joe", 120.0,
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

#if 0  // part (b) test code
    {  // nested block: local objects created here will be destroyed at end of block
	cout << "In nested block:\n";
        cout << "Next Employee id: " << Employee::get_next_id() << '\n';
        cout << "# of Employees:   " << Employee::get_num_emps() << '\n';
        cout << "# of Managers:    " << Manager::get_num_mgrs() << '\n';
        cout << "# of CEOs:        " << CEO::get_num_ceos() << '\n';
        Employee deb("Deb", 54.32);
        Employee eric("Eric", 44.75);
        Manager fred("Fred", 70.12, "Foreman", 200000.0);
        deb.print();
        eric.print();
        fred.print();
	cout << "Still in nested block:\n";
        cout << "Next Employee id: " << Employee::get_next_id() << '\n';
        cout << "# of Employees:   " << Employee::get_num_emps() << '\n';
        cout << "# of Managers:    " << Manager::get_num_mgrs() << '\n';
        cout << "# of CEOs:        " << CEO::get_num_ceos() << '\n';
    }
    cout << "After nested block:\n";
    cout << "Next Employee id: " << Employee::get_next_id() << '\n';
    cout << "# of Employees:   " << Employee::get_num_emps() << '\n';
    cout << "# of Managers:    " << Manager::get_num_mgrs() << '\n';
    cout << "# of CEOs:        " << CEO::get_num_ceos() << '\n';
#endif

#if 0  // part (c) test code
    cout << "Should not be much to see here: explicit inline functions should work\n"
	 << "just like the functions they replaced.\n";
#endif

#if 0  // part (d) test code
    {
	cout << "In part (d) nested block:\n";
	Employee gene("Gene");
	Employee hal("Hal", 77.75);
	Manager irene("Irene");
	Manager jerry("Jerry", 62.22);
	Manager karl("Karl", 66.33, "Boss");
	Manager lucy("Lucy", 82.15, "CFO", 175000.0);
	CEO mary("Mary");
        cout << "Next Employee id: " << Employee::get_next_id() << '\n';
        cout << "# of Employees:   " << Employee::get_num_emps() << '\n';
        cout << "# of Managers:    " << Manager::get_num_mgrs() << '\n';
        cout << "# of CEOs:        " << CEO::get_num_ceos() << '\n';
	gene.print();
	hal.print();
	irene.print();
	jerry.print();
	karl.print();
	lucy.print();
	cout << "Leaving part (d) nested block:\n";
    }
    cout << "Next Employee id: " << Employee::get_next_id() << '\n';
    cout << "# of Employees:   " << Employee::get_num_emps() << '\n';
    cout << "# of Managers:    " << Manager::get_num_mgrs() << '\n';
    cout << "# of CEOs:        " << CEO::get_num_ceos() << '\n';
#endif

#if 0  // part (e) test code
    buy_soup(bob, "Split Pea");         // No soup for you!
    buy_soup(carl, "Mushroom");         // Chicken noodle soup for you.
    buy_soup(hank, "Tomato");           // No soup for you!
    buy_soup(joe, "Lobster Bisque");    // Here is your Lobster Bisque.  Please come again!
    buy_soup("Mary", "Clam Chowder");   // should not compile!
#endif

}

