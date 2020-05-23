//
// Created by gitarist on 5/8/20.
//

#ifndef GENERICPROGRAMMING_SRC_SMART_POINTERS_DEFAULTSPSTORAGE_H_
#define GENERICPROGRAMMING_SRC_SMART_POINTERS_DEFAULTSPSTORAGE_H_

template<class T>
class DefaultSPStorage {
 protected:
  //the type of the pointee_ object //type returned by operator->
  typedef T *StoredType;
  typedef T *PointerType;
  typedef T &ReferenceType; //type returned by operator*

 public:

  DefaultSPStorage() : pointee_(Default()) {}

  DefaultSPStorage(const StoredType &p) : pointee_(p) {}

  PointerType operator->() const { return pointee_; }

  ReferenceType operator*() const { return *pointee_; }

  friend inline PointerType GetImpl(const DefaultSPStorage &sp) { return sp.pointee_; }

  friend inline const StoredType &GetImplRef(const DefaultSPStorage &sp) { return sp.pointee_; }

  friend inline StoredType &GetImplRef(DefaultSPStorage &sp) { return sp.pointee_; }
 protected:
  void Destroy() { delete pointee_; }

  static StoredType Default() { return 0; }
 private:

  StoredType pointee_;
};

#endif //GENERICPROGRAMMING_SRC_SMART_POINTERS_DEFAULTSPSTORAGE_H_
