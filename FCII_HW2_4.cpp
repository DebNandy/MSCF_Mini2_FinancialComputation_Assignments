
//
// File: FCII_HW2_4.cpp
// Author(s):
//

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Term {
public:
    Term() {}
    virtual ~Term() {}
    virtual string to_string() = 0;
    virtual double to_value() = 0;
};

class Constant : public Term {
public:
    Constant(double v) : value(v) {}
    virtual ~Constant() {}
    virtual string to_string() {
        ostringstream oss;
        oss << value;
        return oss.str();
    }
    virtual double to_value()
    {   return value;   }
private:
    double value;
};

class BinaryOp : public Term {
public:
    BinaryOp(Term * lf, Term * rt) {
        left = lf;    // now owner of lf
        right = rt;
    }
    virtual ~BinaryOp() {
        delete left;  // ... so can delete
        delete right;
    }
protected:
    Term *left, *right;
};

class Plus : public BinaryOp {    // concrete class
public:
    Plus(Term * l, Term * r) : BinaryOp(l, r) {}
    virtual ~Plus() {}
    virtual string to_string() {
        ostringstream oss;
        oss << "(" << left->to_string() << " + "
               << right->to_string() << ")";
        return oss.str();
    }
    virtual double to_value() {
        return (left->to_value() + right->to_value());
    }
};

int main()
{
    Term *c1 = new Constant(1.1);
    Term *c2 = new Constant(2.2);
    Term *c3 = new Constant(3.3);
    Term *p1 = new Plus(c1, c2);    // p1 now owns c1 and c2
    Term *p2 = new Plus(p1, c3);    // p2 now owns p1 and c3
    cout << p2->to_string() << " = "
            << p2->to_value() << "\n";
    delete p2;    // all Terms deleted

#if 0
    Term *ca = new Constant(1.5);
    Term *cb = new Constant(2.7);
    Term *cc = new Constant(0.8);
    Term *cd = new Constant(3.3);
    Term *ce = new Constant(4.7);
    Term *m = new Minus(ce, cc);
    Term *d = new Divide(cd, ca);
    Term *t = new Times(d, cb);
    Term *p = new Plus(m, t);
    cout << p->to_string() << " = "
         << p->to_value() << "\n";
    delete p;
#endif

#if 0
    {
        cout << "# Terms: " << Term::get_nterms()
             << '\n';             // should display 0
        cout << "# Constants: " << Constant::get_ncons()
             << '\n';             // should display 0
        Term *ca = new Constant(0.6);
        Term *cb = new Constant(-2.2);
        Term *cc = new Constant(0.7);
        Term *m = new Minus(ca, cb);
        Term *p = new Plus(m, cc);
        cout << p->to_string() << " = "
             << p->to_value() << "\n";
        cout << "# Terms: " << Term::get_nterms()
             << '\n';             // should display 5
        cout << "# Constants: " << Constant::get_ncons()
             << '\n';             // should display 3
        delete p;
        cout << "# Terms: " << Term::get_nterms()
             << '\n';             // should display 0
        cout << "# Constants: " << Constant::get_ncons()
             << '\n';             // should display 0
    }
#endif
}

