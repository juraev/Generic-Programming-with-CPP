//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_TO_TYPE_MAPPING_H_
#define GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_TO_TYPE_MAPPING_H_

#include <iostream>

struct Widget{
  Widget(int, int){};
};

template <typename T>
struct Type2Type
{
  typedef T OriginalType;
};

template<class T, class U>
T* create(const U& arg, Type2Type<T>)
{
  return new T(arg);
};

template <class U>
Widget* create(const U& arg, Type2Type<Widget>)
{
  return new Widget(arg, -1);
}

void usage__(){
  std::string* pStr = create("Hello", Type2Type<std::string>());
  Widget* pW = create(100, Type2Type<Widget>());
}

#endif //GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_TO_TYPE_MAPPING_H_
