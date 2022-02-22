#include "Stack.hpp"
#include <stack>
#include <iostream>
#include <vector>
#include <unistd.h>
#define _ratio 10000

template <class T>
int run_stack_unit_test(std::string test_name, std::vector<int> (func1)(std::stack<T>), std::vector<int> (func2)(ft::stack<T>)) {
    int    result;
    int    leaks;
    time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::stack<int> stack;
	ft::stack<int> my_stack;

	// printElement(test_name);
	res1 = func1(stack);
	res2 = func2(my_stack);
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

	return !(!result && !leaks);;
}

template <class T>
std::vector<int> constructor_test(std::stack<T> stk) {
	std::vector<int> v;
	std::deque<int> deque;
	for (int i = 0; i < 100 * _ratio; ++i)
		deque.push_back(i);
	for (int i = 100 * _ratio; i < 200 * _ratio; ++i)
		stk.push(i);
	// g_start1 = timer();
	std::stack<int> stack(deque);
	std::stack<int> stack2(stk);
	std::stack<int> stack3;
	stack3 = stack2;
	// g_end1 = timer();
	while (stack.size() > 0) {
		v.push_back(stack.top());
		stack.pop();
	}
	while (stack2.size() > 0) {
		v.push_back(stack2.top());
		stack2.pop();
	}
	return v;
}

template <class T>
std::vector<int> constructor_test(ft::stack<T> stk) {
	std::vector<int> v;
	ft::vector<int> deque;
	for (int i = 0; i < 100 * _ratio; ++i)
		deque.push_back(i);
	for (int i = 100 * _ratio; i < 200 * _ratio; ++i)
		stk.push(i);
	// g_start2 = timer();
	ft::stack<int> stack(deque);
	ft::stack<int> stack2(stk);
	ft::stack<int> stack3;
	stack3 = stack2;
	// g_end2 = timer();
	while (stack.size() > 0) {
		v.push_back(stack.top());
		stack.pop();
	}
	while (stack2.size() > 0) {
		v.push_back(stack2.top());
		stack2.pop();
	}
	return v;
}

int main() {

	exit(run_stack_unit_test<int>("constructor", constructor_test, constructor_test));
}