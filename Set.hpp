#ifndef SET_HPP
#define SET_HPP

#include "RBtree.hpp"

namespace ft{
    template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
    class set{
		public:
			typedef T           										key_type;
			typedef T           										value_type;
			typedef Compare     										key_compare;
			typedef Compare     										value_compare;
			typedef Allocator   										alloc_type;
			typedef T&          										refetence;
			typedef const T&    										const_reference;
			typedef T*         											pointer;
			typedef const T*    										const_pointer;
			typedef std::size_t                                         size_type;
			typedef std::ptrdiff_t                                      diff_t;
			typedef ft::rbtree<value_type, value_compare, alloc_type>   tree;
			typedef typename tree::iterator					            iterator;
			typedef typename tree::const_iterator		            	const_iterator;
			typedef typename tree::reverse_iterator		            	reverse_iterator;
			typedef typename tree::const_reverse_iterator	            const_reverse_iterator;

		private:
			alloc_type 	_alloc;
			tree		_tree;

		public:
			explicit set(const key_compare & comp = key_compare(), const alloc_type &alloc = alloc_type()) : _alloc(alloc), _tree(tree(comp, alloc)){}

			template <class InputIt>
			set(InputIt first, InputIt last, const key_compare & comp = key_compare(), const alloc_type & alloc = alloc_type(),
				typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) : _alloc(alloc), _tree(first, last, comp, alloc){}
			
			set(const set &x) : _alloc(x._alloc), _tree(x._tree){}
			~set(){}
			set & operator=(const set &x){
				if (this != &x){
					_alloc = x._alloc;
					_tree = x._tree;
				}
				return *this;
			}

			iterator begin(){return _tree.begin();}
			const_iterator begin() const{return _tree.begin();}

			iterator end() {return _tree.end();}
			const_iterator end() const{return _tree.end();}

			reverse_iterator rbegin() {return _tree.rbegin();}
			const_reverse_iterator rbegin() const {return _tree.rbegin();}

			reverse_iterator rend(){return _tree.rend();}
			const_reverse_iterator rend() const {return _tree.rend();}

			bool empty() const{return _tree.empty();}
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _tree.max_size(); }

			pair<iterator, bool> insert(const value_type & value) { return _tree.insert(value); }
			iterator insert(iterator pos, const value_type & value) { return _tree.insert(pos, value); }
			template<class InputIt>
			void insert(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) { _tree.insert(first, last); }
    
			void erase(iterator pos){ _tree.erase(pos); }
			size_type erase(const key_type & val) { return _tree.erase(val); }
			void erase(iterator first, iterator last) {_tree.erase(first, last); } 

			void swap(set  & x){_tree.swap(x._tree); }
			void clear() {_tree.clear(); }
			key_compare key_comp() const {return key_compare(); }
			value_compare value_comp() const {return value_compare() ;}

			iterator find(const value_type & val) {return _tree.find(val); }
			const_iterator find(const value_type &val) const { return _tree.find(val); }

			size_type count(const value_type & val) const{
				size_type i = 0;
				for (iterator it = begin(); it != end(); ++it){
					if (*it == val)
						++i;
				}
				return i;
			}

			iterator lower_bound(const value_type &val) { return _tree.lower_bound(val); }
			const_iterator lower_bound(const value_type &val) const {return _tree.lower_bound(val) ;}
			iterator upper_bound(const value_type &val){ return _tree.upper_bound(val); }
			const_iterator upper_bound(const value_type &val) const {return _tree.upper_bound(val); }
			ft::pair<iterator,iterator> equal_range(const value_type & val) { return _tree.equal_range(val); }
			ft::pair<const_iterator,const_iterator> equal_range(const value_type & val) const { return _tree.equal_range(val); }
			alloc_type get_allocator() const { return _alloc; }
	};

	template <class T, class Compare, class Allocator>
	bool operator==(const ft::set<T, Compare, Allocator> &x, const ft::set<T, Compare, Allocator> &y){
		if (x.size() == y.size()){
			typename ft::set<T, Compare, Allocator>::iterator it = x.begin();
			typename ft::set<T, Compare, Allocator>::iterator ite = y.begin();
			for (; it != x.end(); ++it, ++ite){
				if (*it != *ite)
					return false;
			}
			return true;
		}
		return false;
	}

	template <class T, class Compare, class Allocator>
	bool operator!=(const ft::set<T, Compare, Allocator> &x, const ft::set<T, Compare, Allocator> &y){
		return (!(x == y));
	}

	template <class T, class Compare, class Allocator>
	bool operator<(const ft::set<T, Compare, Allocator> &x, const ft::set<T, Compare, Allocator> &y){
		typename ft::set<T, Compare, Allocator>::iterator it = x.begin();
		typename ft::set<T, Compare, Allocator>::iterator ite = y.begin();
		for (; it != x.end() && ite != y.end(); ++it, ++ite){
			if (*it != *ite)
				return *it < *ite;
		}
		return x.size() < y.size();
	}

	template <class T, class Compare, class Allocator>
	bool operator>(const ft::set<T, Compare, Allocator> &x, const ft::set<T, Compare, Allocator> &y){	
		return ((y < x));
	}

	template <class T, class Compare, class Allocator>
	bool operator<=(const ft::set<T, Compare, Allocator> &x, const ft::set<T, Compare, Allocator> &y){
		return !(x > y);
	}

	template <class T, class Compare, class Allocator>
	bool operator>=(const ft::set<T, Compare, Allocator> &x, const ft::set<T, Compare, Allocator> &y){
		return !(x < y);
	}
}

namespace std{
	template <class T, class Compare, class Allocator>
	void swap(ft::set<T, Compare, Allocator> &x, ft::set<T, Compare, Allocator> &y){
		x.swap(y);
	}
}

#endif