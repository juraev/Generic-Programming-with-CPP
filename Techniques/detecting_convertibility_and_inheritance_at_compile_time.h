//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_SRC_TECHNIQUES_DETECTING_CONVERTIBILITY_AND_INHERITANCE_AT_COMPILE_TIME_H_
#define GENERICPROGRAMMING_SRC_TECHNIQUES_DETECTING_CONVERTIBILITY_AND_INHERITANCE_AT_COMPILE_TIME_H_

#include <iostream>
#include <vector>

struct T {};
struct U {};

template<class T, class U>
class Conversion {
  typedef char Small;
  class Big { char dummy[2]; };

  static Small Test(U);
  static Big Test(...);
  static T Make();

 public:
  enum { exists = sizeof(Test(Make())) == sizeof(Small) };
  enum { sameType = false };
};

template<class T>
class Conversion<T, T> {
 public:
  enum { exists = 1, sameType = 1 };
};

#define SUPERSUBCLASS(T, U) \
(Conversion<const U*, const T*>::exists && \
!Conversion<const T*, const void*>::sameType)

void usage() {
  using namespace std;
  cout
      << Conversion<double, int>::exists << ' '
      << Conversion<char, char *>::exists << ' '
      << Conversion<size_t, std::vector<int> >::exists << ' ';

  SUPERSUBCLASS(double, int);
}
#endif //GENERICPROGRAMMING_SRC_TECHNIQUES_DETECTING_CONVERTIBILITY_AND_INHERITANCE_AT_COMPILE_TIME_H_
