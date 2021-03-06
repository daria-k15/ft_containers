#ifndef ITER_HPP
#define ITER_HPP

#include "utils.hpp"

namespace ft{
	template <class Value>
	class TreeIterator{
		public:
            typedef std::bidirectional_iterator_tag            					iterator_category;
            typedef typename ft::iterator_traits<Value *>::value_type			value_type;
			typedef typename ft::iterator_traits<Value *>::pointer				pointer;
			typedef typename ft::iterator_traits<Value *>::reference			reference;
            typedef const typename ft::iterator_traits<Value *>::reference		const_reference;
            typedef const typename ft::iterator_traits<Value *>::pointer    	const_pointer;
            typedef typename ft::iterator_traits<Value *>::difference_type      difference_type;
            typedef std::size_t                             				    size_type;
			typedef  Node<typename remove_const<Value>::type>*				node_pointer;
		protected:
			node_pointer _root;
			node_pointer find_min(node_pointer point) const{
				while(point->left != NULL && !point->left->is_nil)
					point = point->left;
				return (point);
			}

			node_pointer find_max(node_pointer point) const{
				while (!point->right->is_nil)
					point = point->right;
				return (point);
			}
		public:
			TreeIterator(){}
			TreeIterator(node_pointer ptr) : _root(ptr){}
			TreeIterator(const TreeIterator<typename remove_const<Value>::type>& other){
				*this = other;
			}
			TreeIterator& operator=(const TreeIterator<typename remove_const<Value>::type>& other){
				if (this != &other)
					_root = other._root;
				return (*this);
			}

			~TreeIterator(){}

			reference operator*(){return *_root->value;}
			pointer operator->(){return &operator*();}
			const_reference operator*() const {return *(_root->value);}
			const_pointer operator->() const {return &operator*();}
			node_pointer getPointer() const {return _root;}


			TreeIterator & operator++(){
				if (_root->right != NULL && !_root->right->is_nil)
					_root = find_min(_root->right);
				else{
					node_pointer tmp = _root->parent;
					while (tmp && _root == tmp->right){
						_root = tmp;
						tmp = tmp->parent;
					}
					_root = tmp;
				}
				return (*this);
			}

			TreeIterator operator++(int){
				TreeIterator<value_type> tmp(*this);
				if (!_root->right->is_nil)
					_root = find_min(_root->right);
				else{
					node_pointer tmp = _root->parent;
					while (tmp && _root == tmp->right){
						_root = tmp;
						tmp = tmp->parent;
					}
					_root = tmp;
				}
				return tmp;
			}

			TreeIterator& operator--(){
				if (_root->left != NULL && !_root->left->is_nil)
					_root = find_max(_root->left);
				else{
					node_pointer tmp = _root->parent;
					while (tmp && _root == tmp->left){
						_root = tmp;
						tmp = tmp->parent;
					}
					_root = tmp;
				}
				return (*this);
			}


			TreeIterator operator--(int){
				TreeIterator<value_type> tmp(*this);
				*this = operator--();
				return tmp;
			}

			template<class T>
			bool operator==(const TreeIterator<T>& other){
				return (_root == other._root);
			}
			template<class T>
			bool operator!=(const TreeIterator<T>& other) const{
				return (_root != other._root);
			}
	};
};

#endif