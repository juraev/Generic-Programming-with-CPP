//
// Created by gitarist on 4/19/20.
//

#ifndef GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_POINTERS_TO_MEMBER_FUNCTIONS_H_
#define GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_POINTERS_TO_MEMBER_FUNCTIONS_H_
#include <iostream>
#include "Functor.h"
using namespace std;

class Parrot {
 public:
  void Eat() {
    cout << "Tsk, knick, tsk...\n";
  }
  void Speak() {
    cout << "Oh Captain, my Captain!\n";
  }
};


void use() {
//  // Define a type: pointer to a member function of
//  // Parrot, taking no arguments and
//  // returning void.
//  typedef void (Parrot::* TpMemFun)();
//
//  // Create an object of that type
//  // and initialize it with the address of
//  // Parrot::Eat.
//  TpMemFun pActivity = &Parrot::Eat;
//
//  // Create a Parrot...
//  Parrot geronimo;
//
//  // ...and a pointer to it
//  Parrot *pGeronimo = &geronimo;
//
//  // Invoke the member function stored in Activity
//  // via an object. Notice the use of operator.*
//  (geronimo.*pActivity)();
//
//  // Same, via pointer. Now we use operator->*
//  (pGeronimo->*pActivity)();
//
//  // Change the activity
//  pActivity = &Parrot::Speak;
//
//  // Wake up, Geronimo!
//  (geronimo.*pActivity)();
  Parrot geronimo;
  // Define two Functors

  Functor<void, NullType>
      cmd1(&geronimo, &Parrot::Eat),
      cmd2(&geronimo, &Parrot::Speak);

  // Invoke each of them
  cmd1();
  cmd2();
}

#endif //GENERICPROGRAMMING_SRC_GENERALIZEDFUNCTORS_POINTERS_TO_MEMBER_FUNCTIONS_H_
