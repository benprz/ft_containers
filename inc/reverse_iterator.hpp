/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:12:07 by allanganoun       #+#    #+#             */
/*   Updated: 2022/04/15 11:41:44 by alganoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include "./iterator.hpp"

namespace ft
{


template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator							iterator_type;
            typedef typename Iterator::value_type		value_type;
            typedef typename Iterator::difference_type	difference_type;
            typedef typename Iterator::pointer			pointer;
            typedef typename Iterator::reference		reference;

            reverse_iterator(): _ptr() {}
			
            explicit reverse_iterator (iterator_type it): _ptr(it) {}

            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it) : _ptr(rev_it.base()) {}

            virtual ~reverse_iterator() {}

            iterator_type base() const { return (_ptr); }
            reference operator*() const { iterator_type tmp = _ptr; return (*(--tmp)); }
            reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_ptr - n)); }
            reverse_iterator& operator++() { --_ptr; return (*this); }
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }
            reverse_iterator& operator+= (difference_type n) { _ptr -= n; return (*this); }
            reverse_iterator& operator-= (difference_type n) { _ptr += n; return (*this); }
            reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_ptr + n)); }
            difference_type operator +(reverse_iterator b) { return (b._ptr + _ptr); };
	        difference_type operator -(reverse_iterator b) { return (b._ptr - _ptr); }; 
            reverse_iterator& operator--() { ++_ptr; return (*this); }
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                --(*this);
                return (tmp);
            }
            
            pointer operator->() const { return &(operator*()); }
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

            static const bool input_iter = false;

        private:
            iterator_type     _ptr;
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
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }
}

