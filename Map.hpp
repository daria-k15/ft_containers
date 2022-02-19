#ifndef MAP_HPP
#define MAP_HPP

#include "RBtree.hpp"

namespace ft{
    template <class Key, class T, class Compare=std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map{
        public:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef pair<const key_type, T>                    	value_type;
            typedef Compare                                     key_compare;
            typedef Allocator                                   allocator_type;
            typedef value_type&									reference;
            typedef const value_type&							const_reference;
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
			typedef ft::rbtree<value_type, value_compare, allocator_type> tree;
			typedef typename tree::iterator					iterator;
			typedef typename tree::const_iterator			const_iterator;
			typedef typename tree::reverse_iterator			reverse_iterator;
			typedef typename tree::const_reverse_iterator	const_reverse_iterator;


        private:
            key_compare		_compare;
			allocator_type 	_alloc;
			tree			_rbtree;

		public:
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
				_alloc(alloc), _compare(comp), _rbtree(tree(comp, alloc)){}

			template <class InputIt>
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0):
				 _compare(comp),_alloc(alloc), _rbtree(first, last, comp, alloc){}

			map(map const &x): _compare(x._compare), _alloc(x._alloc), _rbtree(x._rbtree){*this = x;}

			map & operator=(const map &x){
				if (this != &x){
					_alloc = x._alloc;
					_compare = x._compare;
					_rbtree = x._rbtree;
				}
				return *this;
			}
			
			~map(){}

			mapped_type & at(const key_type& key){
				iterator it = find(key);
				if (it == end()){
					throw std::out_of_range("map");
				}
				return it->second;
			}


			const mapped_type & at(const key_type& key) const {
				iterator it = find(key);
				if (it == end()){
					throw std::out_of_range("map");
				}
				return it->second;
			}

			mapped_type& operator[](const key_type& k){
				return(*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
			}


			size_type size() const{ return _rbtree.size();}
			size_type max_size() const {return _rbtree.max_size();}
			bool empty() const{return _rbtree.empty();}

			value_compare value_comp() const{return value_compare(_compare);}
			key_compare key_comp() const{return _compare;}

			iterator begin(){return _rbtree.begin();}
			const_iterator begin() const{return _rbtree.begin();}
			iterator end(){return _rbtree.end();}
			const_iterator end() const{return _rbtree.end();}
			reverse_iterator rbegin(){return _rbtree.rbegin();}
			reverse_iterator rend(){return _rbtree.rend();}
			const_reverse_iterator rbegin() const{return _rbtree.rbegin();}
			const_reverse_iterator rend() const{return _rbtree.rend();}


			pair<iterator, bool>insert(const value_type &value){
				return _rbtree.insert(value);
			}

			iterator insert(iterator it, const value_type &value){return _rbtree.insert(it, value);}

			template<class InputIt>
			void insert(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0){
				 _rbtree.insert(first, last); 
			}

			void erase(iterator pos){_rbtree.erase(pos);}
			size_type erase(const Key &key){return _rbtree.erase(make_pair(key, mapped_type()));}
			void erase(iterator first, iterator last){_rbtree.erase(first, last);}

			void swap(map &x){
				std::swap(_alloc, x._alloc);
				std::swap(_compare, x._compare);
				_rbtree.swap(x._rbtree);
			}

			void clear(){return _rbtree.clear();}

			iterator find(const key_type& value){return _rbtree.find(ft::make_pair(value, mapped_type()));}
			const_iterator find(const key_type& value) const{return _rbtree.find(ft::make_pair(value, mapped_type()));}

			size_type count(const key_type& key) const{
				size_type i = 0;
				for (iterator it = begin(); it != end(); ++it){
					if (it->first == key)
						i++;
				}
				return i;
			}
			iterator lower_bound(const key_type& key){
				for (iterator it = begin(); it != end(); ++it){
					if(!_compare(it->first, key))
						return it;
				}
				return end();
			}
			const_iterator lower_bound(const key_type& key)const {
				for(const_iterator it = begin(); it != end(); ++it){
					if (!_compare(it->first, key))
						return static_cast<const_iterator>(it);
				}
				return end();
			}
			iterator upper_bound(const key_type& key){
				for (iterator it = begin(); it != end(); ++it){
					if (_compare(it->first, key))
						return it;
				}
				return end();
			}
			const_iterator upper_bound(const key_type& key)const{
				for (const_iterator it = begin(); it != end(); ++it){
					if (_compare(it->first, key))
						return static_cast<const_iterator>(it);
				}
				return end();
			}
			pair<iterator, iterator> equal_range(const key_type& key){return _rbtree.equal_range(ft::make_pair(key, mapped_type()));}
			pair<const_iterator, const_iterator> equal_range(const key_type& key) const{return _rbtree.equal_range(ft::make_pair(key, mapped_type()));}
			allocator_type get_allocator() const{return _alloc;}
    };

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const ft::map<Key, T, Compare, Allocator> &x, const ft::map<Key, T, Compare, Allocator> &y){
		if (x.size() != y.size())
			return false;
		typename ft::map<Key, T, Compare, Allocator>::const_iterator it = x.begin();
		typename ft::map<Key, T, Compare, Allocator>::const_iterator ite = y.begin();
		for (; it != x. end(); ++it, ++ite){
			if (*it != *ite)
				return false;
		}
		return true;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const ft::map<Key, T, Compare, Allocator>&x, const ft::map<Key, T, Compare, Allocator>&y){
		return (!(x == y));
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
	}

};

namespace std{
	template <class Key, class T, class Compare, class Allocator>
	void swap(ft::map<Key, T, Compare, Allocator>& x, ft::map<Key, T, Compare, Allocator>& y){
		x.swap(y);
	}
}



#endif