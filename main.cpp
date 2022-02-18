#include "Stack.hpp"
#include "Vector.hpp"
#include "Map.hpp"
#include "test.hpp"
#include <stack>
#include <vector>
#include <map>
#include <vector>

// template <class T, class V>
// std::vector<int> insert_test_3(std::map<T, V> mp) {
//     std::vector<int> v;
//     typename std::map<T, V>::iterator it = mp.end();
//     // g_start1 = timer();
//     for (int i = 0, j = 0; i < 50 * 1000; ++i, ++j) {
//         mp.insert(it, std::make_pair(i, j));
//     }
//     // g_end1 = timer();
//     typename std::map<T, V>::iterator it2 = mp.begin();
//     for (; it2 != mp.end(); ++it2) {
//         v.push_back(it2->first);
//         v.push_back(it2->second);
//     }
//     return v;
// }

// template <class T, class V>
// std::vector<int> insert_test_3(ft::map<T, V> mp) {
//     std::vector<int> v;
//     typename ft::map<T, V>::iterator it = mp.end();
//     // g_start2 = timer();
//     for (int i = 0, j = 0; i < 50 * 1000; ++i, ++j) {
//         mp.insert(it, ft::make_pair(i, j));
//     }
//     // g_end2 = timer();
//     typename ft::map<T, V>::iterator it2 = mp.begin();
//     for (; it2 != mp.end(); ++it2) {
//         v.push_back(it2->first);
//         v.push_back(it2->second);
//     }
//     return v;
// }

template <class T, class V>
std::vector<int> erase_test_2(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 0; i < 30 * 1000; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    typename std::map<T, V>::iterator it = mp.begin();
    v.push_back(it->first);
    mp.erase(it);
    v.push_back(mp.size());
    it = mp.begin();
    mp.erase(++it);
    v.push_back(mp.size());
    it = mp.begin();
    v.push_back(it->first);
    typename std::map<T, V>::iterator it4 = mp.begin();
    // g_start1 = timer();
    for (; it4 != mp.end(); it4 = mp.begin())
        mp.erase(it4);
    // g_end1 = timer();
    v.push_back(mp.size());
    std::map<int, int> mp2;
    for (int i = 0, j = 0; i < 10 ; ++i, ++j)
        mp2.insert(std::make_pair(i, j));
    typename std::map<T, V>::iterator ittest = mp2.begin();
    for (int i = 0; i < 2; ++i) ittest++;
    mp2.erase(ittest);
    ittest = mp2.begin();
    for (int i = 0; i < 5; ++i) ittest++;
    mp2.erase(ittest);
    typename std::map<T, V>::iterator it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> erase_test_2(ft::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 0; i < 30 * 1; ++i, ++j)
        mp.insert(ft::make_pair(i, j));
    typename ft::map<T, V>::iterator it = mp.begin();
    v.push_back(it->first);
    mp.erase(it);
    v.push_back(mp.size());
    it = mp.begin();
    mp.erase(++it);
    // v.push_back(mp.size());
    // it = mp.begin();
    // v.push_back(it->first);
    // typename ft::map<T, V>::iterator it4 = mp.begin();
    // // g_start2 = timer();
    // for (; it4 != mp.end(); it4 = mp.begin())
    //     mp.erase(it4);
    // // g_end2 = timer();
    // v.push_back(mp.size());
    // ft::map<int, int> mp2;
    // for (int i = 0, j = 0; i < 10 ; ++i, ++j)
    //     mp2.insert(ft::make_pair(i, j));
    // typename ft::map<T, V>::iterator ittest = mp2.begin();
    // for (int i = 0; i < 2; ++i) ittest++;
    // mp2.erase(ittest);
    // ittest = mp2.begin();
    // for (int i = 0; i < 5; ++i) ittest++;
    // mp2.erase(ittest);
    // typename ft::map<T, V>::iterator it3 = mp2.begin();
    // for (; it3 != mp2.end(); ++it3) {
    //     v.push_back(it3->first);
    //     v.push_back(it3->second);
    // }
    return v;
}

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

int main()
{
    return(run_map_unit_test<int, int>("erase(InputIt)", erase_test_2, erase_test_2));
    // return 0;
}
    
    

