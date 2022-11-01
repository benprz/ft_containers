#pragma once

#include <iterator>

namespace ft
{
	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	> struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template<typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference 			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t 					difference_type;
		typedef T 								value_type;
		typedef T* 								pointer;
		typedef T& 								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t 					difference_type;
		typedef T 								value_type;
		typedef const T* 						pointer;
		typedef const T& 						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	class vector_iterator
	{
		public:
			typedef typename iterator_traits<T*>::difference_type	difference_type;
			typedef typename iterator_traits<T*>::value_type			value_type;
			typedef typename iterator_traits<T*>::pointer			pointer;
			typedef typename iterator_traits<T*>::reference			reference;
			typedef typename iterator_traits<T*>::iterator_category	iterator_category;

		private:
			pointer _base;

		public:
			vector_iterator() : _base(NULL) {}
			vector_iterator(pointer base) : _base(base) {}
			vector_iterator(const vector_iterator<const T> &vector) : _base(vector._base) {}
			vector_iterator& operator=(const vector_iterator &vector)
			{
				_base = vector.base();
				return *this;
			}
			~vector_iterator() {}

			T* base() const { return _base; }
			operator vector_iterator<const T> () const { return (_base); }
			bool operator==(const vector_iterator &vector) const { return _base == vector._base; }
			bool operator!=(const vector_iterator &vector) const { return _base != vector._base; }
			reference operator*() const { return *_base; }
			pointer operator->() const { return &(operator*()); }
			vector_iterator& operator++()
			{
				++_base;
				return *this;
			}
			vector_iterator operator++(int)
			{
				vector_iterator tmp = *this;
				operator++();
				return tmp;
			}
			vector_iterator& operator--()
			{
				--_base;
				return *this;
			}
			vector_iterator operator--(int)
			{
				vector_iterator tmp = *this;
				operator--();
				return tmp;
			}
			vector_iterator& operator+=(const difference_type b)
			{
				_base += b;
				return *this;
			}
			vector_iterator operator+(const difference_type b) const
			{
				vector_iterator tmp = *this;
				return tmp += b;
			}
			vector_iterator& operator-=(const difference_type b)
			{
				_base -= b;
				return *this;
			}
			vector_iterator operator-(const difference_type b) const
			{
				vector_iterator tmp = *this;
				return tmp -= b;
			}
			difference_type operator-(const vector_iterator &b) { return _base - b._base; }
			reference operator[](difference_type b) { return _base[b]; }
			bool operator<(const vector_iterator &b) const { return _base < b._base; }
			bool operator>(const vector_iterator &b) const { return _base > b._base; }
			bool operator<=(const vector_iterator &b) const { return _base <= b._base; }
			bool operator>=(const vector_iterator &b) const { return _base >= b._base; }
	};

	template<typename T, typename T2>
	bool operator==(const vector_iterator<T> &a, const vector_iterator<T2> &b)
	{
		return a.base() == b.base();
	}
	template<typename T, typename T2>
	bool operator!=(const vector_iterator<T> &a, const vector_iterator<T2> &b)
	{
		return a.base() != b.base();
	}
	template<typename T, typename T2>
	bool operator<(const vector_iterator<T> &a, const vector_iterator<T2> &b)
	{
		return a.base() < b.base();
	}
	template<typename T, typename T2>
	bool operator>(const vector_iterator<T> &a, const vector_iterator<T2> &b)
	{
		return a.base() > b.base();
	}
	template<typename T, typename T2>
	bool operator<=(const vector_iterator<T> &a, const vector_iterator<T2> &b)
	{
		return a.base() <= b.base();
	}
	template<typename T, typename T2>
	bool operator>=(const vector_iterator<T> &a, const vector_iterator<T2> &b)
	{
		return a.base() >= b.base();
	}
	template<typename T>
	vector_iterator<T> operator+(const typename vector_iterator<T>::difference_type b, const vector_iterator<T> a)
	{
		return a.operator+(b);
	}
	template<typename T>
	vector_iterator<T> operator-(const vector_iterator<T> a, const typename vector_iterator<T>::difference_type b)
	{
		return a - b;
	}
	template<typename T, typename U>
	typename vector_iterator<T>::difference_type operator-(const vector_iterator<T> a, const vector_iterator<U> b)
	{
		return a.base() - b.base();
	}

	template<typename T>
	class map_iterator
	{
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef typename T::value_type			value_type;
			typedef value_type*						pointer;
			typedef value_type& 					reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

		private:
			T* _base;

		public:
			map_iterator() : _base(NULL) {}
			map_iterator(T* base) : _base(base) {}
			map_iterator(const map_iterator &map) : _base(map._base) {}
			map_iterator& operator=(const map_iterator &map)
			{
				_base = map.base();
				return *this;
			}
			~map_iterator() {}

			reference operator*() const { return _base->data; }
			pointer operator->() const { return &(operator*()); }
			map_iterator& operator++()
			{
				_base = _base->get_next_node();
				return *this;
			}
			map_iterator operator++(int)
			{
				map_iterator tmp = *this;
				operator++();
				return tmp;
			}
			map_iterator& operator--()
			{
				_base = _base->get_previous_node();
				return *this;
			}
			map_iterator operator--(int)
			{
				map_iterator tmp = *this;
				operator--();
				return tmp;
			}
			bool operator==(const map_iterator &map) const { return _base == map._base; }
			bool operator!=(const map_iterator &map) const { return _base != map._base; }
			T* base() const { return _base; }
	};

	template<typename T>
	class const_map_iterator
	{
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef typename T::value_type			value_type;
			typedef const value_type*				pointer;
			typedef const value_type& 				reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

		private:
			T* _base;

		public:
			const_map_iterator() : _base(NULL) {}
			const_map_iterator(T* base) : _base(base) {}
			const_map_iterator(const map_iterator<T> &map) : _base(map.base()) {}
			const_map_iterator(const const_map_iterator &map) : _base(map._base) {}
			const_map_iterator& operator=(const const_map_iterator &map)
			{
				_base = map.base();
				return *this;
			}
			~const_map_iterator() {}

			reference operator*() const { return _base->data; }
			pointer operator->() const { return &(operator*()); }
			const_map_iterator& operator++()
			{
				_base = _base->get_next_node();
				return *this;
			}
			const_map_iterator operator++(int)
			{
				const_map_iterator tmp = *this;
				operator++();
				return tmp;
			}
			const_map_iterator& operator--()
			{
				_base = _base->get_previous_node();
				return *this;
			}
			const_map_iterator operator--(int)
			{
				const_map_iterator tmp = *this;
				operator--();
				return tmp;
			}
			bool operator==(const const_map_iterator &map) const { return _base == map._base; }
			bool operator!=(const const_map_iterator &map) const { return _base != map._base; }
			T* base() const { return _base; }
	};

	template <class Iterator>
	class reverse_iterator
	: public iterator<
				typename iterator_traits<Iterator>::iterator_category,
				typename iterator_traits<Iterator>::value_type,
				typename iterator_traits<Iterator>::difference_type,
				typename iterator_traits<Iterator>::pointer,
				typename iterator_traits<Iterator>::reference
				>
	{
		public:
			typedef Iterator											iterator_type;
			typedef typename iterator_traits<Iterator>::value_type		value_type;
			typedef typename iterator_traits<Iterator>::difference_type	difference_type;
			typedef typename iterator_traits<Iterator>::pointer			pointer;
			typedef typename iterator_traits<Iterator>::reference		reference;

		private:
			iterator_type     _base;

		public:
			reverse_iterator(): _base() {}
			explicit reverse_iterator (iterator_type it): _base(it) {}
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it.base()) {}
			~reverse_iterator() {}

			iterator_type base() const { return (_base); }
			reference operator*() const { iterator_type tmp = _base; return (*(--tmp)); }
			reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_base - n)); }
			reverse_iterator& operator++() { --_base; return (*this); }
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}
			reverse_iterator& operator+= (difference_type n) { _base -= n; return (*this); }
			reverse_iterator& operator-= (difference_type n) { _base += n; return (*this); }
			reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_base + n)); }
			difference_type operator +(reverse_iterator b) { return (b._base + _base); };
			difference_type operator -(reverse_iterator b) { return (b._base - _base); }; 
			reverse_iterator& operator--() { ++_base; return (*this); }
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}
			
			pointer operator->() const { return &(operator*()); }
			reference operator[] (difference_type n) const { return (base()[-n - 1]); }

	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) 
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator== (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator!= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator< (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator<= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator> (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator_L, class Iterator_R>
	bool operator>= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
}