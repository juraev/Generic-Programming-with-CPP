//
// Created by gitarist on 5/9/20.
//

#ifndef GENERICPROGRAMMING_SRC_SMART_POINTERS_REFCOUNTED_H_
#define GENERICPROGRAMMING_SRC_SMART_POINTERS_REFCOUNTED_H_

template<class P>
class RefCounted {
  unsigned int *pCount_;
 protected:
  RefCounted() : pCount_(new unsigned int(1)) {}

  P Clone(const P &val) {
    ++*pCount_;
    return val;
  }

  bool Release(const P &) {
    if (!--*pCount_) {
      delete pCount_;
      return true;
    }
    return false;
  }
  enum { destructiveCopy = false }; // see below
};

#endif //GENERICPROGRAMMING_SRC_SMART_POINTERS_REFCOUNTED_H_
