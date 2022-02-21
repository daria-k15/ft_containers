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
			// typedef Container                           container_t;
            // typedef typename Container::value_type		value_type;
            // typedef typename Container::size_type	    size_type;
			// typedef typename Container::reference		ref;
			// typedef typename Container::const_reference	const_ref;

        protected:
            container_t container;
        
        public:
            explicit stack(const container_t &cont = container_t()) : container(cont){}


            ~stack(){}

            stack &operator=(const stack &other){
                if (*this != other)
                    container = other.container;
                return *this;
            }

            ref top(){
                return (container.back());
            }

            const_ref top() const{
                return (container.back());
            }

            bool empty() const{
                return(container.empty());
            }

            size_type size() const{
                return (container.size());
            }

            void push(const value_type& value){
                container.push_back(value);
            }

            void pop(){
                container.pop_back();
            }

            template <class A, class Cont>
            friend bool operator==(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.container == rhs.container);
            }

            template <class A, class Cont>
            friend bool operator!=(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.container != rhs.container);
            }

            template <class A, class Cont>
            friend bool operator>(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.container > rhs.container);
            }

            template <class A, class Cont>
            friend bool operator<(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.container < rhs.container);
            }

            template <class A, class Cont>
            friend bool operator>=(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.container >= rhs.container);
            }

            template <class A, class Cont>
            friend bool operator<=(const stack<A, Cont>& other, const stack<A, Cont>& rhs){
                return (other.container <= rhs.container);
            }
    };
};

#endif