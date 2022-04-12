#pragma once

#include <memory>
#include <iostream>
#include <iterator>
#include <cmath>

template<
    typename T,
    class Allocator = std::allocator<T>
> class vector
{
	private:
		//Member types
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef std::size_t									size_type;
		//typedef typename std::ptrdiff_t						difference_type;
		typedef value_type&      							reference;
		//typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer         	pointer;
		//typedef typename allocator_type::const_pointer		const_pointer;
		typedef pointer										iterator;
		//typedef implementation-defined                   const_iterator;
		//typedef std::reverse_iterator<iterator>          reverse_iterator;
		//typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

		iterator	_container;
		size_type	_allocated_bytes;
		size_type	_size;

	public:
		std::allocator<T> alloc;

		//Member functions
		vector();
		~vector();
		vector& operator=( const vector& other );
		void assign( size_type count, const T& value );
		allocator_type get_allocator() const;

		//Element access
		reference at( size_type pos ) { return (_container[pos]); };
		reference operator[]( size_type pos ) { return (_container[pos]); };
		reference front() { return (_container[0]); };
		//reference back() { return (container[size()]); };
		T* data() { return (&_container[0]); };
		//Capacity
		bool empty() const { return (_allocated_bytes == 0); };
		size_type size() const { return (_size); };
		size_type max_size() const { 
			size_type sizeof_type = sizeof(value_type) > 1 ? sizeof(value_type) : 2;
			return (static_cast<size_type>(std::powl(2, sizeof(void *) * 8)) / sizeof_type); 
		}; 
		void reserve( size_type new_cap );
		size_type capacity() const { return (_allocated_bytes / sizeof(T)); };
		//Modifiers
		void clear();
		iterator insert( iterator pos, const T& value );
		iterator erase( iterator pos );
		iterator erase( iterator first, iterator last );
		void push_back( const T& value );
		void pop_back();
		void resize( size_type count );
		void swap( vector& other );
};

template<class T, class Allocator>
vector<T, Allocator>::vector()
{
	std::cout << "vector constructor\n";

	_container = NULL;
	_allocated_bytes = 0;
	_size = 0;
};

template<class T, class Allocator>
vector<T, Allocator>::~vector()
{
	std::cout << "vector destructor\n";
	//alloc.deallocate(_container, _allocated_bytes);
};