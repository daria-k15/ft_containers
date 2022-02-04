#include "Stack.hpp"
#include "Vector.hpp"
#include "test.hpp"
#include <stack>
#include <vector>

int main(){
    // vector_test();
    // stack_test();

    ft::vector<int>v;
    for (int i = 0; i < 10; i++){
        v.push_back(i);
    }
    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
        std::cout << *it << std::endl;

    v.insert(v.begin() + 3, 15);

    std::cout << std::endl;

    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
        std::cout << *it << std::endl;

}   