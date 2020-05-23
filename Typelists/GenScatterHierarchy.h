//
// Created by gitarist on 4/6/20.
//

#ifndef GENERICPROGRAMMING_SRC_TYPELISTS_GENSCATTERHIERARCHY_H_
#define GENERICPROGRAMMING_SRC_TYPELISTS_GENSCATTERHIERARCHY_H_

#include "typelist.h"
#include <string>
#include <iostream>
#include "../Techniques/type_to_type_mapping.h"
#include "../Techniques/map_integrals_to_types.h"

template<class TList, template<class> class Unit>
class GenScatterHierarchy;

// GenScatterHierarchy specialization: Typelist to Unit
template<class T1, class T2, template<class> class Unit>
class GenScatterHierarchy<Typelist<T1, T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>, public GenScatterHierarchy<T2, Unit> {
 public:
  typedef Typelist<T1, T2> TList;
  typedef GenScatterHierarchy<T1, Unit> LeftBase;
  typedef GenScatterHierarchy<T2, Unit> RightBase;
};

// Pass an atomic type (non-typelist) to Unit
template<class AtomicType, template<class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType> {
  typedef Unit<AtomicType> LeftBase;
};

// Do nothing for NullType
template<template<class> class Unit>
class GenScatterHierarchy<NullType, Unit> {
};

template<class H, typename R>
inline R &FieldHelper(H &obj, Type2Type<R>, Int2Type<0>) {
  typename H::LeftBase &subObj = obj;
  return subObj;
}

template<class H, typename R, int i>
inline R &FieldHelper(H &obj, Type2Type<R> tt, Int2Type<i>) {
  typename H::RightBase &subobj = obj;
  return FieldHelper(subobj, tt, Int2Type<i - 1>());
}



//==================================
//usage

template<class T>
struct Holder {
  T value_;
};

struct Widget_ {};

namespace Hierarchy {
void usage_() {
  typedef GenScatterHierarchy<TYPELIST_3(int, std::string, Widget_), Holder> WidgetInfo;

  WidgetInfo obj;

  (static_cast<Holder<std::string> &>(obj)).value_ = "Hello ";
  (static_cast<Holder<int> &>(obj)).value_ = 10;

  std::string name = (static_cast<Holder<std::string> &>(obj)).value_;
  int age = (static_cast<Holder<int> &>(obj)).value_;

  std::cout << name << " " << age << std::endl;
}
};

#endif //GENERICPROGRAMMING_SRC_TYPELISTS_GENSCATTERHIERARCHY_H_
