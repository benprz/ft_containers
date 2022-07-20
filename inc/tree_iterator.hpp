#pragma once

#include <cstddef>
#include "pair.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <iostream>
#include <memory>
#include <algorithm>
#include <cstddef>

namespace ft
{
template <typename T>
class	tree_iterator
{
public:

	typedef T							value_type;
	typedef typename T::value_type    	pair;
	typedef pair&						reference;
	typedef const pair&					const_reference;
	typedef pair*						pointer;
	typedef const pair*					const_pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	tree_iterator(void) : _node(NULL) {}
	tree_iterator(T* other) : _node(other) {}
	tree_iterator(const tree_iterator &src) { *this = src; }

	virtual ~tree_iterator() {}

	tree_iterator &operator=(tree_iterator const &src) { _node = src._node; return (*this); }

	bool operator ==(T* const base) const { return (_node == base); }
	bool operator ==(tree_iterator const& b) const { return (_node == b._node); }
	bool operator !=(tree_iterator const& b) const { return (!(_node == b._node)); }

	tree_iterator& operator ++() { _node = _node->get_next_node(); return ((*this)); }
	tree_iterator operator ++(int)
	{
		T* tmp = _node;
		_node = _node->get_next_node();
		return tree_iterator(tmp);
	}
	tree_iterator& operator --() { _node = _node->get_previous_node(); return ((*this)); }
	tree_iterator operator --(int)
	{
		T* tmp = _node;
		_node = _node->get_previous_node();
		return tree_iterator(tmp);
	}

	reference operator *() { return (_node->data); }
	const_reference operator *() const { return (_node->data); }
	pointer operator ->() { return &(_node->data); }
	const_pointer operator ->() const { return &(_node->data); }

	T* base() const {return _node;};

	private:
		T* _node;
};

template <typename T>
class	const_tree_iterator
{
public:

	typedef T							value_type;
	typedef typename T::value_type    	pair;
	typedef const pair&					reference;
	typedef const pair*					pointer;
	typedef typename std::ptrdiff_t 	difference_type;

	const_tree_iterator(void) : _node(NULL) {}
	const_tree_iterator(T* other) : _node(other) {}
	const_tree_iterator(const const_tree_iterator &src) { *this = src; }
	const_tree_iterator(const tree_iterator<value_type> &src) { _node = src.base(); }

	virtual ~const_tree_iterator() {}

	const_tree_iterator &operator=(const_tree_iterator const &src) { _node = src._node; return (*this); }

	bool operator ==(T* const base) const { return (_node == base); }
	bool operator ==(const_tree_iterator const& b) const { return (_node == b._node); }
	bool operator !=(const_tree_iterator const& b) const { return (!(_node == b._node)); }

	const_tree_iterator& operator ++() { _node = _node->get_next_node(); return ((*this)); }
	const_tree_iterator operator ++(int)
	{
		T* tmp = _node;
		_node = _node->get_next_node();
		return const_tree_iterator(tmp);
	}
	const_tree_iterator& operator --() { _node = _node->get_previous_node(); return ((*this)); }
	const_tree_iterator operator --(int)
	{
		T* tmp = _node;
		_node = _node->get_previous_node();
		return const_tree_iterator(tmp);
	}

	reference operator *() const { return (_node->data); }
 	pointer operator ->() const { return &(_node->data); }

 	T* base() const {return _node;}

 	private:
 		T* _node;

};

	template <class Iterator>
    class tree_reverse_iterator
    {
        public:
            typedef Iterator							iterator_type;
            typedef typename Iterator::value_type		value_type;
            typedef typename Iterator::difference_type	difference_type;
            typedef typename Iterator::pointer			pointer;
            typedef typename Iterator::reference		reference;

            tree_reverse_iterator(): _elem() {}

            explicit tree_reverse_iterator (iterator_type it): _elem(it) {}

            template <class Iter>
            tree_reverse_iterator (const tree_reverse_iterator<Iter>& rev_it): _elem(rev_it.base()) {}

            virtual ~tree_reverse_iterator() {}

            iterator_type base() const { return (_elem); }
            reference operator*() const { iterator_type tmp = _elem; return (*(--tmp)); }
            tree_reverse_iterator operator+ (difference_type n) const { return (tree_reverse_iterator(_elem - n)); }
            tree_reverse_iterator& operator++() { --_elem; return (*this); }
            tree_reverse_iterator operator++(int)
            {
                tree_reverse_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }
            tree_reverse_iterator& operator+= (difference_type n) { _elem -= n; return (*this); }
            tree_reverse_iterator operator- (difference_type n) const { return (tree_reverse_iterator(_elem + n)); }
            tree_reverse_iterator& operator--() { ++_elem; return (*this); }
            tree_reverse_iterator operator--(int)
            {
                tree_reverse_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

            tree_reverse_iterator& operator-= (difference_type n) { _elem += n; return (*this); }
            pointer operator->() const { return &(operator*()); }
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

        private:
            iterator_type     _elem;
    };

	template <typename T>
    bool operator==(const ft::tree_iterator<T> lhs, const ft::tree_iterator<T> rhs)
    {
        return (lhs.operator*() == rhs.operator*());
    }

    template<typename T_L, typename T_R>
    bool operator==(const ft::tree_iterator<T_L> lhs, const ft::tree_iterator<T_R> rhs)
    {
        return (lhs.operator*() == rhs.operator*());
    }

    template <typename T>
    bool operator!=(const ft::tree_iterator<T> lhs, const ft::tree_iterator<T> rhs)
    {
        return (lhs.operator*() != rhs.operator*());
    }

    template<typename T_L, typename T_R>
    bool operator!=(const ft::tree_iterator<T_L> lhs, const ft::tree_iterator<T_R> rhs)
    {
        return (lhs.operator*() != rhs.operator*());
    }

	template <class Iterator>
	bool operator== (const tree_reverse_iterator<Iterator>& lhs, const tree_reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	};
	template <class Iterator>
	bool operator!= (const tree_reverse_iterator<Iterator>& lhs, const tree_reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	};
	template <class Iterator>
	bool operator< (const tree_reverse_iterator<Iterator>& lhs, const tree_reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	};
	template <class Iterator>
	bool operator<= (const tree_reverse_iterator<Iterator>& lhs, const tree_reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	};
	template <class Iterator>
	bool operator> (const tree_reverse_iterator<Iterator>& lhs, const tree_reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	};
	template <class Iterator>
	bool operator>= (const tree_reverse_iterator<Iterator>& lhs, const tree_reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	};
}

