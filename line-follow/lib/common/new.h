#pragma once

#include <new>
#include <bits/functexcept.h>
#include <cstdlib>
#include <cstddef>

template <bool abortOnFail>
static inline void *allocate(size_t size) _GLIBCXX_USE_NOEXCEPT;

void *operator new(size_t size);
void *operator new[](size_t size);
void *operator new(std::size_t size, const std::nothrow_t &) _GLIBCXX_USE_NOEXCEPT;
void *operator new[](std::size_t size, const std::nothrow_t &) _GLIBCXX_USE_NOEXCEPT;
void operator delete(void *ptr) _GLIBCXX_USE_NOEXCEPT;
void operator delete(void *ptr, size_t) _GLIBCXX_USE_NOEXCEPT;
void operator delete[](void *ptr) _GLIBCXX_USE_NOEXCEPT;
void operator delete[](void *ptr, size_t) _GLIBCXX_USE_NOEXCEPT;
void operator delete(void *ptr, const std::nothrow_t &) _GLIBCXX_USE_NOEXCEPT;
void operator delete[](void *ptr, const std::nothrow_t &) _GLIBCXX_USE_NOEXCEPT;
