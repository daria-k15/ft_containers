#ifndef REFERSEITER_HPP
#define REFERSEITER_HPP

#include "utils.hpp"

namespace ft{
    template<class Iterator>
        class ReverseIterator{
            public:
                typedef Iterator                                                    it_type;
                typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category; 
                typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
                typedef typename ft::iterator_traits<Iterator>::diff_t           diff_t;
                typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
                typedef typename ft::iterator_traits<Iterator>::reference           reference;
            private:
                it_type _it;
            
            public:
                ReverseIterator() : _it(){}
                explicit ReverseIterator(it_type it) : _it(it){}
                template <class Iter>
                ReverseIterator(const ReverseIterator<Iter>& other) : _it(other._it){}
                
                it_type base() const{return _it;}

                reference operator*() const{
                    it_type tmp = _it;
                    return (*--tmp);
                }

                ReverseIterator operator+(diff_t n) const{return (ReverseIterator(_it - n));}
                ReverseIterator operator++(){
                    --_it;
                    return *this;
                }
                ReverseIterator operator++(int){
                    ReverseIterator tmp = *this;
                    ++(*this);
                    return (tmp);
                }
                ReverseIterator operator+=(diff_t n){
                    _it -= n;
                    return *this;
                }

                ReverseIterator operator-(diff_t n) const{return(ReverseIterator(_it + n));}
                ReverseIterator operator--(){
                    ++_it;
                    return *this;
                }
                ReverseIterator operator--(int){
                    ReverseIterator tmp = *this;
                    --(*this);
                    return tmp;
                }
                ReverseIterator operator-=(diff_t n){
                    _it += n;
                    return *this;
                }

                pointer operator->() const{return &(operator*());}
                reference operator[] (diff_t n) const{return _it[-n-1];}
            };
    
    template <class Iterator>
    bool operator==(const ReverseIterator<Iterator> &x, const ReverseIterator<Iterator> &y){
        return x.base() == y.base();
    }
    template <class Iterator>
    bool operator!=(const ReverseIterator<Iterator> &x, const ReverseIterator<Iterator> &y){
        return x.base() != y.base();
    }

    template <class Iterator>
    bool operator<(const ReverseIterator<Iterator> &x, const ReverseIterator<Iterator> &y){
        return x.base() < y.base();
    }
    template <class Iterator>
    bool operator<=(const ReverseIterator<Iterator> &x, const ReverseIterator<Iterator> &y){
        return x.base() <= y.base();
    }

    template <class Iterator>
    bool operator>(const ReverseIterator<Iterator> &x, const ReverseIterator<Iterator> &y){
        return x.base() < y.base();
    }
    template <class Iterator>
    bool operator>=(const ReverseIterator<Iterator> &x, const ReverseIterator<Iterator> &y){
        return x.base() < y.base();
    }

    template <class Iterator>
    ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::diff_t n, const ReverseIterator<Iterator> &t){
        return t+n;
    }

    template <class Iterator>
    typename ReverseIterator<Iterator>::diff_t operator-(const ReverseIterator<Iterator> x, const ReverseIterator<Iterator> &y){
        return x.base() - y.base();
    }

};
	


#endif