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
            typedef T                                           map_type;
            typedef std::pair<const key_type, map_type>         val_type;
            typedef Compare                                     key_compare;
            typedef Allocator                                   alloc_t;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::const pointer      const_pointer;
            typedef std::ptrdiff_t                              diff_t;
            typedef std::size_t                                 size_type;
    };
}

#endif