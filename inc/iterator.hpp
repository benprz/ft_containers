/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:26:33 by allanganoun       #+#    #+#             */
/*   Updated: 2022/04/15 11:35:43 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>

namespace ft
{


template <typename T>
class	iterator
{
public:

	typedef T							value_type;
	typedef value_type&						reference;
	typedef value_type*						pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	iterator(void) : _ptr(NULL) {}
	iterator(pointer other) : _ptr(other) {}
	iterator(const iterator &src) : _ptr(src._ptr) {}

	virtual ~iterator() {}

	iterator &operator=(iterator const &src) { this->_ptr = src._ptr; return (*this); }

	bool operator ==(T* const base) const { return (_ptr == base); }
	bool operator ==(iterator const& b) const { return (_ptr == b._ptr); }
	bool operator !=(iterator const& b) const { return (_ptr != b._ptr); }
	bool operator >(iterator const& b) const { return (_ptr > b._ptr); }
	bool operator <(iterator const& b) const { return (_ptr < b._ptr); }
	bool operator >=(iterator const& b) const { return (_ptr >= b._ptr); }
	bool operator <=(iterator const& b) const { return (_ptr <= b._ptr); }

	iterator operator +(difference_type b) const { return (iterator(_ptr + b)); }
	iterator operator -(difference_type b) const { return (iterator(_ptr - b)); }
	difference_type operator +(iterator b) { return (_ptr + b._ptr); }
	difference_type operator -(iterator b) { return (_ptr - b._ptr); }
	
	iterator& operator +=(difference_type b) {_ptr += b; return *this; }
	iterator& operator -=(difference_type b) {_ptr -= b; return *this; }


	iterator& operator ++() { _ptr++; return ((*this)); }
	iterator operator ++(int) 													
	{
		T* tmp = _ptr;
		_ptr++;
		return iterator(tmp);
	}
	iterator& operator --() { _ptr--; return ((*this)); }
	iterator operator --(int)
	{
		T* tmp = _ptr;
		_ptr--;
		return iterator(tmp);
	}

	reference operator [](difference_type b) { return (*(_ptr + b)); };
	reference operator *() { return *_ptr; }
	pointer operator ->() { return &(this->operator*()); }


	operator iterator<const T> () const
        { return (iterator<const T>(this->_ptr)); }

	T* base() const {return this->_ptr;}

	private:
		T* _ptr;
};

	template <typename T>
    bool operator==(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator==(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    bool operator!=(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator!=(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    bool operator<(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator<(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    bool operator>(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator>(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    bool operator<=(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator<=(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    bool operator>=(const ft::iterator<T> lhs, const ft::iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator>=(const ft::iterator<T_L> lhs, const ft::iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }


	template <class InputIterator>
	typename InputIterator::difference_type operator-(const InputIterator &lhs, const InputIterator&rhs) {
		return lhs.base() - rhs.base();
	}

	template <class InputIterator>
	InputIterator operator+(const typename InputIterator::difference_type &lhs, const InputIterator&rhs) {
		return rhs + lhs;
	}
}
