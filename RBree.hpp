#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>
#include "MapIter.hpp"

template <class Value, class Compare = std::less<Value>, class Allocator = std::allocator<Value> >
class rbtree{
	public:
		Value value_type;
		typedef Value value_type;
		typedef Compare _compare;
		typedef Allocator alloc_type;
		typedef typename Allocator::template rebind<Node<Value> >::other	node_alloc;
		typedef typename node_alloc::pointer	node_pointer;
		typedef typename _alloc::reference reference;
		typedef typename _alloc::const_reference const_reference;
		typedef typename _alloc::pointer pointer;
		typedef typename _alloc::const_pointer const_pointer;
		typedef std::ptrdiff_t diff_type;
		typedef std::size_t size_type;
		typedef TreeIterator<Value> iterator;
		typedef TreeIterator<const Value> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverce_iterator;

	private:
		alloc_type		_alloc;
		node_alloc		_node_alloc;
		value_compare	_compare;
		node_pointer	_nil;
		node_pointer	_head;
		node_pointer	_root;
		size_type		_size;

		node_pointer tree_min(node_pointer node) const{
			while (node != NULL && !is_nil(node->left))
				node = node->left;
			return (node);
		}

		node_pointer tree_max(node_pointer node) const{
			while (node != NULL && !is_nil(node->right))
				node = node->right;
			return node;
		}

		void rotate_right(node_pointer node){
			node_pointer tmp;

			tmp = node->left;
			node->left = tmp->right;
			if (!is_nil(tmp->parent))
				tmp->right->parent = node;
			else if (node == node->parent->left)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->right = node;
			node->parent = tmp;
		}

		void rotate_left(node_pointer node){
			node_pointer tmp;

			tmp = node->right;
			node->right = tmp->left;
			if (!is_nil(tmp->left))
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (node->parent == NULL)
				_root = tmp;
			else if (node == node->parent->left)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->left = node;
			node->parent = tmp;
		}

		node_pointer insert(node_pointer newNode){
			if (_root == _head)
				_root = newNode;
			else
				insert_to_node(_root, newNode);
			return (newNode);
		}

		node_pointer insert_to_node(node_pointet root, node_pointet newNode){
			if (_compare(*newNode->value, *root->value)){
				if (!is_nil(root->left))
					return(insert_to_node(root->left));
				root->left = newNode;
			} else {
				if (!is_nil(root->right))
					return insert_to_node(root->right);
				root->right = newNode;
			}
			newNode->parent = root;
			return newNode;
		}

		node_pointer insert_to_tree(node_pointer n, node_pointer where){
			if (_root == _head)
				_root = n;
			else
				insert_to_node(where, n);
			return n;
		}

		void insertFixUp(node_pointer node){
			node_pointer parent = node->parent;
			if (node != _root && !isNill(node)){

			}
		}

};

#endif