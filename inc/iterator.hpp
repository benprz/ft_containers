#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
	template<typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference 			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template< typename T >
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t 					difference_type;
		typedef T 								value_type;
		typedef T* 								pointer;
		typedef T& 								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template< typename T >
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t 					difference_type;
		typedef T 								value_type;
		typedef const T* 						pointer;
		typedef const T& 						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	class bidirectional_iterator
	{
		public:
			typedef std::ptrdiff_t 					difference_type;
			typedef T								value_type;
			typedef _node_tree<value_type>*			pointer;
			typedef _node_tree<value_type>&			reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

		private:
			pointer _ptr;

		public:
			bidirectional_iterator() {}
			bidirectional_iterator(pointer ptr) : _ptr(ptr) {}
			bidirectional_iterator(bidirectional_iterator const &c) : _ptr(c._ptr) {}
			bidirectional_iterator& operator=(bidirectional_iterator const &c) { _ptr = c._ptr; }
			~bidirectional_iterator() {}

			bool operator==(bidirectional_iterator const &c) const { return _ptr == c._ptr; }
			bool operator!=(bidirectional_iterator const &c) const { return _ptr != c._ptr; }

			reference operator*() const { return _ptr->data; }
			reference operator->() const { return _ptr->data; }

			reference operator=(reference value) {}

			bidirectional_iterator& operator++()
			{
				_ptr = _ptr
				return *this;
			}
			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator it = _ptr;
				operator++();
				return it;
			}
			bidirectional_iterator& operator--()
			{
				return *this;
			}
			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator it = _ptr;
				operator--();
				return it;
			}
	};












/*
	template <typename T>
		class random_access_iterator// : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef  T		value_type;
			typedef std::ptrdiff_t	difference_type;
			typedef T*			pointer;
			typedef T&			reference;
			typedef std::random_access_iterator_tag	iterator_category;

			random_access_iterator() : _current(NULL) {}

			random_access_iterator(pointer ptr) : _current(ptr) {}

			random_access_iterator(const random_access_iterator &cpy) : _current(cpy._current) {}

			virtual ~random_access_iterator() {}

			random_access_iterator &operator=(const random_access_iterator &op)
			{
				if (this == &op)
					return (*this);
				this->_current = op._current;
				return (*this);
			}

			operator random_access_iterator<const T> () const
			{
				return (this->_current);
			}

			reference	operator*() const {return (*_current);}

			pointer		operator->() const
			{
				return (&(this->operator*()));
			}

			random_access_iterator&	operator++()
			{
				++_current;
				return (*this);
			}

			random_access_iterator	operator++(int)
			{
				random_access_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			random_access_iterator&	operator--()
			{
				--_current;
				return (*this);
			}

			random_access_iterator	operator--(int)
			{
				random_access_iterator tmp(*this);
				operator--();
				return (tmp);
			}

			random_access_iterator	operator+(difference_type n) const
			{
				return (_current + n);
			}

			random_access_iterator	operator-(difference_type n) const
			{
				return (_current - n);
			}

			random_access_iterator	operator+=(difference_type n)
			{
				_current += n;
				return (*this);
			}

			random_access_iterator	operator-=(difference_type n)
			{
				_current -= n;
				return (*this);
			}

			reference	operator[](difference_type n) const
			{
				return (*(_current + n));
			}

			friend bool operator==(const random_access_iterator<T> &it1, const random_access_iterator<T> &it2)
			{
				return (it1._current == it2._current);
			}

			friend bool operator!=(const random_access_iterator<T> &it1, const random_access_iterator<T> &it2)
			{
				return (it1._current != it2._current);
			}

			const pointer& base() const	{ return _current; }

		protected:
			pointer _current;

	};

	template <class T>
		bool operator==(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() == rhs.base();
		}

	template <class T>
		bool operator!=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() != rhs.base();
		}

	template <class T>
		bool operator<(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() < rhs.base();
		}
	template <class TL, class TR>
		bool operator<(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs)
		{
			return lhs.base() < rhs.base();
		}

	template <class T>
		bool operator>(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() > rhs.base();
		}

	template <class TL, class TR>
		bool operator>(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs)
		{
			return lhs.base() > rhs.base();
		}

	template <class T>
		bool operator<=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

	template <class TL, class TR>
		bool operator<=(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

	template <class TL, class TR>
		bool operator>=(const random_access_iterator<TL>& lhs, const random_access_iterator<TR>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

	template <class T>
		bool operator>=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

	template <class T>
		random_access_iterator<T>
		operator+(typename random_access_iterator<T>::difference_type lhs, const random_access_iterator<T> rhs)
		{
			return lhs + rhs.base();
		}

	template <class T, class U>
		typename random_access_iterator<T>::difference_type
		operator-(const random_access_iterator<T> lhs, const random_access_iterator<U> rhs)
		{
			return lhs.base() - rhs.base();
		}

	template <class Iterator>
		class reverse_iterator
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		protected:
			Iterator baseIt;

		public:
			reverse_iterator() : baseIt() { }
			explicit reverse_iterator(iterator_type it) : baseIt(it) { }
			template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) :
					baseIt(rev_it.base()) { }

			iterator_type base() const { return baseIt; }

			reference operator*() const
			{
				Iterator tmp = baseIt;
				return *--tmp;
			}
			reverse_iterator operator+(difference_type n) const
			{
				return reverse_iterator (baseIt - n);
			}
			reverse_iterator& operator++()
			{
				--baseIt;
				return *this;
			}
			reverse_iterator  operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}
			reverse_iterator& operator+=(difference_type n)
			{
				baseIt -= n;
				return *this;
			}
			reverse_iterator operator-(difference_type n) const
			{
				return reverse_iterator (baseIt + n);
			}
			reverse_iterator& operator--()
			{
				++baseIt;
				return *this;
			}
			reverse_iterator  operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}
			reverse_iterator& operator-=(difference_type n)
			{
				baseIt += n;
				return *this;
			}
			pointer operator->() const						{ return &(operator*()); }
			reference operator[](difference_type n) const	{ return base()[- n - 1]; }

			template <class IteratorF>
				friend bool operator>=(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator>(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator<=(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator<(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator!=(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);
			template <class IteratorF>
				friend bool operator==(const reverse_iterator<IteratorF>& lhs,
						const reverse_iterator<IteratorF>& rhs);

	};
	template <class IteratorL, class IteratorR>
		bool operator==(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() == rhs.base();
		}

	template <class Iterator>
		bool operator==(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() == rhs.base();
		}

	template <class IteratorL, class IteratorR>
		bool operator!=(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return !(lhs == rhs);
		}

	template <class Iterator>
		bool operator!=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return !(lhs == rhs);
		}

	template <class IteratorL, class IteratorR>
		bool operator<(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() > rhs.base();
		}

	template <class Iterator>
		bool operator<(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() > rhs.base();
		}

	template <class IteratorL, class IteratorR>
		bool operator<=(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

	template <class Iterator>
		bool operator<=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() >= rhs.base();
		}

	template <class IteratorL, class IteratorR>
		bool operator>(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() < rhs.base();
		}

	template <class Iterator>
		bool operator>(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() < rhs.base();
		}

	template <class IteratorL, class IteratorR>
		bool operator>=(const reverse_iterator<IteratorL>& lhs,
				const reverse_iterator<IteratorR>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

	template <class Iterator>
		bool operator>=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() <= rhs.base();
		}

	template <class Iterator>
		reverse_iterator<Iterator>
		operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> rhs)
		{
			return reverse_iterator<Iterator>(rhs.base() - n);
		}

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type
		operator-(const reverse_iterator<Iterator> lhs, const reverse_iterator<Iterator> rhs)
		{
			return rhs.base() - lhs.base();
		}

	template <class IteratorL, class IteratorR>
		typename reverse_iterator<IteratorL>::difference_type
		operator-(const reverse_iterator<IteratorL> lhs, const reverse_iterator<IteratorR> rhs)
		{
			return rhs.base() - lhs.base();
		}
		*/
	template <typename T>
	class random_access_iterator
	{
		public:
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;

		private:
			pointer _current;

		public:
			random_access_iterator() : _current(NULL) {}
			random_access_iterator (pointer ptr) : _current(ptr) {}
			random_access_iterator (const random_access_iterator& other ) : _current(other._current) {}
			random_access_iterator& operator=(const random_access_iterator& other)
			{
				_current = other._current;
				return *this;
			}
			~random_access_iterator() {}

			operator random_access_iterator<const T> () const { return (_current); }

			bool operator==(const random_access_iterator &other) const { return (_current == other._current); }
			bool operator!=(const random_access_iterator &other) const { return (_current != other._current); }

			reference	operator*() const { return (*_current); }
		/*
			pointer	operator->() const { return (_current); }

			random_access_iterator& operator++(void) 
			{
				_current++;
				return (*this); 
			}
			random_access_iterator operator++(int)
			{
				random_access_iterator tmp = *this;
				_current++;
				return (tmp);
			}
			random_access_iterator& operator--(void) 
			{
				_current--;
				return (*this); 
			}
			random_access_iterator operator--(int)
			{
				random_access_iterator tmp = *this;
				_current--;
				return (tmp);
			}

			random_access_iterator	operator+(const int i) const { return (random_access_iterator(_current + i)); }
			random_access_iterator	operator-(const difference_type i) const { return (random_access_iterator(_current - i)); }
			difference_type	operator-(const random_access_iterator &other) const { return (_current - other._current); }

			bool	operator<(const random_access_iterator &other) const { return (_current < other._current); }
			bool	operator>(const random_access_iterator &other) const { return (_current > other._current); }
			bool	operator<=(const random_access_iterator &other) const { return (_current <= other._current); }
			bool	operator>=(const random_access_iterator &other) const { return (_current >= other._current); }

			random_access_iterator&	operator+=(difference_type i) 
			{
				_current += i; 
				return (*this);
			}
			random_access_iterator&	operator-=(difference_type i)
			{
				_current -= i;
				return (*this);
			}

			reference	operator[](const difference_type i) const { return (_current[i]); }
			*/


			pointer		operator->() const
			{
				return (&(this->operator*()));
			}

			random_access_iterator&	operator++()
			{
				++_current;
				return (*this);
			}

			random_access_iterator	operator++(int)
			{
				random_access_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			random_access_iterator&	operator--()
			{
				--_current;
				return (*this);
			}

			random_access_iterator	operator--(int)
			{
				random_access_iterator tmp(*this);
				operator--();
				return (tmp);
			}

			random_access_iterator	operator+(difference_type n) const
			{
				return (_current + n);
			}

			random_access_iterator	operator-(difference_type n) const
			{
				return (_current - n);
			}

			random_access_iterator	operator+=(difference_type n)
			{
				_current += n;
				return (*this);
			}

			random_access_iterator	operator-=(difference_type n)
			{
				_current -= n;
				return (*this);
			}

			reference	operator[](difference_type n) const
			{
				return (*(_current + n));
			}

			friend bool operator==(const random_access_iterator<T> &it1, const random_access_iterator<T> &it2)
			{
				return (it1._current == it2._current);
			}

			friend bool operator!=(const random_access_iterator<T> &it1, const random_access_iterator<T> &it2)
			{
				return (it1._current != it2._current);
			}

			const pointer& base() const	{ return _current; }
	};
			
	template <typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, random_access_iterator<T> it) { return (random_access_iterator<T>(&*it + n)); }

	template< class Iter >
	class reverse_iterator
	{
		public:
			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;

		private:
			iterator_type current;

		public:
			reverse_iterator() : current(NULL) {}
			explicit reverse_iterator( iterator_type x ) : current(x) {}
			template< typename U >
			reverse_iterator( const reverse_iterator<U>& other ) { *this = other; }
			template< typename U >
			reverse_iterator& operator=( const reverse_iterator& other ) { current = other.current; return *this; }
			iterator_type base() const { return current; }
			reference operator*() const { return *current; }
			pointer operator->() const { return current; }
			reference operator[]( difference_type n ) const { return current[n]; }
			reverse_iterator& operator++()
			{
				current--;
				return *this;
			}
			reverse_iterator& operator--() 
			{
				current++;
				return *this;
			}
			reverse_iterator operator++( int )
			{
				--current;
				return *this;
			}
			reverse_iterator operator--( int )
			{
				++current;
				return *this;
			}
			reverse_iterator operator+( difference_type n ) const { return (reverse_iterator(current - n)); }
			reverse_iterator operator-( difference_type n ) const { return (reverse_iterator(current + n)); }
			reverse_iterator& operator+=( difference_type n )
			{
				current -= n;
				return *this;
			}
			reverse_iterator& operator-=( difference_type n )
			{
				current += n;
				return *this;
			}
	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		if (lhs.base() == rhs.base())
			return true;
		return false;
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		if (lhs.base() != rhs.base())
			return true;
		return false;
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		if (lhs.base() > rhs.base())
			return true;
		return false;
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		if (lhs.base() >= rhs.base())
			return true;
		return false;
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		if (lhs.base() < rhs.base())
			return true;
		return false;
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs )
	{
		if (lhs.base() <= rhs.base())
			return true;
		return false;
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return std::distance(lhs, rhs);
	}
}


#endif