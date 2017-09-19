////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  15146508 Gwatkin, Cai                                                                159.234 Assignment 2 Part 2  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  This code contains the declarations and definitions for a template class to be used as a container for sets of    //
//  data. The union and intersection of two sets of the same data type can be computed using the + and * operators    //
//  respectively.                                                                                                     //
//                                                                                                                    //
//  Notes:                                                                                                            //
//  Copied sets retain the same order as the original due to the insert method inserting new elements to the          //
//  end of the linked list used to store the set.                                                                     //
//                                                                                                                    //
//  No main function due to restrictions from lecturer, to ensure simple testing using batch file.                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SetUnionIntersection.h"


// Displays the author's information
void info()
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << "159.234 A2P2 - 15146508 Gwatkin, Cai" << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

// Default constructor
template <typename T>
Set<T>::Set()
{
    _first = nullptr;
    _size = 0;
}

// Copy constructor
template <typename T>
Set<T>::Set(const Set &rhs)
{
    _first = nullptr;
    _size = 0;

    if (rhs.isEmpty()) return;

    Node *current = rhs._first;
    while (current != nullptr)
    {
        insert(current->data);
        current = current->next;
    }
    _size = rhs._size;
}

// Move constructor
template <typename T>
Set<T>::Set(Set &&rhs)
{
    _first = rhs._first;
    _size = rhs._size;

    rhs._first = nullptr;
    rhs._size = 0;
}

// Destructor
template <typename T>
Set<T>::~Set()
{
    setToEmptySet();
}

// Copy assignment
template <typename T>
Set<T>& Set<T>::operator=(const Set &rhs)
{
    if (this != &rhs)
    {
        setToEmptySet();

        if (rhs.isEmpty()) return *this;

        Node *current = rhs._first;
        while (current != nullptr)
        {
            insert(current->data);
            current = current->next;
        }
        _size = rhs._size;
    }

    return *this;
}

// Move assignment
template <typename T>
Set<T>& Set<T>::operator=(Set &&rhs)
{
    assert(this != &rhs);

    setToEmptySet();

    if (rhs.isEmpty()) return *this;

    _first = rhs._first;
    _size = rhs._size;

    rhs._first = nullptr;
    rhs._size = 0;

    return *this;
}

// Returns union of sets
template <typename T>
Set<T> Set<T>::operator+(const Set &rhs) const
{
    Set<T> unionSet;

    if (!isEmpty() && !rhs.isEmpty())
    {
        if (!isEmpty())
        {
            Node *current = _first;
            while (current != nullptr)
            {
                unionSet.insert(current->data);
                current = current->next;
            }
        }
        if (!rhs.isEmpty())
        {
            Node *current = rhs._first;
            while (current != nullptr)
            {
                unionSet.insert(current->data);
                current = current->next;
            }
        }
    }

    return unionSet;
}

// Returns intersection of sets
template <typename T>
Set<T> Set<T>::operator*(const Set &rhs) const
{
    Set<T> intersectionSet;

    if (isEmpty() || rhs.isEmpty()) return intersectionSet;

    Node *currentThis = _first;
    while (currentThis != nullptr)
    {
        Node *currentRHS = rhs._first;
        while (currentRHS != nullptr)
        {
            if (currentThis->data == currentRHS->data)
            intersectionSet.insert(currentRHS->data);
            currentRHS = currentRHS->next;
        }
        currentThis = currentThis->next;
    }

    return intersectionSet;
}

// Returns true if an element exists in the set
template <typename T>
bool Set<T>::isElement(const T &element) const
{
    if (isEmpty()) return false;

    Node *current = _first;
    while (current != nullptr)
    {
        if (current->data == element) return true;
        current = current->next;
    }

    return false;
}

// Returns true if the set is empty
template <typename T>
bool Set<T>::isEmpty() const
{
    if (_size == 0) return true;

    return false;
}

// Returns the size of the set
template <typename T>
int Set<T>::getSize() const
{
    return _size;
}

// Display on out all elements in the set between {..}
template <typename T>
void Set<T>::print(std::ostream &out) const
{
    out << "{ ";
    Node *current = _first;
    while (current != nullptr)
    {
        out << current->data;
        current = current->next;
        if (current != nullptr) out << ", ";
    }
    out << " }";
}

// Deletes all set data and makes empty set
template <typename T>
void Set<T>::setToEmptySet()
{
    if (isEmpty()) return;

    Node *current = _first, *next = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        delete current;
        current = next;
    }
    _first = nullptr;
    _size = 0;
}

// Inserts a new element into the back of the set
template <typename T>
void Set<T>::insert(const T &newElement)
{
    if (isElement(newElement)) return;

    if (isEmpty())
    {
        _first = new Node(newElement);
        _size++;
        return;
    }

    Node *current = _first, *previous = nullptr;
    while (current != nullptr)
    {
        previous = current;
        current = current->next;
    }
    current = new Node(newElement);
    previous->next = current;
    _size++;
}

// Removes an element from the set, can throw exceptions, always use try/catch
template <typename T>
void Set<T>::remove(const T &element)
{
    if (isEmpty()) throw RemoveFromEmpty();
    if (!isElement(element)) throw NonExistingElem();

    Node *current = _first, *previous = nullptr;
    while (current->data != element)
    {
        previous = current;
        current = current->next;
    }
    if (previous == nullptr)
    {
        _first = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    delete current;
    _size--;
}


// Overloaded output operator for sets
template <typename T>
std::ostream &operator<< (std::ostream& os, const Set<T> &rhs)
{
    rhs.print(os);
    return os;
}
