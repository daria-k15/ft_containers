#ifndef VECTORITER_HPP
#define VECTORITER_HPP

#include "utils.hpp"

namespace ft{
	template <class T>
	class VectorIterator{
		public:
			typedef typename ft::iterator_traits<T *>::value_type 			value_type;
			typedef typename ft::iterator_traits<T *>::pointer				pointer;
			typedef typename ft::iterator_traits<T *>::reference 			reference;
			typedef typename ft::iterator_traits<T *>::difference_type		difference_type;
			typedef typename ft::iterator_traits<T *>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T *>::pointer				iterator_type;
		protected:
			pointer _point;

		public:
			VectorIterator(){}
			~VectorIterator(){}
			VectorIterator(pointer point) : _point(point){}
			VectorIterator(const VectorIterator &x){*this = x; }
			VectorIterator & operator=(const VectorIterator &x){
				if (this != &x){
					_point = x._point;
				}
				return *this;
			}

			bool operator>(const VectorIterator &x) {return _point > x._point; }
			bool operator >= (const VectorIterator &x) { return _point >= x._point; }
			bool operator < (const VectorIterator &x) { return _point < x._point; }
			bool operator <= (const VectorIterator &x) { return _point <= x._point; }
			bool operator==(const VectorIterator &x) { return _point == x._point; }
			bool operator!=(const VectorIterator &x){ return _point != x._point; }

			reference operator*(){ return *this->_point; }
			pointer operator->(){ return &_point; }
			reference operator[](int i) {return _point[i]; }

			VectorIterator & operator++(){
				_point++;
				return *this;
			}

			VectorIterator & operator--(){
				_point--;
				return *this;
			}

			VectorIterator operator++(int){
				VectorIterator tmp(*this);
				*this = operator++();
				return tmp;
			}

			VectorIterator operator--(int){
				VectorIterator tmp(*this);
				*this = operator--();
				return tmp;
			}
			VectorIterator &operator+=(int n){
				this->_point += n;
				return *this;
			}
			VectorIterator&operator-=(int n){
				this->_point -= n;
				return *this;
			}
			VectorIterator operator+(int n){
				VectorIterator tmp(*this);
				return (tmp += n);
			}

			VectorIterator operator-(int n){
				VectorIterator tmp(*this);
				return (tmp -= n);
			}
	};

	template<class T>
	class ConstVectorIterator : public VectorIterator<T>{
		public:
			typedef typename VectorIterator<T>::reference     		reference;
            typedef typename VectorIterator<T>::pointer       		pointer;   
            typedef const typename VectorIterator<T>::reference     const_reference;
            typedef const typename VectorIterator<T>::pointer       const_pointer;   
            ConstVectorIterator() {}
            ~ConstVectorIterator() {}
            ConstVectorIterator(pointer _p) : VectorIterator<T>(_p) {}
            ConstVectorIterator(const ConstVectorIterator & other) {*this = other;}
            ConstVectorIterator & operator=(const ConstVectorIterator & other) {
                if (this != &other)
                    this->_point = other._point;
                return *this;
            }
            const_reference operator*() {return *this->_point;}
            const_pointer operator->() {return this->_point;}
            const_reference operator[](int i) {return *(*this + i);}
	};

	template<class T>
    class ReverseVectorIterator : public VectorIterator<T> {
		public:
			typedef typename VectorIterator<T>::reference     		reference;
			typedef typename VectorIterator<T>::pointer       		pointer;   
			typedef const typename VectorIterator<T>::reference     const_reference;
			typedef const typename VectorIterator<T>::pointer       const_pointer;   
			ReverseVectorIterator() {}
			~ReverseVectorIterator() {}
			ReverseVectorIterator(pointer _p) : VectorIterator<T>(_p) {}
			ReverseVectorIterator(const ReverseVectorIterator & other) {*this = other;}
			ReverseVectorIterator & operator=(const ReverseVectorIterator & other) {
				if (this != &other)
					this->_point = other._point;
				return *this;
			}
			bool operator>(const ReverseVectorIterator & other) const {return this->_point > other._point;}
			bool operator>=(const ReverseVectorIterator & other) const {return this->_point >= other._point;}
			bool operator<(const ReverseVectorIterator & other) const {return this->_point < other._point;}
			bool operator<=(const ReverseVectorIterator & other) const {return this->_point <= other._point;}
			bool operator==(const ReverseVectorIterator & other) const {return this->_point == other._point;}
			bool operator!=(const ReverseVectorIterator & other) const {return this->_point != other._point;}
			ReverseVectorIterator & operator++() {this->_point--; return *this;}
			ReverseVectorIterator & operator--() {this->_point++; return *this;}
			ReverseVectorIterator operator++(int) {
				ReverseVectorIterator  res(*this);
				*this = operator--();
				return res;
			}
			ReverseVectorIterator operator--(int) {
				ReverseVectorIterator res(*this);

				*this = operator++();
				return res;
			}
			ReverseVectorIterator operator+(int n) {
				ReverseVectorIterator temp(*this);

				temp += n;
				return temp;
			}
			ReverseVectorIterator operator-(int n) {
				ReverseVectorIterator temp(*this);

				temp -= n;
				return temp;
			}
			ReverseVectorIterator & operator+=(int n) {
				if (n >= 0)
					while (n--)
						(*this)--;
				else
					while (n++)
						(*this)--;
				return *this;
			}
			ReverseVectorIterator & operator-=(int n) {
				if (n >= 0)
					while (n--)
						(*this)++;
				else
					while (n++)
						(*this)++;
				return *this;
			}
			reference operator[](int i) {return *(*this - i);}
    };

    template<class T>
    class ConstReverseVectorIterator : public ReverseVectorIterator<T> {
        public:
          	typedef typename VectorIterator<T>::reference     		reference;
        	typedef typename VectorIterator<T>::pointer       		pointer;   
        	typedef const typename VectorIterator<T>::reference     const_reference;
        	typedef const typename VectorIterator<T>::pointer       const_pointer;   
            ConstReverseVectorIterator() {}
            ~ConstReverseVectorIterator() {}
            ConstReverseVectorIterator(pointer _p) : ReverseVectorIterator<T>(_p) {}
            ConstReverseVectorIterator(const ConstReverseVectorIterator & other) {*this = other;}
            ConstReverseVectorIterator & operator=(const ConstReverseVectorIterator & other) {
                if (this != &other)
                    this->_point = other._point;
                return *this;
            }
            const_reference operator*() {return *this->_point;}
            const_pointer operator->() {return this->_point;}
            const_reference operator[](int i) {return *(*this - i);}
    };
}

#endif