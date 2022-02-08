#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>

template <class Value, class Compare = std::less<Value>, class Allocator = std::allocator<Value> >
class rbtree{
	public:
		typedef Value value_type;
		typedef Compare _compare;
		typedef Allocator _alloc;
		typedef typename Allocator::template rebind<Node<Value> >::other	node_alloc;
		typedef typename node_alloc::pointer	node_pointer;
		typedef typename _alloc::reference reference;
		typedef typename _alloc::const_reference const_reference;
		typedef typename _alloc::pointer pointer;
		typedef typename _alloc::const_pointer const_pointer;
		typedef std::ptrdiff_t diff_type;
		typedef std::size_t size_type;
		typedef TreeIterator<Value> iterator;
		typedef TreeIterator<const Value> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverce_iterator;
}

#endif