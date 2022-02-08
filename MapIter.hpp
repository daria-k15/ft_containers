#ifndef MAPITER_HPP
#define MAPITER_HPP

template <class Value>
struct Node{
	public:
		explicit Node(Value *val = 0) : value(val), parent(0), left(0), right(0), is_black(false), is_nil(false){}

		Value *value;
		Node* parent;
		Node* left;
		Node* right;
		bool is_black;
		bool is_nil;

		Node(Node const& x){
			this->is_black = x.is_black;
			this->value = x.value;
			this->parent = x.parent;
			this->is_nil = x.is_nil;
			this->right = x.right;
			this->left = x.left;
		};

		Node&operator=(const Node& x){
			if (*this != x){
				this->is_black = x.is_black;
				this->value = x.value;
				this->parent = x.parent;
				this->is_nil = x.is_nil;
				this->right = x.right;
				this->left = x.left;
			}
			return *this;
		}

	virtual ~Node(){}
};

private:
	class TreeIterator{
		protected:
			node_pointer _ptr;

			node_pointer find_min(node_pointer point) const{
				while(point->left != NULL && !point->left->is_nil)
					point = point->left;
				return (point);
			}

			node_pointer find_max(node_pointer point) const{
				while (!point->right->is_nil)
					point = point->right;
				return (point);
			}
		public:
			TreeIterator(){
				_ptr = NULL;
			}
			TreeIterator(node_pointer ptr){
				_ptr = ptr;
			}
			~TreeIterator(){}

			reference& operator*() const{
				return *(this->_ptr);
			}

			reference*operator->() const{
				return(this->_ptr);
			}
	};

public:
	typedef class iterator : public TreeIterator{
		public:
			iterator() : TreeIterator(){}
			explicit iterator(node_pointer ptr) : TreeIterator(ptr){}
			iterator& operator=(const iterator& x){
				if (*this == x)
					return (*this);
				this->_ptr = x._ptr;
				return (*this);
			}

			iterator(const iterator& x){
				this->_ptr = x._ptr;
			}

			virtual ~iterator(){}

			iterator& operator++(){
				if (_ptr->right && !_ptr->right->is_nil)
					_ptr = find_min(_ptr->right);
				else{
					node_pointer x = _ptr->parent;
					while (x != NULL && _ptr==x->right){
						_ptr = x;
						x = x->parent;
					}
					_ptr = x;
				}
				return *this;
			}
	}

#endif