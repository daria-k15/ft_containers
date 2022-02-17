#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>
#include <functional>
#include <iostream>
#include <limits>
#include "Iter.hpp"
#include "ReverseIter.hpp"
#include "utils.hpp"

namespace ft{
	template <class Value, class Compare = std::less<Value>, class Allocator = std::allocator<Value> >
	class rbtree{
		public:
			typedef Value																		value_type;
			typedef Compare 																	value_compare;
			typedef Allocator 																	allocator_type;
			typedef typename allocator_type::template rebind<ft::Node<value_type> >::other		node_alloc;
			typedef typename node_alloc::pointer												node_pointer;
			typedef typename allocator_type::reference 											reference;
			typedef typename allocator_type::const_reference 									const_reference;
			typedef typename allocator_type::pointer 											pointer;
			typedef typename allocator_type::const_pointer 										const_pointer;
			typedef std::ptrdiff_t 																diff_type;
			typedef std::size_t 																size_type;
			typedef class ft::TreeIterator<Value> 												iterator;
			typedef class ft::TreeIterator<Value> 												const_iterator;
			typedef class ft::ReverseIterator<iterator> 										reverse_iterator;
			typedef class ft::ReverseIterator<const_iterator> 									const_reverse_iterator;

		private:
			allocator_type		_alloc;
			node_alloc			_node_alloc;
			value_compare		_compare;
			node_pointer		_nil;
			node_pointer		_head;
			node_pointer		_root;
			size_type			_size;

			node_pointer tree_min(node_pointer node) const{
				while (node->left && !is_nil(node->left))
					node = node->left;
				return (node);
			}

			node_pointer tree_max(node_pointer node) const{
				while (node->right && !is_nil(node->right))
					node = node->right;
				return node;
			}

			bool is_nil(node_pointer node) const{
				return (node == _nil || node == _head);
			}

			void init_head(){
				_nil = _node_alloc.allocate(1);
				_node_alloc.construct(_nil, Node<value_type>());
				_nil->is_black = true;
				_nil->is_nil = true;
				_head = _node_alloc.allocate(1);
				_node_alloc.construct(_head, Node<value_type>());
				_head->value = _alloc.allocate(1);
				_alloc.construct(_head->value, value_type());
				_head->is_black = true;
			}

			void clearTree(node_pointer node){
				if (node && !is_nil(node)){
					clearTree(node->right);
					clearTree(node->left);
					clearNode(node);
				}
			}

			void clearNode(node_pointer node){
				_alloc.destroy(node->value);
				_alloc.deallocate(node->value, 1);
				_node_alloc.deallocate(node, 1);
			}

			void rotate_right(node_pointer node){
				node_pointer tmp;

				tmp = node->left;
				node->left = tmp->right;
				if (!is_nil(tmp->right))
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (!node->parent)
					_root = tmp;
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
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
				tmp->left = node;
				node->parent = tmp;
			}

			node_pointer insert_to_node(node_pointer where, node_pointer node){
				if (_compare(*(node->value), *(where->value))){
					if (!is_nil(where->left))
						return(insert_to_node(where->left, node));
					where->left = node;
				} else {
					if (!is_nil(where->right))
						return insert_to_node(where->right, node);
					where->right = node;
				}
				node->parent = where;
				return node;
			}

			node_pointer insert_to_tree(node_pointer n, node_pointer where){
				if (_root == _head)
					_root = n;
				else
					where == _root ? insert_to_node(where, n) : insert_to_node(_root, n);
				return n;
			}

			void insertFixUp(node_pointer node){
				if (node != _root && node->parent != _root){
					// node_pointer gparent = node->parent->parent;
					while (node != _root && !node->parent->is_black){
						if (node->parent == node->parent->parent->left){
							node_pointer uncle = node->parent->parent->right;
							if (!uncle->is_black){
								node->parent->is_black = true;
								uncle->is_black = true;
								node->parent->parent->is_black = false;
								node = node->parent->parent;
							} else {
								if (node == node->parent->right){
									node = node->parent;
									rotate_left(node);
								}
								node->parent->is_black = true;
								node->parent->parent->is_black = false;
								rotate_right(node->parent->parent);
							}
						} else {
							node_pointer uncle = node->parent->parent->left;
							if (!uncle->is_black){
								node->parent->is_black = true;
								uncle->is_black = true;
								node->parent->parent->is_black = false;
								node = node->parent->parent;
							} else {
								if (node == node->parent->left){
									node = node->parent;
									rotate_right(node);
								}
								node->parent->is_black = true;
								node->parent->parent->is_black = true;
								rotate_left(node->parent->parent);
							}
						}
					}
				}
				_root->is_black = true;
			}

			void eraseFixUp(node_pointer node){
				node_pointer tmp;
				while(node != _root && node->is_black){
					if (node == node->parent->left){
						tmp = node->parent->right;
						if (!tmp->is_black){
							tmp->is_black = true;
							node->parent->is_black = false;
							rotate_left(node->parent);
							tmp = node->parent->right;
						}
						if (tmp->left->is_black && tmp->right->is_black){
							tmp->is_black = false;
							node = node->parent;
						} else {
							if (tmp->right->is_black){
								tmp->left->is_black = true;
								tmp->is_black = false;
								rotate_right(tmp);
								tmp = node->parent->right;
							}
							tmp->is_black = node->parent->is_black;
							node->parent->is_black = true;
							tmp->right->is_black = true;
							rotate_left(node->parent);
							node = _root;
						}
					} else {
						tmp = node->parent->left;
						if (!tmp->is_black){
							tmp->is_black = true;
							node->parent->is_black = false;
							rotate_right(node->parent);
							tmp = node->parent->left;
						}
						if (tmp->right->is_black && tmp->left->is_black){
							tmp->is_black = false;
							node = node->parent;
						} else {
							if (tmp->left->is_black){
								tmp->right->is_black = true;
								tmp->is_black = false;
								rotate_left(tmp);
								tmp = node->parent->left;
							}
							tmp->is_black = node->parent->is_black;
							node->parent->is_black = true;
							tmp->left->is_black = true;
							rotate_right(node->parent);
							node = _root;
						}
					}
				}
			}


			node_pointer copyNode(node_pointer node){
				node_pointer res = _node_alloc.allocate(1);
				_node_alloc.construct(res,  Node<Value>());
				res->is_black = node->is_black;
				res->is_nil = node->is_nil;
				if (node->value){
					res->value = _alloc.allocate(1);
					_alloc.construct(res->value, *node->value);
				}
				return (res);
			}

			void copyChild(node_pointer node, node_pointer other){
				if (other->left->is_nil){
					node->left = _nil;
				} else {
					node->left = copyNode(other->left);
					node->left->parent = node;
					copyChild(node->left, other->left);
				}
				if(other->right->is_nil)
					node->right = _nil;
				else if (!other->right->right){
					node->right = _head;
					_head->parent = node;
				} else {
					node->right = copyNode(other->right);
					node->right->parent = node;
					copyChild(node->right, other->right);
				}
			}

			node_pointer search(const_reference value, node_pointer node) const{
				if (!node || is_nil(node))
					return NULL;
				if (_compare(value, *(node->value)))
					return search(value, node->left);
				if (_compare(*(node->value), value))
					return search(value, node->right);
				return node;
			}


			void _relocate(node_pointer where, node_pointer node){
				if (where == _root)
					_root = node;
				else if (where == where->parent->left)
					where->parent->left = node;
				else
					where->parent->right = node;
				node->parent = where->parent;
			}



		public:
			rbtree() : _alloc(allocator_type()), _node_alloc(node_alloc()), _compare(value_compare()){
				init_head();
				_root = _head;
				_size = 0;
			}

			explicit rbtree(const value_compare & comp = value_compare(), const allocator_type & alloc = allocator_type()) : 
				_alloc(alloc), _compare(comp), _node_alloc(node_alloc()){
				init_head();
				_root = _head;
				_size = 0;
			}

			template<class InputIt>
			rbtree(InputIt first, InputIt last, const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type(), 
				typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) : _alloc(alloc), _node_alloc(node_alloc()), _compare(comp){
				 init_head();
				 _root = _head;
				 _size = 0;
				 insert(first, last);
			 }

			rbtree(const rbtree &x) : _alloc(x._alloc), _node_alloc(x._node_alloc), _compare(x._compare){
				*this = x;
			}

			rbtree&operator=(rbtree const &x){
				if (this != &x){
					this->_node_alloc = x._node_alloc;
					this->_alloc = x._alloc;
					this->_compare = x._compare;
					if (this->_root == NULL)
						init_head();
					else
						clearTree(_root);
					if (x._size == 0)
						this->_root = this->_head;
					else{
						this->_root = copyNode(x._root);
						copyChild(this->_root, x._root);
					}
					this->_size = x._size;
				}
				return *this;
			}

			~rbtree(){
				// clearNode(_root);
				// _alloc.destroy(_head->value);
				// _alloc.deallocate(_head->value, 1);
				// _node_alloc.deallocate(_head, 1);
				// _node_alloc.deallocate(_nil, 1);
			}


			iterator	end(){return(iterator(_head));}
			const_iterator end() const{return (const_iterator(_head));}

			iterator begin(){return iterator(_size ? iterator(tree_min(_root)) : _head);}
			const_iterator begin() const {return const_iterator(_size ? const_iterator(tree_min(_root)) : _head);}
	
			reverse_iterator rbegin() {return reverse_iterator(end());}
			const_reverse_iterator rbegin() const {return const_reverce_iterator(end());}

			reverse_iterator rend() {return reverse_iterator(begin());}
			const_reverse_iterator rend() const {return const_reverce_iterator(begin());}

			bool empty() const{ return (_size == 0);}
			size_type size() const {return _size;}
			size_type max_size() const {return std::numeric_limits<size_type>::max() / sizeof(size_type);}
	
			void clear(){
				clearNode(_root);
				_size = 0;
				_root = _head;
				_head->parent = NULL;
			}

			pair<iterator, bool> insert(const_reference val){
				iterator it = find(val);
				if (it != end())
					return ft::pair<iterator, bool>(it, false);
				node_pointer node = _node_alloc.allocate(1);
				pointer data = _alloc.allocate(1);
				_alloc.construct(data, val);
				_node_alloc.construct(node, Node<value_type>(data));
				node->left = node->right = _nil;
				insert_to_tree(node, _root);
				ft::pair<iterator, bool> res(iterator(node), true);
				insertFixUp(node);
				node = tree_max(_root);
				node->right = _head;
				_head->parent = node;
				_size++;
				return res;
			}

			iterator insert(iterator pos, const_reference value){
				node_pointer node = search(value, _root);
				if (node)
					return iterator(node);
				node = _node_alloc.allocate(1);
				pointer data = _alloc.allocate(1);
				_alloc.construct(data, value);
				_node_alloc.construct(node, Node<value_type>(data));
				node->left = node->left = _nil;
				if (pos == end()){
					--pos;
					insert_to_tree(node, end() == begin() || _compare(value, *pos) ? _root : _head->parent);
				}else if(pos == begin())
					insert_to_tree(node, end() == begin() || _compare(*pos, value) ? _root : tree_min(_root));
				else
					insert_to_tree(node, _root);
				// if (pos == begin()){
				// 	if (pos != end() && _compare(value, *pos))
				// 		insert_to_tree(node, tree_min(_root));
				// 	else
				// 		insert_to_tree(node, _root);
				// }else if (pos == end()){
				// 	if(pos != begin() && _compare(*(--pos), value))
				// 		insert_to_tree(node, _head->parent);
				// 	else
				// 		insert_to_tree(node, _root); 
				// } else
				// 	insert_to_tree(node, _root);
				insertFixUp(node);
				++_size;
				node_pointer max_v = tree_max(_root);
				max_v->right = _head;
				_head->parent = max_v;
				return iterator(node);
				// iterator it = find(value);
				// if (it != end())
				// 	return end();
				// node_pointer res = _node_alloc.allocate(1);
				// pointer data = _alloc.allocate(1);
				// _alloc.construct(data, value);
				// _node_alloc.construct(res, Node<value_type>(data));
				// res->left = res->right = _nil;
				// if (pos == begin()){
				// 	if (pos != end() && _compare(value, *pos))
				// 		insert_to_tree(res, tree_min(_root));
				// 	else
				// 		insert_to_tree(res, _root);
				// } else if(pos == end()){
				// 	if (pos != begin() && _compare(*(--pos), value))
				// 		insert_to_tree(res, _head->parent);
				// 	else
				// 		insert_to_tree(res, _root);
				// } else 
				// 	insert_to_tree(res, _root);
				// insertFixUp(res);
				// ++_size;
				// node_pointer max_v = tree_max(_root);
				// max_v->right = _head;
				// _head->parent = max_v;
				// return iterator(res);
			}

			template<class InputIt>
			void insert(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0){
				for(; first != last; first++){
					insert(*first);
				}
			}

			void erase(iterator pos){
				node_pointer node = pos.getPointer();
				node_pointer del = node, tmp;
				bool isBlack = node->is_black;
				if(is_nil(node->left)){
					tmp = node->right;
					_relocate(node, node->right);
				} else if(is_nil(node->right)){
					tmp = node->left;
					_relocate(node, node->left);
				} else{
					node_pointer x = node;
					node = tree_min(x->right);
					isBlack = node->is_black;
					tmp = node->right;
					if (node->parent != x){
						_relocate(node, node->right);
						node->right = x->right;
						x->right->parent = node;
					}
					_relocate(x, node);
					node->left = x->left;
					node->left->parent = node;
					node->is_black = x->is_black;
				}
				clearNode(del);
				if(isBlack){
					eraseFixUp(tmp);
				}
				_nil->parent = NULL;
				--_size;
				if (_size > 0){
					tmp = _size == 1 ? _root : tree_max(_root);
					tmp->right = _head;
					_head->parent = tmp;
				}
				else
					_root = _head;
			}

			size_type erase(const_reference value){
				node_pointer res = search(value, _root);
				if (res)
					erase(iterator(res));
				return res != NULL;
			}

			void erase(iterator first, iterator last){
				while (first != last){
					erase(first);
					++first;
				}
			}

			value_compare value_comp() const { return _compare; }

			allocator_type get_allocator() const{return _alloc;}

			void swap(rbtree &other){
				std::swap(_alloc, other._alloc);
				std::swap(_node_alloc, other._node_alloc);
				std::swap(_compare, other._compare);
				std::swap(_root, other._root);
				std::swap(_head, other._head);
				std::swap(_nil, other._nil);
				std::swap(_size, other._size);
			}

			// size_type count(const value_type& value) const{return(find(value) != end());}

			iterator find(const_reference value){
				if (!_root || is_nil(_root))
					return end();
				node_pointer node = search(value, _root);
				return (node ? iterator(node) : end());
			}

			const_iterator find(const_reference value) const{
				if (!_root || is_nil(_root))
					return end();
				node_pointer node = search(value, _root);
				return (node ? iterator(node) : end());
			}

			iterator lower_bound(const value_type &val){
				for (iterator it = begin(); it != end(); ++it){
					if(!_compare(*it, val))
						return it;
				}
				return end();
			}

			const_iterator lower_bound(const value_type &val)const{
				for(const_iterator it = begin(); it != end(); ++it){
					if (!_compare(*it, val))
						return static_cast<const_iterator>(it);
				}
				return end();
			}

			iterator upper_bound(const value_type &val){
				for (iterator it = begin(); it != end(); ++it){
					if (_compare(val, *it))
						return it;
				}
				return end();
			}

			const_iterator upper_bound(const value_type &val) const{
				for (const_iterator it = begin(); it != end(); ++it){
					if (_compare(val, *it))
						return static_cast<const_iterator>(it);
				}
				return end();
			}

			ft::pair<iterator, iterator> equal_range(const value_type &val){
				return ft::make_pair(lower_bound(val), upper_bound(val));
			}

			


	};

};

namespace std{
	template<class T, class Compare, class Allocator>
	void swap(const ft::rbtree<T, Compare, Allocator> &x, const ft::rbtree<T, Compare, Allocator> &y){
		x.swap(y);
	}
}

#endif