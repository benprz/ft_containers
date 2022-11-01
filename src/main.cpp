#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"

#include <vector>
#include <map>
#include <stack>

#define N ft

int main()
{
	ft::stack<int> stack;

	stack.push(5);
	std::cout << stack.top() << std::endl;
	ft::stack<int> stack2(stack);
	if (stack == stack2)
		std::cout << "stack!" << std::endl;
	/*
	std::cout << "#VECTOR" << std::endl;
	N::vector<int> vec(20, 42);
	N::vector<int>::iterator it = vec.begin();

	while (it != vec.end())
	{
		std::cout << *it << " "; 
		vec.pop_back();
	}
	std::cout << vec.capacity() <<  " " << vec.size() << " " << vec.empty() << std::endl;
	vec.reserve(100);
	vec.reserve(50);
	for (size_t i = 0; i < vec.capacity(); i++)
		vec.push_back(43);
	for (N::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); rit++)
		std::cout << *rit << " ";
	vec.push_back(666);
	std::cout << vec.back() << " " << vec.front() << std::endl;
	vec.resize(103, 777);
	std::cout << vec.back() << " " << vec.front() << std::endl;
	N::vector<int> vec2(vec);
	vec.erase(vec.begin(), vec.erase(vec.end() - 2));
	std::cout << vec[vec.size() - 1] << std::endl;
	std::cout << vec.capacity() <<  " " << vec.size() << " " << vec.empty() << std::endl;
	vec.pop_back();
	std::cout << vec.capacity() <<  " " << vec.size() << " " << vec.empty() << std::endl;
	vec2.assign(vec.begin(), vec.end());
	N::vector<int>::const_iterator cit = vec2.end();
	for (N::vector<int>::iterator it2 = vec2.begin(); it2 != cit; it2++)
	{
		std::cout << *it2 << " ";
		vec2.erase(it2);
	}
	std::cout << vec2.capacity() <<  " " << vec2.size() << " " << vec2.empty() << std::endl;

	std::cout << std::endl << "#MAP" << std::endl; 
	N::map<char, int> map;
	char z = 'z';
	for (size_t i = 1; i <= 26; i++)
		map.insert(N::make_pair(z--, i));
	N::map<char, int>::iterator it3 = map.begin();
	while (it3 != map.end())
	{
		std::cout << it3->first << " " << it3->second << std::endl;
		it3++;
	}
	std::cout << map.size() << " " << map.empty() << std::endl;
	std::cout << map.lower_bound((--((((--(--it3))--)--)--))->first)->second << std::endl;
	std::cout << map.upper_bound((--((((--(--it3))--)--)--))->first)->second << std::endl;
	map.clear();
	std::cout << map.size() << " " << map.empty() << std::endl;
	map.insert(N::make_pair('a', 26));
	map.insert(N::make_pair('b', 25));
	map.insert(N::make_pair('c', 24));
	map.insert(N::make_pair('d', 23));
	map.insert(N::make_pair('e', 22));
	map.insert(N::make_pair('f', 21));
	map.insert(N::make_pair('g', 20));
	map.insert(N::make_pair('h', 19));
	map.insert(N::make_pair('i', 18));
	map.insert(N::make_pair('j', 17));
	map.insert(N::make_pair('k', 16));
	map.insert(N::make_pair('l', 15));
	map.insert(N::make_pair('m', 14));
	map.insert(N::make_pair('n', 13));
	map.insert(N::make_pair('o', 12));
	map.insert(N::make_pair('p', 11));
	map.insert(N::make_pair('q', 10));
	map.insert(N::make_pair('r', 9));
	map.insert(N::make_pair('s', 8));
	map.insert(N::make_pair('t', 7));
	map.insert(N::make_pair('u', 6));
	map.insert(N::make_pair('v', 5));
	map.insert(N::make_pair('w', 4));
	map.insert(N::make_pair('x', 3));
	map.insert(N::make_pair('y', 2));
	map.insert(N::make_pair('z', 1));
	map.insert(N::make_pair('z', 1));
	map.insert(N::make_pair('z', 1));
	map.insert(N::make_pair('z', 1));
	N::map<char, int>::reverse_iterator rit2 = map.rbegin();
	N::map<char, int>::reverse_iterator rit3 = map.rend();
	while (rit2 != rit3)
	{
		std::cout << rit2->first << " " << rit2->second << std::endl;
		rit2++;
	}
	std::cout << map.count('z') << std::endl;
	std::cout << map.find('z')->second << std::endl;
	std::cout << map.size() << " " << map.empty() << std::endl;
	map.erase(map.begin(), map.end());
	std::cout << map.size() << " " << map.empty() << std::endl;
*/

	return 0;
}