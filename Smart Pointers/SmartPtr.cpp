//
// Created by gitarist on 5/7/20.
//

#include "SmartPtr.h"

bool SmartPtr::operator!() const {
  return pointee_ == 0;
}

bool SmartPtr::operator==(const SmartPtr &lhs, const T *rhs) const {
  return lhs.pointee_ == rhs;
}

bool SmartPtr::operator==(const T *lhs, const SmartPtr &rhs) const {
  return lhs == rhs.pointee_;
}

bool SmartPtr::operator!=(const SmartPtr &lhs, const T *rhs) const {
  return lhs.pointee_ != rhs;
}

bool SmartPtr::operator!=(const T *lhs, const SmartPtr &rhs) const {
  return lhs != rhs.pointee_;
}

template<class U>
bool SmartPtr::operator==(const SmartPtr &lhs, const U *rhs) const {
  return lhs.pointee_ == rhs;
}

template<class U>
bool SmartPtr::operator==(const U *lhs, const SmartPtr &rhs) const {
  return lhs == rhs.pointee_;
}
template<class U>
bool SmartPtr::operator!=(const SmartPtr &lhs, const U *rhs) const {
  return lhs.pointee_ != rhs;
}
template<class U>
bool SmartPtr::operator!=(const U *lhs, const SmartPtr &rhs) const {
  return lhs != rhs.pointee_;
}

bool SmartPtr::operator==(const SmartPtr<U> &rhs) const {
  return pointee_ == rhs.pointee_;
}

Tester *SmartPtr::operator Tester *() {
  if (!pointee_) return 0;
  static Tester test;
  return &test;
}

SmartPtr::operator T *() { return pointee_ };

SmartPtr::operator void *() { return pointee_ };

namespace std {
template<class T>
struct less<SmartPtr<T>> : public binary_function<SmartPtr<T>, SmartPtr<T>, bool> {
  bool operator()(const SmartPtr<T> &lhs, const SmartPtr<T> &rhs) const {
    return less<T *>()(GetImpl(lhs), GetImpl(rhs));
  }
};
}