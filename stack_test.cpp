#include "Stack.hpp"
#include <stack>
#include <unistd.h>

void stack_test(){
	std::cout << "---------------------" << std::endl;
	std::cout << "     STACK TESTS     " << std::endl;
	std::cout << "---------------------" << std::endl << std::endl;

	std::stack<char> std_stack_char_one;
	ft::stack<char> ft_stack_char_one;

	std_stack_char_one.push('a');
	std_stack_char_one.push('b');
	std_stack_char_one.push('c');
	ft_stack_char_one.push('a');
	ft_stack_char_one.push('b');
	ft_stack_char_one.push('c');

	std::cout << "Std stack top: " << std_stack_char_one.top() << std::endl;
	std::cout << "Ft stack top: " << ft_stack_char_one.top() << std::endl;
	std::cout << std::endl;

	std_stack_char_one.push('d');
	ft_stack_char_one.push('d');

	std::stack<char> std_stack_char_two(std_stack_char_one);
	ft::stack<char> ft_stack_char_two(ft_stack_char_one);
	std::cout << "Std stack top: " << std_stack_char_two.top() << std::endl;
	std::cout << "Ft stack top: " << ft_stack_char_two.top() << std::endl;
	std::cout << std::endl;

	std::cout << "Std is empty: " << std_stack_char_two.empty() << std::endl;
	std::cout << "Ft is empty: " << ft_stack_char_two.empty() << std::endl;
	std::cout << std::endl;

	std::cout << "Std stack size: " << std_stack_char_two.size() << std::endl;
	std::cout << "Ft stack size: " << ft_stack_char_two.size() << std::endl;
	std::cout << std::endl;

	std_stack_char_one.pop();
	ft_stack_char_one.pop();
	std::cout << "Std stack top after pop: " << std_stack_char_one.top() << std::endl;
	std::cout << "Ft stack top after pop: " << ft_stack_char_one.top() << std::endl;
	std::cout << std::endl;

	std::cout << "Std stack ==: " << (std_stack_char_one == std_stack_char_two) << std::endl;
	std::cout << "Ft stack ==: " << (ft_stack_char_one == ft_stack_char_two) << std::endl;
	std::cout << std::endl;

	std::cout << "Std stack !=: " << (std_stack_char_one != std_stack_char_two) << std::endl;
	std::cout << "Ft stack !=: " << (ft_stack_char_one != ft_stack_char_two) << std::endl;
	std::cout << std::endl;

	std::cout << "Std stack <: " << (std_stack_char_one < std_stack_char_two) << std::endl;
	std::cout << "Ft stack <: " << (ft_stack_char_one < ft_stack_char_two) << std::endl;
	std::cout << std::endl;

	std::cout << "Std stack <=: " << (std_stack_char_one <= std_stack_char_two) << std::endl;
	std::cout << "Ft stack <=: " << (ft_stack_char_one <= ft_stack_char_two) << std::endl;
	std::cout << std::endl;

	std::cout << "Std stack >: " << (std_stack_char_one > std_stack_char_two) << std::endl;
	std::cout << "Ft stack >: " << (ft_stack_char_one > ft_stack_char_two) << std::endl;
	std::cout << std::endl;

	std::cout << "Std stack >=: " << (std_stack_char_one >= std_stack_char_two) << std::endl;
	std::cout << "Ft stack >=: " << (ft_stack_char_one >= ft_stack_char_two) << std::endl;
	std::cout << std::endl;
}