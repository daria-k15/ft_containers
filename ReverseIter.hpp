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
                typedef typename ft::iterator_traits<Iterator>::difference_type     diff_t;
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
                    it_type tmp(_it);
                    return (*--tmp);
                }

                ReverseIterator operator+(diff_t n) const{return (ReverseIterator(_it - n));}
                ReverseIterator & operator++(){
                    --_it;
                    return *this;
                }
                ReverseIterator operator++(int){
                    ReverseIterator tmp = *this;
                    *this = operator++();
                    return (tmp);
                }
                ReverseIterator operator+=(diff_t n){
                    _it -= n;
                    return *this;
                }

                ReverseIterator operator-(diff_t n) const{return(ReverseIterator(_it + n));}
                ReverseIterator & operator--(){
                    ++_it;
                    return *this;
                }
                ReverseIterator operator--(int){
                    ReverseIterator tmp = *this;
                    *this = operator--();
                    return tmp;
                }
                ReverseIterator operator-=(diff_t n){
                    _it += n;
                    return *this;
                }

                pointer operator->() const{return &(operator*());}
                reference operator[] (diff_t n) const{return _it[-n-1];}
            };
    
    template <class Iter>
    bool operator==(const ReverseIterator<Iter> &x, const ReverseIterator<Iter> &y){
        return x.base() == y.base();
    }
    template <class Iter>
    bool operator!=(const ReverseIterator<Iter> &x, const ReverseIterator<Iter> &y){
        return x.base() != y.base();
    }

    template <class Iter>
    bool operator<(const ReverseIterator<Iter> &x, const ReverseIterator<Iter> &y){
        return x.base() < y.base();
    }
    template <class Iter>
    bool operator<=(const ReverseIterator<Iter> &x, const ReverseIterator<Iter> &y){
        return x.base() <= y.base();
    }

    template <class Iter>
    bool operator>(const ReverseIterator<Iter> &x, const ReverseIterator<Iter> &y){
        return x.base() < y.base();
    }
    template <class Iter>
    bool operator>=(const ReverseIterator<Iter> &x, const ReverseIterator<Iter> &y){
        return x.base() < y.base();
    }

    template <class Iter>
    ReverseIterator<Iter> operator+(typename ReverseIterator<Iter>::diff_t n, const ReverseIterator<Iter> &t){
        return t+n;
    }

    template <class Iter>
    typename ReverseIterator<Iter>::diff_t operator-(const ReverseIterator<Iter> x, const ReverseIterator<Iter> &y){
        return x.base() - y.base();
    }

};
	


#endif