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

	template<class K, class V>
	struct pair{
		typedef K	first_type;
		typedef V	second_type;

		first_type key;
		second_type	value;

		pair() : key(), value() {}
		pair(const first_type &x, second_type &y) : key(x), value(y){}
		template<class T1, class T2>
		pair(const pair<T1, T2> &other){
			key = other.key;
			value = other.value;
		}

		pair&operator=(pair const &other){
			if (*this != other){
				key = other.key;
				value = other.value;
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

			explicit Node(Value *val = 0) : value(val), parent(0), left(0), right(0), is_black(false), is_nil(false){}
			Node(Node const& x){
				this->is_black = x.is_black;
				this->value = x.value;
				this->parent = x.parent;
				this->is_nil = x.is_nil;
				this->right = x.right;
				this->left = x.left;
			};

			Node&operator=(const Node& x){
				if (*this != x){
					this->is_black = x.is_black;
					this->value = x.value;
					this->parent = x.parent;
					this->is_nil = x.is_nil;
					this->right = x.right;
					this->left = x.left;
				}
				return *this;
			}

		virtual ~Node(){}
	};
};

#endif