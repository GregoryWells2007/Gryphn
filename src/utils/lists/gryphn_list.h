#pragma once
#include "math.h"
#include "stdio.h"

// TODO: Wack ass list class, needs some serious refactoring, buttttt it works for what I need it to do
// Imma touch this later cuz like I dont like working with C code cuz its wierd but like its also fun
// who needs std::vector when you've got malloc, calloc, and free
// shit just forgot that I dont clean any of this up, imma do this later cuz like its boring
// ive decided to do it now, I hate this, I hate coding, C is fun, this is a Cpp file, what am I doing with life
// I never did it id be super easy just like one anitconstructor????? i dont remeber what is called its the one with the squigly bracked
// TODO: future me rewirte these comments to be less stupid
// TODO: Add insert function, also remove function, orrrrrr i could have people copy lists whever they wanna remove stuff, nah thats gunna piss me off too

#define GRYPHN_LIST_GROWTH_RATE 2 // number straight from my ass I wanted to use 1.5f cuz thats what STL does but like it complained
                                  // im in an abbusive relationship with the compiler, I need to get out of this
                                  // but like I also kinda like it imma pick of drinking (not actually imma just play minecraft)

template <typename Type> // fuck templates
struct gnList {
protected:
    Type* items = nullptr;
    int size = 0, max_size = 0;
public:
    gnList() {}

    // why did I make shit protected
    // theres gotta be a better way to do this with compiler macros but like that sounds hard
    // im never touching this wack ass code ever again
    template <typename T>
    friend gnList<T> gnCreateList(int size);
    template <typename T>
    friend void gnListAdd(gnList<T>& list, T item);
    template <typename T>
    friend int gnListLength(const gnList<T>& list);
    template <typename T>
    friend T& gnListGet(const gnList<T>& list, int index);
    template <typename T>
    friend T* gnListGetPtr(const gnList<T>& list, int index);
    template <typename T>
    friend void gnListSet(const gnList<T>& list, int index, T item);
    template <typename T>
    friend T* gnListData(const gnList<T>& list);
public:
    Type operator[](int index) const { return items[index]; } // idfk what that const is doin there but the compiler complained I was tryna change a const value
                                                              // .... I was not, I really am in an abusive relationship
    Type& operator[](int index) { return items[index]; }
};

template <typename T>
gnList<T> gnCreateList(int size = 0) {
    gnList<T> new_list = gnList<T>();
    new_list.size = size;
    if (size == 0) size = round(GRYPHN_LIST_GROWTH_RATE);
    new_list.items = (T*)malloc(sizeof(T) * size);
    new_list.max_size = size;
    return new_list;
}

template <typename T>
void gnListAdd(gnList<T>& list, T item) {
    if (gnListLength(list) == list.max_size) {
        list.max_size = list.max_size * GRYPHN_LIST_GROWTH_RATE;
        list.items = (T*)realloc(list.items, sizeof(T) * list.max_size);
    }

    list.items[list.size] = item;
    list.size++;
}

template <typename T>
int gnListLength(const gnList<T>& list) { return list.size; }

template <typename T>
T& gnListGet(const gnList<T>& list, int index) { return list.items[index]; }

template <typename T>
T* gnListGetPtr(const gnList<T>& list, int index) { return &list.items[index]; }

template <typename T>
void gnListSet(const gnList<T>& list, int index, T item) { list.items[index] = item; }

template <typename T>
T* gnListData(const gnList<T>& list) { return list.items; } // wack ass function for binary shit
                                                            // if this ever breaks change it to return &list.items[0] cuz that might work
                                                            // I have zero clue what any of this shit does
