
// File: FCII_HW1_2.cpp
// Author(s): AVINASH SHRIVASTAVA, DEBAJYOTI NANDY, PALLAV RAJ

#include <iostream>
#include <set>
#include <string>
using namespace std;

typedef bool (*pFbii)(int i, int j);
bool gtr_than(int i, int j) { return i > j; }

bool even_up_odd_down(int i, int j) {
    if(i%2==0 && j%2==0)
        return i < j;
    else if(i%2==1 && j%2==1)
        return i > j;
    else if(i%2==1 && j%2==0)
        return false;
    else// if(i%2==0 && j%2==1)
        return true;// > j;
}

int main()
{
	set<int> si1{ 4, 2, 5, -3, 0, -1, 9, 6, 6, 2, 5, 4, 12 };
	for (int el : si1)
		cout << el << ' ';
	cout << '\n';

    //Part b
    set<int, bool (*)(int,int)> si2(gtr_than);
    for (int el : si1)
        si2.insert(el); //Values are stored in descending order

    for (int el : si2)
        cout << el << ' ';
    cout << '\n';
    
    //Part c
    set<int, pFbii> si3(gtr_than); //code is cleaner compare to above declaration of si2
    for (int el : si1)
        si3.insert(el);
    
    for (int el : si3)
        cout << el << ' ';
    cout << '\n';

    //Part d
    set<int, pFbii> si4(even_up_odd_down);
    for (int el : si1)
        si4.insert(el);
    
    for (int el : si4)
        cout << el << ' '; //even values are ascending and odd are in descending order
    cout << '\n';

}
