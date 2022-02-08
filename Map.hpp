#ifndef MAP_HPP
#define MAP_HPP
#include <memory>
#include <limits>
#include <iostream>

namespace ft{
	template <class Key, class T>
		struct node{
			std::pair<Key, T> pair;
			node* parent;
			node* left;
			node* right;
			bool end;
		};
};

namespace ft{
    template <class Key, class T, class Compare=std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
    class map{
        public:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef std::pair<const Key, T>                     value_type;
			typedef node<Key, T>*							node;
            typedef Compare                                     key_compare;
            typedef Allocator                                   allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef std::ptrdiff_t                              diff_t;
            typedef std::size_t                                 size_type;

            typedef class value_compare {
                private:
                    typedef bool result_type;
                    typedef value_type first_arg_type;
                    typedef value_type second_arg_type;
                protected:
                    Compare comp;
                    value_compare(){
                        comp = std::less<T>();
                    }
                    value_compare(Compare new_comp){
                        comp = new_comp;
                    }
                    bool operator()(const value_type& x, const value_type& y) const{
                        return comp(x.first, y.first);
                    }
            }       value_compare;

			// template <class Key, class T>
			// struct node{
			// 	std::pair<Key, T> pair;
			// 	node* parent;
			// 	node* left;
			// 	node* right;
			// 	bool end;
			// };

        private:
            node		_root;
			size_type	_size;
			Allocator 	_alloc;
			Compare		_compare;

			node _new_node(key_type key, mapped_type val, node parent, bool end){
				node node = new node<key_type, mapped_type>();
				node->pair = std::make_pair(key, val);
				node->right = NULL;
				node->left = NULL;
				node->end = false;
				node->parent = parent;
				return (node);
			}

			void free_tree(node node){
				if (node->right)
					free_tree(node->right);
				if (node->left)
					free_tree(node->left);
				delete node;
			}

			node insert_node(node node, key_type key, mapped_type val, bool end = false){
				if (node->end){
					if (node->left == NULL){
						node->left = _new_node(key, val, node);
					}
					return (node->left);
				}
				if (key < node->pair.first && !end){
					if(node->left == NULL){
						node->left = _new_node(key, val, node, end);
						return (node->left);
					}else{
						return (insert_node(node->left, key, val));
					}
				} else {
					if (node->right == NULL){
						node->right = _new_node(key, val, node, end);
						return node->right;
					} else {
						return (insert_node(node->right, key, val));
					}
				}
			}

			node find_node(node node, key_type key) const{
				node tmp;
				if (node->end == false && node->pair.first == key && node->parent)
					return (node);
				if (node->right){
					if (tmp = find_node(node->right, key))
						return (tmp);
				}
				if (node->left){
					if (tmp = find_node(node->left, key))
						return (tmp);
				}
				return NULL;
			}

			void delete_node(node node){
				node tmp = node->parent;
				if (node->left == NULL && node->right == NULL){
					if (parent->right == node)
						parent->right = NULL;
					else
						parent->left = NULL;
					delete node;
					return ;
				}
				if (node->right != NULL && node->left == NULL){
					if (parent->right == node)
						parent->right = node->right;
					else
						parent->left = node->right;
					node->right->parent = parent;
					delete node;
					return ;
				}
				if (node->left != NULL && node->right == NULL){
					if (parent->right == node)
						parent->right = node->left;
					else
						parent->left = node->left;
					node->left->parent = parent;
					delete node;
					return ;
				}
				node next = (++iterator(n)).node();
				if(next == NULL)
					next = (--iterator(n)).node();
				ft::swap(next->pair, n->pair);
				delete_node(next);
			}

			void init_tree(void){
				_root = _new_node(key_type(), mapped_type(), NULL);
				_root->right = _new_node(key_type(), mapped_type(), _root, true);
				_size = 0;
			}


		public:
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){
            	_alloc = alloc;
            	_compare = comp;
            	init_tree();
        	}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()){
				_compare = comp;
				_alloc = alloc;
				init_tree();
				insert(first, last);
			}

			map(const map& x){ //???????
				_alloc = x._alloc;
				_compare = x._compare;
				init_tree();
				insert(x.begin(), x.end());
			}

			~map(){
				free_tree(_root);
			}

            map& operator= (const map& x){
                if (*this == x)
                    return *this;
                if (_size != 0)
                    clear();
                _compare = x._compare;
                _alloc = x._alloc;
                insert(x.begin(), x.end());
                return (*this);
            }

            bool empty() const{
                if (_size == 0)
                    return true;
                return false;
            }

            size_type size() const{
                return _size;
            }

            size_type max_size() const{
                return (std::numeric_limits<size_type>::max() / sizeof(node));
            }

			mapped_type& operator[](const key_type& k){
				iterator it = find(k);
				if (it != end())
					return it->second;
				return(insert(std::make_pair(k, mapped_type())).first->second);
			}



		private:
			class iter{
				protected:
					node*	_it;

					node _successor(node* it){
						node* next;
						if (ptr->right == NULL){
							next = it;
							while (next->parent && next->parent->right)
								next = next->parent;
						} else{
							next = it->right;
							while (next->left != NULL)
								next = next->left;
						}
						return next;
					}

					node predecessor(node* it){
						node* next;

						if (it->left == NULL){
							next = it;
							while (next->parent && next->parent->left)
							{
								next = next->parent;
							}
							next = next->parent;
						}
						else{
							next = it->left;
							while(next->right)
								next = next->right;
						}
						return next;
					}

				public:
					iter(){
						_it = NULL;
					}

					iter(node* it){
						_it = it;
					}

					~iter(){}

					bool operator==(const iter& x) const{
						return (_it == x._it);
					}

					bool operator!=(const iter& x) const{
						return (_it != x._it);
					}

					value_type& operator*(){
						return(_it->pair);
					}

					value_type* operator->() const{
						return(&(_it->pair));
					}
			};

		public:
			typedef class iterator : public iter{
				public:
					iterator() : iter(){}
					iterator(node* it) : iter(it){}
					iterator& operator=(const iterator& x){
						if (*this == x)
							return this;
						this->_it = x._it;
						return *this;
					}

					iterator(const iterator& x){
						this->_it = x._it;
					}
					virtual ~iterator(){}

					iterator& operator++(){
						_it = successor(_it);
					}

					iterator& operator--(){
						_it = predecessor(_it);
					}

					iterator operator++(int){
						iterator tmp(*this);
						this->operator++();
						return(tmp);
					}

					iterator operator--(int){
						iterator tmp(*this);
						this->operator--();
						return (tmp);
					}

					bool operator==(const iterator& other){
						return (_it == other._it);
					}

					bool operator != (const iterator &other){
						return (_it != other._it);
					}

					bool operator>(const iterator& x){
						return (_it > x._it);
					}

					bool operator<(const iterator& x){
						return (_it < x._it);
					}

					bool operator>=(const iterator& x){
						return(_it >= x._it);
					}

					bool operator<=(const iterator& x){
						return(_it <= x._it);
					}
			} iterator;

			typedef class const_iterator : public iterator {
				public:
					const_iterator() : iterator(){}
					explicit const_iterator(node it) : iterator(it){}
					explicit const_iterator(const iterator& x) : iterator(x){}
					virtual ~const_iterator(){}
					const value_type& operator*(){
						return (_it->pair);
					}
			}	const_iterator;

			typedef class reverse_iterator : public iter{
				public:
					reverse_iterator() : iter(){}
					reverse_iterator(const node* it) : iter(it){}
					reverse_iterator& operator=(const reverse_iterator& x){
						if (*this == x)
							return *this;
						_it = x._it;
						return *this;
					}

					reverse_iterator(const reverse_iterator& x){
						_it = x._it;
					}
					virtual ~reverse_iterator(){}
					reverse_iterator& operator++(){
						_it = predecessor(_it);
						return *this;
					}
					reverse_iterator& operator--(){
						_it = successor(_it);
						return *this;
					}
					reverse_iterator operator++(int){
						reverse_iterator tmp(*this);
						this->operator++();
						return tmp;
					}
					reverse_iterator operator--(int){
						reverse_iterator tmp(*this);
						this->operator--();
						return tmp;
					}

					bool operator==(const reverse_iterator& other){
							return (_it == other._it);
						}

					bool operator != (const reverse_iterator &other){
						return (_it != other._it);
					}

					bool operator>(const reverse_iterator& x){
						return (_it > x._it);
					}

					bool operator<(const reverse_iterator& x){
						return (_it < x._it);
					}

					bool operator>=(const reverse_iterator& x){
						return(_it >= x._it);
					}

					bool operator<=(const reverse_iterator& x){
						return(_it <= x._it);
					}
			} reverse_iterator;

			typedef class const_reverse_iterator : public reverse_iterator{
				public:
					const_reverse_iterator() : reverse_iterator(){}
					const_reverse_iterator(node *it) : revrese_iterator(it){}
					const_reverse_iterator(const const_reverse_iterator& x){
						*this = x;
					}
					virtual ~const_reverse_iterator(){}
					const_reverse_iterator& operator=(const const_reverse_iterator& x){
						_it = x._it;
						return *this;
					}
			}		const_reverse_iterator;
		public:
			iterator begin(){
				node* node = _root;
				if (node->left == NULL && node->right == NULL)
					return end();
				if (node->left == NULL && node->right != NULL){
					node = node->right;
				}
				while(node->left)
					node = node->left;
				return (iterator(node));
			}

			const_iterator begin() const{
				node* node = _root;
				if (node->left == NULL && node->right == NULL)
					return end();
				if (node->left == NULL && node->right != NULL){
					node = node->right;
				}
				while(node->left)
					node = node->left;
				return (const_iterator(node));
			}

			iterator end(){
				return (iterator(_end));
			}

			const_iterator end() const{
				return (const_iterator(_end));
			}

			reverse_iterator rbegin(){
				iterator i = end();
				i--;
				return (reverse_iterator(i.node()));
			}

			const_reverse_iterator rbegin() const{
				iterator i = end();
				i--;
				return (const_reverse_iterator(i.node()));
			}
			
			reverse_iterator rend(){
				return reverse_iterator(_root);
			}

			const_reverse_iterator rend() const{
				return const_reverse_iterator(_root);
			}	

			std::pair<iterator, bool> insert(const value_type &value){
				iterator tmp;

				if ((tmp = find_node(value.first)) != end)
					return (std::make_pair(tmp, false));
				++_size;
				return (std::make_pair(iterator(insert_node(_root, value.first, value.second))));
			}

			iterator insert(iterator pos, const value_type& value){
				iterator tmp;

				if ((tmp = find_node(value.first)) != end)
					return tmp;
				++_size;
				return (iterator(insert_node(pos.node(), value.first, value.second)));
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last){
				while(first != last){
					insert(*first);
					++first;
				}
			};

			void erase(iterator position){
				delete_node(position.node());
				--_size;
			}

			size_type erase(const key_type& value){
				int i = 0;
				iterator it;
				while ((it = find_node(value)) != end()){
					erase(it);
					i++;
				}
				return (i);
			}

			void erase(iterator first, iterator last){
				while (first != last)
					erase(first++);
			}

			void swap(map& x){
				ft::swap(_size, x._size);
				ft::swap(_root, x._root);
			}

			void clear(){
				erade(begin(), end());
			}

			key_compare key_comp() const{
				return (comp);
			}

			value_compare value_comp() const{
				return (this->value_compare);
			}

			iterator find(const key_type &value){
				if (empty)
					return(end());
				node* tmp = find_node(_root, value);
				if (tmp)
					return (iterator(tmp));
				return (end());
			}

			const_iterator find(const key_type &value) const{
				if (empty)
					return(end());
				node* tmp = find_node(_root, value);
				if (tmp)
					return (const_iterator(tmp));
				return (end());
			}

			size_type count(const key_type& value) const{
				size_t i = 0;
				const_iterator it = begin();
				while (it != end()){
					if (it->first == value)
						++i;
					++it;
				}
				return (i);
			}

			iterator lower_bound(const key_type &key){
				iterator it = begin();
				while (it != end()){
					if (this->comp(it->first, key) <= 0)
						return (it);
					++it;
				}
				return (end());
			}

			const_iterator lower_bound(const key_type &key) const{
				const_iterator it = begin();
				while (it != end()){
					if (this->comp(it->first, key) <= 0)
						return (it);
					++it;
				}
				return (end());
			}

			iterator upper_bound(const key_type key){
				iterator it = begin();
				while (it != end()){
					if (it->first != key && this->comp(it->first, key) <= 0)
						return (it);
					++it;
				}
				return (end());
			}

			const_iterator upper_bound(const key_type key) const{
				const_iterator it = begin();
				while (it != end()){
					if (it->first != key && this->comp(it->first, key) <= 0)
						return (it);
					++it;
				}
				return (end());
			}

			std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const{
				return (std::pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k)));
			}

			std::pair<iterator, iterator> equal_range(const key_type &key){
				return (std::pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
			}


    };

	template <class Key, class T, class Compare, class Allocator>
	void swap(ft::map<Key, T, Compare, Allocator>& x, ft::map<Key, T, Compare, Allocator>& y){
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator> &x, const map<Key, T, Compare, Allocator> &y){
		if (x.size() != y.size())
			return false;
		typename ft::map<Key, T, Compare, Allocator>::const_iterator it = x.begin();
		typename ft::map<Key, T, Compare, Allocator>::const_iterator ite = y.begin();
		while (it != x.end()){
			if (*it != *ite)
				return false;
			++it;
			++it2;
		}
		return true;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator>&x, const map<Key, T, Compare, Allocator>&y){
		return (x != y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key, T, Compare, Allocator>&x, const map<Key, T, Compare, Allocator>&y){
		if (x.size() > y.size())
			return true;
		typename ft::map<Key, T, Compare, Allocator>::const_iterator it = x.begin();
		typename ft::map<Key, T, Compare, Allocator>::const_iterator ite = y.begin();
		while (it != x.end() && ite != y.end()){
			if (*it > *ite)
				return true;
			++it;
			++it2;
		}
		return false;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key, T, Compare, Allocator>&x, const map<Key, T, Compare, Allocator>&y){
		return (x < y);
	}	

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator>&x, const map<Key, T, Compare, Allocator>&y){
		return (x <= y);
	}	

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator>&x, const map<Key, T, Compare, Allocator>&y){
		return (x >= y);
	};

};



#endif