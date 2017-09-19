#ifndef A2P2_H
#define A2P2_H


#include <iostream>
#include <exception>
#include <assert.h>


// To be thrown when trying to remove an element from an empty set
class RemoveFromEmpty : std::exception
{
public:
    RemoveFromEmpty() { _message = "EmptySetException: Set is empty, cannot remove element from empty set."; }
    const char* what() const noexcept { return _message.c_str(); }
private:
    std::string _message;
};

// To be thrown when the element to be removed is not found in the set
class NonExistingElem : std::exception
{
public:
    NonExistingElem() { _message = "NonExistingElem: Element is not in set, cannot remove element from set."; }
    const char* what() const noexcept { return _message.c_str(); }
private:
    std::string _message;
};


// Template Class that stores a set of elements which can be intersected or unioned with another set of elements
template <typename T>
class Set
{
public:
    // Constructors
    Set();                                      // Default constructor
    Set(const Set &rhs);                        // Copy constructor
    Set(Set &&rhs);                             // Move constructor
    ~Set();                                     // Destructor
    
    // Overloaded operators
    Set &operator=(const Set &rhs);             // Copy assignment
    Set &operator=(Set &&rhs);                  // Move assignment
    Set operator+(const Set &rhs) const;        // Returns union of sets
    Set operator*(const Set &rhs) const;        // Returns intersection of sets
    
    // Methods
    bool isElement(const T &element) const;     // Returns true if an element exists in the set
    bool isEmpty() const;                       // Returns true if the set is empty
    int getSize() const;                        // Returns the size of the set
    void print(std::ostream &out = std::cout) const; // Display on out all elements in the set between {..}
    void setToEmptySet();                       // Deletes all set data and makes empty set

    // Methods to work with individual elements of a set
    void insert(const T &newElement);           // Inserts a new element into the back of the set
    void remove(const T &element);              // Removes an element from the set, throws exceptions, use try/catch

private:
    struct Node                                 // Linked list of nodes representing/storing the set
    {
        Node(const T &d = T(), Node *n = nullptr) : data(d), next(n) { }
        T data;
        Node *next;
    };

    Node *_first;                               // The first node in the linked list of nodes
    int _size;                                  // The size of the set, to have an efficient getSize()
};

void info();                                                                    // Displays the author's information

#endif
