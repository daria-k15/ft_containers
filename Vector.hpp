// #ifndef VECTOR_HPP
// #define VECTOR_HPP

// #include <iostream>
// #include <memory>
// #include <limits>
// #include "utils.hpp"
// #include "VectorIter.hpp"

// namespace ft{
//     template <class T, class Allocator = std::allocator<T> >
//     class vector{
//         public:
//             typedef T                                 					value_type;
//             typedef Allocator                         					allocator_type;
//             typedef std::size_t                       					size_type;
//             typedef T&                            						reference;
//             typedef const T&                          					const_reference;
//             typedef T*                                					pointer;
//             typedef const T*                          					const_pointer;
//             typedef class ft::VectorIterator<T>			  				iterator;
//             typedef class ft::ConstVectorIterator<T>      				const_iterator;
//             typedef class ft::ReverseVectorIterator<T>      			reverse_iterator;
//             typedef class ft::ConstReverseVectorIterator<T>  			const_reverse_iterator;
// 			typedef typename ft::VectorIterator<T>::diff_t				diff_t;
        
//         private:
//             allocator_type  _alloc;
//             size_type       _size;
//             size_type       _capacity;
//             pointer         _data;

// 			void capacity_realloc(size_type n){
// 				pointer tmp = this->_alloc.allocate(n);
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.construct(tmp + i, _data[i]);
// 				size_type tmp_size = _size;
// 				delete_vect();
// 				_size = tmp_size;
// 				_capacity = n;
// 				_data = tmp;
// 			}

// 			void delete_vect(){
// 				if (_size != 0){
// 					for (size_type i = 0; i < _size; i++)
// 						_alloc.destroy(_data + i);
// 					_alloc.deallocate(_data, _capacity);
// 					_capacity = 0;
// 					_size = 0;
// 				}
// 			}


//         public:
//             explicit vector(const allocator_type &alloc = allocator_type()){
//                 _alloc = alloc;
//                 _size = 0;
//                 _capacity = 0;
//                // _data = _alloc.allocate(20);
//             }

//             explicit vector(size_type n, const_reference &val = value_type(), const allocator_type &alloc = allocator_type()){
//                 _alloc = alloc;
//                 _size = n;
//                 _capacity = n;
//                 _data = _alloc.allocate(_capacity);
//                 for(size_t i = 0; i < _size; i++)
//                     _alloc.construct(_data + i, val);
//             }

//             template <class InputIterator>
// 			vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){
// 				_alloc = alloc;
// 				_size = 0;
// 				_capacity = 20;
// 				if (first > last)
// 					throw std::length_error("vector");
// 				_data = _alloc.allocate(_capacity);
// 				assign(first, last);
// 			}

// 			vector(const vector &x){
// 				_size = 0;
// 				_capacity = 0;
// 				_data = NULL;
// 				*this = x;
// 			}

// 			~vector(){
// 				this->delete_vect();
// 			}

// 			vector& operator= (const vector &x){
// 				if (*this == x){
// 					return (*this);
// 				}
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.destroy(_data + i);
// 				this->_size = x._size;
// 				if (_capacity < _size){
// 					if (_capacity != 0)
// 						_alloc.deallocate(_data, _capacity);
// 					_capacity = _size;
// 					_data = _alloc.allocate(_capacity);
// 				}
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.construct(_data + i, x[i]);
// 				return (*this);
// 			}
		
// 			iterator begin(){
// 				return (iterator(this->_data));
// 			}
// 			const_iterator begin() const{
// 				return (const_iterator(this->_data));
// 			}
// 			iterator end(){
// 				return (iterator(this->_data + _size));
// 			}
// 			const_iterator end() const{
// 				return (const_iterator(this->_data + _size));
// 			}
// 			reverse_iterator rbegin(){
// 				return (reverse_iterator(this->_data + (_size - 1)));
// 			}
// 			const_reverse_iterator rbegin() const{
// 				return (const_reverse_iterator(this->_data + (_size - 1)));
// 			}
// 			reverse_iterator rend(){
// 				return (reverse_iterator(this->_data - 1));
// 			}
// 			const_reverse_iterator rend() const{
// 				return (const_reverse_iterator(this->_data - 1));
// 			}

// 			//		Capacity
// 			size_type size() const{
// 				return _size;
// 			}

// 			size_type max_size() const{
// 				return (_alloc.max_size());
// 			}

// 			void resize (size_type n, value_type val = value_type()){
// 				if (n < _size){
// 					while (_size > n)
// 						this->pop_back();
// 				}
// 				else if (n > _size){
// 					if (n > _capacity){
// 						this->capacity_realloc(_capacity * 2 > n ? _capacity * 2 : n);
// 					}
// 					while (_size < n)
// 						this->push_back(val);
// 				}
// 			}

// 			size_type capacity() const{
// 				return _capacity;
// 			}

// 			bool empty() const{
// 				if (_size == 0){
// 					return true;
// 				}
// 				return false;
// 			}

// 			void reserve (size_type n){
// 				if (n <= this->_capacity)
// 					return;
// 				if (n > max_size())
// 					throw std::length_error("reserve: too big size to reallocate");
// 				capacity_realloc(n);
// 			}


// 			reference operator[] (size_type n){
// 				return _data[n];
// 			}

// 			const_reference operator[] (size_type n) const{
// 				return _data[n];
// 			}

// 			reference at (size_type n){
// 				if (n >= _size)
// 					throw std::out_of_range("vector");
// 				return _data[n];
// 			}

// 			const_reference at (size_type n) const{
// 				if (n >= _size)
// 					throw std::out_of_range("vector");
// 				return _data[n];
// 			}

// 			reference front(){
// 				return _data[0];
// 			}

// 			const_reference front() const{
// 				return _data[0];
// 			}

// 			reference back(){
// 				return _data[_size - 1];
// 			}

// 			const_reference back() const{
// 				return _data[_size - 1];
// 			}

// 			pointer data() {return (_size ? _data : nullptr);}
// 			const_pointer data() const {return (_size ? _data : nullptr); }

// 			template<class InputIt>
// 			void assign(InputIt first, InputIt last, typename enable_if<!std::numeric_limits<InputIt>::is_specialized>::type * = 0) {
// 				if (first > last)
// 					throw std::length_error("vector");
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.destroy(_data + i);
// 				int count = 0;
// 				for (InputIt it = first; it != last; ++it, ++count);
// 				if (_capacity < count) {
// 					_alloc.deallocate(_data, _capacity);
// 					_capacity = count;
// 					_data = _alloc.allocate(_capacity);
// 				}
// 				_size = count;
// 				for (int i = 0; first != last; ++first, ++i)
// 					_alloc.construct(_data + i, *first);
// 			}

// 			void assign(size_type count, const_reference value) {
// 				if (!_capacity)
// 					_data = _alloc.allocate(count);
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.destroy(_data + i);
// 				if (_capacity < count) {
// 					_alloc.deallocate(_data, _capacity);
// 					_capacity = count;
// 					_data = _alloc.allocate(_capacity);
// 				}
// 				_size = count;
// 				for (int i = 0; i < count; i++) {
// 					_alloc.construct(_data + i, value);
// 				}
// 			}

// 			void push_back (const value_type& val){
// 				if (_size == _capacity)
// 					reserve(_capacity ? _capacity * 2 : 1);
// 				_alloc.construct(_data + _size++, val);
// 			}

// 			void pop_back(){
// 				if (!empty()){
// 					_alloc.destroy(_data + _size--);
// 				}
// 			}

// 			iterator insert(iterator pos, const_reference value) {
// 				size_type indexToInsert = 0;
// 				for (iterator it = begin(); it != pos; ++it, ++indexToInsert);
// 				if (!_capacity)
// 					reserve(1);
// 				if (_size == _capacity)
// 					reserve(_capacity * 2);
// 				for (size_type i = _size; i > indexToInsert; --i) {
// 					_alloc.destroy(_data + i);
// 					_alloc.construct(_data + i, _data[i - 1]);
// 				}
// 				_alloc.destroy(_data + indexToInsert);
// 				_alloc.construct(_data + indexToInsert, value);
// 				++_size;
// 				return iterator(_data + indexToInsert);
// 			}

// 			void insert(iterator pos, size_type count, const_reference value) {
// 				size_type indexToInsert = 0;
// 				for (iterator it = begin(); it != pos; ++it, ++indexToInsert);
// 				if (!_capacity)
// 					reserve(count);
// 				if (_size + count > _capacity)
// 					reserve(_size + count > _capacity * 2 ? _size + count : _capacity * 2);
// 				for (size_type i = _size; i > indexToInsert; --i) {
// 					_alloc.destroy(_data + i + count - 1);
// 					_alloc.construct(_data + i + count - 1, _data[i - 1]);
// 				}
// 				for (size_type i = 0; i < count; ++i) {
// 					_alloc.destroy(_data + indexToInsert);
// 					_alloc.construct(_data + indexToInsert++, value);
// 				}
// 				_size += count;
// 			}

// 			template <class InputIterator>
// 			void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){

// 				size_type len = 0;
// 				iterator it_start = this->begin();
// 				while (it_start++ != position) {len++;}
// 				size_type n = 0;
// 				InputIterator tmp = first;
// 				while (tmp++ != last)
// 					n++;
// 				if (_size + n > _capacity){
// 					size_type new_capacity = _size + n > _capacity * 2 ? _size + n : _capacity * 2;
// 					pointer newArr = _alloc.allocate(new_capacity);
// 					for (size_type i = 0; i < len; i++)
// 						_alloc.construct(newArr + i, _data[i]);
// 					try{
// 						for(size_type i = 0; i < n; i++, first++)
// 							_alloc.construct(newArr + len + i, *first);
// 					} catch(...){
// 						for (size_type i = 0; i < len + n; i++)
// 							_alloc.destroy(newArr + i);
// 						_alloc.deallocate(newArr, new_capacity);
// 						throw "vector";
// 					}
// 					for (size_type i = len; i < _size; ++i)
// 						_alloc.construct(newArr + n + i, _data[i]);
// 					for (size_type i = 0; i < _size; ++i)
// 						_alloc.destroy(_data + i);
// 					_alloc.deallocate(_data, _capacity);
// 					_size += n;
// 					_capacity = new_capacity;
// 					_data = newArr;
// 				} else {
// 					for (size_type i = _size; i > len; --i){
// 						_alloc.destroy(_data + i + n - 1);
// 						_alloc.construct(_data + i + n - 1, _data[i - 1]);
// 					}
// 					for (size_type i = len; i != len + n; ++i){
// 						_alloc.construct(_data + i, *first);
// 						++first;
// 					}
// 					_size += n;
// 				}
					
// 			}

// 			iterator erase (iterator position) {
// 				if (position == this->end()) {
// 					this->pop_back();
// 					return iterator(_data + _size);
// 				}
// 				int len = 0;
// 				iterator it_start = this->begin();
// 				while (it_start++ != position) {
// 					len++;
// 				}
// 				_alloc.destroy(_data + len);
// 				for (size_type i = len; i < this->size(); i++) {
// 					_alloc.construct(_data + i, _data[i + 1]);
// 					_alloc.destroy(_data + i + 1);
// 				}
// 				_size--;
// 				return (iterator(_data + len));
// 			}

// 			iterator erase (iterator first, iterator last) {
// 				if (first > last)
// 					throw std::length_error("vector");
// 				size_type indexOfFirst = 0;
// 				size_type indexOfLast = _size;
// 				for (iterator it = begin(); it != first; ++it)
// 					indexOfFirst++;
// 				for (iterator it = end(); it != last; --it)
// 					indexOfLast--;
// 				if (last == end()) {
// 					for (; indexOfLast != indexOfFirst; indexOfLast--)
// 					pop_back();
// 					return end();
// 				}
// 				size_type range = indexOfLast - indexOfFirst;
// 				for (int i = indexOfFirst; indexOfLast < _size; ++i) {
// 					_alloc.destroy(_data + i);
// 					_alloc.construct(_data + i, _data[indexOfLast++]);
// 				}
// 				_size -= range;
// 				return iterator(_data + indexOfFirst);
// 			}

// 			void swap (vector& x){
// 				std::swap(_data, x._data);
// 				std::swap(_size, x._size);
// 				std::swap(_capacity, x._capacity);
// 				std::swap(_alloc, x._alloc);
// 			}

// 			void clear(){
// 				for (size_type i = 0; i < _size; i++){
// 					_alloc.destroy(_data + i);
// 				}
// 				_size = 0;
// 			}


// 			public:
// 				allocator_type get_allocator() const{
// 					return std::allocator<T>(_alloc);
// 				}
// 			};

// 			template <class T, class Allocator>
// 			bool operator== (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
// 				if (lhs.size() != rhs.size())
// 					return false;
// 				typename ft::vector<T, Allocator>::const_iterator it_lhs = lhs.begin();
// 				typename ft::vector<T, Allocator>::const_iterator it_rhs = rhs.begin();
// 				typename ft::vector<T, Allocator>::const_iterator ite_lhs = lhs.end();
// 				while (it_lhs != ite_lhs){
// 					if (*it_lhs != *it_rhs)
// 						return false;
// 					it_lhs++;
// 					it_rhs++;
// 				}
// 				return true;
// 			}

// 			template <class T, class Allocator>
// 			bool operator!= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
// 				return (!(lhs == rhs));
// 			}

// 			template <class T, class Allocator>
// 			bool operator<  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
// 				typename ft::vector<T>::const_iterator it_lhs = lhs.begin();
// 				typename ft::vector<T>::const_iterator it_rhs = rhs.begin();
// 				typename ft::vector<T>::const_iterator ite_lhs = lhs.end();
// 				typename ft::vector<T>::const_iterator ite_rhs = rhs.end();
// 				while (it_lhs != ite_lhs && it_rhs != ite_rhs){
// 					if (*it_lhs < *it_rhs)
// 						return true;
// 					if (*it_lhs > *it_rhs)
// 						return false;
// 					it_lhs++;
// 					it_rhs++;
// 				}
// 				if (it_lhs == ite_lhs && it_rhs != ite_rhs) {
// 					return true;
// 				}
// 				return false;
// 			}

// 			template <class T, class Allocator>
// 			bool operator<= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
// 				return (lhs < rhs || lhs == rhs);
// 			}

// 			template <class T, class Allocator>
// 			bool operator>  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
// 				return (rhs < lhs);
// 			}

// 			template <class T, class Allocator>
// 			bool operator>= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
// 				return (lhs > rhs || lhs == rhs);
// 	}
    
// };

// namespace std{
// 	template <class T, class Allocator>
// 		void swap (ft::vector<T,Allocator>& x, ft::vector<T,Allocator>& y){
// 			x.swap(y);
// 		}
// }

// #endif
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <limits>
#include "utils.hpp"
#include "VectorIter.hpp"

namespace ft{
    template <class T, class Allocator = std::allocator<T> >
    class vector{
        public:
            typedef T                                 					value_type;
            typedef Allocator                         					allocator_type;
            typedef std::size_t                       					size_type;
            typedef T&                            						reference;
            typedef const T&                          					const_reference;
            typedef T*                                					pointer;
            typedef const T*                          					const_pointer;
            typedef class ft::VectorIterator<T>			  				iterator;
            typedef class ft::ConstVectorIterator<T>      				const_iterator;
            typedef class ft::ReverseVectorIterator<T>      			reverse_iterator;
            typedef class ft::ConstReverseVectorIterator<T>  			const_reverse_iterator;
			typedef typename ft::VectorIterator<T>::diff_t				diff_t;

        
        private:
            allocator_type  _alloc;
            size_type       _size;
            size_type       _capacity;
            pointer           _data;

        public:
            explicit vector(const allocator_type &alloc = allocator_type()){
                _alloc = alloc;
                _size = 0;
                _capacity = 0;
               // _data = _alloc.allocate(20);
            }

            explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()){
                _alloc = alloc;
                _size = n;
                _capacity = n;
                _data = _alloc.allocate(_capacity);
                for(size_t i = 0; i < _size; i++)
                    _alloc.construct(_data + i, val);
            }

            template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){
				_alloc = alloc;
				_size = 0;
				_capacity = 20;
				_data = _alloc.allocate(20);
				assign(first, last);
			}

			vector(const vector &x){ //??????
				_size = 0;
				_capacity = 0;
				// _data = NULL;
				// _alloc = x._alloc;
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
					_alloc.destroy(_data + i);
				this->_size = x._size;
				if (_capacity < _size){
					if (_capacity != 0)
						_alloc.deallocate(_data, _capacity);
					_capacity = _size;
					_data = _alloc.allocate(_capacity);
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_data + i, x[i]);
				return (*this);
			}


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
				return (_alloc.max_size());
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
				pointer tmp = this->_alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, _data[i]);
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

			reference operator[] (size_type n){
				return _data[n];
			}

			const_reference operator[] (size_type n) const{
				return _data[n];
			}

			reference at (size_type n){
				if (n >= _size)
					throw std::out_of_range("vector");
				return _data[n];
			}

			const_reference at (size_type n) const{
				if (n >= _size)
					throw std::out_of_range("vector");
				return _data[n];
			}

			reference front(){
				return _data[0];
			}

			const_reference front() const{
				return _data[0];
			}

			reference back(){
				return _data[_size - 1];
			}

			const_reference back() const{
				return _data[_size - 1];
			}

			pointer data() {return (_size ? _data : nullptr);}
			const_pointer data() const {return (_size ? _data : nullptr); }
        //		Modifiers

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){
			size_type n = 0;
			InputIterator tmp = first;
			while (tmp++ != last)
				n++;
			this->clear();
			if (n > _capacity){
				_alloc.deallocate(_data, _capacity);
				_data = _alloc.allocate(n);
				_capacity = n;
			}
			while (first != last)
				this->push_back(*first++);
		}

		void assign (size_type n, const value_type& val){
			_data = _alloc.allocate(20);
			this->clear();
			if (n > _capacity){
				_alloc.deallocate(_data, _capacity);
				_data = _alloc.allocate(n);
				_capacity = n;
			}
			for (size_type i = 0; i < n; i++)
				this->push_back(val);
		}

		void push_back (const value_type& val){
			if (_size == _capacity)
				reserve(_capacity ? _capacity * 2 : 1);
				// this->capacity_realloc(_capacity == 0 ? 1 : _capacity * 2);
			_alloc.construct(_data + _size++, val);
			// _size++;
		}

		void pop_back(){
			if (!empty()){
				_alloc.destroy(_data + _size--);
			}
		}

		iterator insert (iterator position, const value_type& val){
			size_type len = 0;
			iterator it_start = begin();
			while (it_start++ != position) {
				len++;
			}
			if (!_capacity)
				reserve(1);
			if (_size + 1 > _capacity)
				reserve(_size + 1 > _capacity * 2 ? _size + 1 : _capacity * 2);
			for (size_type i = _size; i > len; --i){
				_alloc.destroy(_data + i);
				_alloc.construct(_data + i, _data[i - 1]);
			}
			_alloc.destroy(_data + len);
			_alloc.construct(_data + len, val);
			++_size;
			return iterator(_data + len);
		}

		void insert (iterator position, size_type n, const value_type& val){
			if (n == 0)
				return ;
			if (position == end()) {
				for (size_type i = 0; i < n; i++)
					push_back(val);
				return;
			}
			size_type len = 0;
			iterator it_start = begin();
			while (it_start++ != position) {
				len++;
			}
			if (!_capacity)
					reserve(1);
			if (_size + n > _capacity)
				reserve(_size + n > _capacity * 2 ? _size + n : _capacity * 2);
			for (size_type i = _size; i > len; --i) {
				_alloc.destroy(_data + i + n - 1);
				_alloc.construct(_data + i + n - 1, _data[i - 1]);
			}
			for (size_type i = 0; i < n; ++i){
				_alloc.destroy(_data + len);
				_alloc.construct(_data + len++, val);
			}
			_size += n;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0){

			size_type len = 0;
			iterator it_start = this->begin();
			while (it_start++ != position) {
				len++;
			}
			size_type n = 0;
			InputIterator tmp = first;
			while (tmp++ != last)
				n++;
			if (_size + n > _capacity){
				size_type new_capacity = _size + n > _capacity * 2 ? _size + n : _capacity * 2;
				pointer newArr = _alloc.allocate(new_capacity);
				for (size_type i = 0; i < len; i++)
					_alloc.construct(newArr + i, _data[i]);
				try{
					for(size_type i = 0; i < n; i++, first++)
						_alloc.construct(newArr + len + i, *first);
				} catch(...){
					for (size_type i = 0; i < len + n; i++)
						_alloc.destroy(newArr + i);
					_alloc.deallocate(newArr, new_capacity);
					throw "vector";
				}
				for (size_type i = len; i < _size; ++i)
					_alloc.construct(newArr + n + i, _data[i]);
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				_size += n;
				_capacity = new_capacity;
				_data = newArr;
			} else {
				for (size_type i = _size; i > len; --i){
					_alloc.destroy(_data + i + n - 1);
					_alloc.construct(_data + i + n - 1, _data[i - 1]);
				}
				for (size_type i = len; i != len + n; ++i){
					_alloc.construct(_data + i, *first);
					++first;
				}
				_size += n;
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
			_alloc.destroy(_data + len);
			for (size_type i = len; i < this->size(); i++) {
				_alloc.construct(_data + i, _data[i + 1]);
				_alloc.destroy(_data + i + 1);
			}
			_size--;
			return (iterator(_data + len));
		}

		iterator erase (iterator first, iterator last) {
			if (first > last)
				throw std::length_error("vector");
			size_type indexOfFirst = 0;
			size_type indexOfLast = _size;
			for (iterator it = begin(); it != first; ++it)
				indexOfFirst++;
			for (iterator it = end(); it != last; --it)
				indexOfLast--;
			if (last == end()) {
				for (; indexOfLast != indexOfFirst; indexOfLast--)
				pop_back();
				return end();
			}
			size_type range = indexOfLast - indexOfFirst;
			for (int i = indexOfFirst; indexOfLast < _size; ++i) {
				_alloc.destroy(_data + i);
				_alloc.construct(_data + i, _data[indexOfLast++]);
			}
			_size -= range;
			return iterator(_data + indexOfFirst);
		}

		void swap (vector& x){
			std::swap(_data, x._data);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(_alloc, x._alloc);
		}

		void clear(){
			for (size_type i = 0; i < _size; i++){
				_alloc.destroy(_data + i);
			}
			_size = 0;
		}

		private:
			void delete_vect(){
				if (this->_size != 0){
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, _capacity);
					_capacity = 0;
					_size = 0;
				}
			}

		public:
			allocator_type get_allocator() const{
				return std::allocator<T>(_alloc);
			}
		};

		template <class T, class Allocator>
		bool operator== (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
			if (lhs.size() != rhs.size())
				return false;
			typename ft::vector<T, Allocator>::const_iterator it_lhs = lhs.begin();
			typename ft::vector<T, Allocator>::const_iterator it_rhs = rhs.begin();
			typename ft::vector<T, Allocator>::const_iterator ite_lhs = lhs.end();
			while (it_lhs != ite_lhs){
				if (*it_lhs != *it_rhs)
					return false;
				it_lhs++;
				it_rhs++;
			}
			return true;
		}

		template <class T, class Allocator>
		bool operator!= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
			return (!(lhs == rhs));
		}

		template <class T, class Allocator>
		bool operator<  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
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

		template <class T, class Allocator>
		bool operator<= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
			return (lhs < rhs || lhs == rhs);
		}

		template <class T, class Allocator>
		bool operator>  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs){
			return (rhs < lhs);
		}

		template <class T, class Allocator>
		bool operator>= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
			return (lhs > rhs || lhs == rhs);
	}
    
};

namespace std{
	template <class T, class Allocator>
		void swap (ft::vector<T,Allocator>& x, ft::vector<T,Allocator>& y){
			x.swap(y);
		}
}

#endif