#ifndef rbtree_HPP
#define rbtree_HPP

#include <memory>
#include <functional>
#include <limits>
#include "Iter.hpp"
#include "ReverseIter.hpp"
#include "utils.hpp"

namespace ft {
	template <class Value, class Compare = std::less<Value>, class Allocator = std::allocator<Value> >
	class rbtree {
		public:
			typedef Value																	value_type;
			typedef Compare																	value_compare;
			typedef Allocator																allocator_type;
			typedef typename allocator_type::template rebind<ft::Node<value_type> >::other	node_allocator;
			typedef typename node_allocator::pointer										node_pointer;
			typedef typename allocator_type::pointer										pointer;
			typedef typename allocator_type::reference										reference;
			typedef typename allocator_type::const_reference								const_reference;
			typedef typename allocator_type::const_pointer									const_pointer;
			typedef std::size_t																size_type;
			typedef std::ptrdiff_t															difference_type;
			typedef class ft::TreeIterator<Value>												iterator;
			typedef const class ft::TreeIterator<Value>										const_iterator;
			typedef ft::ReverseIterator<iterator>											reverse_iterator;
			typedef ft::ReverseIterator<const_iterator>									const_reverse_iterator;
		private:
			allocator_type 				_alloc_value;
			node_allocator				_alloc_node;
			value_compare				_compare;
			node_pointer				_root;
			node_pointer				_head;
			node_pointer				_nil;
			size_type					_size;
			
			void init_head() {
				_nil = _alloc_node.allocate(1);
				_alloc_node.construct(_nil, Node<value_type>());
				_nil->is_black = _nil->is_nil = true;
				_head = _alloc_node.allocate(1);
				_alloc_node.construct(_head, Node<value_type>());
				_head->value = _alloc_value.allocate(1);
				_alloc_value.construct(_head->value, value_type());
				_head->is_black = true;
			}
			bool isNil(node_pointer ptr) const { return ptr == _nil || ptr == _head; }
			node_pointer tree_max(node_pointer ptr) const {
				while (ptr->right && !isNil(ptr->right))
					ptr = ptr->right;
				return ptr;
			}
			node_pointer tree_min(node_pointer ptr) const {
				while (ptr->left && !isNil(ptr->left))
					ptr = ptr->left;
				return ptr;
			}
			void rotate_right(node_pointer ptr) {
				node_pointer tmp = ptr->left;
				ptr->left = tmp->right;
				if (!isNil(tmp->right))
					tmp->right->parent = ptr;
				tmp->parent = ptr->parent;
				if (!ptr->parent)
					_root = tmp;
				else if (ptr == ptr->parent->left)
					ptr->parent->left = tmp;
				else 
					ptr->parent->right = tmp;
				tmp->right = ptr;
				ptr->parent = tmp;
			}
			void rotate_left(node_pointer ptr) {
				node_pointer tmp = ptr->right;
				ptr->right = tmp->left;
				if (!isNil(tmp->left))
					tmp->left->parent = ptr;
				tmp->parent = ptr->parent;
				if (!ptr->parent)
					_root = tmp;
				else if (ptr == ptr->parent->right)
					ptr->parent->right = tmp;
				else
					ptr->parent->left = tmp;
				tmp->left = ptr;
				ptr->parent = tmp;
			}
			void clearNode(node_pointer toDelete) {
				_alloc_value.destroy(toDelete->value);
				_alloc_value.deallocate(toDelete->value, 1);
				_alloc_node.deallocate(toDelete, 1);
			}
			void clearTree(node_pointer toDelete) {
				if (toDelete && !isNil(toDelete)) {
					clearTree(toDelete->right);
					clearTree(toDelete->left);
					clearNode(toDelete);
				}
			}
			void insertFixUp(node_pointer noda) {
				if (noda != _root && noda->parent != _root) {
					while (noda != _root && !noda->parent->is_black) {
						if (noda->parent == noda->parent->parent->right) {
							node_pointer fatherBrother = noda->parent->parent->left;
							if (fatherBrother->is_black) {
								if (noda == noda->parent->left) {
									noda = noda->parent;
									rotate_right(noda);
								}
								noda->parent->is_black = true;
								noda->parent->parent->is_black = false;
								rotate_left(noda->parent->parent);
							} else {
								noda->parent->is_black = true;
								fatherBrother->is_black = true;
								noda->parent->parent->is_black = false;
								noda = noda->parent->parent;
							}
						} else {
							node_pointer fatherBrother = noda->parent->parent->right;
							if (fatherBrother->is_black) {
								if (noda == noda->parent->right) {
									noda = noda->parent;
									rotate_left(noda);
								}
								noda->parent->is_black = true;
								noda->parent->parent->is_black = false;
								rotate_right(noda->parent->parent);
							} else {
								noda->parent->is_black = true;
								fatherBrother->is_black = true;
								noda->parent->parent->is_black = false;
								noda = noda->parent->parent;
							}
						}
					}
				}
				_root->is_black = true;
			}
			void eraseFixUp(node_pointer noda) {
				node_pointer tmp;
				while (noda != _root && noda->is_black) {
					if (noda == noda->parent->left) {
						tmp = noda->parent->right;
						if (!tmp->is_black) {
							tmp->is_black = true;
							noda->parent->is_black = false;
							rotate_left(noda->parent);
							tmp = noda->parent->right;
						}
						if (tmp->left->is_black && tmp->right->is_black) {
							tmp->is_black = false;
							noda = noda->parent;
						} else {
							if (tmp->right->is_black) {
								tmp->left->is_black = true;
								tmp->is_black = false;
								rotate_right(tmp);
								tmp = noda->parent->right;
							}
							tmp->is_black = noda->parent->is_black;
							noda->parent->is_black = true;
							tmp->right->is_black = true;
							rotate_left(noda->parent);
							noda = _root;
						}
					} else {
						tmp = noda->parent->left;
						if (!tmp->is_black) {
							tmp->is_black = true;
							noda->parent->is_black = false;
							rotate_right(noda->parent);
							tmp = noda->parent->left;
						}
						if (tmp->left->is_black && tmp->right->is_black) {
							tmp->is_black = false;
							noda = noda->parent;
						} else {
							if (tmp->left->is_black) {
								tmp->right->is_black = true;
								tmp->is_black = false;
								rotate_left(tmp);
								tmp = noda->parent->left;
							}
							tmp->is_black = noda->parent->is_black;
							noda->parent->is_black = true;
							tmp->left->is_black = true;
							rotate_right(noda->parent);
							noda = _root;
						}
					}
				}
			}
			node_pointer insert_to_node(node_pointer where, node_pointer noda) {
				if (_compare(*(noda->value), *(where->value))) {
					if (!isNil(where->left))
						return insert_to_node(where->left, noda);
					where->left = noda; 	
				} else {
					if (!isNil(where->right))
						return insert_to_node(where->right, noda);
					where->right = noda; 	
				}
				noda->parent = where;
				return noda;
			}
			node_pointer insert_to_tree(node_pointer noda, node_pointer where) {
				if (_root != _head)
					where == _root ? insert_to_node(where, noda) : insert_to_node(_root, noda);
				else
					_root = noda;
				return noda;
			}
			node_pointer search(const_reference value, node_pointer noda) const {
				if (!noda || isNil(noda))
					return nullptr;
				if (_compare(value, *(noda->value)))
					return search(value, noda->left);
				if (_compare(*(noda->value), value))
					return search(value, noda->right);
				return noda;
			}
			node_pointer copyNode(node_pointer other) {
				node_pointer res = _alloc_node.allocate(1);
				_alloc_node.construct(res, Node<value_type>());
				res->is_black = other->is_black;
				res->is_nil = other->is_nil;
				if (other->value) {
					res->value = _alloc_value.allocate(1);
					_alloc_value.construct(res->value, *other->value);
				}
				return res;
			}
			void copyChild(node_pointer noda, node_pointer other) {
				if (other->left->is_nil)
					noda->left = _nil;
				else {
					noda->left = copyNode(other->left);
					noda->left->parent = noda;
					copyChild(noda->left, other->left);
				}
				if (other->right->is_nil)
					noda->right = _nil;
				else if (!other->right->right) {
					noda->right = _head;
					_head->parent = noda;
				} else {
					noda->right = copyNode(other->right);
					noda->right->parent = noda;
					copyChild(noda->right, other->right);
				}
			}
			void relocate(node_pointer to, node_pointer noda) {
				if (to == _root)
					_root = noda;
				else if (to == to->parent->left)
					to->parent->left = noda;
				else 
					to->parent->right = noda;
				noda->parent = to->parent;
			}
		public:
			rbtree() : _alloc_value(allocator_type()), _alloc_node(node_allocator()), _compare(value_compare()) {
				init_head();
				_root = _head;
				_size = 0;
			}
			explicit rbtree(const value_compare & comp = value_compare(), const allocator_type & alloc = allocator_type()) :
				_alloc_value(alloc), _alloc_node(node_allocator()), _compare(comp) {
				init_head();
				_root = _head;
				_size = 0;
			}
			template<class InputIt>
			rbtree(InputIt first, InputIt last, const value_compare & comp = value_compare(), const allocator_type & alloc = allocator_type(),
				typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) :
				_alloc_value(alloc), _alloc_node(node_allocator()), _compare(comp) {
					init_head();
					_root = _head;
					_size = 0;
					insert(first, last);
			}
			rbtree(const rbtree & other) : _alloc_value(other._alloc_node), _alloc_node(other._alloc_node), _compare(other._compare) { *this = other; }
			rbtree & operator=(const rbtree & other) {
				if (this != &other) {
					_root ? clearTree(_root) : init_head();
					if (other._size) {
						_root = _alloc_node.allocate(1);
						_alloc_node.construct(_root, Node<value_type>());
						_root->is_black = other._root->is_black;
						_root->is_nil = other._root->is_nil;
						if (other._root->value) {
							_root->value = _alloc_value.allocate(1);
							_alloc_value.construct(_root->value, *other._root->value);
						}
						copyChild(_root, other._root);
					} else 
						_root = _head;
					_size = other._size;
				}
				return *this;
			}
			~rbtree() {
				clearTree(_root);
				clearNode(_head);
				_alloc_node.deallocate(_nil, 1);
			}
			iterator begin() { return iterator(_size ? iterator(tree_min(_root)) : _head); }
			const_iterator begin() const { return const_iterator(_size ? const_iterator(tree_min(_root)) : _head); }
			iterator end() { return iterator(_head); }
			const_iterator end() const { return const_iterator(_head); }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
			bool empty() const { return !_size; }
			size_type size() const { return _size; }
			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(size_type); }
			void clear() {
				clearTree(_root);
				_size = 0;
				_root = _head;
				_head->parent = nullptr;
			}
			void swap(rbtree & other) {
				std::swap(_alloc_value, other._alloc_value);
				std::swap(_alloc_node, other._alloc_node);
				std::swap(_compare, other._compare);
				std::swap(_root, other._root);
				std::swap(_head, other._head);
				std::swap(_nil, other._nil);
				std::swap(_size, other._size);
			}
			ft::pair<iterator, bool> insert(const_reference val) {
				iterator it = find(val);
				if (it != end())
					return ft::pair<iterator, bool>(it, false);
				node_pointer noda = _alloc_node.allocate(1);
				pointer valueVal = _alloc_value.allocate(1);
				_alloc_value.construct(valueVal, val);
				_alloc_node.construct(noda, Node<value_type>(valueVal));
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
				node_pointer noda = _alloc_node.allocate(1);
				pointer valueVal = _alloc_value.allocate(1);
				_alloc_value.construct(valueVal, value);
				_alloc_node.construct(noda, Node<value_type>(valueVal));
			 	noda->left = noda->right = _nil;
				if (pos == end()) {
					--pos;
					insert_to_tree(noda, end() == begin() || _compare(value, *pos) ? _root : _head->parent);
				} else if (pos == begin())
					insert_to_tree(noda, end() == begin() || _compare(*pos, value) ? _root : tree_min(_root));
				else 
					insert_to_tree(noda, _root);
				insertFixUp(noda);
				node_pointer max_noda = tree_max(_root);
				max_noda->right = _head;
				_head->parent = max_noda;
				++_size;
				return iterator(noda);
			}
			template<class InputIt>
			void insert(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) {
				for (; first != last; ++first)
					insert(*first);
			}
			void erase(iterator pos) {
				node_pointer noda = pos.getPointer(); 
				node_pointer toDelete = noda, tmp;
				bool _is_black = noda->is_black;
				if (isNil(noda->left)) {
					tmp = noda->right;
					relocate(noda, noda->right);
				} else if (isNil(noda->right)) {
					tmp = noda->left;
					relocate(noda, noda->left);
				} else {
					node_pointer copyNoda = noda;
					noda = tree_min(copyNoda->right);
					_is_black = noda->is_black;
					tmp = noda->right;
					if (noda->parent != copyNoda) {
						relocate(noda, noda->right);
						noda->right = copyNoda->right;
						copyNoda->right->parent = noda;
					}
					relocate(copyNoda, noda);
					noda->left = copyNoda->left;
					noda->left->parent = noda;
					noda->is_black = copyNoda->is_black;
				}
				clearNode(toDelete);
				if (_is_black)
					eraseFixUp(tmp);
				_nil->parent = nullptr;
				--_size;
				if (_size > 0) {
					tmp = _size == 1 ? _root : tree_max(_root);
					tmp->right = _head;
					_head->parent = tmp;
				} else 
					_root = _head;
			}
			size_type erase(const_reference value) {
				size_type i = 0;
				node_pointer noda = search(value, _root);
				if (noda)
					erase(iterator(noda));
				return noda != nullptr;
			}
			void erase(iterator first, iterator last) {
				while (first != last)
					erase(first++);
			}
			value_compare value_comp() const { return _compare; }
			iterator find(const_reference value) {
				if (!_root || isNil(_root))
					return end();
				node_pointer tmp = search(value, _root);
				return tmp ? iterator(tmp) : end();
			}
			const_iterator find(const_reference value) const {
				if (!_root || isNil(_root))
					return end();
				node_pointer tmp = search(value, _root);
				return tmp ? iterator(tmp) : end();
			}
			iterator lower_bound(const value_type & key) {
				for (iterator it = begin(); it != end(); ++it)
					if (!_compare(*it, key))
						return it;
				return end();
			}
			const_iterator lower_bound(const value_type & key) const {
				for (iterator it = begin(); it != end(); ++it)
					if (!_compare(*it, key))
						return static_cast<const_iterator>(it);
				return end();
			}
			iterator upper_bound(const value_type & key) {
				for (iterator it = begin(); it != end(); ++it)
					if (_compare(key, *it))
						return it;
				return end();
			}
			const_iterator upper_bound(const value_type & key) const {
				for (iterator it = begin(); it != end(); ++it)
					if (_compare(key, *it))
						return static_cast<const_iterator>(it);
				return end();
			}
			ft::pair<iterator,iterator> equal_range(const value_type & key) { return ft::make_pair(lower_bound(key), upper_bound(key)); }
			allocator_type get_allocator() const { return _alloc_value; }
	};
}

namespace std {
	template<class T, class Compare, class Alloc>
	void swap(ft::rbtree<T, Compare, Alloc> & lhs, ft::rbtree<T, Compare, Alloc> & rhs) { lhs.swap(rhs); }
}
#endif

