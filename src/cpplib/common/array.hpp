#ifndef _CPPLIB_COMMON_ARRAY_HPP
#define _CPPLIB_COMMON_ARRAY_HPP

#include <stdint.h>

#include "object.hpp"

template<typename T>
class Array : public Object {
    size_t sz;
    T *data;

    public:
    Array(size_t sz) {
        data = new T[sz];
    }

    ~Array() {
        delete[] data;
    }

    size_t length() const {
        return sz;
    }

    T &operator[](size_t i) {
        return get(i);
    }

    const T &operator[](size_t i) const {
        return get(i);
    }

    T *ptr() {
        return data;
    }

    T &get(size_t i) {
        return data[i];
    }

    const T &get(size_t i) const {
        return data[i];
    }

    void set(size_t i, T &v) {
        data[i] = v;
    }
};

#endif
