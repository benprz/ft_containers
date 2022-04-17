#ifndef VECTOR_HPP
#define VECTOR_HPP

#pragma once

#include <memory>
#include <iostream>
#include <iterator>
#include <cmath>

namespace ft
{
	
template<
    typename T,
    class Allocator = std::allocator<T>
> class vector
{
	public:
		//Member types
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef std::size_t									size_type;
		//typedef typename std::ptrdiff_t						difference_type;
		typedef value_type&      							reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer         	pointer;
		//typedef typename allocator_type::const_pointer		const_pointer;
		typedef pointer										iterator;
		//typedef const_pointer								const_iterator;
		typedef typename std::reverse_iterator<iterator>				reverse_iterator;
		//typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		pointer	_container;
		//size_type	_allocated_bytes;
		size_type	_capacity;
		size_type	_size;
	
	public:
		std::allocator<T> alloc;

		vector();
		//explicit vector( const Allocator& alloc );
		//explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
		//template< class InputIt > vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
		//vector( const vector& other );
		~vector();
		//vector& operator=( const vector& other );
		void assign( size_type count, const T& value );
		//template< class InputIt > void assign( InputIt first, InputIt last );
		allocator_type get_allocator() const { return (alloc); };

		//---------------
		// Element access |
		//---------------
		reference at( size_type pos ) { return (_container[pos]); };
		//const_reference at( size_type pos ) const;
		reference operator[]( size_type pos ) { return (_container[pos]); };
		//const_reference operator[]( size_type pos ) const;
		reference front() { return (_container[0]); };
		//const_reference front() const;
		reference back() { return (_container[_size - 1]); };
		//const_reference back() const;
		T* data() { return (&_container[0]); };
		//const T* data() const;

		//----------
		// Iterators |
		//----------
		//iterator begin() { return iterator(_container); };
		//const_iterator begin() const;
		//iterator end() { return (&_container[_size]); };
		//const_iterator end() const;
		//reverse_iterator rbegin() { return (std::reverse_iterator<std::iterator>(_container)); };
		//const_reverse_iterator rbegin() const;
		//reverse_iterator rend() { return (&_container[-1]); };
		//const_reverse_iterator rend() const;

		//---------
		// Capacity |
		//---------
		bool empty() const { return (_size == 0); };
		size_type size() const { return (_size); };
		size_type max_size() const {
			size_type sizeof_type = sizeof(value_type) > 1 ? sizeof(value_type) : 2;
			return (static_cast<size_type>(std::powl(2, sizeof(void *) * 8)) / sizeof_type); 
		};
		void reserve( size_type new_cap );
		size_type capacity() const { return (_capacity); };

		//----------
		// Modifiers |
		//----------
		void clear() { _size = 0; };
		//iterator insert( iterator pos, const T& value );
		//void insert( iterator pos, size_type count, const T& value );
		//template< class InputIt > void insert( iterator pos, InputIt first, InputIt last );
		//iterator erase( iterator pos );
		//iterator erase( iterator first, iterator last );
		void push_back( const T& value );
		void pop_back() { _size--; };
		void resize( size_type count, T value = T() );
		void swap( vector& other );


		//--------------------
		// TOOLS FUNCTIONS
		void increase_container_capacity(size_type new_cap);
};

template<class T, class Allocator>
vector<T, Allocator>::vector()
{
	std::cout << "vector constructor\n";

	_container = NULL;
	//_allocated_bytes = 0;
	_capacity = 0;
	_size = 0;
};

template<class T, class Allocator>
vector<T, Allocator>::~vector()
{
	std::cout << "vector destructor\n";
	for (size_type i = 0; i < _size; i++)
		alloc.destroy(_container + i);
	alloc.deallocate(_container, _capacity);
};

template<class T, class Allocator>
void vector<T, Allocator>::assign( size_type count, const T& value )
{
	if (count > _capacity)
	{
		alloc.deallocate(_container, _capacity);
		_container = alloc.allocate(count);
		_capacity = count;
	}
	_size = count;
	for (int i = 0; i < _size; i++)
		_container[i] = value;
}

//---------------
// Element access |
//---------------
/*
template<class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at( size_type pos )
{
	if (pos >= _size)
		throw ;
	return (_container[pos]);
}
*/

//---------
// Capacity |
//---------
template<class T, class Allocator>
void vector<T, Allocator>::reserve(size_type new_cap)
{
	if (new_cap > _capacity)
	{
		pointer _new_container;

		_capacity = new_cap;
		_new_container = alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; i++)
		{
			alloc.construct(_new_container + i, _container[i]);
			alloc.destroy(_container + i);
		}
		alloc.deallocate(_container, _size);
		_container = _new_container;
	}
}

//----------
// Modifiers |
//----------
template<class T, class Allocator>
void vector<T, Allocator>::push_back(const T& value)
{
	if (_capacity == 0)
	{
		_capacity = 1;
		_container = alloc.allocate(_capacity);
	}
	else if (_capacity == _size)
		increase_container_capacity(_size + 1);
	alloc.construct(&_container[_size], value);
	_size++;
}

template<class T, class Allocator>
void vector<T, Allocator>::resize( size_type count, T value )
{
	if (count > _size)
	{
		if (_capacity < count)
			increase_container_capacity(count);
		for (size_type i = _size; i < count; i++)
			alloc.construct(_container + i, value);
	}
	else if (count < _size)
	{
		for (size_type i = count; i < _size; i++)
			alloc.destroy(_container + i);
	}
	_size = count;
}

template<class T, class Allocator>
void vector<T, Allocator>::swap( vector& other )
{
	pointer tmp_container;
	size_type tmp_capacity;
	size_type tmp_size;

	tmp_container = _container;
	tmp_capacity = _capacity;
	tmp_size = _size;
	_container = other.data();
	_capacity = other.capacity();
	_size = other.size();
	other._container = tmp_container;
	other._capacity = tmp_capacity;
	other._size = tmp_size;
}

//----------------------------------------------
//              TOOLS FUNCTIONS

template<class T, class Allocator>
void vector<T, Allocator>::increase_container_capacity(size_type new_cap)
{
	pointer _new_container;

	if (_capacity * 2 >= new_cap)
		_capacity *= 2;
	else
		_capacity = new_cap;
	_new_container = alloc.allocate(_capacity);
	for (size_type i = 0; i < _size; i++)
	{
		alloc.construct(_new_container + i, _container[i]);
		alloc.destroy(_container + i);
	}
	alloc.deallocate(_container, _size);
	_container = _new_container;
}

}

#endif