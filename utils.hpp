#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

namespace ft{
	template<bool B, class T = void>
	struct enable_if{};

	template<class T>
	struct enable_if<true, T>{
		typedef T	type;
	};

	template<class T>struct remove_const{typedef T type;};
	template<class T>struct remove_const<const T>{typedef T type;};

	template<class K, class V>
	struct pair{
		typedef K	first_type;
		typedef V	second_type;

		first_type first;
		second_type	second;

		pair() : first(), second() {}
		pair(const first_type &x, const second_type &y) : first(x), second(y){}

		template<class T1, class T2>
		pair(const pair<T1, T2> &other): first(other.first), second(other.second){}	

		pair(const pair& other) : first(other.first), second(other.second){}

		pair&operator=(pair const &other){
			if (this != &other){
				first = other.first;
				second = other.second;
			}
			return *this;
		}
	};

	template<class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 t1, T2 t2){
		return (ft::pair<T1, T2>(t1, t2));
	}

	template<class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
		return (lhs.key == rhs.key && lhs.value == rhs.value);
	}

	template<class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
		return (lhs.key != rhs.key && lhs.value != rhs.value);
	}
	template<class T1, class T2>
	bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
		return (lhs.key > rhs.key && lhs.value > rhs.value);
	}

	template<class T1, class T2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
		return (lhs.key >= rhs.key && lhs.value >= rhs.value);
	}

	template<class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
		return (lhs.key < rhs.key && lhs.value < rhs.value);
	}

	template<class T1, class T2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs){
		return (lhs.key <= rhs.key && lhs.value <= rhs.value);
	}

	template <class Value>
	struct Node{
		public:
			Value *value;
			Node* parent;
			Node* left;
			Node* right;
			bool is_black;
			bool is_nil;

			explicit Node(Value *val = NULL) : value(val), parent(NULL), left(NULL), right(NULL), is_black(false), is_nil(false){}
			Node(Node const& x){
				*this = x;
			};

			Node&operator=(const Node& x){
				if (this != &x){
					is_black = x.is_black;
					value = x.value;
					parent = x.parent;
					is_nil = x.is_nil;
					right = x.right;
					left = x.left;
				}
				return *this;
			}

		// virtual ~Node(){}
	};
};

#endif