#ifndef _CPPLIB_COMMON_ARRAY_HPP
#define _CPPLIB_COMMON_ARRAY_HPP

#include <stdint.h>

#include "object.hpp"

template<typename T>
class Slice : public Object {
    protected:
    size_t sz;
    T *data;

    public:
    Slice(size_t _sz, T *_data) : sz(_sz), data(_data) {
    }

    virtual ~Slice() {
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

// An array is just a slice that owns its data.
template<typename T>
class Array : public Slice<T> {
    public:
    Array(size_t _sz) : Slice<T>(_sz, new T[_sz]) {
    }

    Array(size_t _sz, T *_data) : Slice<T>(_sz, _data) {
    }

    Slice<T> slice() {
        return Slice<T>(this->sz, this->data);
    }

    Slice<T> slice(int start, int end) {
        return Slice<T>(end - start, &this->data[start]);
    }

    virtual ~Array() {
        delete[] this->data;
    }
};

#endif
