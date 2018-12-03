
// File: FCII_HW4.cpp
// Authors(s): 
// DEBAJYOTI NANDY
// AVINASH SHRIVASTAVA
// PALLAV RAJ

#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>        // for sqrt(), exp(), pow()
#include <ctime>        // for time()
#include <random>       // for minstd_rand, distributions
using namespace std;


/***************************************************************/


double my_sqrt(int i) {
	return sqrt(i);
}
double my_exp(double i) {
	return exp(i);
}
double my_ceil(double i) {
	return ceil(i);
}
double my_log(double i) {
	return log(i);
}
double my_pow(double x, double y) {
	return pow(x, y);
}
void add_rand(double &i) {
	double random = 0.01*(1.0 + rand() % 100);//uniform between 0.01-1.00
	i += random;
}

int main()
{
    cout << boolalpha;  // true, false not 1, 0

                             // seed to 0 so everyone gets the same "random" numbers
    minstd_rand msrand(0);   // linear congruential with range 0 through 2^32-1

// (a)
    vector<int> v1;
    for (int i(0); i < 25; ++i)
        v1.push_back(msrand() % 10);
    cout << setw(8) << "v1: " << "size: " << setw(4) << v1.size() << ":  ";
    for (auto& el : v1) cout << el << ' '; cout << '\n';

    multimap<char,int> mm1;
    for (vector<int>::iterator it(v1.begin()); it != v1.end(); ++it) {
        pair<char,int> pci;
        pci.first = 'a' + msrand() % 5;  // random char in 'a','b','c','d','e'
        pci.second = *it;
        mm1.insert(pci);
    }
    cout << setw(8) << "mm1: " << "size: " << setw(4) << mm1.size() << ":  ";
    for (auto& el : mm1) cout << el.first << el.second << ' '; cout << '\n';

// (b)
/***** uncomment the code below for part (b)*/
    cout << "\ncreating v3, a vector of 50,000,000 random ints:\n";
    auto before_v3 = time(0);
    cout << setw(21) << "time before v3:  " << before_v3 << '\n';
    vector<int> v3;
    for (int i(0); i < 50'000'000; ++i)
        v3.push_back(msrand() % 200'000'000);
    auto after_v3 = time(0);
    cout << setw(21) << "time after v3:  " << after_v3 << '\n';
    cout << setw(21) << "to create v3:  " << after_v3 - before_v3 << " seconds\n";

    cout << "\nperforming 1000 lookups in v3:\n";
    before_v3 = time(0);
    cout << setw(21) << "time before looks:  " << before_v3 << '\n';
    int num_found(0);
    for (int i(0); i < 1000; ++i) {
        int val(msrand() % 200'000'000);
        if (find(v3.begin(), v3.end(), val) != v3.end())
            ++num_found;
    }
    after_v3 = time(0);
    cout << setw(21) << "time after looks:  " << after_v3 << '\n';
    cout << setw(21) << "to perform looks:  " << after_v3 - before_v3 << " seconds\n";
    cout << setw(21) << "num matches found:  " << num_found << "\n";

/*****/
	/*
	Comments on the output:
	i) push_back function is very efficient. It inserted 50 mil integers in 34 seconds
	ii) linear search find() function took around 110 seconds to look up 1000 integers, a little 
	less than 0.1 second for each integer lookup which is very slow
	iii) around 20% of the time a randomly generated number is found in the vector. Assuming uniformly
	chosen numbers from 200 mil integers, the vector got a maximum of 25%(50/200) of the integers so the
	num of matches is upper bounded by 25% and we found an average of 20% match.
	*/

// (c)
/***** uncomment and complete the code below for part (c)
    copy and paste the code from (b) above.
    modify the code to sort vector v3, instead of creating
    a new vector, and report the time needed to do the sort.
    then, modify the code to use the binary_search algorithm
    rather than the find algorithm, and perform 10,000,000
    lookups rather than 1000; report the time needed for the
    lookups.
	*/

	cout << "\nsorting v3, a vector of 50,000,000 random ints:\n";
	auto before_sort_v3 = time(0);
	cout << setw(21) << "time before sort v3:  " << before_sort_v3 << '\n';
	sort(v3.begin(),v3.end());
	auto after_sort_v3 = time(0);
	cout << setw(21) << "time after sort v3:  " << after_sort_v3 << '\n';
	cout << setw(21) << "to sort v3:  " << after_sort_v3 - before_sort_v3 << " seconds\n";

	cout << "\nperforming 10'000'000 lookups in v3:\n";
	before_v3 = time(0);
	cout << setw(21) << "time before looks:  " << before_v3 << '\n';
	num_found = 0; //reset num_found
	for (int i(0); i < 10'000'000; ++i) {
	int val(msrand() % 200'000'000);
	if (binary_search(v3.begin(), v3.end(), val))
	++num_found;
	}
	after_v3 = time(0);
	cout << setw(21) << "time after looks:  " << after_v3 << '\n';
	cout << setw(21) << "to perform looks:  " << after_v3 - before_v3 << " seconds\n";
	cout << setw(21) << "num matches found:  " << num_found << "\n";

/*****/
/*
	Comments on the output:
	i) sorting the 50 mil sized vector took 120 seconds, which seems very efficient. I believe quicksort
	algorithm is used in this STL function, which runs in O(nlog(n)) on average
	ii) binary_search function took around 53 seconds to look up 10 mil integers, which is almost 20,000 
	times faster than the linear search per element look up. It makes sense as binary_search algorithm
	utilizes the sorted structure of the vector and runs in O(log(n)) whereas linear search runs in O(n)
	iii) Even in this case the fraction of number of matches is around 20%, similar to the previous case
	which is expected.
	*/

// (d)
/***** uncomment and complete the code below for part (d)
    copy and paste the code from (c) above.
    modify the code to create a set of 50,000,000 random ints,
    using the set<int>::insert member function rather than
    vector<int>::push_back, and report the time needed to
    create the set.
    then, modify the code to use the set<int>::find() member
    function rather than the find() algorithm, and to perform
    10,000,000 lookups rather than 1000; report the time
    needed to do the lookups.
	*/
	cout << "\ncreating s2, a set of 5,000,000 random ints:\n";
	auto before_s2 = time(0);
	cout << setw(21) << "time before s2:  " << before_s2 << '\n';
	set<int> s2;
	s2.insert(msrand() % 200'000'000);
	
	for (int i(0); i < 5'000'000; ++i)
	{
		s2.insert(msrand() % 200'000'000);
	}
	auto after_s2 = time(0);
	cout << setw(21) << "time after s2:  " << after_s2 << '\n';
	cout << setw(21) << "to create s2:  " << after_s2 - before_s2 << " seconds\n";

	cout << "\nperforming 10'000'000 lookups in s2:\n";
	before_s2 = time(0);
	cout << setw(21) << "time before looks:  " << before_s2 << '\n';
	num_found = 0;
	for (int i(0); i < 10'000'000; ++i) {
		int val(msrand() % 200'000'000);
		if (s2.find(val) != s2.end())
			++num_found;
	}
	after_s2 = time(0);
	cout << setw(21) << "time after looks:  " << after_s2 << '\n';
	cout << setw(21) << "to perform looks:  " << after_s2 - before_s2 << " seconds\n";
	cout << setw(21) << "num matches found:  " << num_found << "\n";

/*****/
	/*
	Comments on the output:
	i) For some reason, the program crashes in my Visual Studio for 50 mil ints. So I created a set of 
	5 mil ints. It took 34 seconds to load 5 mil ints. If ran for 50 mil ints, it might probably take 
	300 seconds, which is a little higher than vector initialization + sorting. May be because the set
	only keeps unique elements and thus some time is spent to check whether a new element already exists
	in the set
	ii) the set::find function possibly follows a binary search type algorithm as the set is already sorted
	It took 59 seconds to look up 10 mil numbers which is comparable to binary search in vector.
	iii) The fraction of the number of matches is around 2%, which makes sense as the set only got 5 mil
	integers among possible 200 mil integers, which aligns with the behavior observed in part b,c.

// (e)
/***** uncomment and complete the code below for part (e)
    copy and paste the code from (d) above.
    modify the code to create an unordered_set of 50,000,000
    random ints, and report the time needed to create the
    unordered_set.
    use unordered_set<int>::find (which has the same interface
    as set<int>::find) to perform 10,000,000 lookups; report
    the time needed to do the lookups.
	*/
	cout << "\ncreating s3, an unordered set of 50,000,000 random ints:\n";
	auto before_s3 = time(0);
	cout << setw(21) << "time before s3:  " << before_s3 << '\n';
	unordered_set<int> s3;
	s3.insert(msrand() % 200'000'000);

	for (int i(0); i < 10'000'000; ++i)
	{
		s3.insert(msrand() % 200'000'000);
	}
	auto after_s3 = time(0);
	cout << setw(21) << "time after s3:  " << after_s3 << '\n';
	cout << setw(21) << "to create s3:  " << after_s3 - before_s3 << " seconds\n";

	cout << "\nperforming 10'000'000 lookups in s3:\n";
	before_s3 = time(0);
	cout << setw(21) << "time before looks:  " << before_s3 << '\n';
	num_found = 0;
	for (int i(0); i < 10'000'000; ++i) {
	int val(msrand() % 200'000'000);
	if (s3.find(val) != s3.end())
	++num_found;
	}
	after_s3 = time(0);
	cout << setw(21) << "time after looks:  " << after_s3 << '\n';
	cout << setw(21) << "to perform looks:  " << after_s3 - before_s3 << " seconds\n";
	cout << setw(21) << "num matches found:  " << num_found << "\n";

/*****/
	/*
	Comments on the output:
	i) For same reason as part d), I created an ordered set of 10 mil ints. It took 111 seconds to load
	10 mil ints. 
	ii)The unordered set got created in 111 seconds which is a little less efficient than
	set::insert for ordered set
	ii) the unordered_set::find function managed to finish the look up in 30 seconds which is 
	even faster than ordered set, vector binary search. The look up in ordered set is O(1) which results 
	into such faster lookups
	iii) The fraction of the number of matches is around 4%, which makes sense as the set only got 10 mil
	integers among possible 200 mil integers, which aligns with the behavior observed in part b,c,d.
*/

// (f)
/* uncomment and test this code:*/
    vector<double> dv1(v1.size());
    cout << "initially:\n";
    cout << setw(8) << "dv1: " << "size: " << setw(4) << dv1.size() << ":  ";
    for (auto& el : dv1) cout << el << ' '; cout << '\n';
    for (int i(0); i < v1.size(); ++i)
        dv1[i] = sqrt(v1[i]);
    cout << "after filled with square roots:\n";
    cout << setw(8) << "dv1: " << "size: " << setw(4) << dv1.size() << ":  ";
    for (auto& el : dv1) cout << el << ' '; cout << '\n';
/**/

//  write the rest of the code for part (f) here
	dv1.assign(dv1.size(),0.0);	// assign dv1.size() number of 0.0s
	for (auto& el : dv1) cout << el << ' '; cout << '\n';
	transform(v1.begin(), v1.end(), dv1.begin(), my_sqrt);
	cout << "after filled with square roots using transform:\n";
	for (auto& el : dv1) cout << el << ' '; cout << '\n';
// (g)
//  write your code for part (g) here, except for add_rand() defined above main()
	vector<double> dv2(dv1);
	cout << setw(8) << "dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';

	for_each(dv2.begin(), dv2.end(), add_rand);
	cout << setw(8) << "modified_dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';
// (h)
//  write your code for part (h) here
	random_shuffle(dv2.begin(), dv2.end());
	cout << setw(8) << "shuffled_dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';

	reverse(dv2.begin(), dv2.end());
	cout << setw(8) << "reversed_dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';

	sort(dv2.begin(), dv2.end());
	cout << setw(8) << "sorted_dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';

	auto low_2 = lower_bound(dv2.begin(),dv2.end(),2.0);
	auto low_3 = lower_bound(dv2.begin(), dv2.end(),3.0);
	cout << "lower bound of 2.0 at location:  " << low_2 - dv2.begin() << "\n";
	cout << "lower bound of 3.0 at location:  " << low_3 - dv2.begin() << "\n";

	for (auto it = low_2;it != low_3;++it) cout << *it << "  ";
	cout << '\n' << '\n';

	//Above code runs as expected
// (i)
//  write your code for part (i) here

	//my_exp defined above main. Visual Studio 2017 won't take cast_ exp
	transform(dv2.begin(), dv2.end(), dv2.begin(), my_exp);
	cout << setw(8) << "exponentiated_dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';

	//my_ceil defined above main. Visual Studio 2017 won't take cast_ ceil
	transform(dv2.begin(), dv2.end(), dv2.begin(), my_ceil);
	cout << setw(8) << "ceiled_dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';

	//my_log defined above main. Visual Studio 2017 won't take cast_ log
	transform(dv2.begin(), dv2.end(), dv2.begin(), my_log);
	cout << setw(8) << "log-ed_dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';

	//Above code runs as expected
// (j)
//  write your code for part (j) here

	vector<double>dv3(dv2.size());

	transform(dv1.begin(), dv1.end(), dv2.begin(), dv3.begin(), my_pow);

	cout << setw(8) << "current dv1: " << "size: " << setw(4) << dv1.size() << ":  ";
	for (auto& el : dv1) cout << el << ' '; cout << '\n' << '\n';
	cout << setw(8) << "current dv2: " << "size: " << setw(4) << dv2.size() << ":  ";
	for (auto& el : dv2) cout << el << ' '; cout << '\n' << '\n';

	cout << setw(8) << "dv3: " << "size: " << setw(4) << dv3.size() << ":  ";
	for (auto& el : dv3) cout << el << ' '; cout << '\n' << '\n';

	//Above code runs as expected
// (k)
//  write your code for part (k) here
	vector<int> v2(v1);
	auto res = equal(v1.begin(), v1.end(), v2.begin(), v2.end());
	cout << "Result of the equal algorithm: " << res << '\n';

	random_shuffle(v1.begin(), v1.end());
	res = equal(v1.begin(), v1.end(), v2.begin(), v2.end());
	cout << "Result of the equal algorithm after random shuffling: " << res << '\n';

	auto is_it_permuted = is_permutation(v1.begin(), v1.end(), v2.begin(), v2.end());
	cout << "Result of the is_permutation algorithm after random shuffling: " << is_it_permuted << '\n';

	//The output of the functions are as expected
// (l)
//  write your code for part (l) here
	int count_3 = count(v1.cbegin(), v1.cend(), 3);
	cout << "count of 3 in v1 is : " << count_3 << '\n';
	auto min_max = minmax_element(v1.begin(), v1.end());
	cout << "min value is : " << *min_max.first << ", max value is : " << *min_max.second << '\n';
	auto find_9 = find(v1.begin(), v1.end(), 9);
	for (auto it = find_9;it != v1.end();++it) cout << *it << "  ";
	cout << '\n' << '\n';

	//result of the above code is as expected
// (m)
//  write your code for part (m) here
	cout << setw(8) << "v1: " << "size: " << setw(4) << v1.size() << ":  ";
	for (auto& el : v1) cout << el << ' '; cout << '\n' << '\n';

	v1.resize(v1.size() / 2);

	cout << setw(8) << "halved_v1: " << "size: " << setw(4) << v1.size() << ":  ";
	for (auto& el : v1) cout << el << ' '; cout << '\n' << '\n';
	//Looks like the resize function discards the second half and keeps the first half of the vector
// (n)
//  write your code for part (n) here
	set<int>s1;
	set<int, greater<int>>s_2; //s2 already defined in part (d)

	s1.insert(v1.begin(), v1.end());
	cout << setw(8) << "copied s1: " << "size: " << setw(4) << s1.size() << ":  ";
	for (auto& el : s1) cout << el << ' '; cout << '\n' << '\n';

	s_2.insert(v1.begin(), v1.end());
	cout << setw(8) << "copied s2: " << "size: " << setw(4) << s_2.size() << ":  ";
	for (auto& el : s_2) cout << el << ' '; cout << '\n' << '\n';
	//As shown in the output the ordering of elements in s1, s_2 are in reverse direction
// (o)
//  write your code for part (o) here
	mt19937 mte;
	normal_distribution<> nd(0.0, 2.0);
	map<int, int> buckets;
	for (int i(0); i < 1000000; ++i) {
		buckets[int(round(nd(mte)))] += 1;
	}
	for (auto& el : buckets) cout << el.first << "\t"
		<< el.second << '\n';
	/*
	below is the output which displays the normal behaviour of the drawn samples with 
	maximum draws around the mean 0.0
-10     1
-9      5
-8      88
-7      492
-6      2456
-5      9003
-4      27876
-3      65316
-2      121159
-1      174771
0       197498
1       174735
2       120718
3       65743
4       27945
5       9259
6       2382
7       474
8       72
9       7
	*/

// (p)
//  write your code for part (p) here

	//mt19937 mte;
	normal_distribution<> snd;	//generate from std normal
	buckets.clear();	//need to clear the bucket before I can reuse
	//map<int, int> buckets;
	for (int i(0); i < 1000000; ++i) {
		buckets[int(round(snd(mte)))] += 1;
	}
	int cumulative_count = 0;
	cout << "generating histogram for standard normal \n";
	for (auto& el : buckets) {
		cumulative_count += el.second;
		cout << el.first << "\t"
			<< el.second << "\t" << cumulative_count/1000000.0 << '\n';
	}
	// keeping a cumulative count of the samples in each bucket and dividing by total samples drawn
	// should give the CDF. The result makes sense as there is very small probability of the samples 
	// to be beyond [-3,3] as 99% of the CDF is within the interval
// (q)
//  write your code for part (q) here

//mt19937 mte;
	uniform_int_distribution<> U(1,10);	//generate from  uniform [1,10]
	buckets.clear();	//need to clear the bucket before I can reuse
						//map<int, int> buckets;
	for (int i(0); i < 1000000; ++i) {
		buckets[int(round(U(mte)))] += 1;
	}
	cumulative_count = 0;
	cout << "generating histogram for discrete uniform \n";
	for (auto& el : buckets) {
		cumulative_count += el.second;
		cout << el.first << "\t"
			<< el.second << "\t" << cumulative_count / 1000000.0 << '\n';
	}
	//The output of the result makes sense as each of the buckets got nearly equal marginal probability
	//and the CDF is a straight line wrt the bin values.
	/*
1       100248  0.100248
2       99825   0.200073
3       100355  0.300428
4       100080  0.400508
5       99425   0.499933
6       99878   0.599811
7       99582   0.699393
8       100185  0.799578
9       99924   0.899502
10      100498  1
	*/
}
