#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#pragma once

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

	template <typename T>
	class random_access_iterator
	{
		public:
			typedef typename iterator_traits<T>::difference_type difference_type;
			typedef typename iterator_traits<T>::value_type value_type;
			typedef typename iterator_traits<T>::pointer pointer;
			typedef typename iterator_traits<T>::reference reference;
			typedef typename iterator_traits<T>::iterator_category iterator_category;

		private:
			pointer _ptr;

		public:
			random_access_iterator() { _ptr = NULL; };
			explicit random_access_iterator (pointer ptr) { _ptr = ptr; };
			template <typename Iter>
			random_access_iterator (const random_access_iterator<Iter>& other ) { *this = other; };
			random_access_iterator& operator=(const random_access_iterator& other)
			{
				_ptr = other._ptr;
				return *this;
			}
			~random_access_iterator() {};

			bool operator==(const random_access_iterator &other) const { return (_ptr == other._ptr); };
			bool operator!=(const random_access_iterator &other) const { return (_ptr != other._ptr); };

			reference	operator*() const { return (*_ptr); };
			pointer	operator->() const { return (_ptr); };

			random_access_iterator& operator++(void) 
			{
				_ptr++;
				return (*this); 
			};
			random_access_iterator operator++(int)
			{
				random_access_iterator tmp = *this;
				_ptr++;
				return (tmp);
			};
			random_access_iterator& operator--(void) 
			{
				_ptr--;
				return (*this); 
			};
			random_access_iterator operator--(int)
			{
				random_access_iterator tmp = *this;
				_ptr--;
				return (tmp);
			};

			random_access_iterator	operator+(const int i) const { return (random_access_iterator(_ptr + i)); };
			random_access_iterator	operator-(const difference_type i) const { return (random_access_iterator(_ptr - i)); };
			difference_type	operator-(const random_access_iterator &other) const { return (_ptr - other._ptr); };

			bool	operator<(const random_access_iterator &other) const { return (_ptr < other._ptr); };
			bool	operator>(const random_access_iterator &other) const { return (_ptr > other._ptr); };
			bool	operator<=(const random_access_iterator &other) const { return (_ptr <= other._ptr); };
			bool	operator>=(const random_access_iterator &other) const { return (_ptr >= other._ptr); };

			random_access_iterator&	operator+=(difference_type i) 
			{
				_ptr += i; 
				return (*this);
			};
			random_access_iterator&	operator-=(difference_type i)
			{
				_ptr -= i;
				return (*this);
			};

			reference	operator[](const difference_type i) const { return (_ptr[i]); };
	};
			
	template <typename T>
	random_access_iterator<T> operator+(int n, random_access_iterator<T> it) { return (random_access_iterator<T>(&*it + n)); };

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

			reverse_iterator();
			explicit reverse_iterator( iterator_type x );
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other );
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other );
			iterator_type base() const;
			reference operator*() const;
			pointer operator->() const;
			reference operator[]( difference_type n ) const;
			reverse_iterator& operator++();
			reverse_iterator& operator--();
			reverse_iterator operator++( int );
			reverse_iterator operator--( int );
			reverse_iterator operator+( difference_type n ) const;
			reverse_iterator operator-( difference_type n ) const;
			reverse_iterator& operator+=( difference_type n );
			reverse_iterator& operator-=( difference_type n );
	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator!=( const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator<( const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator>( const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
					const std::reverse_iterator<Iterator2>& rhs );
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it);
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
}


#endif