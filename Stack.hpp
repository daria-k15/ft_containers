#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"
#include <iostream>

namespace ft{
    template<class T, class Container = ft::vector<T> >
    class stack{
        public:
            typedef T                                   value_type;
            typedef Container                           container_t;
            typedef typename Container::size_type	    size_type;
            typedef value_type&		ref;
            typedef value_type&	const_ref;
        
        protected:
            container_t C;
        
        public:
            explicit stack(const Container &cont = Container()) : C(cont){}

            // stack(const stack &other) : C(other.C){}

            ~stack(){}

            stack &operator=(const stack &other){
                if (*this != other)
                    C = other.C;
                return *this;
            }

            ref top(){
                return (C.back());
            }

            const_ref top() const{
                return (C.back());
            }

            bool empty() const{
                return(C.empty());
            }

            size_type size() const{
                return (C.size());
            }

            void push(const value_type& value){
                C.push_back(value);
            }

            void pop(){
                C.pop_back();
            }

            template <class A, class Cont>
            friend bool operator==(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.C == rhs.C);
            }

            template <class A, class Cont>
            friend bool operator!=(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.C != rhs.C);
            }

            template <class A, class Cont>
            friend bool operator>(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.C > rhs.C);
            }

            template <class A, class Cont>
            friend bool operator<(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.C < rhs.C);
            }

            template <class A, class Cont>
            friend bool operator>=(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.C >= rhs.C);
            }

            template <class A, class Cont>
            friend bool operator<=(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.C <= rhs.C);
            }
    };
};

#endif