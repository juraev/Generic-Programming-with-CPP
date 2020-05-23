//
// Created by gitarist on 5/7/20.
//

#ifndef GENERICPROGRAMMING_SRC_SMART_POINTERS_SMARTPTR_H_
#define GENERICPROGRAMMING_SRC_SMART_POINTERS_SMARTPTR_H_
#include "DefaultSPStorage.h"

template<
    typename T,
    template<class> class OwnershipPolicy = RefCounted,
    class ConversionPolicy = DisallowConversion,
    template<class> class CheckingPolicy = AssertCheck,
    template<class> class StoragePolicy = DefaultSPStorage>
class SmartPtr : StoragePolicy<T>{
 public:

  explicit SmartPtr(T *pointee) : StoragePolicy(pointee) {};

  SmartPtr &operator=(const SmartPtr &other);

  ~SmartPtr();

  bool operator!() const;

  inline friend bool operator==(const SmartPtr &lhs, const T *rhs) const;
  inline friend bool operator==(const T *lhs, const SmartPtr &rhs) const;
  inline friend bool operator!=(const SmartPtr &lhs, const T *rhs) const;
  inline friend bool operator!=(const T *lhs, const SmartPtr &rhs) const;

  template<class U>
  inline friend bool operator==(const SmartPtr &lhs, const U *rhs) const;
  template<class U>
  inline friend bool operator==(const U *lhs, const SmartPtr &rhs) const;
  template<class U>
  inline friend bool operator!=(const SmartPtr &lhs, const U *rhs) const;
  template<class U>
  inline friend bool operator!=(const U *lhs, const SmartPtr &rhs) const;
  template<class U>
  bool operator==(const SmartPtr<U> &rhs) const;

  operator T *();

  operator void *();

  operator Tester *();

 private:

  class Tester {
    void operator delete(void *);
  };

  T *pointee_;
};

#endif //GENERICPROGRAMMING_SRC_SMART_POINTERS_SMARTPTR_H_
