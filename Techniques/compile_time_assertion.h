//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_COMPILE_TIME_ASSERTION_H
#define GENERICPROGRAMMING_COMPILE_TIME_ASSERTION_H

#include <iostream>

//#define STATIC_CHECK(expr) {char unnamed[(expr) ? 1 : 0]; }

//template<bool>
//struct CompileTimeError;
//template<>
//struct CompileTimeError<true> {
//};
//#define STATIC_CHECK(expr) \
//    CompileTimeError<expr != 0>()

template<bool>
struct CompileTimeChecker {
  CompileTimeChecker(...) = default;
};

template<>
struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg)\
    {\
        class ERROR_##msg {};\
        CompileTimeChecker<expr != 0>((ERROR_##msg()));\
    }

template<class To, class From>
To safe_reinterpret_cast(From from) {
//    assert (sizeof(From) <= sizeof(To));
  STATIC_CHECK(sizeof(From) <= sizeof(To), Destination_Type_Too_Narrow);

//    return reinterpret_cast<To>(from);
  return 'c';
}

void usage() {
  int i = 0;
  char p = safe_reinterpret_cast<char, int>(i);
}

#endif //GENERICPROGRAMMING_COMPILE_TIME_ASSERTION_H
