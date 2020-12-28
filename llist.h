#pragma once

#include <string>

/*
 llist
 Linked list.
*/
template <typename T>
struct llist
{
	const T* const data;		// The data at the head of the linked list.
	const llist<T>* const rest;	// A pointer to the rest of the linked list, which is also a linked list.

	llist(const T*, const llist<T>* const);
	llist(const T*);

	const llist<T>* const cons(const T* const) const;	// Append a node to the front of the linked list.
	const size_t size() const;							// Return the number of nodes in the linked list.
	const bool contains(const T* const) const;			// Return whether the linked list contains a certain object.
	const llist<T>* const find(const T* const) const;	// Return the linked list where a specific element is first.

	std::string to_string(std::string (*f)(const T* const) = nullptr, std::string = ", ") const;
};

template <typename T>
inline llist<T>::llist(const T* data, const llist<T>* const rest)
	: data(data), rest(rest) {}

template <typename T>
inline llist<T>::llist(const T* data)
	: data(data), rest((const llist<T>* const)nullptr) {}

/*
 llist::cons
 Append a node to the front of the linked list.
*/
template <typename T>
inline const llist<T>* const llist<T>::cons(const T* const data) const
{
	return new llist<T>(data, this);
}

/*
 llist::size
 Return the number of nodes in linked list.
*/
template <typename T>
inline const size_t llist<T>::size() const
{
	if (rest)
	{
		return (size_t)1 + rest->size();	// Count this node and add it to the size of the rest of the linked list.
	}
	else
	{
		return (size_t)1;	// Count this node and stop counting.
	}
}

/*
 llist::contains
 Return whether the linked list contains a certain object.
*/
template<typename T>
inline const bool llist<T>::contains(const T* const object) const
{
	return (data == object
		? true
		: (rest
			? rest->contains(object)
			: false));
}

template<typename T>
inline const llist<T>* const llist<T>::find(const T* const object) const
{
	return (data == object
		? this
		: (rest
			? rest->find(object)
			: false));
}

template <typename T>
inline std::string llist<T>::to_string(std::string (*to_string_function)(const T* const), std::string delimiter) const
{
	const std::string data_string =
		to_string_function				// If there is a function to convert data into a string...
		? to_string_function(data)		//  Convert data into a string and store the result.
		: std::to_string((size_t)data);	//  Otherwise, convert the pointer value to a string and store the result.
	
	if (rest)
	{
		return data_string + delimiter + rest->to_string(to_string_function, delimiter);
	}
	else
	{
		return data_string;
	}
}