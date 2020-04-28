//
// Created by gitarist on 4/10/20.
//

#ifndef GENERICPROGRAMMING_SRC_TYPELISTS_HIERARCHIES_H_
#define GENERICPROGRAMMING_SRC_TYPELISTS_HIERARCHIES_H_

#include "../Techniques/nulltype_and_empty.h"
#include "typelist.h"

template<class T, class Base>
class EventHandler : public Base {
 public:
  virtual void OnEvent(const T &, int eventId = 0) = 0;
};

struct Window {};
struct Button {};
struct ScrollBar {};

template<class TList, template<class AtomicType, class Base> class Unit, class Root=EmptyType>
class GenerateLinearHierarchy;

template<class T1, class T2, template<class, class> class Unit, class Root>
class GenerateLinearHierarchy<Typelist<T1, T2>, Unit, Root> : public Unit<T1, GenerateLinearHierarchy<T2, Unit, Root>> {
};

template<class T, template<class, class> class Unit, class Root>
class GenerateLinearHierarchy<TYPELIST_1(T), Unit, Root> : public Unit<T, Root> {};

typedef GenerateLinearHierarchy<TYPELIST_3(Window, Button, ScrollBar), EventHandler> MyEventHandler;

namespace genhier {
void usage() {
  MyEventHandler handler();
}
}

#endif //GENERICPROGRAMMING_SRC_TYPELISTS_HIERARCHIES_H_
