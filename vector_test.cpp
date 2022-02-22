#include "Vector.hpp"
#include <vector>
#include <iostream>
// #include "tests.hpp"

template <class T>
void print_ft_vec(const ft::vector<T> & vec){
	typename ft::vector<T>::const_iterator it = vec.begin();
	typename ft::vector<T>::const_iterator ite = vec.end();
	std::cout << "FT vector" << std::endl;
	std::cout << "Size " << vec.size() << std::endl;
	std::cout << "Capacity " << vec.capacity() << std::endl;
	while (it != ite){
		std::cout << *it++ << std::endl;
	}
	std::cout << std::endl;
}

template <class T>
void print_std_vec(const std::vector<T> & vec){
	typename std::vector<T>::const_iterator it = vec.begin();
	typename std::vector<T>::const_iterator ite = vec.end();
	std::cout << "STD vector" << std::endl;
	std::cout << "Size " << vec.size() << std::endl;
	std::cout << "Capacity " << vec.capacity() << std::endl;
	while (it != ite){
		std::cout << *it++ << std::endl;
	}
	std::cout << std::endl;
}

void vector_test(){
	std::cout << "---------------------" << std::endl;
	std::cout << "     VECTOR TESTS    " << std::endl;
	std::cout << "---------------------" << std::endl << std::endl;

	ft::vector<int> ft_vec;
	std::vector<int> std_vec;

	ft_vec.push_back(10);
	ft_vec.push_back(20);
	ft_vec.push_back(30);
	std_vec.push_back(10);
	std_vec.push_back(20);
	std_vec.push_back(30);

	// std::cout << "Empty vector and push_back " << std::endl;
	// print_ft_vec(ft_vec);
	// print_std_vec(std_vec);

	// ft_vec.pop_back();
	// std_vec.pop_back();
	// std::cout << "After pop_back" << std::endl;
	// print_ft_vec(ft_vec);
	// print_std_vec(std_vec);

	// ft::vector<int> ft_vec2(5, -3);
	// std::vector<int> std_vec2(5, -3);
	// std::cout << "Vector constructor with 5 copies of -3" << std::endl;
	// print_ft_vec(ft_vec2);
	// print_std_vec(std_vec2);

	// ft::vector<int> ft_vec3(ft_vec.begin(), --ft_vec.end());
	// std::vector<int> std_vec3(std_vec.begin(), --std_vec.end());
	// std::cout << "Constructor with iterators" << std::endl;
	// print_ft_vec(ft_vec3);
	// print_std_vec(std_vec3);

	// ft::vector<int> ft_vec4(ft_vec);
	// std::vector<int> std_vec4(std_vec);
	// std::cout << "Copy constructor" << std::endl;
	// print_ft_vec(ft_vec4);
	// print_std_vec(std_vec4);

	// ft_vec4.clear();
	// std_vec4.clear();
	// std::cout << "After clear fuction" << std::endl;
	// print_ft_vec(ft_vec4);
	// print_std_vec(std_vec4);

	// ft_vec4 = ft_vec3;
	// std_vec4 = std_vec3;
	// std::cout << "Operator =" << std::endl;
	// print_ft_vec(ft_vec4);
	// print_std_vec(std_vec4);

	// std::cout << "Max size" << std::endl;
	// std::cout << "FT vector\t" << ft_vec.max_size() << std::endl;
	// std::cout << "STD vector\t" << std_vec.max_size() << std::endl << std::endl;

	// ft_vec2.resize(2);
	// std_vec2.resize(2);
	// std::cout << "After resize function" << std::endl;
	// print_ft_vec(ft_vec2);
	// print_std_vec(std_vec2);

	// std::cout << "Empty function on non-empty vector" << std::endl;
	// std::cout << "FT vector\t" << ft_vec.empty() << std::endl;
	// std::cout << "STD vector\t" << std_vec.empty() << std::endl << std::endl;

	// ft_vec2.clear();
	// std_vec2.clear();
	// std::cout << "Empty function on empty vector" << std::endl;
	// std::cout << "FT vector\t" << ft_vec2.empty() << std::endl;
	// std::cout << "STD vector\t" << ft_vec2.empty() << std::endl << std::endl;

	// ft_vec2.reserve(20);
	// std_vec2.reserve(20);
	// std::cout << "After reserve function" << std::endl;
	// print_ft_vec(ft_vec2);
	// print_std_vec(std_vec2);

	// std::cout << "Operator[]" << std::endl;
	// std::cout << "FT vector[1]\t" << ft_vec[1] << std::endl;
	// std::cout << "STD vector[1]\t" << std_vec[1] << std::endl << std::endl;

	// try{
	// 	std::cout << "Operator at with index out of bound" << std::endl;
	// 	std::cout << "FT vector at 7\t" << ft_vec.at(7) << std::endl;
	// }
	// catch (std::out_of_range ex){
	// 	std::cout << "An exception was caught. It's message: ";
	// 	std::cout << ex.what() << std::endl;
	// }
	// try{
	// 	std::cout << "STD vector at 7\t" << std_vec.at(7) << std::endl << std::endl;
	// }
	// catch (std::out_of_range ex){
	// 	std::cout << "An exception was caught. It's message: ";
	// 	std::cout << ex.what() << std::endl;
	// }

	// try{
	// 	std::cout << std::endl << "Operator at with valid index" << std::endl;
	// 	std::cout << "FT vector at 0\t" << ft_vec.at(0) << std::endl;
	// }
	// catch (std::out_of_range ex){
	// 	std::cout << "An exception was caught. It's message: ";
	// 	std::cout << ex.what() << std::endl;
	// }
	// try{
	// 	std::cout << "STD vector at 0\t" << std_vec.at(0) << std::endl << std::endl;
	// }
	// catch (std::out_of_range ex){
	// 	std::cout << "An exception was caught. It's message: ";
	// 	std::cout << ex.what() << std::endl;
	// }

	// std::cout << "Front function" << std::endl;
	// std::cout << "FT vector\t" << ft_vec.front() << std::endl;
	// std::cout << "STD vector\t" << std_vec.front() << std::endl << std::endl;

	// std::cout << "Back function" << std::endl;
	// std::cout << "FT vector\t" << ft_vec.back() << std::endl;
	// std::cout << "STD vector\t" << std_vec.back() << std::endl << std::endl;

	// ft_vec.insert(++ft_vec.begin(), 7);
	// std_vec.insert(++std_vec.begin(), 7);
	// std::cout << "After inserting single element (7) to iterator position" << std::endl;
	// print_ft_vec(ft_vec);
	// print_std_vec(std_vec);

	// ft_vec.insert(++ft_vec.begin(),3, -2);
	// std_vec.insert(++std_vec.begin(), 3, -2);
	// std::cout << "After inserting n (3) elements (-2) to iterator position" << std::endl;
	// print_ft_vec(ft_vec);
	// print_std_vec(std_vec);

	// ft_vec.insert(--ft_vec.end(),ft_vec3.begin(), ft_vec3.end());
	// std_vec.insert(--std_vec.end(), std_vec3.begin(), std_vec3.end());
	// std::cout << "After inserting range specified by iterators to iterator position" << std::endl;
	// print_ft_vec(ft_vec);
	// print_std_vec(std_vec);

	// ft_vec2.assign(++ft_vec.rbegin(), --ft_vec.rend());
	// std_vec2.assign(++std_vec.rbegin(), --std_vec.rend());
	// std::cout << "After assign with range specified by iterators" << std::endl;
	// print_ft_vec(ft_vec2);
	// print_std_vec(std_vec2);

	// ft_vec3.assign(5, 9);
	// std_vec3.assign(5, 9);
	// std::cout << "After assign with n (5) elements (9)" << std::endl;
	// print_ft_vec(ft_vec3);
	// print_std_vec(std_vec3);

	// ft_vec2.erase(++ft_vec2.begin());
	// std_vec2.erase(++std_vec2.begin());
	// std::cout << "After erase single element specified by iterator" << std::endl;
	// print_ft_vec(ft_vec2);
	// print_std_vec(std_vec2);

	// ft_vec3.erase(++ft_vec3.begin(), --ft_vec3.end());
	// std_vec3.erase(++std_vec3.begin(), --std_vec3.end());
	// std::cout << "After erase range of elements specified by iterators" << std::endl;
	// print_ft_vec(ft_vec3);
	// print_std_vec(std_vec3);

	// ft_vec3.swap(ft_vec);
	// std_vec3.swap(std_vec);
	// std::cout << "After swap" << std::endl;
	// print_ft_vec(ft_vec3);
	// print_std_vec(std_vec3);

	// ft_vec.clear();
	// std_vec.clear();
	// std::cout << "After clear" << std::endl;
	// print_ft_vec(ft_vec);
	// print_std_vec(std_vec);

	// std::cout << std::endl << "== operator" << std::endl;
	// std::cout << "FT Vector\t\t" << (ft_vec == ft_vec3) << std::endl;
	// std::cout << "STD Vector\t\t" << (std_vec == std_vec3) << std::endl;

	// std::cout << std::endl << "!= operator" << std::endl;
	// std::cout << "FT Vector\t\t" << (ft_vec != ft_vec3) << std::endl;
	// std::cout << "STD Vector\t\t" << (std_vec != std_vec3) << std::endl;

	// std::cout << std::endl << "< operator" << std::endl;
	// std::cout << "FT Vector\t\t" << (ft_vec < ft_vec3) << std::endl;
	// std::cout << "STD Vector\t\t" << (std_vec < std_vec3) << std::endl;

	// std::cout << std::endl << "<= operator" << std::endl;
	// std::cout << "FT Vector\t\t" << (ft_vec <= ft_vec3) << std::endl;
	// std::cout << "STD Vector\t\t" << (std_vec <= std_vec3) << std::endl;

	// std::cout << std::endl << "> operator" << std::endl;
	// std::cout << "FT Vector\t\t" << (ft_vec > ft_vec3) << std::endl;
	// std::cout << "STD Vector\t\t" << (std_vec > std_vec3) << std::endl;

	// std::cout << std::endl << ">= operator" << std::endl;
	// std::cout << "FT Vector\t\t" << (ft_vec >= ft_vec3) << std::endl;
	// std::cout << "STD Vector\t\t" << (std_vec >= std_vec3) << std::endl;

	// swap(ft_vec3, ft_vec2);
	// swap(std_vec3, std_vec2);
	// std::cout << "After non-member swap" << std::endl;
	// print_ft_vec(ft_vec3);
	// print_std_vec(std_vec3);

}

#define _ratio 10000

template <class T>
int run_vector_unit_test(std::string test_name, std::vector<int> (func1)(std::vector<T>), std::vector<int> (func2)(ft::vector<T>)) {
    int    result;
    int    leaks;
    time_t t1;
    time_t t2;
    std::vector<int > res1;
    std::vector<int > res2;
    std::vector<int> vector;
    ft::vector<int> my_vector;

	// printElement(test_name);
	res1 = func1(vector);
	res2 = func2(my_vector);
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

	return !(!result && !leaks);
}

template <typename T>
std::vector<int> erase_test_1(std::vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    // g_start1 = timer();
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio)));
    // g_end1 = timer();
    v.push_back(*(vector.begin() + 82 * _ratio));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> erase_test_1(ft::vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 9900 * _ratio; ++i)
        vector.push_back(i);
    // g_start2 = timer();
    v.push_back(*(vector.erase(vector.begin() + 8 * _ratio)));
    // g_end2 = timer();
    v.push_back(*(vector.begin() + 82 * _ratio));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

int main() {

    exit(run_vector_unit_test<int>("erase(value)", erase_test_1, erase_test_1));
}