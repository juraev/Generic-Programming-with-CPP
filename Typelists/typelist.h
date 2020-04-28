//
// Created by gitarist on 4/2/20.
//

#ifndef GENERICPROGRAMMING_SRC_TYPELISTS_TYPELIST_H_
#define GENERICPROGRAMMING_SRC_TYPELISTS_TYPELIST_H_

#include <iostream>
#include "../Techniques/nulltype_and_empty.h"
#include "../Techniques/detecting_convertibility_and_inheritance_at_compile_time.h"
#include "../Techniques/type_selection.h"

template<class T, class U>
struct Typelist {
  typedef U Head;
  typedef T Tail;
};

namespace TL {
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4) >

template<class TList> struct Length;

template<>
struct Length<NullType> {
  enum { value = 0 };
};
template<class T, class U>
struct Length<Typelist<T, U> > {
  enum { value = 1 + Length<U>::value };
};

template<class TList, unsigned int index>
struct TypeAt;

template<class Head, class Tail>
struct TypeAt<Typelist<Head, Tail>, 0> {
  typedef Head Result;
};

template<class Head, class Tail, unsigned int i>
struct TypeAt<Typelist<Head, Tail>, i> {
  typedef typename TypeAt<Tail, i - 1>::Result Result;
};

template<class TList, unsigned int index, class DefaultResult>struct TypeAtNonStrict;

template<unsigned int index, class DefaultResult>
struct TypeAtNonStrict<NullType, index, DefaultResult> {
  typedef DefaultResult Result;
};

template<class Head, class Tail, class DefaultResult>
struct TypeAtNonStrict<Typelist<Head, Tail>, 0, DefaultResult> {
  typedef Head Result;
};

template<class Head, class Tail, unsigned int i, class DefaultResult>
struct TypeAtNonStrict<Typelist<Head, Tail>, i, DefaultResult> {
  typedef typename TypeAtNonStrict<Tail, i - 1, DefaultResult>::Result Result;
};

template<class TList, class T>
struct IndexOf;

template<class T>
struct IndexOf<NullType, T> {
  enum { value = -1 };
};

template<class T, class Tail>
struct IndexOf<Typelist<T, Tail>, T> {
  enum { value = 0 };
};

template<class Head, class Tail, class T>
struct IndexOf<Typelist<Head, Tail>, T> {
 private:
  enum { temp = IndexOf<Tail, T>::value };
 public:
  enum { value = temp == -1 ? -1 : 1 + temp };
};

template<class TList, class T>
struct Append;

template<>
struct Append<NullType, NullType> {
  typedef NullType Result;
};

template<class T>
struct Append<NullType, T> {
  typedef TYPELIST_1(T) Result;
};

template<class Head, class Tail>
struct Append<NullType, Typelist<Head, Tail>> {
  typedef Typelist<Head, Tail> Result;
};

template<class Head, class Tail, class T>
struct Append<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename Append<Tail, T>::Result> Result;
};

template<class TList, class T>
struct Erase;

template<class T>
struct Erase<NullType, T> {
  typedef NullType Result;
};

template<class Tail, class T>
struct Erase<Typelist<T, Tail>, T> {
  typedef Tail Result;
};

template<class Head, class Tail, class T>
struct Erase<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename Erase<Tail, T>::Result> Result;
};

template<class TList, class T>
struct EraseAll;

template<class T>
struct EraseAll<NullType, T> {
  typedef NullType Result;
};

template<class Tail, class T>
struct EraseAll<Typelist<T, Tail>, T> {
  typedef typename Erase<Tail, T>::Result Result;
};

template<class Head, class Tail, class T>
struct EraseAll<Typelist<Head, Tail>, T> {
  typedef Typelist<Head, typename EraseAll<Tail, T>::Result> Result;
};

template<class TList>
struct NoDublicates;

template<>
struct NoDublicates<NullType> {
  typedef NullType Result;
};

template<class Head, class Tail>
struct NoDublicates<Typelist<Head, Tail>> {
  typedef typename Typelist<Head, Erase<NoDublicates<Tail>, Head>>::Result Result;
};

template<class TList, class T, class U>
struct Replace;

template<class T, class U>
struct Replace<NullType, T, U> {
  typedef NullType Result;
};

template<class TList, class T>
struct Replace<TList, T, T> {
  typedef TList Result;
};

template<class Tail, class T, class U>
struct Replace<Typelist<T, Tail>, T, U> {
  typedef Typelist<U, Tail> Result;
};

template<class Head, class Tail, class T, class U>
struct Replace<Typelist<Head, Tail>, T, U> {
  typedef Typelist<Head, typename Replace<Tail, T, U>::Result> Result;
};

template<class TList, class T>
struct MostDerived;

template<class T>
struct MostDerived<NullType, T> {
  typedef T Result;
};

template<class Head, class Tail, class T>
struct MostDerived<Typelist<Head, Tail>, T>{
 private:
  typedef typename MostDerived<Tail, T> :: Result Candidate;
 public:
  typedef typename Select<SUPERSUBCLASS(Candidate, Head), Head, Candidate> :: Result Result;
};

template<class TList>
struct DerivedToFront;

template<>
struct DerivedToFront<NullType> {
  typedef NullType Result;
};

template<class Head, class Tail>
struct DerivedToFront<Typelist<Head, Tail>> {
 private:
  typedef typename MostDerived<Tail, Head> :: Result TheMostDerived;
  typedef typename Replace<Tail, TheMostDerived, Head> :: Result L;
 public:
  typedef typename Typelist<TheMostDerived, DerivedToFront<L>> :: Result Result;
};

}

#endif //GENERICPROGRAMMING_SRC_TYPELISTS_TYPELIST_H_
