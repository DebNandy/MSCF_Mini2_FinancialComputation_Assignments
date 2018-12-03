
//
// File: EuropeanOptions.cpp
// Author(s):
//  DEBAJYOTI NANDY
//  AVINASH SHRIVASTAVA
//  PALLAV RAJ

#include <iostream>
#include <vector>
#include <cmath>      // for pow()
#include <algorithm>  // for max()
#include <iomanip>    // for setw()
#include <string>
using namespace std;

/* ---------------- EuropeanCallOption class definition ----------------- */

class EuropeanCallOption {
private:
    // Basic values of a stock option
    double S0;         // initial stock price
    double K;          // strike price
    double r;          // risk-free rate
    double sigma;      // volatility
    double T;          // expiration time
    // Inner class used by the binomial tree method
    class Price {
    public:
        double stockPrice;
        double optionPrice;
    };

    // a private helper function
    void put_BinomialTree(string header, const vector<vector<Price>>& bT);

public:
    // constructor defined inline within the class definition
    EuropeanCallOption(double s0, double k, double rfr, 
                                double v, double et)
    : S0(s0), K(k), r(rfr), sigma(v), T(et)
    {}
 
    // Calculate the Price of the option
    // using the binomial tree method
    double binomialPrice(int numIntervals);
	double BSMPrice();

    // ... other pricing methods can be added here ...

};


/* ---------- EuropeanCallOption member function definition ----------- */

void EuropeanCallOption::put_BinomialTree(string header,
                                          const vector<vector<Price>>& bT)
{
    int N = (bT.size() == 0)
            ? 0
            : bT.size() - 1;

    if (N > 9) {  // if tree is too big, refuse to print anything
        // cout << header << "\n";
        // cout << "BinomialTree has " << N << " levels: too many to print!\n";
        return;
    }

    cout << "\n" << header << "\n\n";
    cout << "BinomialTree with " << N << " time steps:\n\n";
    for (int i(0); i < bT.size(); ++i) {
        cout << "Stock:  ";
        for (int j(0); j < bT[i].size(); ++j) {
	    cout << setw(8) << bT[i][j].stockPrice;
        }
        cout << "\n";
        cout << "Option: ";
        for (int j(0); j < bT[i].size(); ++j) {
	    cout << setw(8) << bT[i][j].optionPrice;
        }
        cout << "\n\n";
    }
    cout << "\n";
}


double EuropeanCallOption::binomialPrice(int numIntervals)
{
    // time interval length
    double deltaT  = T / numIntervals;;
    // factor by which stock price might rise at each step
    double u 	   = exp(sigma * sqrt(deltaT));
    // factor by which stock price might fall at each step
    double d 	   = 1 / u;
    // risk-free interest rate factor for one time interval
    double a	   = exp(r * deltaT);
    // RN probability of an up move in stock price
    double p	   = (a - d) / (u - d);
    // RN probability of a down move in stock price
    double q	   = 1.0 - p;
    // container for the binomialTree
    vector<vector<Price>> binomialTree;

    // put_BinomialTree("Initial, empty binomialTree:", binomialTree);

    // Build the shape of the binomialTree, by pushing
    // successively longer vector<Price> values (initially
    // all elements 0.0)
    for (int i(0); i <= numIntervals; ++i) {
        vector<Price> vInterval(i+1);    // i+1 {0.0,0.0} values
        binomialTree.push_back(vInterval);
    }
    put_BinomialTree("After filled in with all 0.0:", binomialTree);

    // Fill the stockPrice component of the binomialTree
    for (int i(0); i <= numIntervals; ++i) 
        for (int j(0); j <= i; ++j)
            binomialTree[i][j].stockPrice = 
                S0 * pow(u, j) * pow(d, i-j);
    put_BinomialTree("After filled in with stock prices:", binomialTree);

    // Fill the optionPrices at the terminal nodes
    for (int j(0); j <= numIntervals; ++j) {
        binomialTree[numIntervals][j].optionPrice =
                  max(binomialTree[numIntervals][j].stockPrice - K,
                           0.0);
    }
    put_BinomialTree("After filled in with terminal option values:", binomialTree);

    // Now work backwards, filling optionPrices in the rest of the tree
    // Your code here
	// 1.(b)
	for (int j(numIntervals - 1);j >= 0;j--) {
		for (int i(0);i <= j;i++) {
			binomialTree[j][i].optionPrice = (q * binomialTree[j + 1][i].optionPrice + 
											  p * binomialTree[j + 1][i + 1].optionPrice) / a;
		}
	}

    put_BinomialTree("After filled in with all option values:", binomialTree);

    // Return the time 0 call price
    return binomialTree[0][0].optionPrice;
}

// part 1.(g)
double EuropeanCallOption::BSMPrice() {

	double denom = sigma * pow(T, 0.5);
	double d1 = (log(S0 / K) + (r + sigma * sigma*0.5)*T) / denom;
	double d2 = d1 - denom;
	double nd1 = (1.0 + erf(d1 / sqrt(2))) / 2.0;
	double nd2 = (1.0 + erf(d2 / sqrt(2))) / 2.0;
	double df = exp(-r * T);
	double BSMPrice = S0 * nd1 - K * df*nd2;

	return BSMPrice;
};

//part 1.(f)

/* ---------------- EuropeanPutOption class definition ----------------- */

class EuropeanPutOption {
private:
	// Basic values of a stock option
	double S0;         // initial stock price
	double K;          // strike price
	double r;          // risk-free rate
	double sigma;      // volatility
	double T;          // expiration time
					   // Inner class used by the binomial tree method
	class Price {
	public:
		double stockPrice;
		double optionPrice;
	};

	// a private helper function
	void put_BinomialTree(string header, const vector<vector<Price>>& bT);

public:
	// constructor defined inline within the class definition
	EuropeanPutOption(double s0, double k, double rfr,
		double v, double et)
		: S0(s0), K(k), r(rfr), sigma(v), T(et)
	{}

	// Calculate the Price of the option
	// using the binomial tree method
	double binomialPrice(int numIntervals);
	double BSMPrice();
	// ... other pricing methods can be added here ...

};


/* ---------- EuropeanCallOption member function definition ----------- */

void EuropeanPutOption::put_BinomialTree(string header,
	const vector<vector<Price>>& bT)
{
	int N = (bT.size() == 0)
		? 0
		: bT.size() - 1;

	if (N > 9) {  // if tree is too big, refuse to print anything
				  // cout << header << "\n";
				  // cout << "BinomialTree has " << N << " levels: too many to print!\n";
		return;
	}

	cout << "\n" << header << "\n\n";
	cout << "BinomialTree with " << N << " time steps:\n\n";
	for (int i(0); i < bT.size(); ++i) {
		cout << "Stock:  ";
		for (int j(0); j < bT[i].size(); ++j) {
			cout << setw(8) << bT[i][j].stockPrice;
		}
		cout << "\n";
		cout << "Option: ";
		for (int j(0); j < bT[i].size(); ++j) {
			cout << setw(8) << bT[i][j].optionPrice;
		}
		cout << "\n\n";
	}
	cout << "\n";
}


double EuropeanPutOption::binomialPrice(int numIntervals)
{
	// time interval length
	double deltaT = T / numIntervals;;
	// factor by which stock price might rise at each step
	double u = exp(sigma * sqrt(deltaT));
	// factor by which stock price might fall at each step
	double d = 1 / u;
	// risk-free interest rate factor for one time interval
	double a = exp(r * deltaT);
	// RN probability of an up move in stock price
	double p = (a - d) / (u - d);
	// RN probability of a down move in stock price
	double q = 1.0 - p;
	// container for the binomialTree
	vector<vector<Price>> binomialTree;

	// put_BinomialTree("Initial, empty binomialTree:", binomialTree);

	// Build the shape of the binomialTree, by pushing
	// successively longer vector<Price> values (initially
	// all elements 0.0)
	for (int i(0); i <= numIntervals; ++i) {
		vector<Price> vInterval(i + 1);    // i+1 {0.0,0.0} values
		binomialTree.push_back(vInterval);
	}
	put_BinomialTree("After filled in with all 0.0:", binomialTree);

	// Fill the stockPrice component of the binomialTree
	for (int i(0); i <= numIntervals; ++i)
		for (int j(0); j <= i; ++j)
			binomialTree[i][j].stockPrice =
			S0 * pow(u, j) * pow(d, i - j);
	put_BinomialTree("After filled in with stock prices:", binomialTree);

	// Fill the optionPrices at the terminal nodes
	for (int j(0); j <= numIntervals; ++j) {
		binomialTree[numIntervals][j].optionPrice =
			max(K - binomialTree[numIntervals][j].stockPrice,
				0.0); // this terminal payoff function is the major change
	}
	put_BinomialTree("After filled in with terminal option values:", binomialTree);

	// Now work backwards, filling optionPrices in the rest of the tree
	// Your code here
	// 1.(b)
	for (int j(numIntervals - 1);j >= 0;j--) {
		for (int i(0);i <= j;i++) {
			binomialTree[j][i].optionPrice = (q * binomialTree[j + 1][i].optionPrice +
				p * binomialTree[j + 1][i + 1].optionPrice) / a;
		}
	}

	put_BinomialTree("After filled in with all option values:", binomialTree);

	// Return the time 0 call price
	return binomialTree[0][0].optionPrice;
}

// part 1.(h)
double EuropeanPutOption::BSMPrice() {

	double denom = sigma * pow(T, 0.5);
	double d1 = (log(S0 / K) + (r + sigma * sigma*0.5)*T) / denom;
	double d2 = d1 - denom;
	double nd1 = (1.0 + erf(-d1 / sqrt(2))) / 2.0;
	double nd2 = (1.0 + erf(-d2 / sqrt(2))) / 2.0;
	double df = exp(-r * T);
	double BSMPrice = K * df*nd2 - S0*nd1;

	return BSMPrice;
};

int main()
{
    EuropeanCallOption ec1(50.0,     // current stock price, S0
                           50.0,     // option strike price, K
                           0.10,     // risk-free rate
                           0.40,     // stock price volatility
                           0.4167);  // expiration time T (5 months)

    int N = 1000;  // number of time intervals for Binomial Tree
	double ec1price = ec1.binomialPrice(N);
    cout << "Call price, with " << N << " intervals: "
         << ec1price << "\n";
	
	/*
	1.(c) as the number if intervals increase, the price
	converges towards the BSM model implied price $6.12
	# of time
	intervals | Price
	----------|-------
	5	  | $6.35983
	10     | $5.99123
	20     | $6.05354
	50     | $6.09138
	100     | $6.10407
	200     | $6.11042
	500     | $6.11424
	1000     | $6.11551
	*/

	//part 1.(d)
	EuropeanCallOption ec2( 5.0,
						    5.0,
							0.10,     // risk-free rate
							0.40,     // stock price volatility
							0.4167);  // expiration time T (5 months)
	double ec2price = ec2.binomialPrice(N);
	double tolerance = 0.00000001; // 10^-8
	cout << "Test no-arbitrage on downsize of contracts: " << ec1price/10 << " == " << ec2price << "\n";
	if (abs(ec1price / 10 - ec2price)<tolerance)
		cout << "correct\n";
	else cout << "incorrect\n";

	EuropeanCallOption ec3( 500.0,
							500.0,
							0.10,     // risk-free rate
							0.40,     // stock price volatility
							0.4167);  // expiration time T (5 months)
	double ec3price = ec3.binomialPrice(N);
	cout << "Test no-arbitrage on upsize of contracts: " << ec1price * 10 << " == " << ec3price << "\n";
	if (abs(ec1price * 10 - ec3price)<tolerance)
		cout << "correct\n";
	else cout << "incorrect\n";


	// part 1.(e)
	EuropeanCallOption 
		ecv05(50.0, 50.0, 0.10, 0.05, 0.4167),
		ecv10(50.0, 50.0, 0.10, 0.10, 0.4167),
		ecv20(50.0, 50.0, 0.20, 0.20, 0.4167),
		ecv40(50.0, 50.0, 0.10, 0.40, 0.4167),
		ecv80(50.0, 50.0, 0.10, 0.80, 0.4167),
		ecv160(50.0, 50.0, 0.10, 1.60, 0.4167);
	double price1 = ecv05.binomialPrice(N),
		price2 = ecv10.binomialPrice(N),
		price3 = ecv20.binomialPrice(N),
		price4 = ecv40.binomialPrice(N),
		price5 = ecv80.binomialPrice(N),
		price6 = ecv160.binomialPrice(N);
	vector <double> pricevec;
	pricevec.push_back(price1);
	pricevec.push_back(price2);
	pricevec.push_back(price3);
	pricevec.push_back(price4);
	pricevec.push_back(price5);
	pricevec.push_back(price6);
	cout << "Test european style call option prices increase with increase in volatility: " << "\n" <<
		"Price for volatility 0.05 : " << price1 << "\n" <<
		"Price for volatility 0.10 : " << price2 << "\n" <<
		"Price for volatility 0.20 : " << price3 << "\n" <<
		"Price for volatility 0.40 : " << price4 << "\n" <<
		"Price for volatility 0.80 : " << price5 << "\n" <<
		"Price for volatility 1.60 : " << price6 << "\n";
	if (is_sorted(pricevec.begin(), pricevec.end()))
		cout << "correct\n";
	else cout << "incorrect\n";

	/*
	The price is non-linear in volatility as doubling the volatility doesn't double the price. Also
	when volatility is small, the sensitivity of price with volatility is small, but when volatility 
	is large the sensitivity is also large 
	Price for volatility 0.05 : 2.11384
	Price for volatility 0.10 : 2.53498
	Price for volatility 0.20 : 4.96546
	Price for volatility 0.40 : 6.11551
	Price for volatility 0.80 : 11.0294
	Price for volatility 1.60 : 20.3493
	*/
	//part 1.(f)

	EuropeanPutOption ep1(50.0,     // current stock price, S0
		50.0,     // option strike price, K
		0.10,     // risk-free rate
		0.40,     // stock price volatility
		0.4167);  // expiration time T (5 months)

	//int N = 1000;  // number of time intervals for Binomial Tree
	double ep1price = ep1.binomialPrice(N);
	cout << "Put price, with " << N << " intervals: "
		<< ep1price << "\n";

	EuropeanPutOption ep2(5.0,
		5.0,
		0.10,     // risk-free rate
		0.40,     // stock price volatility
		0.4167);  // expiration time T (5 months)
	double ep2price = ep2.binomialPrice(N);
	//double tolerance = 0.00000001; // 10^-8
	cout << "Test no-arbitrage on downsize of contracts: " << ep1price / 10 << " == " << ep2price << "\n";
	if (abs(ep1price / 10 - ep2price)<tolerance)
		cout << "correct\n";
	else cout << "incorrect\n";

	EuropeanPutOption ep3(500.0,
		500.0,
		0.10,     // risk-free rate
		0.40,     // stock price volatility
		0.4167);  // expiration time T (5 months)
	double ep3price = ep3.binomialPrice(N);
	cout << "Test no-arbitrage on upsize of contracts: " << ep1price * 10 << " == " << ep3price << "\n";
	if (abs(ep1price * 10 - ep3price)<tolerance)
		cout << "correct\n";
	else cout << "incorrect\n";

	EuropeanPutOption
		epv05(50.0, 50.0, 0.10, 0.05, 0.4167),
		epv10(50.0, 50.0, 0.10, 0.10, 0.4167),
		epv20(50.0, 50.0, 0.20, 0.20, 0.4167),
		epv40(50.0, 50.0, 0.10, 0.40, 0.4167),
		epv80(50.0, 50.0, 0.10, 0.80, 0.4167),
		epv160(50.0, 50.0, 0.10, 1.60, 0.4167);
	double pricep1 = epv05.binomialPrice(N),
		pricep2 = epv10.binomialPrice(N),
		pricep3 = epv20.binomialPrice(N),
		pricep4 = epv40.binomialPrice(N),
		pricep5 = epv80.binomialPrice(N),
		pricep6 = epv160.binomialPrice(N);
	vector <double> putpricevec;
	putpricevec.push_back(pricep1);
	putpricevec.push_back(pricep2);
	putpricevec.push_back(pricep3);
	putpricevec.push_back(pricep4);
	putpricevec.push_back(pricep5);
	putpricevec.push_back(pricep6);
	cout << "Test european style put option prices increase with increase in volatility: " << "\n" <<
		"Price for volatility 0.05 : " << pricep1 << "\n" <<
		"Price for volatility 0.10 : " << pricep2 << "\n" <<
		"Price for volatility 0.20 : " << pricep3 << "\n" <<
		"Price for volatility 0.40 : " << pricep4 << "\n" <<
		"Price for volatility 0.80 : " << pricep5 << "\n" <<
		"Price for volatility 1.60 : " << pricep6 << "\n";
	if (is_sorted(putpricevec.begin(), putpricevec.end()))
		cout << "correct\n";
	else cout << "incorrect\n";

	//part 1.(g)
	
	cout << "Binomial Price for ec1 : " << ec1.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ec1.BSMPrice() << "\n";
	cout << "Binomial Price for ec2 : " << ec2.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ec2.BSMPrice() << "\n";
	cout << "Binomial Price for ec3 : " << ec3.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ec3.BSMPrice() << "\n";
	cout << "Binomial Price for ecv05 : " << ecv05.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ecv05.BSMPrice() << "\n";
	cout << "Binomial Price for ecv10 : " << ecv10.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ecv10.BSMPrice() << "\n";
	cout << "Binomial Price for ecv20 : " << ecv20.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ecv20.BSMPrice() << "\n";
	cout << "Binomial Price for ecv40 : " << ecv40.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ecv40.BSMPrice() << "\n";
	cout << "Binomial Price for ecv80 : " << ecv80.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ecv80.BSMPrice() << "\n";
	cout << "Binomial Price for ecv160 : " << ecv160.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ecv160.BSMPrice() << "\n";

	//Below tables shows the above output and the closeness of the binomial price
	// and the BSM price of european call option for large interval estimate.
	/*
	// Part 1.(i)
	Call Option Object | Binomial Price | BSM Price | ERI Price
	      ec1		   |   6.11666      |  6.11679  |  6.1168
		  ec2		   |   0.611666     |  0.611666 |  0.6117
		  ec3		   |  61.1666       | 61.1679   | 61.1678
		  ecv05        |   2.114		|  2.11402  |  2.114
		  ecv10		   |   2.53531      |  2.53535  |  2.5353
		  ecv40        |   6.11666		|  6.11679  |  6.1168
		  ecv80		   |  11.0317       | 11.0319   | 11.0391
		  ecv160	   |  20.3537		| 20.3541   | 20.3541
	*/

	/*part 1.(h)*/
	cout << "Binomial Price for ec1 : " << ep1.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ep1.BSMPrice() << "\n";
	cout << "Binomial Price for ec2 : " << ep2.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ep2.BSMPrice() << "\n";
	cout << "Binomial Price for ec3 : " << ep3.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << ep3.BSMPrice() << "\n";
	cout << "Binomial Price for ecv05 : " << epv05.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << epv05.BSMPrice() << "\n";
	cout << "Binomial Price for ecv10 : " << epv10.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << epv10.BSMPrice() << "\n";
	cout << "Binomial Price for ecv20 : " << epv20.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << epv20.BSMPrice() << "\n";
	cout << "Binomial Price for ecv40 : " << epv40.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << epv40.BSMPrice() << "\n";
	cout << "Binomial Price for ecv80 : " << epv80.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << epv80.BSMPrice() << "\n";
	cout << "Binomial Price for ecv160 : " << epv160.binomialPrice(10000) << "\n" <<
		"BSM Price for ec1 : " << epv160.BSMPrice() << "\n";

	//Below tables shows the above output and the closeness of the binomial price
	// and the BSM price of european put option for large interval estimate.
	/*
	// Part 1.(i)
	Put Option Object | Binomial Price | BSM Price  | ERI Price
	     ep1		  |   4.07597      |  4.0761    |  4.0761
		 ep2		  |   0.407597     |  0.40761   |  0.4076
		 ep3		  |  40.7597       | 40.761     | 40.7609
		 ecv05        |   0.0733144	   |  0.0733326 |  0.0733
		 ecv10		  |   0.494623     |  0.494659  |  0.4947
		 ecv40        |   4.07597	   |  4.0761    |  4.0761
		 ecv80		  |   8.99098      |  8.99124   |  8.9912
		 ecv160	      |  18.313	       | 18.3135    | 18.3135
	*/

	//1.i the ERI calculated prices match the binomial and BSM model implied prices for put and 
	// call options very well.
}
