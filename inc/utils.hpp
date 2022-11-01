#pragma once

namespace ft
{
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template< bool B, class T = void >
	struct enable_if {};
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<bool is_integral, typename T>
	struct is_integral_res
	{
		typedef T type;
		static const bool value = is_integral;
	};

	template<typename>
	struct is_integral_type : public is_integral_res<false, bool> {};
	template<>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};
	template<>
	struct is_integral_type<char> : public is_integral_res<true, char> {};
	template<>
	struct is_integral_type<char16_t> : public is_integral_res<true, char16_t> {};
	template<>
	struct is_integral_type<char32_t> : public is_integral_res<true, char32_t> {};
	template<>
	struct is_integral_type<wchar_t> : public is_integral_res<true, wchar_t> {};
	template<>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
	template<>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};
	template<>
	struct is_integral_type<int> : public is_integral_res<true, int> {};
	template<>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};
	template<>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
	template<>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
	template<>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
	template<>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
	template<>
	struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
	template<>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template<typename T>
	struct is_integral : public is_integral_type<T> { };

	template<class T1, class T2>
	class pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			pair() : first(), second() {}
			pair(const first_type &x, const second_type &y) : first(x), second(y) {}
			template<class U1, class U2>
			pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}
			~pair() {}
			pair& operator=(const pair &other)
			{
				first = other.first;
				second = other.second;
				return *this;
			}
	};
	
	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) 
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
	
	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) 
	{
		return !(lhs == rhs);
	}
	
	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
	}
	
	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}
	
	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}
	
	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return ft::pair<T1, T2>(x, y);
	}
}
