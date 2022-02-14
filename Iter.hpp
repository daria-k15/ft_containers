#ifndef MAPITER_HPP
#define MAPITER_HPP

#include "utils.hpp"

namespace ft{
	template <class Value>
	class TreeIterator{
		public:
            typedef Value                                       value_type;
            typedef Value&										reference;
			typedef Value*										pointer;
            typedef const reference   							const_reference;
            typedef const pointer					            const_pointer;
            typedef std::ptrdiff_t                              diff_t;
            typedef std::size_t                                 size_type;
			typedef Node<typedef remove_const<Value>::type>*	node_pointer;
		protected:
			node_pointer _ptr;
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
			TreeIterator(node_pointer* ptr) : _root(static_cast<node_pointer>(ptr)){}
			TreeIterator(const TreeIterator<typename remove_const<Value>::type>& other){
				*this = other;
			}
			TreeIterator& operator=(const TreeIterator<typename remove_const<Value>::type>& other){
				if (*this != other)
					this->_root = other._root;
				return (*this);
			}

			~TreeIterator(){}

			pointer operator->(){return _root->value;}
			reference operator*(){return *(_root->value);}
			node_pointer getPointer() const{return _root;}


			TreeIterator& operator++(){
				if (_root->right != NULL && !_root->right->isNil)
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

		TreeIterator& operator--(){
			if (_root->left != NULL && !_root->left->isNil)
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

		TreeIterator operator++(int){
			TreeIterator<value_type> tmp(*this);
			*this = operator++();
			return tmp;
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
		bool operator!=(const TreeIterator<T>& other){
			return (_root != other._root);
		}
	};

	template<class Value>
	class ConstTreeIterator : public TreeIterator<Val> {
		public:
			typedef typename TreeIterator<Value>::const_pointer		const_pointer;
			typedef typename TreeIterator<Value>::const_reference	const_reference;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									diff_type;
			typedef typename TreeIterator<Val>::node_pointer		node_pointer;

			ConstTreeIterator() : TreeIterator<Val>(){}
			ConstTreeIterator(node_pointer ptr) : TreeIterator<Val>(ptr){}
			ConstTreeIterator(const TreeIterator<typename remove_const<Val>::type>& other){
				*this = other;
			}
			ConstTreeOperator&operator=(const ConstTreeIterator<typename remove_const<Val>::type>&other){
				if (*this != other)
					this->_root = other._root;
				return *this;
			}
			virtual ~ConstTreeIterator(){}
			const_pointer operator->() const{
				return this->root->_data;
			}
			const_reference operator*()const{
				return(*(this->_root->_data));
			}
			template<class T>
			bool operator==(const ConstTreeIterator<T>& other){
				return (this->_root == other._root);
			}
			template<class T>
			bool operator!=(const ConstTreeIterator<T>& other){
				return (this->_root != other._root);
			}
	};

	template<class Value>
	class ReverseIterator : public TreeIterator<Val> {
		public:
			typedef typename TreeIterator<Value>::const_pointer		const_pointer;
			typedef typename TreeIterator<Value>::const_reference	const_reference;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									diff_type;
			typedef typename TreeIterator<Val>::node_pointer		node_pointer;

			ReverseIterator() : TreeIterator<Val>(){}
			ReverseIterator(node_pointer ptr) : TreeIterator<Val>(ptr){}
			ReverseIterator(const TreeIterator<typename remove_const<Val>::type>& other){
				*this = other;
			}
			ReverseOperator&operator=(const ConstTreeIterator<typename remove_const<Val>::type>&other){
				if (*this != other)
					this->_root = other._root;
				return *this;
			}
			virtual ~ReverseIterator(){}

			ReverseIterator& operator--(){
				if (_root->right != NULL && !_root->right->isNil)
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

			ReverseIterator& operator++(){
				if (_root->left != NULL && !_root->left->isNil)
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

			ReverseIterator operator++(int){
				TreeIterator<value_type> tmp(*this);
				*this = operator++();
				return tmp;
			}

			ReverseIterator operator--(int){
				TreeIterator<value_type> tmp(*this);
				*this = operator--();
				return tmp;
			}

			template<class T>
			bool operator==(const ReverseIterator<T>& other){
				return (_root == other._root);
			}
			template<class T>
			bool operator!=(const ReverseIterator<T>& other){
				return (_root != other._root);
			}
		};

	template<class Value>
	class ConstReverseIterator : public ReverseIterator<Val> {
		public:
			typedef typename TreeIterator<Value>::const_pointer		const_pointer;
			typedef typename TreeIterator<Value>::const_reference	const_reference;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									diff_type;
			typedef typename TreeIterator<Val>::node_pointer		node_pointer;

			ConstReverseIterator() : ReverseIterator<Val>(){}
			ConstReverseIterator(node_pointer ptr) : ReverseIterator<Val>(ptr){}
			ConstReverseIterator(const ConstReverseIterator<typename remove_const<Val>::type>& other){
				*this = other;
			}
			ConstReverseIterator&operator=(const ConstReverseIterator<typename remove_const<Val>::type>&other){
				if (*this != other)
					this->_root = other._root;
				return *this;
			}
			virtual ~ConstReverseIterator(){}

			const_reference& operator*() const{
				return *(_root->data);
			}

			const_pointer*operator->() const{
				return(_root->data);
			}

			template<class T>
			bool operator==(const ConstReverseIterator<T>& other){
				return (_root == other._root);
			}
			template<class T>
			bool operator!=(const ConstReverseIterator<T>& other){
				return (_root != other._root);
			}
		};
};

#endif