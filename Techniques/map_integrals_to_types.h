//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_SRC_TECHNIQUES_MAP_INTEGRALS_TO_TYPES_H_
#define GENERICPROGRAMMING_SRC_TECHNIQUES_MAP_INTEGRALS_TO_TYPES_H_

#include <iostream>

template<int v>
struct Int2Type {
  enum { value = v };
};

template <typename T, bool isPolymorphic>
class NiftyContainer
{
 private:
  void doSomething(T* pObj, Int2Type<true>){
    T* pNewObj = pObj -> Clone();
  }
  void doSomething(T* pObj, Int2Type<false>){
    T* pNewObj = new T(pObj);
  }
 public:
  void doSomething(T* pObj){
    doSomething(pObj, Int2Type<isPolymorphic>());
  }
};

#endif //GENERICPROGRAMMING_SRC_TECHNIQUES_MAP_INTEGRALS_TO_TYPES_H_
