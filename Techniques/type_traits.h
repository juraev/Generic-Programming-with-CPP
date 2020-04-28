//
// Created by gitarist on 4/1/20.
//

#ifndef GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_TRAITS_H_
#define GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_TRAITS_H_

#include <iostream>
#include <vector>
#include "nulltype_and_empty.h"
#include "detecting_convertibility_and_inheritance_at_compile_time.h"
#include "../Typelists/typelist.h"
#include "map_integrals_to_types.h"

template<typename InIt, typename OutIt>
OutIt copy(InIt first, InIt last, OutIt result) {
  for (; first != last; ++first, ++result)
    *result = *first;
}

void BitBlast(const void *src, void *dest, size_t bytes);

template<typename T>
class TypeTraits {

 private:
  typedef TYPELIST_4(
      unsigned char, unsigned short int,
      unsigned int, unsigned long int)
      UnsignedInts;

  typedef TYPELIST_4(
      char, short int,
      int, long int)
      SignedInts;

  typedef TYPELIST_3(
      bool, char, wchar_t)
      OtherInts;

  typedef TYPELIST_3(
      float, double, long double)
      Floats;

 public:

  enum { isStdUnsignedInt = TL::IndexOf<UnsignedInts, T>::value >= 0 };
  enum { isStdSignedInt = TL::IndexOf<SignedInts, T>::value >= 0 };
  enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt || TL::IndexOf<OtherInts, T>::value >= 0 };
  enum { isStdFloat = TL::IndexOf<Floats, T>::value >= 0 };
  enum { isStdArith = isStdIntegral || isStdFloat };
  enum { isStdFundamental = isStdArith || isStdFloat || Conversion<T, void>::sameType };

 private:
  template<class U>
  struct PointerTraits {
    enum { result = false };
    typedef NullType PointeeType;
  };

  template<class U>
  struct PointerTraits<U *> {
    enum { result = true };
    typedef U PointeeType;
  };

  template<class U>
  struct PToMTraits {
    enum { result = false };
  };

  template<class U, class V>
  struct PToMTraits<U V::*> {
    enum { result = true };
  };

 public:
  typedef typename PointerTraits<T>::PointeeType PointeeType;
  enum { isPointer = PointerTraits<T>::result };
  enum { isMemberPointer = PToMTraits<T>::result };

 private:
  template<class U>
  struct ReferencedTraits {
    enum { result = false };
    typedef NullType ReferencedType;
  };

  template<class U>
  struct ReferencedTraits<U &> {
    enum { result = true };
    typedef U ReferencedType;
  };
 public:
  typedef typename ReferencedTraits<T>::ReferencedType ReferencedType;
  typedef typename Select<isStdArith || isPointer || isMemberPointer, T, ReferencedType &>::Result ParameterType;

 private:
  template <class U>
  struct UnConst{
    typedef U Result;
  };

  template <class U>
  struct UnConst<const U>{
    typedef U Result;
  };

 public:
  typedef typename UnConst<T> :: Result NonConstType;
};

//BitBlasting

enum CopyAlgoSelector {Conservative, Fast};

//Conservative routine – works for any type
template <typename InIt, typename OutIt>
OutIt CopyImpl(InIt first, InIt last, OutIt result, Int2Type<Conservative>){
  for(; first != last; ++first, ++ result)
    result = first;
  return result;
}

template <typename InIt, typename OutIt>
OutIt CopyImpl(InIt first, InIt last, OutIt result, Int2Type<Fast>){
  const size_t n = last - first;
  BitBlast(first, last, n * sizeof(*first));
  return result + n;
}

template <typename InIt, typename OutIt>
OutIt Copy(InIt first, InIt last, OutIt result){
  typedef typename TypeTraits<InIt> :: PointeeType SrcPointee;
  typedef typename TypeTraits<OutIt> :: PointeeType DestPointee;

  enum { copyAlgo =
      TypeTraits<InIt> :: isPointer &&
      TypeTraits<OutIt> :: isPointer &&
      TypeTraits<SrcPointee> :: isStdFundamental &&
      TypeTraits<DestPointee> :: isStdFundamental &&
      sizeof(SrcPointee) == sizeof(DestPointee) ? Fast : Conservative
  };
  return CopyImpl(first, last, result, Int2Type<copyAlgo>);
}

void usage_() {
  const bool iterIsPtr = TypeTraits<std::vector<int>::iterator>::isPointer;
  std::cout << "vector<int>::iterator is " << (iterIsPtr ? "fast" : "smart") << std::endl;
}

#endif //GENERICPROGRAMMING_SRC_TECHNIQUES_TYPE_TRAITS_H_
