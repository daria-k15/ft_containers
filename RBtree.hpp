#ifndef rbtree_HPP
#define rbtree_HPP

#include <memory>
#include <functional>
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
			typedef typename allocator_type::pointer 											pointer;
			typedef typename allocator_type::reference 											reference;
			typedef typename allocator_type::const_reference 									const_reference;
			typedef typename allocator_type::const_pointer 										const_pointer;
			typedef std::ptrdiff_t 																diff_t;
			typedef std::size_t 																size_type;
			typedef class ft::TreeIterator<Value> 												iterator;
			typedef const class ft::TreeIterator<Value> 										const_iterator;
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
				while (node->left && !isNil(node->left))
					node = node->left;
				return (node);
			}

			node_pointer tree_max(node_pointer node) const{
				while (node->right && !isNil(node->right))
					node = node->right;
				return node;
			}

			bool isNil(node_pointer node) const{
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
				if (node && !isNil(node)){
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
				if (!isNil(tmp->right))
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
				if (!isNil(tmp->left))
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (!node->parent)
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
					if (!isNil(where->left))
						return(insert_to_node(where->left, node));
					where->left = node;
				} else {
					if (!isNil(where->right))
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
								node->parent->parent->is_black = false;
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
				if (!node || isNil(node))
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

			rbtree(rbtree const &x) : _alloc(x._alloc), _node_alloc(x._node_alloc), _compare(x._compare){
				*this = x;
			}

			rbtree&operator=(rbtree const &x){
				if (this != &x){
					_root ? clearTree(_root) : init_head();
					if (x._size){
						_root = _node_alloc.allocate(1);
						_node_alloc.construct(_root, Node<value_type>());
						_root->is_black = x._root->is_black;
						_root->is_nil = x._root->is_nil;
						if (x._root->value){
							_root->value = _alloc.allocate(1);
							_alloc.construct(_root->value, *x._root->value);
						}
						copyChild(_root, x._root);
					} else
						_root = _head;
					_size = x._size;
				}
				return *this;
			}

			~rbtree(){
				clearTree(_root);
				clearNode(_head);
				_node_alloc.deallocate(_nil, 1);
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
				clearTree(_root);
				_size = 0;
				_root = _head;
				_head->parent = NULL;
			}

			ft::pair<iterator, bool> insert(const_reference val) {
				iterator it = find(val);
				if (it != end())
					return ft::pair<iterator, bool>(it, false);
				node_pointer noda = _node_alloc.allocate(1);
				pointer dataVal = _alloc.allocate(1);
				_alloc.construct(dataVal, val);
				_node_alloc.construct(noda, Node<value_type>(dataVal));
			 	noda->left = noda->right = _nil;
				insert_to_tree(noda, _root);
				ft::pair<iterator, bool> res(iterator(noda), true);
				insertFixUp(noda);
				node_pointer max_noda = tree_max(_root);
				max_noda->right = _head;
				_head->parent = max_noda;
				++_size;
				return res;
			}

			iterator insert(iterator pos, const_reference value) {
				iterator it = find(value);
				if (it != end())
					return end();
				node_pointer noda = _node_alloc.allocate(1);
				pointer dataVal = _alloc.allocate(1);
				_alloc.construct(dataVal, value);
				_node_alloc.construct(noda, Node<value_type>(dataVal));
			 	noda->left = noda->right = _nil;
				if (pos == end()) {
					--pos;
					insertPrivate(noda, end() == begin() || comp(value, *pos) ? _root : _head->parent);
				} else if (pos == begin())
					insertPrivate(noda, end() == begin() || comp(*pos, value) ? _root : minimum(_root));
				else 
					insertPrivate(noda, _root);
				normalizeInsert(noda);
				node_pointer max_noda = tree_max(_root);
				max_noda->right = _head;
				_head->parent = max_noda;
				++_size;
				return iterator(noda);
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
				bool orig_color = node->is_black;
				if(isNil(node->left)){
					tmp = node->right;
					_relocate(node, node->right);
				} else if(isNil(node->right)){
					tmp = node->left;
					_relocate(node, node->left);
				} else{
					node_pointer copyNode = node;
					node = tree_min(copyNode->right);
					orig_color = node->is_black;
					tmp = node->right;
					if (node->parent != copyNode){
						_relocate(node, node->right);
						node->right = copyNode->right;
						copyNode->right->parent = node;
					}
					_relocate(copyNode, node);
					node->left = copyNode->left;
					node->left->parent = node;
					node->is_black = copyNode->is_black;
				}
				clearNode(del);
				if(orig_color){
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
					erase(first++);
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

			iterator find(const_reference value){
				if (!_root || isNil(_root))
					return end();
				node_pointer node = search(value, _root);
				return (node ? iterator(node) : end());
			}

			const_iterator find(const_reference value) const{
				if (!_root || isNil(_root))
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

