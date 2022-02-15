#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <limits>
#include <iostream>
#include <functional>
#include "RBtree.hpp"

namespace ft{
    template <class Key, class T, class Compare=std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map{
        public:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef ft::pair<const key_type, T>                    		value_type;
            typedef Compare                                     key_compare;
            typedef Allocator                                   allocator_type;
            typedef value_type&									reference;
            typedef const value_type&									const_reference;
            typedef value_type*									pointer;
            typedef const pointer								const_pointer;
            typedef std::ptrdiff_t                              diff_t;
            typedef std::size_t                                 size_type;

		private:
            class value_compare {
				protected:
					key_compare _comp;
                public:
                    value_compare(const key_compare &comp) : _comp(comp){}
                    bool operator()(const value_type& x, const value_type& y) const{
                        return _comp(x.first, y.first);
                    }
            };

		public:
			// typedef pair_compare							value_compare;
			typedef ft::rbtree<value_type, value_compare, allocator_type> tree;
			typedef typename tree::iterator					iterator;
			typedef typename tree::const_iterator			const_iterator;
			typedef typename tree::reverse_iterator			reverse_iterator;
			typedef typename tree::const_reverse_iterator	const_reverse_iterator;


        private:
            key_compare		_compare;
			allocator_type 	_alloc;
			tree			_tree;

		public:
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
				_alloc(alloc), _compare(comp), _tree(tree(comp, alloc)){}

			template <class InputIt>
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : //, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0):
				_alloc(alloc), _compare(comp), _tree(first, last, alloc, comp){}


			mapped_type& operator[](const key_type& k){
				return(*((this->insert(make_pair(k, mapped_type())).first)).second);
			}


			size_type size() const{ return _tree.size();}
			size_type max_size() const {return _tree.max_size();}
			bool empty() const{return _tree.empty();}
			value_compare value_comp() const{return _tree.value_compare();}
			key_compare key_com() const{return _compare;}

			iterator begin(){return _tree.begin();}
			const_iterator cbegin() const{return _tree.begin();}
			iterator end(){return _tree.end();}
			const_iterator cend() const{return _tree.end();}
			reverse_iterator rbegin(){return _tree.rbegin();}
			reverse_iterator rend(){return _tree.rend();}
			const_reverse_iterator crbegin() const{return _tree.rbegin();}
			const_reverse_iterator crend() const{return _tree.rend();}

			ft::pair<iterator, bool>insert(const value_type &value){
				return _tree.insert(value);
			}

			iterator insert(iterator it, const value_type &value){return _tree.insert(it, value);}

			template<class InputIt>
			void insert(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0){
				 _tree.insert(first, last); 
			}

			void erase(iterator pos){_tree.erase(pos);}
			size_type erase(const Key &key){return _tree.erase(make_pair(key, mapped_type()));}
			void erase(iterator first, iterator last){_tree.erase(first, last);}

			void swap(map &x){return _tree.swap(x);}
			void clear(){return _tree.clear();}
			iterator find(const key_type& value){return _tree.find(value);}
			const_iterator find(const key_type& value) const{return _tree.find(value);}

			size_type count(const key_type& key) const{return _tree.count();}
			iterator lower_bound(const key_type& key){
				for (iterator it = begin(); it < end(); ++it){
					if(!_compare(*it, key))
						return it;
				}
				return end();
			}
			const_iterator lower_bound(const key_type& key)const {
				for(const_iterator it = begin(); it < end(); ++it){
					if (!_compare(*it, key))
						return it;
				}
				return end();
			}
			iterator upper_bound(const key_type& key){
				for (iterator it = begin(); it < end(); ++it){
					if (_compare(*it, key))
						return it;
				}
				return end();
			}
			const_iterator upper_bound(const key_type& key)const{
				for (const_iterator it = begin(); it < end(); ++it){
					if (_compare(*it, key))
						return it;
				}
				return end();
			}
			// pair<iterator, iterator> equal_range(const key_type& key){return _tree.equal_range(key);}
			// pair<const_iterator, const_iterator> equal_range(const key_type& key) const{return _tree.equal_range(key);}
			allocator_type get_allocator() const{return _tree.get_allocator();}


		
		
    };

	template <class Key, class T, class Compare, class Allocator>
	void swap(ft::map<Key, T, Compare, Allocator>& x, ft::map<Key, T, Compare, Allocator>& y){
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const ft::map<Key, T, Compare, Allocator> &x, const ft::map<Key, T, Compare, Allocator> &y){
		if (x.size() != y.size())
			return false;
		typename ft::map<Key, T, Compare, Allocator>::const_iterator it = x.begin();
		typename ft::map<Key, T, Compare, Allocator>::const_iterator ite = y.begin();
		while (it != x.end()){
			if (*it != *ite)
				return false;
			++it;
		}
		return true;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const ft::map<Key, T, Compare, Allocator>&x, const ft::map<Key, T, Compare, Allocator>&y){
		return (x != y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>(const ft::map<Key, T, Compare, Allocator>&x, const ft::map<Key, T, Compare, Allocator>&y){
		if (x.size() > y.size())
			return true;
		typename ft::map<Key, T, Compare, Allocator>::const_iterator it = x.begin();
		typename ft::map<Key, T, Compare, Allocator>::const_iterator ite = y.begin();
		while (it != x.end() && ite != y.end()){
			if (*it > *ite)
				return true;
			++it;
		}
		return false;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const ft::map<Key, T, Compare, Allocator>&x, const ft::map<Key, T, Compare, Allocator>&y){
		return (x < y);
	}	

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const ft::map<Key, T, Compare, Allocator>&x, const ft::map<Key, T, Compare, Allocator>&y){
		return (x <= y);
	}	

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const ft::map<Key, T, Compare, Allocator>&x, const ft::map<Key, T, Compare, Allocator>&y){
		return (x >= y);
	};

};



#endif