#ifndef VECTOR_HPP
#define VECTOR_HPP

#pragma once

#include "iterator.hpp"
#include "utils.hpp"

#include <memory>
#include <iostream>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <type_traits>

namespace ft
{
	template<
		typename T,
		class Allocator = std::allocator<T>
	> class vector
	{
		public:
			//Member types
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;
			typedef typename allocator_type::reference      			reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer         			pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef	typename ft::random_access_iterator<pointer>		iterator;
			typedef typename ft::random_access_iterator<const_pointer>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			pointer				_container;
			size_type			_capacity;
			size_type			_size;
			allocator_type		_alloc;
		
		public:
			vector() : _container(NULL), _capacity(0), _size(0) {};
			explicit vector( const Allocator& alloc ) : _alloc(alloc) { vector(); };
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
				: _capacity(count), _size(count), _alloc(alloc)
			{
				_container = _alloc.allocate(count);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_container + i, value);
			};
			template< class InputIt > 
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename std::enable_if<!std::is_integral<InputIt>::value, int>::type = 0) : _alloc(alloc)
			{
				size_type dist = std::distance(first, last);
				_size = dist;
				_capacity = _size;
				_container = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_container + i, *first++);
			};
			vector( const vector& other ) : _capacity(0)
			{
				*this = other;
			};
			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_container + i);
				if (_capacity)
					_alloc.deallocate(_container, _capacity);
			};
			vector& operator=( const vector& other )
			{
				_size = other._size;
				if (_capacity < other._size)
				{
					_capacity = _size;
					_container = _alloc.allocate(_capacity);
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_container + i, other[i]);
				return *this;
			};
			void assign( size_type count, const T& value )
			{
				if (count > _capacity)
				{
					if (_capacity)
						_alloc.deallocate(_container, _capacity);
					_container = _alloc.allocate(count);
					_capacity = count;
				}
				_size = count;
				for (size_type i = 0; i < _size; i++)
					_container[i] = value;
			};
			template< class InputIt >
			void assign( InputIt first, InputIt last, typename std::enable_if<!std::is_integral<InputIt>::value, int>::type = 0)
			{
				size_type dist = std::distance(first, last); 
				if (dist > _capacity)
				{
					if (_capacity)
						_alloc.deallocate(_container, _capacity);
					_container = _alloc.allocate(dist);
					_capacity = dist;
				}
				_size = dist;
				for (size_type i = 0; first != last; i++)
				{
					_container[i] = *first;
					first++;
				}
			};
			allocator_type get_allocator() const { return (_alloc); };

			//---------------
			// Element access |
			//---------------
			reference at( size_type pos ) 
			{
				if (pos >= 0 && pos < _size)
					return (_container[pos]);
				throw std::out_of_range("vector");
			};
			const_reference at( size_type pos ) const
			{
				if (pos >= 0 && pos < _size)
					return (_container[pos]);
				throw std::out_of_range("vector");
			};
			reference operator[]( size_type pos ) { return (_container[pos]); };
			const_reference operator[]( size_type pos ) const { return (_container[pos]); };
			reference front() { return (_container[0]); };
			const_reference front() const { return (_container[0]); };
			reference back() { return (_container[_size - 1]); };
			const_reference back() const { return (_container[_size - 1]); };
			T* data() { return (&_container[0]); };
			const T* data() const { return (&_container[0]); };

			//----------
			// Iterators |
			//----------
			iterator begin() { return iterator(&_container[0]); };
			const_iterator begin() const { return const_iterator(&_container[0]); };
			iterator end() { return iterator(&_container[_size]); };
			const_iterator end() const { return const_iterator(&_container[_size]); };
			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
			reverse_iterator rend() { return reverse_iterator(begin() - 1); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin() - 1); };

			//---------
			// Capacity |
			//---------
			bool empty() const { return (_size == 0); };
			size_type size() const { return (_size); };
			size_type max_size() const
			{
				size_type sizeof_type = sizeof(value_type) > 1 ? sizeof(value_type) : 2;
				return (static_cast<size_type>(std::powl(2, sizeof(void *) * 8)) / sizeof_type); 
			};
			void reserve( size_type new_cap )
			{
				if (new_cap > _capacity)
				{
					pointer _new_container;

					_capacity = new_cap;
					_new_container = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(_new_container + i, _container[i]);
						_alloc.destroy(_container + i);
					}
					if (_capacity)
						_alloc.deallocate(_container, _size);
					_container = _new_container;
				}
			};
			size_type capacity() const { return (_capacity); };

			//----------
			// Modifiers |
			//----------
			void clear() { _size = 0; };
			iterator insert( iterator pos, const T& value )
			{
				size_type index = std::distance(begin(), pos);
				size_type distance = std::distance(pos, end());

				if (_capacity < _size + 1)
					_increase_container_capacity(_size + 1);
				value_type tmp = _container[index];
				_container[index] = value;
				for (size_type i = index + 1; i < _size + distance; i++)
				{
					value_type tmp2 = _container[i];
					_alloc.construct(&_container[i], tmp);
					tmp = tmp2;
				}
				_size++;
				return (iterator(&_container[index]));
			};
			void insert( iterator pos, size_type count, const T& value )
			{
				size_type dist = std::distance(pos, end());
				pointer tmp = _alloc.allocate(dist);
				iterator tmp_it = iterator(tmp);
				if (_capacity < _size + count)
					_increase_container_capacity(_size + count);
				std::copy(end() - dist, end(), tmp);
				std::fill(end() - dist, end() - dist + count, value);
				std::copy(tmp_it, tmp_it + dist, &*(end() - dist + count));
				_alloc.deallocate(tmp, dist);
				_size += count;
			};
			/*
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last, typename std::enable_if<!std::is_integral<InputIt>::value, int>::type = 0)
			{
				size_type src_dist = std::distance(first, last);	
				size_type dst_dist = std::distance(pos, end());

				pointer tmp = _alloc.allocate(dst_dist);
				iterator tmp_it = iterator(tmp);

				if (_capacity < _size + src_dist)
					_increase_container_capacity(_size + src_dist);

				for (size_type i = 0; i < dst_dist; i++)
					_alloc.destroy(&*(end() - dst_dist + i));
				for (size_type i = 0; i < dst_dist; i++)
					_alloc.construct(tmp + i, *(end() - dst_dist + i));
				for (size_type i = 0; i < src_dist; i++, first++)
					_alloc.construct(&*(end() - dst_dist + i), *first);
				for (size_type i = 0; i < dst_dist; i++, tmp_it++)
					_alloc.construct(&*(end() - dst_dist + src_dist + i), *tmp_it);

				_alloc.deallocate(tmp, dst_dist);
				_size += src_dist;
			};*/


		template<class InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type
		validate_iterator_values(InputIt first, InputIt last, size_t range) {
			pointer reserved_buffer;
			reserved_buffer = _alloc.allocate(range);
			bool result = true;
			size_t i = 0;

			for (;first != last; ++first, ++i) {
				try { reserved_buffer[i] = *first; }
				catch (...) { result = false; break; }
			}
			_alloc.deallocate(reserved_buffer, range);
			return result;
		}

		template <class InputIterator>
    	void insert ( iterator position, InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value, int>::type = 0 )
		{
			//if (position > end()) throw std::out_of_range("out of range");
			
			size_type pos = std::distance(begin(), position);
			size_type count = std::distance(first, last);

			std::cout << "(_capacity=" << _capacity << ")" << std::endl;
			if (!validate_iterator_values(first, last, count))
				 throw std::exception();

			while(_capacity < _size + count)
				_capacity *= 2;
			pointer tmp = _alloc.allocate(_capacity);
			for (size_type i = 0; i < pos; i++)
				_alloc.construct( tmp + i , *(_container + i) );
			for (size_type i = pos; i < pos + count; i++, first++)
				_alloc.construct( (tmp + i) , *first );
			for (size_type i = pos; i < _size; i++)
				_alloc.construct( tmp + i + count, *(_container + i) );
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_container + i);
			_alloc.deallocate(_container, _capacity);
			_container = tmp;
			_size += count;
		};
			iterator erase( iterator pos )
			{
				if (_size == 0 || _size == 1)
				{
					clear();
					return end();
				}
				else
				{
					std::copy(pos + 1, end(), pos);
					_size--;
					return (pos);
				}
			};
			iterator erase( iterator first, iterator last )
			{
				size_type dist = std::distance(first, last);
				if (_size == 0 || _size == dist)
				{
					clear();
					return end();
				}
				else
				{
					std::copy(last, end(), first);
					_size -= dist;
					return (first);
				}
			}
			void push_back( const T& value )
			{
				if (_capacity == 0)
				{
					_capacity = 1;
					_container = _alloc.allocate(_capacity);
				}
				else if (_capacity == _size)
					_increase_container_capacity(_size + 1);
				_alloc.construct(&_container[_size], value);
				_size++;
			};
			void pop_back() { _size--; };
			void resize( size_type count, T value = T() )
			{
				if (count > _size)
				{
					if (_capacity < count)
						_increase_container_capacity(count);
					for (size_type i = _size; i < count; i++)
						_alloc.construct(_container + i, value);
				}
				else if (count < _size)
				{
					for (size_type i = count; i < _size; i++)
						_alloc.destroy(_container + i);
				}
				_size = count;
			};
			void swap (vector& other)
			{
				ft::swapContent(_container, other._container);
				ft::swapContent(_size, other._size);
				ft::swapContent(_capacity, other._capacity);
				ft::swapContent(_alloc, other._alloc);
			};

		private:
			//--------------------
			// TOOLS FUNCTIONS

			void _increase_container_capacity(size_type new_cap)
			{
				pointer new_container;

				if (_capacity * 2 >= new_cap)
					_capacity *= 2;
				else
					_capacity = new_cap;
				new_container = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(new_container + i, _container[i]);
					_alloc.destroy(_container + i);
				}
				if (_capacity)
					_alloc.deallocate(_container, _size);
				_container = new_container;
			};
	};

	// NON-MEMBER FUNCTIONS
	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		if (lhs.size() == rhs.size())
		{
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}
		return false;
	};

	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	};

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return !(rhs < lhs);
	};

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return rhs < lhs;
	}

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}
}

#endif