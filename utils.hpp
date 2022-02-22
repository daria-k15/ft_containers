#ifndef UTILS_HPP
#define UTILS_HPP

#include <iterator>

namespace ft{
	template<bool B, class T = void>
	struct enable_if{};

	template<class T>
	struct enable_if<true, T>{
		typedef T	type;
	};

	template<class T>struct remove_const{typedef T type;};
	template<class T>struct remove_const<const T>{typedef T type;};

	template<class T, bool V>
	struct integral_const{
		static const bool value = V;
		typedef T value_type;
		typedef integral_const type;
		operator value_type() const{return value;}
	};

	template<class T> struct is_integral : public ft::integral_const<T, false>{};
	template <> struct is_integral<bool> : public ft::integral_const<bool, true>{};
	template <> struct is_integral<char> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<signed char>	: public ft::integral_const<bool, true> {};
	template <> struct is_integral<unsigned char> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<wchar_t>	 : public ft::integral_const<bool, true> {};
	template <> struct is_integral<char16_t> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<short> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<unsigned short> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<int>	: public ft::integral_const<bool, true> {};
	template <> struct is_integral<unsigned int> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<long> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<unsigned long> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<long long> : public ft::integral_const<bool, true> {};
	template <> struct is_integral<unsigned long long>	: public ft::integral_const<bool, true> {};
	
	template<class InputIter1, class InputIter2>
	bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2){
		for (; first1 != last1; ++first1, ++first2){
			if (*first1 != *first2)
				return false;
		}
		return true;
	}

	template<class InputIter1, class InputIter2, class BinaryPredicate>
	bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, BinaryPredicate p) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
    	return true;
	}

	template<class InputIter1, class InputIter2>
	bool lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (comp(*first1, *first2)) return true;
			if (comp(*first2, *first1)) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class Iterator>
	class iterator_traits{
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>{
		public:		
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>{
		public:		
			typedef std::ptrdiff_t						difference_type;
			typedef const T								value_type;
			typedef const T*							pointer;
			typedef const T&							reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};

	template<class K, class V>
	struct pair {
		typedef K	first_type;
		typedef V	second_type;
		first_type first;
		second_type second;
		pair() : first(), second() {}
		pair(const first_type & x, const second_type & y) : first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2> & other) : first(other.first), second(other.second) {}
		pair(const pair & other) : first(other.first), second(other.second) {}
		pair & operator=(const pair & other) {
			if (this != &other) {
				first = other.first;
				second = other.second;
			}
			return *this;
		}
	};
	template<class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 t, T2 u) { return ft::pair<T1, T2>(t, u); }

	template< class T1, class T2 >
	bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }

	template< class T1, class T2 >
	bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs == rhs); }
	
	template< class T1, class T2 >
	bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		if (lhs.first < rhs.first)
			return true;
		if (lhs.first > rhs.first)
			return false;
		return lhs.second < rhs.second;
	}
	template< class T1, class T2 >
	bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return lhs < rhs || lhs == rhs; }
	template< class T1, class T2 >
	bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs <= rhs); }
	template< class T1, class T2 >
	bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs < rhs); }


	template <class Value>
	struct Node{
		public:
			Value *value;
			Node* parent;
			Node* left;
			Node* right;
			bool is_black;
			bool is_nil;

			explicit Node(Value *val = NULL) : value(val), parent(NULL), left(NULL), right(NULL), is_black(false), is_nil(false){}
			Node(Node const& x){
				*this = x;
			};

			Node&operator=(const Node& x){
				if (this != &x){
					is_black = x.is_black;
					value = x.value;
					parent = x.parent;
					is_nil = x.is_nil;
					right = x.right;
					left = x.left;
				}
				return *this;
			}

	};
};

#endif