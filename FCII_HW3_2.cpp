
//
// File: FCII_HW3_2.cpp
// Author(s):
//

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
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

// (4b)
class Variable : public Term {
public:
    Variable(double v) : value(v) {}
    virtual ~Variable() {}
    virtual string to_string() {
        return "X";
    }
    virtual double to_value()
    {   return value;   }
    void set_value(double x) {
        value = x;
    }
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

class Minus : public BinaryOp {    // concrete class
public:
    Minus(Term * l, Term * r) : BinaryOp(l, r) {}
    virtual ~Minus() {}
    virtual string to_string() {
        ostringstream oss;
        oss << "(" << left->to_string() << " - "
               << right->to_string() << ")";
        return oss.str();
    }
    virtual double to_value() {
        return (left->to_value() - right->to_value());
    }
};

class Times : public BinaryOp {    // concrete class
public:
    Times(Term * l, Term * r) : BinaryOp(l, r) {}
    virtual ~Times() {}
    virtual string to_string() {
        ostringstream oss;
        oss << "(" << left->to_string() << " * "
               << right->to_string() << ")";
        return oss.str();
    }
    virtual double to_value() {
        return (left->to_value() * right->to_value());
    }
};

class Divide : public BinaryOp {    // concrete class
public:
    Divide(Term * l, Term * r) : BinaryOp(l, r) {}
    virtual ~Divide() {}
    virtual string to_string() {
        ostringstream oss;
        oss << "(" << left->to_string() << " / "
               << right->to_string() << ")";
        return oss.str();
    }
    virtual double to_value() {
        return (left->to_value() / right->to_value());
    }
};

double rand_constant()
{
    return (rand() % 5000 + 1) / 1000.0;
}

Term *rand_operator(Term *t1, Term *t2)
{
    switch (rand() % 4) {
    case 0:
        return new Plus(t1, t2);
    case 1:
        return new Minus(t1, t2);
    case 2:
        return new Times(t1, t2);
    default:
        return new Divide(t1, t2);
    }
}


int main()
{
    // five randomly generated arithmetic expressions
    for (int i(0); i < 5; ++i) {
        Constant *c1 = new Constant(rand_constant());
        Constant *c2 = new Constant(rand_constant());
        Constant *c3 = new Constant(rand_constant());
        Constant *c4 = new Constant(rand_constant());
        Term *p1 = rand_operator(c1, c2);    // p1 now owns c1 and c2
        Term *p2 = rand_operator(c3, c4);    // p2 now owns c3 and c4
        Term *p3 = rand_operator(p1, p2);    // p3 now owns p1 and c2
        cout << p3->to_string() << " = "
             << p3->to_value() << "\n";
        delete p3;    // all Terms deleted
    }

    Constant *c1 = new Constant(1.1);
    Constant *c2 = new Constant(2.2);
    Constant *c3 = new Constant(3.3);
    Constant *c4 = new Constant(4.4);
    Variable *v1 = new Variable(5.5);
    Plus *p = new Plus(c1, c2);
    Times *t = new Times(c3, c4);
    Divide *d = new Divide(t, v1);
    Minus *m = new Minus(p, d);

    cout << "X = " << v1->to_value() << '\n';
    cout << m->to_string() << " = "
         << m->to_value() << "\n";
    v1->set_value(-4.5);
    cout << "X = " << v1->to_value() << '\n';
    cout << m->to_string() << " = "
         << m->to_value() << "\n";
    delete m;    // all Terms deleted

#if 0  // part (e) test code
    add_x(c1, 1.2);   // should do nothing
    add_x(v1, 1.1);   // should add 1.1 to the Variable
    add_x(p, 2.5);    // should do nothing
    cout << "X = " << v1->to_value() << "\n";
    cout << m->to_string() << " = "
         << m->to_value() << "\n";
#endif

}

