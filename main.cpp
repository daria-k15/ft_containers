#include "Stack.hpp"
#include "Vector.hpp"
#include "Map.hpp"
#include "test.hpp"
#include <stack>
#include <vector>
#include <map>
#include <vector>

#define _ratio 10000

class MapBoolTest {
public:
	std::map<int, int> m1, m2, m3, m4;
	std::map<std::string, std::string> m5, m6, m7, m8, m9;
	ft::map<int, int> mp1, mp2, mp3, mp4;
	ft::map<std::string, std::string> mp5, mp6, mp7, mp8, mp9;

	MapBoolTest() {
		m1.insert(std::make_pair(2, 3)); mp1.insert(ft::make_pair(2, 3));
		m2.insert(std::make_pair(3, 3)); mp2.insert(ft::make_pair(3, 3));
		m3.insert(std::make_pair(3, 4)); mp3.insert(ft::make_pair(3, 4));
		m4.insert(std::make_pair(4, 4)); mp4.insert(ft::make_pair(4, 4));
		m4.insert(std::make_pair(4, 5)); mp4.insert(ft::make_pair(4, 5));
		m5.insert(std::make_pair("123", "123")); mp5.insert(ft::make_pair("123", "123"));
		m6.insert(std::make_pair("123", "124")); mp6.insert(ft::make_pair("123", "124"));
		m7.insert(std::make_pair("124", "123")); mp7.insert(ft::make_pair("124", "123"));
		m8.insert(std::make_pair("12", "123")); mp8.insert(ft::make_pair("12", "123"));
		m9.insert(std::make_pair("123", "12")); mp9.insert(ft::make_pair("123", "12"));
	}
};


template <class T, class V>
int run_map_unit_test(std::string test_name, std::vector<int> (func1)(std::map<T, V>), std::vector<int> (func2)(ft::map<T, V>)) {
    int    result;
    int    leaks;
	time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::map<int, int> map;
	ft::map<int, int> my_map;

	// printElement(test_name);
	res1 = func1(map);
	res2 = func2(my_map);
	if (res1 == res2) {
	    std::cout << "OK" << std::endl;
	    result = 0;
	}
	else {
	     std::cout << "KO" << std::endl;
	    result = 1;
	}
	return result;
}

int run_bool_unit_test(std::string test_name, bool (func1)()) {
    int ret = 0;
    time_t t1;
    time_t t2;
    bool res;

	// printElement(test_name);
	res = func1();
	if (res) {
	    std::cout << "OK" << std::endl;
	    ret = 0;
	}
	else {
	     std::cout << "KO" << std::endl;
	    ret = 1;
	}
	// t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	// (t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	// (t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	// cout << endl;

    return ret;
}

template <class T, class V>
        std::vector<int> upper_bound_test(std::map<T, V> mp) {
    std::vector<int> v;
    std::map<int, int, std::greater<int> > mp2;
    mp.insert(std::make_pair(10, 10));
    mp2.insert(std::make_pair(10, 10));
    if (mp.upper_bound(11) == mp.end())
        v.push_back(1);
    if (mp2.upper_bound(1) == mp2.end())
        v.push_back(1);
    mp.insert(std::make_pair(20, 20));
    mp.insert(std::make_pair(30, 30));
    mp.insert(std::make_pair(40, 40));
    mp.insert(std::make_pair(50, 50));
    mp.insert(std::make_pair(60, 60));
    mp2.insert(std::make_pair(20, 20));
    mp2.insert(std::make_pair(30, 30));
    mp2.insert(std::make_pair(40, 40));
    mp2.insert(std::make_pair(50, 50));
    mp2.insert(std::make_pair(60, 60));
    std::map<int, int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = mp.upper_bound(i);
        v.push_back(it->first);
    }
    for (int i = 11; i < 70; i += 10) {
        it = mp2.upper_bound(i);
        v.push_back(it->first);
    }
    std::map<int, int> mp3;
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp3.insert(std::make_pair(i, j));
    }
    std::map<int, int> mp4;
    mp.insert(std::make_pair(-10, 10));
    mp.insert(std::make_pair(-20, 20));
    v.push_back((--mp.upper_bound(0))->first);
    // g_start1 = timer();
    mp3.upper_bound(49 * _ratio);
    // g_end1 = timer();
    return v;
}

template <class T, class V, class C, class A>
void allocator_test(ft::map<T, V, C, A> mp) {

    for (int i = 0, j = 10; i < 10; ++i, ++j) {
        mp.insert(ft::make_pair(i, j));
    }
}

int main() {

    exit(run_map_allocator_unit_test<int, int, std::less<int>, Alloc<_pair<const int, int> > >("using allocator", allocator_test));
}