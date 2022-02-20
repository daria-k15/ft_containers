#include "Set.hpp"
#include <vector>
#include <set>

#define _ratio 10000

template <class T>
int run_set_unit_test(std::string test_name, std::vector<int> (func1)(std::set<T>), std::vector<int> (func2)(ft::set<T>)) {
    int    result;
    int    leaks;
    time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::set<int> set;
	ft::set<int> my_set;

	// printElement(test_name);
	res1 = func1(set);
	res2 = func2(my_set);
	if (res1 == res2) {
        std::cout << "OK" << std::endl;
	    result = 0;
	}
	else {
        std::cout << "KO" << std::endl;
	    result = 1;
	}
	// t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	// (t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	// (t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	// leaks = leaks_test(getpid());
	// cout << endl;

	return result;
}

template <class T>
std::vector<int> insert_test(std::set<T> st) {
    std::vector<int> v;
    std::pair<std::set<int>::iterator , bool> pair = st.insert(7);
    std::set<int>::iterator it = st.begin();
    v.push_back(*it);

    v.push_back(*(pair.first));
    v.push_back(pair.second);
    st.insert(9);
    std::pair<std::set<int>::iterator , bool> pair2 = st.insert(9);
    std::set<int>::iterator it2 = pair.first;
    v.push_back(*it2);
    v.push_back(*(pair2.first));
    v.push_back(pair2.second);
    // g_start1 = timer();
    for (int i = 0; i < 50 * _ratio; ++i) {
        st.insert(i);
    }
    // g_end1 = timer();
    typename std::set<T>::iterator it3 = st.begin();
    for (; it3 != st.end(); ++it3) {
        v.push_back(*it3);
    }
    v.push_back(st.size());
    return v;
}

template <class T>
std::vector<int> insert_test(ft::set<T> st) {
    std::vector<int> v;
    ft::pair<ft::set<int>::iterator , bool> pair = st.insert(7);
    ft::set<int>::iterator it = st.begin();
    v.push_back(*it);

    v.push_back(*(pair.first));
    v.push_back(pair.second);
    st.insert(9);
    ft::pair<ft::set<int>::iterator , bool> pair2 = st.insert(9);
    ft::set<int>::iterator it2 = pair.first;
    v.push_back(*it2);
    v.push_back(*(pair2.first));
    v.push_back(pair2.second);
    // g_start2 = timer();
    for (int i = 0; i < 50 * _ratio; ++i) {
        st.insert(i);
    }
    // g_end2 = timer();
    typename ft::set<T>::iterator it3 = st.begin();
    for (; it3 != st.end(); ++it3) {
        v.push_back(*it3);
    }
    v.push_back(st.size());
    return v;
}

int main() {

    exit(run_set_unit_test<int>("insert(value)", insert_test, insert_test));
}