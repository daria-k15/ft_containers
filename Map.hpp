#ifndef MAP_HPP
#define MAP_HPP
#include <memory>
#include <limits>
#include <iostream>

namespace ft{
    template <class Key, class T, class Compare=std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
    class Map{
        public:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef std::pair<const Key, T>                     value_type;
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
                    bool operator()(const value_type& lhs, const value_type& rhs) const{
                        return comp(lhs.first, rhs.first);
                    } value_compare;
                private:
                    class node{
                        public:
                            value_type  value;
                            node *parent;
                            node *left;
                            node *right;
                            node(){}
                            node( const value_type& val) : value(val){}
                            node(const node& other) : value(other.value){}
                            ~node(){}
                    };
            }
    };
}

#endif