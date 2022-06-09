#include "vector.hpp"
#include <vector>

#include <map>
#include "map.hpp"

#include <iterator>
#include <iostream>
#include <iterator>
#include <memory>

#include <typeinfo>
#include <string>
#include <string_view>
#include <type_traits>
#include <algorithm>

unsigned long _ratio = 10000;

template <typename T>
std::vector<int> swap_test(ft::vector<T> vector)
{
    std::vector<int> v;
    vector.assign(1100 * _ratio, 11);
    ft::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.swap(tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp4);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}


class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};

template <typename T>
std::vector<int> insert_test_3(ft::vector<T> vector) {
    std::vector<int> v;
	/*
    ft::vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	*/

    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    ft::vector<A> vv;
    ft::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
		std::cout << "catch" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }

    return v;
}

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

	// SEGFAULT <
	//ft::vector<int> vec;
	//ft::vector<int>::const_iterator it = vec.begin();

	ft::vector<int>	vec(10, 42);
	ft::vector<int> vec2;

	vec2.insert(vec2.begin(), vec.begin(), vec.end());
*/

	//insert_test_3<int>(ft::vector<int>());

	ft::vector<int> v(1, 1);
	ft::vector<int>::const_iterator it = v.begin();

	return 0;
}
