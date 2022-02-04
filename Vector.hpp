#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <limits>

namespace ft{
    template <class T, class Allocator = std::allocator<T> >
    class vector{
        public:
            typedef T value_type;
            typedef Allocator allocator_type;
            typedef std::size_t size_type;
            typedef ptrdiff_t diff_type;
            typedef typename allocator_type::reference ref;
            typedef typename allocator_type::const_reference const_ref;
            typedef typename allocator_type::pointer point;
            typedef typename allocator_type::const_pointer const_point;
        
        private:
            allocator_type  _alloc_t;
            size_type       _size;
            size_type       _capacity;
            point           _data;

        public:
            explicit vector(const allocator_type &alloc = allocator_type()){
                _alloc_t = alloc;
                _size = 0;
                _capacity = 0;
                _data = NULL;
            }

            explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()){
                _alloc_t = alloc;
                _size = n;
                _capacity = n;
                _data = _alloc_t.allocate(_capacity);
                for(size_t i = 0; i < _size; i++)
                    _alloc_t.construct(_data + i, val);
            }

            template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){
				_alloc_t = alloc;
				_size = 0;
				_capacity = 0;
				_data = NULL;
				while (first != last){
					this->push_back(*first);
					++first;
				}
			}

			vector(const vector &x){ //??????
				_size = 0;
				_capacity = 0;
				// _data = NULL;
				// _alloc_t = x._alloc_t;
				*this = x;
			}

			~vector(){
				this->delete_vect();
			}

			vector& operator= (const vector &x){
				if (*this == x){
					return (*this);
				}
				for (size_type i = 0; i < _size; i++)
					_alloc_t.destroy(_data + i);
				this->_size = x._size;
				if (_capacity < _size){
					if (_capacity != 0)
						_alloc_t.deallocate(_data, _capacity);
					_capacity = _size;
					_data = _alloc_t.allocate(_capacity);
				}
				for (size_type i = 0; i < _size; i++)
					_alloc_t.construct(_data + i, x[i]);
				return (*this);
				// this->delete_vect();
				// this->_alloc_t = x._alloc_t;
				// iterator it = x.begin();
				// iterator ite = x.end();
				// while (it != ite){
				// 	this->push_back(*ite);
				// 	it++;
				// }
				// return (*this);
			}

			/*Iterators*/

		private:
		class iter{
			protected:
				point _it_point;
			public:
				iter(){
				_it_point = NULL;
				}
				explicit iter(point it_point){
					_it_point = it_point;
				}
				virtual ~iter(){}
				bool operator==(const iter &other) const{
					return (this->_it_point == other._it_point);
				}
				bool operator!=(const iter &other) const{
					return (this->_it_point != other._it_point);
				}
				T &operator*() const{
					return *(this->_it_point);
				}
				T*operator->() const{
					return (this->_it_point);
				}
				bool operator<(const iter &other) const{
					return (this->_it_point < other._it_point);
				}
				bool operator>(const iter &other) const{
					return (this->_it_point > other._it_point);
				}
				bool operator <=(const iter &other) const{
					return (this->_it_point <= other._it_point);
				}
				bool operator >=(const iter &other) const{
					return (this->_it_point >= other._it_point);
				}
				ref operator[](size_type n){
					return (this->_it_point[n]);
				}
			};
				
		public:
			typedef class iterator : public iter{
			public:
				iterator() : iter(){}
				explicit iterator(point it) : iter(it){}
				iterator &operator=(const iterator &other){
					if (*this == other){
						return (*this);
					}
					this->_it_point = other._it_point;
					return (*this);
				}
				iterator(const iterator &other){
					this->_it_point = other._it_point;
				}
				virtual ~iterator(){}
				iterator &operator++(){
					this->_it_point++;
					return (*this);
				}
				iterator &operator--(){
					this->_it_point--;
					return (*this);
				}
				iterator operator++(int){
					iterator prev_it(*this);
					this->_it_point++;
					return (prev_it);
				}
				iterator operator--(int){
					iterator prev_it(*this);
					this->_it_point--;
					return (prev_it);
				}
				iterator &operator+=(int n){
					this->_it_point += n;
					return (*this);
				}
				iterator operator+(int n){
					iterator tmp(*this);
					return (tmp += n);
				}
				iterator &operator-=(int n){
					this->_it_point -= n;
					return (*this);
				}
				iterator operator-(int n){
					iterator tmp(*this);
					return (tmp -= n);
				}
			} iterator;

			typedef class const_iterator : public iterator {
			public:
				const_iterator() : iterator(){}
				explicit const_iterator(point it) : iterator(it){}
				explicit const_iterator(const iterator& rhs) : iterator(rhs){}
				virtual ~const_iterator(){}
				const T &operator*() const{
					return *(this->_it_point);
				}
			}				const_iterator;

			typedef class reverse_iterator : public iter{
			public:
				reverse_iterator() : iter(){}
				explicit reverse_iterator(point it) : iter(it){}
				reverse_iterator& operator=(const reverse_iterator& rhs) {
					if (*this == rhs)
						return *this;
					this->_it_point = rhs._it_point;
					return *this;
				}
				reverse_iterator(const reverse_iterator& rhs){
					this->_it_point = rhs._it_point;
				}
				virtual ~reverse_iterator(){}
				reverse_iterator& operator++() {
					this->_it_point--;
					return *this;
				}
				reverse_iterator& operator--() {
					this->_it_point++;
					return *this;
				}
				reverse_iterator operator++(int) {
					reverse_iterator prev_it(*this);
					this->_it_point--;
					return prev_it;
				}
				reverse_iterator operator--(int) {
					reverse_iterator prev_it(*this);
					this->_it_point++;
					return prev_it;
				}
				reverse_iterator &operator+=(int n){
					this->_it_point -= n;
					return *this;
				}
				reverse_iterator operator+(int n){
					reverse_iterator tmp(*this);
					return tmp -= n;
				}
				reverse_iterator &operator-=(int n){
					this->_it_point += n;
					return *this;
				}
				reverse_iterator operator-(int n){
					reverse_iterator tmp(*this);
					return tmp += n;
				}
			}				reverse_iterator;

			typedef class const_reverse_iterator : public reverse_iterator {
			public:
				const_reverse_iterator() : reverse_iterator(){}
				explicit const_reverse_iterator(point it) : reverse_iterator(it){}
				explicit const_reverse_iterator(const reverse_iterator& rhs) : reverse_iterator(rhs){}
				virtual ~const_reverse_iterator(){}
				const T &operator*() const{
					return *(this->_it_point);
				}
			}		const_reverse_iterator;

			iterator begin(){
				return (iterator(this->_data));
			}
			const_iterator begin() const{
				return (const_iterator(this->_data));
			}
			iterator end(){
				return (iterator(this->_data + _size));
			}
			const_iterator end() const{
				return (const_iterator(this->_data + _size));
			}
			reverse_iterator rbegin(){
				return (reverse_iterator(this->_data + (_size - 1)));
			}
			const_reverse_iterator rbegin() const{
				return (const_reverse_iterator(this->_data + (_size - 1)));
			}
			reverse_iterator rend(){
				return (reverse_iterator(this->_data - 1));
			}
			const_reverse_iterator rend() const{
				return (const_reverse_iterator(this->_data - 1));
			}

					//		Capacity
			size_type size() const{
				return _size;
			}

			size_type max_size() const{
				return (_alloc_t.max_size());
			}

			void resize (size_type n, value_type val = value_type()){
				if (n < _size){
					while (_size > n)
						this->pop_back();
				}
				else if (n > _size){
					if (n > _capacity){
						this->capacity_realloc(_capacity * 2 > n ? _capacity * 2 : n);
					}
					while (_size < n)
						this->push_back(val);
				}
			}

			size_type capacity() const{
				return _capacity;
			}

			bool empty() const{
				if (_size == 0){
					return true;
				}
				return false;
			}

		private:
			void capacity_realloc(size_type n){
				point tmp = this->_alloc_t.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc_t.construct(tmp + i, _data[i]);
				size_type tmp_size = _size;
				this->delete_vect();
				_size = tmp_size;
				_capacity = n;
				_data = tmp;
			}

		public:
			void reserve (size_type n){
				if (n <= this->_capacity)
					return;
				if (n > max_size())
					throw std::length_error("reserve: too big size to reallocate");
				capacity_realloc(n);
			}

			//		Element access:

			ref operator[] (size_type n){
				return _data[n];
			}

			const_ref operator[] (size_type n) const{
				return _data[n];
			}

			ref at (size_type n){
				if (n >= _size)
					throw std::out_of_range("vector");
				return _data[n];
			}

			const_ref at (size_type n) const{
				if (n >= _size)
					throw std::out_of_range("vector");
				return _data[n];
			}

			ref front(){
				return _data[0];
			}

			const_ref front() const{
				return _data[0];
			}

			ref back(){
				return _data[_size - 1];
			}

			const_ref back() const{
				return _data[_size - 1];
			}
        //		Modifiers

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){
			size_type n = 0;
			InputIterator tmp = first;
			while (tmp++ != last)
				n++;
			this->clear();
			if (n > _capacity){
				_alloc_t.deallocate(_data, _capacity);
				_data = _alloc_t.allocate(n);
				_capacity = n;
			}
			while (first != last)
				this->push_back(*first++);
		}

		void assign (size_type n, const value_type& val){
			this->clear();
			if (n > _capacity){
				_alloc_t.deallocate(_data, _capacity);
				_data = _alloc_t.allocate(n);
				_capacity = n;
			}
			for (size_type i = 0; i < n; i++)
				this->push_back(val);
		}

		void push_back (const value_type& val){
			if (_size + 1 > _capacity)
				this->capacity_realloc(_capacity == 0 ? 1 : _capacity * 2);
			_alloc_t.construct(_data + _size, val);
			_size++;
		}

		void pop_back(){
			if (_size > 0){
				// _alloc_t.destroy(_data + (_size - 1));
				_size--;
			}
		}

		iterator insert (iterator position, const value_type& val){
			size_type i = 0;
			iterator it = begin();
			while (it + i != position && i < _size){
				i++;
			}
			if (_size + 1 > _capacity){
				this->capacity_realloc(_capacity == 0 ? 1 : _capacity * 2);
			}
			size_type len = _size + 1;
			while (len > i){
				_data[len] = _data[len - 1];
				len--;
			}
			_data[i] = val;
			_size++;
			return (iterator(&_data[i]));
		}
			// if (position == this->end()) {
			// 	this->push_back(val);
			// 	return iterator(_data + (_size - 1));
			// }
			// size_t len = 0;
			// iterator it_start = this->begin();
			// while (it_start++ != position) {
			// 	len++;
			// }
			// if (_size + 1 > _capacity)
			// 	this->capacity_realloc(_capacity == 0 ? 1 : _capacity * 2);
			// point tmp;
			// point tmp2 = val;
			// size_t i = len;
			// for (; i < this->size(); i++) {
			// 	tmp = _data[i];
			// 	_alloc_t.destroy(_data + i);
			// 	_alloc_t.construct(_data + i, tmp2);
			// 	tmp2 = tmp;
			// }
			// _alloc_t.construct(_data + i, tmp2);
			// _size++;
			// return iterator(_data + len);
		// }

		void insert (iterator position, size_type n, const value_type& val){
			if (n == 0)
				return ;
			if (position == this->end()) {
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
				return;
			}
			int len = 0;
			iterator it_start = this->begin();
			while (it_start++ != position) {
				len++;
			}
			if (_size + n > _capacity)
				this->capacity_realloc(_capacity * 2 > n ? _capacity * 2 : n);
			for (size_type i = 0; i < n; i++) {
				this->insert(iterator(_data + len + i),val);
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename std::enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){
			if (position == this->end()) {
				while (first != last) {
					this->push_back(*first);
					first++;
				}
				return;
			}
			int len = 0;
			iterator it_start = this->begin();
			while (it_start++ != position) {
				len++;
			}
			int n = 0;
			InputIterator tmp = first;
			while (tmp++ != last)
				n++;
			if (_size + n > _capacity)
				this->capacity_realloc(_capacity * 2 > (_size + n) ? _capacity * 2 : (_size + n));
			for (int i = 0; i < n; i++) {
				this->insert(iterator(_data + len + i), *first++);
			}
		}

		iterator erase (iterator position) {
			if (position == this->end()) {
				this->pop_back();
				return iterator(_data + _size);
			}
			int len = 0;
			iterator it_start = this->begin();
			while (it_start++ != position) {
				len++;
			}
			_alloc_t.destroy(_data + len);
			for (size_type i = len; i < this->size(); i++) {
				_alloc_t.construct(_data + i, _data[i + 1]);
				_alloc_t.destroy(_data + i + 1);
			}
			_size--;
			return (iterator(_data + len));
		}

		iterator erase (iterator first, iterator last) {
			int n = 0;
			iterator tmp = first;
			int len = 0;
			iterator it_start = this->begin();
			while (it_start++ != first) {
				len++;
			}
			while (tmp++ != last)
				n++;
			for (int i = 0; i < n; i++) {
				this->erase(first);
			}
			return (iterator(_data + len));
		}

		void swap (vector& x){
			ft::swap(_data, other._data);
			ft::swap(_size, other._size);
			ft::swap(_capacity, other._capacity);
		}

		void clear(){
			while (_size > 0)
				this->pop_back();
		}

		private:
			void delete_vect(){
				if (this->_size != 0){
					for (size_type i = 0; i < _size; i++)
						_alloc_t.destroy(_data + i);
					_alloc_t.deallocate(_data, _capacity);
					_capacity = 0;
					_size = 0;
				}
			}

		public:
			allocator_type get_allocator() const{
				return std::allocator<T>(_alloc_t);
			}
		};

		template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
			x.swap(y);
		}

		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			if (lhs.size() != rhs.size())
				return false;
			typename ft::vector<T>::const_iterator it_lhs = lhs.begin();
			typename ft::vector<T>::const_iterator it_rhs = rhs.begin();
			typename ft::vector<T>::const_iterator ite_lhs = lhs.end();
			while (it_lhs != ite_lhs){
				if (*it_lhs != *it_rhs)
					return false;
				it_lhs++;
				it_rhs++;
			}
			return true;
		}

		template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!(lhs == rhs));
		}

		template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			typename ft::vector<T>::const_iterator it_lhs = lhs.begin();
			typename ft::vector<T>::const_iterator it_rhs = rhs.begin();
			typename ft::vector<T>::const_iterator ite_lhs = lhs.end();
			typename ft::vector<T>::const_iterator ite_rhs = rhs.end();
			while (it_lhs != ite_lhs && it_rhs != ite_rhs){
				if (*it_lhs < *it_rhs)
					return true;
				if (*it_lhs > *it_rhs)
					return false;
				it_lhs++;
				it_rhs++;
			}
			if (it_lhs == ite_lhs && it_rhs != ite_rhs) {
				return true;
			}
			return false;
		}

		template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (lhs < rhs || lhs == rhs);
		}

		template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
			return (rhs < lhs);
		}

		template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (lhs > rhs || lhs == rhs);
	}
    
}

#endif