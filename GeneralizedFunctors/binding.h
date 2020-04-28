//
// Created by gitarist on 4/22/20.
//

#ifndef GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_BINDING_H_
#define GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_BINDING_H_

#include "Functor.h"
#include <iostream>

using namespace std;

template<class Incoming>
class BindFirst : FunctorImpl<typename Incoming::ResultType, typename Incoming::Arguments::Tail> {
  typedef Functor<typename Incoming::ResultType, typename Incoming::Arguments::Tail> Outgoing;
  typedef typename Incoming::Parm1 Bound;
  typedef typename Incoming::ResultType ResultType;

 public:
  BindFirst(const Incoming &fun, Bound bound) : fun_(fun), bound_(bound) {}
  BindFirst *Clone() const {
    return new BindFirst(*this);
  }
  ResultType operator()() {
    return fun_(bound_);
  }
  ResultType operator()(typename Outgoing::Parm1 p1) {
    return fun_(bound_, p1);
  }
  ResultType operator()(typename Outgoing::Parm1 p1, typename Outgoing::Parm2 p2) {
    return fun_(bound_, p1, p2);
  }
 private:
  Incoming fun_;
  Bound bound_;
};

const char *Fun(int i, int j) {
  cout << "Fun" << i << ", " << j << ") " << "called\n";
  return "0";
}

void useBind() {
  Functor<const char *, TYPELIST_2(char, int) > f1(Fun);

  Functor<std::string, TYPELIST_1(double) > f2(BindFirst(f1, 10));
  // Prints: Fun(10, 15) called
  f2(15);
}

#endif //GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_BINDING_H_
