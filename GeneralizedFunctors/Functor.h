//
// Created by gitarist on 4/14/20.
//

#ifndef GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_FUNCTOR_H_
#define GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_FUNCTOR_H_
#include <memory>
#include "../Techniques/nulltype_and_empty.h"
#include "../Typelists/typelist.h"
#include "../Techniques/type_traits.h"
template<typename ResultType, class TList> class FunctorImpl;

template<class ParentFunctor, typename Fun>
class FunctorHandler : public FunctorImpl <
            typename ParentFunctor::ResultType,
            typename ParentFunctor::Arguments
        > {
 public:
  typedef typename ParentFunctor::ResultType ResultType;
  FunctorHandler(const Fun &fun) : fun_(fun) {}
  FunctorHandler *Clone() const { return new FunctorHandler(*this); }
  ResultType operator()() {
    return fun_();
  }
  ResultType operator()(typename ParentFunctor::Parm1 p1) {
    return fun_(p1);
  }
  ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2) {
    return fun_(p1, p2);
  }
 private:
  Fun fun_;
};

template <class ParentFunctor, typename PointerToObj,
    typename PointerToMemFn>
class MemFunHandler
    : public FunctorImpl
        <
            typename ParentFunctor::ResultType,
            typename ParentFunctor::Arguments
        >
{
 public:
  typedef typename ParentFunctor::ResultType ResultType;
  MemFunHandler(const PointerToObj& pToObj, PointerToMemFn pMemFn)
      : pObj_(pToObj), pMemFn_(pMemFn) {}

  MemFunHandler* Clone() const
  { return new MemFunHandler(*this); }

  typedef typename ParentFunctor::Parm1 Parm1;
  typedef typename ParentFunctor::Parm2 Parm2;

  ResultType operator()()
  {
    return ((*pObj_).*pMemFn_)();
  }

  ResultType operator()(Parm1 p1)
  {
    return ((*pObj_).*pMemFn_)(p1);
  }

  ResultType operator()(Parm1 p1, Parm2 p2)
  {
    return ((*pObj_).*pMemFn_)(p1, p2);
  }

 private:
  PointerToObj pObj_;
  PointerToMemFn pMemFn_;
};


template<typename RType, class TList>
class Functor {
 private:
  // Handy type definition for the body type
  typedef FunctorImpl <RType, TList> Impl;
  std::shared_ptr<Impl> spImpl_;
 public:
  typedef RType ResultType;
  typedef TList Arguments;

 public:
  Functor();
  Functor(const Functor &);
  Functor &operator=(const Functor &);
  explicit Functor(std::shared_ptr<Impl> spImpl);
  template<class Fun>
  Functor(const Fun &fun);

  template<typename PointerToObj, typename PointerToMemFun>
  Functor(const PointerToObj pObj, PointerToMemFun pMemFun);

  typedef typename TypeTraits<typename TL::TypeAtNonStrict<TList, 0, EmptyType>::Result>::ParameterType Parm1;
  typedef typename TypeTraits<typename TL::TypeAtNonStrict<TList, 1, EmptyType>::Result>::ParameterType Parm2;
 public:
  RType operator()() {
    return (*spImpl_)();
  }
  RType operator()(Parm1 p1) {
    return (*spImpl_)(p1);
  }
  RType operator()(Parm1 p1, Parm2 p2) {
    return (*spImpl_)(p1, p2);
  }
};

template<typename ResultType, class TList>
template<typename Fun>
Functor<ResultType, TList>::Functor(const Fun &fun)
    : spImpl_(new FunctorHandler<Functor, Fun>(fun))
{}

template <typename ResultType, typename TList>
template<typename PointerToObj, typename PointerToMemFun>
Functor<ResultType, TList> :: Functor(const PointerToObj pObj, PointerToMemFun pMemFun)
: spImpl_(new MemFunHandler<Functor, PointerToObj, PointerToMemFun>(pObj, pMemFun))
{}

template<typename ResultType>
class FunctorImpl<ResultType, NullType> {
 public:
  virtual ResultType operator()() = 0;
  virtual FunctorImpl *Clone() const = 0;
  virtual ~FunctorImpl() {}
};

template<typename ResultType, class P1>
class FunctorImpl<ResultType, TYPELIST_1(P1) >{
 public:
  virtual ResultType operator()(P1) = 0;
  virtual FunctorImpl *Clone() const = 0;
  virtual ~FunctorImpl() {}
};

template<typename ResultType, class P1, class P2>
class FunctorImpl<ResultType, TYPELIST_2(P1, P2) > {
 public:
  virtual ResultType operator()(P1, P2) = 0;
  virtual FunctorImpl *Clone() const = 0;
  virtual ~FunctorImpl() {}
};

// Test
struct TestFunctor {
  const char* operator()(double, double) {
    static const char buffer[] = "Hello, world!";
// It's safe to return a pointer to a static buffer
    return buffer;
  }
};

const char* TestFunction(double, double) {
  static const char buffer[] = "Hello, world!";
// It's safe to return a pointer to a static buffer
  return buffer;
}

void test(){
  TestFunctor f;
  using namespace std;

  Functor<string, TYPELIST_2(double, double) > cmd(f); // Should print "world!"
  cout << cmd(10, 10).substr(7) << endl;

  Functor<string, TYPELIST_2(int, int) > cmd1(&(TestFunction));
  cout << cmd1(10, 10).substr(7) << endl;
}


#endif //GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_FUNCTOR_H_
