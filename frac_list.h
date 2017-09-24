#ifndef FRAC_LIST_H
#define FRAC_LIST_H

#if 0
#include <vector>

template <typename T>
using frac_list = std::vector<T>;
#else
#include <deque>

template <typename T>
using frac_list = std::deque<T>;
#endif

#endif // FRAC_LIST_H