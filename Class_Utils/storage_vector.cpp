//
// Created by IthisanBrekman on 21.09.2022
//

#include <cstring>

#include "baselib.hpp"

#include "storage_vector.hpp"

VectorStorage::VectorStorage(size_t elem_size, size_t elems) {
    size_t capacity = elems * 2 < VectorStorage::__MIN_CAPACITY ? VectorStorage::__MIN_CAPACITY : elems * 2;

    elem_size  = elem_size;
    data       = calloc(capacity, elem_size);
    capacity   = capacity;
}

VectorStorage::~VectorStorage() {
    free(data);
}

int VectorStorage::push(void const* elem) {
    ASSERT_IF(VALID_PTR(elem), "Invalid elem ptr", 1);

    if (size == capacity) VectorStorage::resize(size);

    // Copy data from elem to thisector
    memcpy((char*)data + elem_size * size++, elem, elem_size);

    return 0;
}

int VectorStorage::pop(void* elem) {
    ASSERT_IF(VALID_PTR(elem), "Invalid elem ptr", 1);

    if (size == 0) return 1;

    VectorStorage::get(size - 1, elem);
    size--;

    if (size * 4 == capacity) VectorStorage::resize(size);

    return 0;
}

int VectorStorage::empty() const {
    return size == 0;
}

int VectorStorage::set(size_t index, void const* elem) {
    ASSERT_IF(VALID_PTR(elem), "Invalid elem ptr", 1);

    if (index >= size) return 1;

    // Copy data from elem to vector
    memcpy((char*)data + elem_size * index, elem, elem_size);

    return 0;
}

int VectorStorage::get(size_t index, void* elem) const {
    ASSERT_IF(VALID_PTR(elem), "Invalid elem ptr", 1);

    if (index >= size) return 1;

    // Calculating address of the index-th vector element
    memcpy(elem, (char*)data + elem_size * index, elem_size);

    return 0;
}

int VectorStorage::resize(size_t new_size) {
    size     = new_size;
    capacity = new_size * 2 < VectorStorage::__MIN_CAPACITY ? VectorStorage::__MIN_CAPACITY : new_size * 2;
    data     = realloc(data, capacity * elem_size);

    return 0;
}

void VectorStorage::dump(void (*pf)(void const *data)) const {
    ASSERT_IF(VALID_PTR(pf), "Invalid pf function ptr", );

    printf("<VectorStorage(%zd): [", size);
    for (int i = 0; i < size; i++) {
        pf((char*)data + i * elem_size);  // Calculating i-th vector element
        if (i + 1 < size) printf(", ");
    }
    printf("] >\n");
}
