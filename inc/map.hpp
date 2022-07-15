#ifndef MAP_HPP
# define MAP_HPP

#include <iterator>
#include <memory>
#include <utility>

#include "map_tree.hpp"

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
	> class map
	{
		public:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef std::pair<const Key, T>								value_type;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;
			typedef Compare												key_compare;
			typedef Allocator											allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename ft::map_tree<key_type, mapped_type>::iterator		iterator;
			typedef typename ft::map_tree<key_type, mapped_type>::const_iterator	const_iterator;

		private:
			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }
			};
			ft::map_tree<key_type, mapped_type>	_container;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {};
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			map (const map& x);
			~map() {};
			reference operator= (const map& x);
			allocator_type get_allocator() const { return _container._node_alloc; };

			//----------
			// Iterators |
			//----------
			iterator begin() { return iterator(_container.begin()); }
			const_iterator begin() const { return const_iterator(_container.begin()); };
			iterator end() { return iterator(_container.end()); }
			const_iterator end() const { return const_iterator(_container.end()); };
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			//---------
			// Capacity |
			//---------
			bool empty() const { return begin() == end(); }
			size_type size() const { return _container.getSize(); }
			size_type max_size() const { return _container._node_alloc.max_size(); }

			//---------------
			// Element access |
			//---------------
			mapped_type& operator[] (const key_type& k) { return _container.get_node(k); };

			//----------
			// Modifiers |
			//----------
			std::pair<iterator,bool> insert (const value_type& val)
			{
				size_type siz = size();
				iterator it = _container.insert_node(val.first, val.second);
				if (siz == size())
					return std::pair<iterator, bool>(it, false);
				return std::pair<iterator, bool>(it, true);
			}
			iterator insert (iterator position, const value_type& val) { return _container.insert_node(position, val.first, val.second); }
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					_container.insert_node(*first);
					first++;
				}
			}
			void erase (iterator position) { _container.erase_node(*position); };
			size_type erase (const key_type& k) { return _container.erase_node(k); }
			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					_container.erase_node(*first);
					last++;
				}
			};
			void swap (map& x)
			{
				std::swap(_alloc, map._alloc);
				std::swap(_alloc, map._alloc);
				std::swap(_alloc, map._alloc);
			};
			void clear() { erase(begin(), end()); }

			//-------------
			// Observations |
			//-------------
			key_compare key_comp() const { return _container.getComp(); }
			value_compare value_comp() const { return key_comp(); }

			//-----------
			// Operations |
			//-----------
			iterator find (const key_type& k) { return iterator(_container.search_node(k)); }
			const_iterator find (const key_type& k) const { return const_iterator(_container.search_node(k)); }
			size_type count (const key_type& k) const { return iterator(_container.search_node(k)) != end(); }
			iterator lower_bound (const key_type& k) { return iterator(_container.lower_bound(k)); }
			const_iterator lower_bound (const key_type& k) const { return const_iterator(_container.lower_bound(k)); }
			iterator upper_bound (const key_type& k) { return iterator(_container.upper_bound(k)); }
			const_iterator upper_bound (const key_type& k) const { return const_iterator(_container.upper_bound(k)); }
			pair<iterator,iterator> equal_range (const key_type& k) { return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)); }
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return lhs == rhs;
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return rhs < lhs;
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	};

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs );
}

#endif