//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_SELECTION_H_
#define GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_SELECTION_H_

#include <iostream>

template<bool flag, typename T, typename U>
struct Select {
  typedef T Result;
};

template<typename T, typename U>
struct Select<false, T, U> {
  typedef U Result;
};

template <typename T, bool isPolymorphic>
class NiftyContainer{
  typedef typename Select<isPolymorphic, T*, T> ::Result ValueType;
};

#endif //GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_SELECTION_H_
