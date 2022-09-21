//
// Created by IthisanBrekman on 21.09.2022
//

#include <cstring>

#include "baselib.hpp"

#include "storage_vector.hpp"

VectorStorage::VectorStorage(size_t elem_size, size_t elems) {
    size_t capacity = elems * 2 < VectorStorage::__MIN_CAPACITY ? VectorStorage::__MIN_CAPACITY : elems * 2;

    this->elem_size  = elem_size;
    this->data       = calloc(capacity, elem_size);
    this->capacity   = capacity;
}

VectorStorage::~VectorStorage() {
    free(this->data);
}

int VectorStorage::push(void const* elem) {
    ASSERT_IF(VALID_PTR(elem), "Invalid elem ptr", 1);

    if (this->size == this->capacity) VectorStorage::resize(this->size);

    // Copy data from elem to thisector
    memcpy((char*)this->data + this->elem_size * this->size++, elem, this->elem_size);

    return 0;
}

int VectorStorage::pop(void* elem) {
    ASSERT_IF(VALID_PTR(elem), "Invalid elem ptr", 1);

    if (this->size == 0) return 1;

    VectorStorage::get(this->size - 1, elem);
    this->size--;

    if (this->size * 4 == this->capacity) VectorStorage::resize(this->size);

    return 0;
}

int VectorStorage::empty() const {
    return this->size == 0;
}

int VectorStorage::set(size_t index, void const* elem) {
    ASSERT_IF(VALID_PTR(elem), "Invalid elem ptr", 1);

    if (index >= this->size) return 1;

    // Copy data from elem to vector
    memcpy((char*)this->data + this->elem_size * index, elem, this->elem_size);

    return 0;
}

int VectorStorage::get(size_t index, void* elem) const {
    ASSERT_IF(VALID_PTR(elem), "Invalid elem ptr", 1);

    if (index >= this->size) return 1;

    // Calculating address of the index-th vector element
    memcpy(elem, (char*)this->data + this->elem_size * index, this->elem_size);

    return 0;
}

int VectorStorage::resize(size_t new_size) {
    this->size     = new_size;
    this->capacity = new_size * 2 < VectorStorage::__MIN_CAPACITY ? VectorStorage::__MIN_CAPACITY : new_size * 2;
    this->data     = realloc(this->data, this->capacity * this->elem_size);

    return 0;
}

void VectorStorage::dump(void (*pf)(void const *data)) const {
    ASSERT_IF(VALID_PTR(pf), "Invalid pf function ptr", );

    printf("<VectorStorage(%zd): [", this->size);
    for (int i = 0; i < this->size; i++) {
        pf((char*)this->data + i * this->elem_size);  // Calculating i-th vector element
        if (i + 1 < this->size) printf(", ");
    }
    printf("] >\n");
}
