#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"

#include <memory>
#include <iostream>
#include <iterator>
#include <cmath>
#include <algorithm>


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
			std::allocator<T>	_alloc;
		
		public:
			vector() : _container(NULL), _capacity(0), _size(0) {};
			explicit vector( const Allocator& alloc ) : _alloc(alloc) { vector(); };
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _container(NULL), _alloc(alloc)
			{
				vector();
				if (_alloc_container(count))
				{
					_size = count;
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_container + i, value);
				}
			};
			template< class InputIt > 
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) : _container(NULL), _alloc(alloc)
			{
				vector();
				size_type dist = std::distance(first, last);
				if (_alloc_container(dist))
				{
					_size = dist;
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_container + i, *first++);
				}
			};
			vector( const vector& other ) : _container(NULL), _capacity(0), _size(0)
			{
				*this = other;
			};
			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_container + i);
				_alloc.deallocate(_container, _capacity);
			};
			vector& operator=( const vector& other )
			{
				if (_capacity < other._size)
				{
					if (!_alloc_container(_size))
						return *this;
				}
				for (size_type i = 0; i < other._size; i++)
					_alloc.construct(_container + i, other[i]);
				_size = other._size;
				return (*this);
			};
			void assign( size_type count, const T& value )
			{
				if (count > _capacity)
				{
					if (!_alloc_container(count))
						throw std::bad_alloc();
				}
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_container + i, value);
				_size = count;
			};
			template< class InputIt >
			void assign( InputIt first, InputIt last )
			{
				size_type dist = std::distance(first, last); 
				if (dist > _capacity)
				{
					if (!_alloc_container(dist))
						throw std::bad_alloc();
				}
				for (size_type i = 0; i < dist; i++)
				{
					_alloc.construct(_container + i, *first);
					first++;
				}
				_size = dist;
			};
			allocator_type get_allocator() const { return (_alloc); };

			//---------------
			// Element access |
			//---------------
			reference at( size_type pos ) 
			{
				if (pos >= 0 && pos < _size)
					return (_container[pos]);
				throw std::out_of_range("vector: out_of_range");
			};
			const_reference at( size_type pos ) const
			{
				if (pos >= 0 && pos < _size)
					return (_container[pos]);
				throw std::out_of_range("vector: out_of_range");
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
			const_iterator begin() const { return iterator(&_container[0]); };
			iterator end() { return iterator(&_container[_size]); };
			const_iterator end() const { return iterator(&_container[_size]); };
			reverse_iterator rbegin() { return (reverse_iterator(end() - 1)); };
			const_reverse_iterator rbegin() const { return (reverse_iterator(end() - 1)); };
			reverse_iterator rend() { return (reverse_iterator(begin() -  1)); };
			const_reverse_iterator rend() const { return (reverse_iterator(begin() - 1)); };

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

					if ((_new_container = _try_alloc(new_cap)))
					{
						for (size_type i = 0; i < _size; i++)
						{
							_alloc.construct(_new_container + i, _container[i]);
							_alloc.destroy(_container + i);
						}
						_alloc.deallocate(_container, _size);
						_container = _new_container;
						_capacity = new_cap;
					}
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
				{
					if (!_increase_container_capacity(_size + 1))
						throw std::bad_alloc();
				}
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
				pointer tmp;
				if ((tmp = _try_alloc(dist)))
				{
					iterator tmp_it = iterator(tmp);
					if (_capacity < _size + count)
					{
						if (!_increase_container_capacity(_size + count))
							throw std::bad_alloc();
					}
					std::copy(end() - dist, end(), tmp);
					std::fill(end() - dist, end() - dist + count, value);
					std::copy(tmp_it, tmp_it + dist, &*(end() - dist + count));
					_size += count;
				}
			};
			template< class InputIt > void insert( iterator pos, InputIt first, InputIt last )
			{
				size_type src_dist = std::distance(first, last);	
				size_type dst_dist = std::distance(pos, end());
				pointer tmp;
				if ((tmp = _try_alloc(dst_dist)))
				{
					iterator tmp_it = iterator(tmp);
					if (_capacity < _size + src_dist)
					{
						if (!_increase_container_capacity(_size + src_dist))
							throw std::bad_alloc();
					}
					std::copy(end() - dst_dist, end(), tmp);
					std::copy(first, last, end() - dst_dist);
					std::copy(tmp_it, tmp_it + dst_dist, &*(end() - dst_dist + src_dist));
					_size += src_dist;
				}
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
					if (!_alloc_container(1))
						throw std::bad_alloc();
				}
				else if (_capacity == _size)
					if (!_increase_container_capacity(_size + 1))
						throw std::bad_alloc();
				_alloc.construct(&_container[_size], value);
				_size++;
			};
			void pop_back() { _size--; };
			void resize( size_type count, T value = T() )
			{
				if (count > _size)
				{
					if (_capacity < count)
						if (!_increase_container_capacity(count))
							throw std::bad_alloc();
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
			void swap( vector& other )
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
			};

		private:
			//--------------------
			// TOOLS FUNCTIONS
			
			pointer _try_alloc(size_type size)
			{
				pointer ptr = _alloc.allocate(size);
				return ptr;
			}
			bool _alloc_container(size_type size)
			{
				if (_container)
					_alloc.deallocate(_container, _capacity);
				_alloc.allocate(size);
				_capacity = size;
				return true;
			}
			bool _increase_container_capacity(size_type new_cap)
			{
				size_type alloc_size = _capacity * 2 >= new_cap ? _capacity * 2 : new_cap;
				pointer new_container;
				if ((new_container = _try_alloc(_capacity)))
				{
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(new_container + i, _container[i]);
						_alloc.destroy(_container + i);
					}
					_alloc.deallocate(_container, _size);
					_container = new_container;
					_capacity = alloc_size;
					return true;
				}
				return false;
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
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	};

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(rhs < lhs);
	};

	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return rhs < lhs;
	}

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}
}

#endif