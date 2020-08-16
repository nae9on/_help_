/*
 * understand_iterators.cpp
 *
 *  Created on: Oct 19, 2019
 *      Author: akadar
 *
 * A simple example to understand what are iterators?
 *
 * References:
 * [1] https://www.cs.helsinki.fi/u/tpkarkka/alglib/k06/lectures/iterators.html#example-simple-list
 * [2] https://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid
 * -common-pitfalls
 * [3] https://stackoverflow.com/questions/7758580/writing-your-own-stl-container/7759622#7759622
 */

#include <iostream>
#include <cassert>
#include <forward_list>

/*
 * This forward list example serves to demonstrate how iterators can be implemented.
 * It is far from being an STL iterator implementation.
 */
template<typename T>
struct node{

	node() = delete;
	node(int val_, node* next_): val{val_}, next{next_} {}

	T val;
	node* next;

	struct iterator {

		using _Self = iterator;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		node* _M_node; // Iterator is a generalized pointer identifying a position in a container.

		iterator():	_M_node(nullptr){}

		explicit iterator(node* p): _M_node(p){}

		// copy-constructor, copy-assignment and destructor are compiler generated

		reference operator*() const { // Pointer dereference op
			return _M_node->val;
		}

		pointer operator->() const { // Member selection op
			return &(_M_node->val);
		}

		_Self& operator++() {
			_M_node = _M_node->next;
			return *this;
		}

		_Self operator++(int) {
			_Self tmp = *this;
			_M_node = _M_node->next;
			return tmp;
		}

		bool operator==(const _Self& other) const {
			return _M_node == other._M_node;
		}

		bool operator!=(const _Self& other) const {
			return _M_node != other._M_node;
		}
	};

	struct const_iterator {

		using _Self = const_iterator;
		using value_type = T;
		using pointer = const T*; // Note difference from iterator
		using reference = const T&; // Note difference from iterator

		// Note difference from iterator
		const node* _M_node; // Iterator is a generalized pointer identifying a position in a container.

		const_iterator():	_M_node(nullptr){}

		explicit const_iterator(const node* p): _M_node(p){}

		reference operator*() const { // Pointer dereference op
			return _M_node->val;
		}

		pointer operator->() const { // Member selection op
			return &(_M_node->val);
		}

		_Self& operator++() {
			_M_node = _M_node->next;
			return *this;
		}

		_Self operator++(int) {
			_Self tmp = *this;
			_M_node = _M_node->next;
			return tmp;
		}

		bool operator==(const _Self& other) const {
			return _M_node == other._M_node;
		}

		bool operator!=(const _Self& other) const {
			return _M_node != other._M_node;
		}
	};

	iterator begin() {
		return iterator(this);
	}

	iterator end() {
		return iterator();
	}

	const_iterator cbegin() {
		return const_iterator(this);
	}

	const_iterator cend() {
		return const_iterator();
	}
};

/*
 * The list iterator defined above supports the following operators *, ->, ++, == and !=
 * Such a list of requirements is sometimes called a concept. A type which satisfy a concept
 * is said to model a concept.
 *
 * Concepts are central to generic programming. Their role is analogous to virtual base classes
 * in object-oriented programming, with models corresponding to derived classes. An important
 * difference is that concepts are not language structures; they are part of the documentation.
 *
 * Refer to Iterator Concepts in [1].
 */
template<typename Iterator, typename T>
Iterator find(Iterator begin, Iterator end, const T& value) {
	while (begin != end && *begin != value)
		++begin;
	return begin;
}

template<typename Iterator>
void traverse(Iterator begin, Iterator end) {
	while (!(begin == end)) {
		std::cout << *begin << " ";
		++begin;
	}
	std::cout<<"\n";
}

int understand_iterators() {

	std::forward_list<int> flist{100,200,300};

	using T = int;
	node<T>* mylist = new node<T>(3, nullptr);
	mylist = new node<T>(2, mylist);
	mylist = new node<T>(1, mylist);

	traverse(flist.begin(), flist.end());
	traverse(mylist->cbegin(), mylist->cend());

	// Update a node value
	node<T>::iterator myiter = find(mylist->begin(), mylist->end(), 2);
	//node<T>::const_iterator myiter = find(mylist->cbegin(), mylist->cend(), 2);
	*myiter = 10; // Not allowed with const_iterator

	traverse(mylist->begin(), mylist->end());

	return 0;
}
