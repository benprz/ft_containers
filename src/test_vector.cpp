#include "vector.hpp"
#include <vector>

#include <map>
//#include "map.hpp"

#include <iterator>
#include <iostream>
#include <iterator>
#include <memory>

#include <typeinfo>
#include <string>
#include <string_view>
#include <type_traits>
#include <algorithm>
#define TESTED_TYPE std::string
#define TESTED_NAMESPACE ft

#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void	checkErase(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct,
					TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
	//std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	//printSize(vct);
}

/*
int		main(void)
{

	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = TESTED_TYPE((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	//printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	//printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));


	return (0);
}
*/

int main()
{
	/*
	std::vector<int> vec;
	
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);

	std::vector<int> vec2;

	vec2.push_back(1);
	vec2.push_back(2);
	vec2.push_back(3);
	vec2.push_back(4);
	vec2.push_back(5);
	vec2.push_back(6);
	vec2.push_back(7);
	vec2.push_back(8);
	vec2.push_back(9);

	vec2 = vec;
	printf("%p %lu %lu | %p %lu %lu\n", vec.data(), vec.size(), vec.capacity(), vec2.data(), vec2.size(), vec2.capacity());
	std::cout << *vec2.end() << std::endl;

	std::cout << *vec.begin() << std::endl;
	std::vector<int>::iterator it = vec.insert(vec.end(), 42);
	std::cout << *it << " " << *vec.begin() << " " << *++vec.begin() << std::endl;
	printf("%p %p\n\n", &*vec.begin(), &*it);

	ft::vector<int> a;

	std::cout << "cap=" << a.capacity() << std::endl;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	
	std::cout << "cap=" << a.capacity() << std::endl;
	ft::vector<int>::iterator ite = a.begin() + 2;
	a.insert(ite, 9);

	for (std::size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << std::endl;

	std::cout << "cap=" << a.capacity() << std::endl;

	std::cout << "-------- b\n";
	std::vector<int> b;	

	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	b.push_back(5);
	b.push_back(6);
	b.push_back(7);
	b.push_back(8);

	std::cout << "cap=" << b.capacity() << std::endl;
	b.insert(b.begin() + 2, 4, 0);
	for (std::size_t i = 0; i < b.size(); i++)
		std::cout << b[i] << std::endl;
	std::cout << "cap=" << b.capacity() << std::endl;

	std::cout << "-------- c\n";
	ft::vector<int> c(a.begin(), a.end());
	for (std::size_t i = 0; i < c.size(); i++)
		std::cout << c[i] << std::endl;
	
	ft::vector<int> d;

	//ft::vector<int>::reverse_iterator rit = c.rbegin();

	d.insert(d.begin(), a.begin(), a.end());
	std::cout << std::endl;
	std::cout << *(d.rend() - 1) << std::endl;
	std::cout << *(d.rend() - 2) << std::endl << std::endl;
	for (std::size_t i = 0; i < d.size(); i++)
		std::cout << d[i] << std::endl;

	ft::vector<int>	vec(10, 42);
	ft::vector<int> vec2;

	vec2.insert(vec2.begin(), vec.begin(), vec.end());

	//swap_test(ft::vector<int>());


    return v[0];
	*/
	std::vector<int> vec;
}