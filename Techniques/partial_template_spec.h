//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_PARTIAL_TEMPLATE_SPEC_H
#define GENERICPROGRAMMING_PARTIAL_TEMPLATE_SPEC_H

#include <iostream>

struct MyDialog {};
struct MyController {};

template<class Arg>
struct Button {};

template<class Window, class Controller>
class Widget {

};

template<>
class Widget<MyDialog, MyController> {

};

template<class Window>
class Widget<Window, MyController> {

};

template<class ButtonArg>
class Widget<Button<ButtonArg>, MyController> {

};

template<class T, class U>
T Fun(U obj); // primary template

//template <class U> void Fun<void, U>(U obj); // illegal partial specialization

template<class T>
T Fun(MyController obj); // legal (overloading)


#endif //GENERICPROGRAMMING_PARTIAL_TEMPLATE_SPEC_H
