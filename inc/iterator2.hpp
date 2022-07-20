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
			typedef typename T::value_type			value_type;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef value_type&				 		reference;
			typedef const value_type&		 		const_reference;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t					difference_type;

		private:
			T* _ptr;

		public:
			bidirectional_iterator() {}
			bidirectional_iterator(T* const ptr) : _ptr(ptr) {}
			bidirectional_iterator(bidirectional_iterator const &c) : _ptr(c._ptr) {}
			bidirectional_iterator& operator=(bidirectional_iterator const &c)
			{
				_ptr = c._ptr;
				return *this;	
			}
			~bidirectional_iterator() {}

			bool operator==(bidirectional_iterator const &c) const { return _ptr == c._ptr; }
			bool operator!=(bidirectional_iterator const &c) const { return _ptr != c._ptr; }

			reference operator*() { return _ptr->data; }
			pointer operator->() { return &_ptr->data; }
			const_reference operator*() const { return _ptr->data; }
			const_pointer operator->() const { return &_ptr->data; }

			bidirectional_iterator& operator++()
			{
				_ptr = _ptr->get_next_node();
				return *this;
			}
			bidirectional_iterator operator++(int)
			{
				T* it = _ptr;
				operator++();
				return bidirectional_iterator(it);
			}
			bidirectional_iterator& operator--()
			{
				_ptr = _ptr->get_previous_node();
				return *this;
			}
			bidirectional_iterator operator--(int)
			{
				T* it = _ptr;
				operator--();
				return bidirectional_iterator(it);
			}

			T* ptr() const { return _ptr; }
	};

	template<typename T>
	class bidirectional_const_iterator
	{
		public:
			typedef typename T::value_type			value_type;
			typedef const value_type*				pointer;
			typedef const value_type&		 		reference;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef std::ptrdiff_t					difference_type;

		private:
			T* _ptr;

		public:
			bidirectional_const_iterator() {}
			bidirectional_const_iterator(T* ptr) : _ptr(ptr) {}
			bidirectional_const_iterator(bidirectional_iterator<T> const &c) : _ptr(c.ptr()) {}
			bidirectional_const_iterator(bidirectional_const_iterator const &c) : _ptr(c._ptr) {}
			bidirectional_const_iterator& operator=(bidirectional_const_iterator const &c)
			{
				_ptr = c._ptr;
				return *this;
			}
			~bidirectional_const_iterator() {}

			bool operator==(bidirectional_const_iterator const &c) const { return _ptr == c._ptr; }
			bool operator!=(bidirectional_const_iterator const &c) const { return _ptr != c._ptr; }

			reference operator*() const { return _ptr->data; }
			pointer operator->() const { return &_ptr->data; }

			bidirectional_const_iterator& operator++()
			{
				_ptr = _ptr->get_next_node();
				return *this;
			}
			bidirectional_const_iterator operator++(int)
			{
				T* it = _ptr;
				operator++();
				return bidirectional_const_iterator(it);
			}
			bidirectional_const_iterator& operator--()
			{
				_ptr = _ptr->get_previous_node();
				return *this;
			}
			bidirectional_const_iterator operator--(int)
			{
				T* it = _ptr;
				operator--();
				return bidirectional_const_iterator(it);
			}
	};

	template <typename T>
    bool operator==(const ft::bidirectional_iterator<T> lhs, const ft::bidirectional_iterator<T> rhs)
    {
        return (lhs.operator*() == rhs.operator*());
    }

    template<typename T_L, typename T_R>
    bool operator==(const ft::bidirectional_iterator<T_L> lhs, const ft::bidirectional_iterator<T_R> rhs)
    {
        return (lhs.operator*() == rhs.operator*());
    }

    template <typename T>
    bool operator!=(const ft::bidirectional_iterator<T> lhs, const ft::bidirectional_iterator<T> rhs)
    {
        return (lhs.operator*() != rhs.operator*());
    }

    template<typename T_L, typename T_R>
    bool operator!=(const ft::bidirectional_iterator<T_L> lhs, const ft::bidirectional_iterator<T_R> rhs)
    {
        return (lhs.operator*() != rhs.operator*());
    }

	template <class Iter>
    class reverse_bidirectional_iterator
    {
        public:
            typedef Iter							iterator_type;
            typedef typename Iter::value_type		value_type;
            typedef typename Iter::difference_type	difference_type;
            typedef typename Iter::pointer			pointer;
            typedef typename Iter::reference		reference;

        private:
            iterator_type _iter;

		public:
            reverse_bidirectional_iterator() {}
            explicit reverse_bidirectional_iterator (iterator_type it): _iter(it) {}
            template <class Iter2>
            reverse_bidirectional_iterator (const reverse_bidirectional_iterator<Iter2>& rev_it): _iter(rev_it.base()) {}
            ~reverse_bidirectional_iterator() {}

            iterator_type base() const { return (_iter); }
            reference operator*() const
			{
				iterator_type tmp(_iter);
				--tmp;
				return *tmp;
			}
            reverse_bidirectional_iterator operator+ (difference_type n) const { return (reverse_bidirectional_iterator(_iter - n)); }
            reverse_bidirectional_iterator& operator++()
			{
				--_iter;
				return (*this);
				}
            reverse_bidirectional_iterator operator++(int)
            {
                reverse_bidirectional_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }
            reverse_bidirectional_iterator& operator+= (difference_type n) { _iter -= n; return (*this); }
            reverse_bidirectional_iterator operator- (difference_type n) const { return (reverse_bidirectional_iterator(_iter + n)); }
            reverse_bidirectional_iterator& operator--()
			{
				++_iter;
				return (*this);
			}
            reverse_bidirectional_iterator operator--(int)
            {
                reverse_bidirectional_iterator tmp = *this;
                --(*this);
                return (tmp);
            }
            reverse_bidirectional_iterator& operator-= (difference_type n)
			{
				_iter += n;
				return (*this);
			}
            pointer operator->() const { return &(operator*()); }
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }
    };

	template <class Iterator>
	bool operator== (const reverse_bidirectional_iterator<Iterator>& lhs, const reverse_bidirectional_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	};
	template <class Iterator>
	bool operator!= (const reverse_bidirectional_iterator<Iterator>& lhs, const reverse_bidirectional_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	};
	template <class Iterator>
	bool operator< (const reverse_bidirectional_iterator<Iterator>& lhs, const reverse_bidirectional_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	};
	template <class Iterator>
	bool operator<= (const reverse_bidirectional_iterator<Iterator>& lhs, const reverse_bidirectional_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	};
	template <class Iterator>
	bool operator> (const reverse_bidirectional_iterator<Iterator>& lhs, const reverse_bidirectional_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	};
	template <class Iterator>
	bool operator>= (const reverse_bidirectional_iterator<Iterator>& lhs, const reverse_bidirectional_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	};

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
			iterator_type _iter;

		public:
			reverse_iterator() : _iter(NULL) {}
			explicit reverse_iterator( iterator_type x ) : _iter(x) {}
			template< typename U >
			reverse_iterator( const reverse_iterator<U>& other ) { *this = other; }
			template< typename U >
			reverse_iterator& operator=( const reverse_iterator& other ) { _iter = other._iter; return *this; }
			iterator_type base() const { return _iter; }
			reference operator*() const { return *_iter; }
			pointer operator->() const { return &(operator*()); }
			reference operator[]( difference_type n ) const { return _iter[n]; }
			reverse_iterator& operator++()
			{
				_iter--;
				return *this;
			}
			reverse_iterator& operator--() 
			{
				_iter++;
				return *this;
			}
			reverse_iterator operator++( int )
			{
				--_iter;
				return *this;
			}
			reverse_iterator operator--( int )
			{
				++_iter;
				return *this;
			}
			reverse_iterator operator+( difference_type n ) const { return (reverse_iterator(_iter - n)); }
			reverse_iterator operator-( difference_type n ) const { return (reverse_iterator(_iter + n)); }
			reverse_iterator& operator+=( difference_type n )
			{
				_iter -= n;
				return *this;
			}
			reverse_iterator& operator-=( difference_type n )
			{
				_iter += n;
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

	template <class Iter>
	reverse_iterator<Iter> operator+ (typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it)
	{
		return reverse_iterator<Iter>(rev_it + n);
	}

	template <class Iter>
	typename reverse_iterator<Iter>::difference_type operator- (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return std::distance(lhs, rhs);
	}
}

#endif