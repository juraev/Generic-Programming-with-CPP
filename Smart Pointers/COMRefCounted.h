//
// Created by gitarist on 5/9/20.
//

#ifndef GENERICPROGRAMMING_SRC_SMART_POINTERS_COMREFCOUNTED_H_
#define GENERICPROGRAMMING_SRC_SMART_POINTERS_COMREFCOUNTED_H_

template<class P>
class COMRefCounted {
 public:
  static P Clone(const P &val) {
    val->AddRef();
    return val;
  }
  static bool Release(const P &val) {
    val->Release();
    return false;
  }
  enum { destructiveCopy = false }; // see below
};

#endif //GENERICPROGRAMMING_SRC_SMART_POINTERS_COMREFCOUNTED_H_
