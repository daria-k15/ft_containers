#include "Stack.hpp"
#include "Vector.hpp"
#include "Map.hpp"
#include "test.hpp"
#include <stack>
#include <vector>
#include <map>
#include <vector>
#include <unistd.h>
#define _ratio 10000

const std::string GREEN = "\x1B[1;32m";
const std::string REDD = "\x1B[1;31m";
const std::string YELLOW = "\x1B[1;33m";
const std::string WHITE = "\x1B[1;39m";
const std::string RESET = "\033[0m";



std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	} catch (...) { pclose(pipe); throw; }
	pclose(pipe);
	return result;
}

std::string get_leak_string(std::string s) {
	std::string tmp;
	int idx = s.find("total leaked bytes");
	for (; s[idx] != '\n' ; --idx) {}
	int edx = idx + 1;
	for (; s[edx] != '\n' ; ++edx) {}

	return s.substr(++idx, edx - 101);
}

int leaks_test(pid_t pid) {
	std::string a = "leaks ";
	a += std::to_string(static_cast<int>(pid));
	usleep(50);
	std::string s = get_leak_string(exec(a.c_str()));

	if (s.find("0 leaks for 0 total leaked bytes") != std::string::npos) {
		std::cout << "CLEAR" << std::endl;
		return (0);
	}
	else {
	    std::cout << "LEAKS" << std::endl;
	    return (1);
	}
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
	// t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	// (t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	// (t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	leaks = leaks_test(getpid());
	// cout << endl;

	return !(!result && !leaks);
}

template <class T, class V>
std::vector<int> assign_overload_test(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    std::map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(std::make_pair(i, j));
    // g_start1 = timer();
    mp2 = mp;
    // g_end1 = timer();
    typename std::map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}

template <class T, class V>
std::vector<int> assign_overload_test(ft::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(ft::make_pair(i, j));
    ft::map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(ft::make_pair(i, j));
    // g_start2 = timer();
    mp2 = mp;
    // g_end2 = timer();
    typename ft::map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}

int main() {
    exit(run_map_unit_test<int, int>("assign overload", assign_overload_test, assign_overload_test));
}