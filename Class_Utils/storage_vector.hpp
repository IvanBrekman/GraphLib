//
// Created by IvanBrekman on 21.09.2022
//

#pragma once

#include <cstdio>

class VectorStorage {
    public:
        size_t elem_size;

        void*  data;

        size_t size;
        size_t capacity;

        static const int __MIN_CAPACITY = 10;
    
    public:
        VectorStorage(size_t elem_size, size_t elems=VectorStorage::__MIN_CAPACITY);
        ~VectorStorage();

        int push (void const* elem);
        int pop  (void*       elem);
        int empty()                             const;

        int set(size_t index, void const* elem);
        int get(size_t index, void*       elem) const;

        int    resize(size_t new_size);

        void dump(void (*pf)(void const *data)) const;
};
