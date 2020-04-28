//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_DECOMPOSING_H
#define GENERICPROGRAMMING_DECOMPOSING_H
#include <iostream>

struct Widget {
    void print() {
        std::cout << "Working" << std::endl;
    }
};

struct ExtendedWidget : Widget {
};

template<class T>
struct OpNewCreator {
    static T *Create() {
        return new T;
    }

protected:
    ~OpNewCreator() = default;
};

template<class T>
struct MallocCreator {
    static T *Create() {
        void *buf = std::malloc(sizeof(T));
        if (!buf) return 0;
        return new(buf) T;
    }
};

template<class T>
struct PrototypeCreator {
    explicit PrototypeCreator(T *pObj = 0) : pPrototype_(pObj) {}

    T *Create() {
        return pPrototype_ ? pPrototype_->Clone() : 0;
    }

    T *GetPrototype() { return pPrototype_; };

    void SetPrototype(T *pObj) { pPrototype_ = pObj; };

    T *pPrototype_;
};

template<template<class> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget> {
public:
    void doSomething() {
        CreationPolicy<Widget>().Create();
    }

    void SwitchPrototype(Widget *pNewPrototype) {
        CreationPolicy<Widget> &myPolicy = *this;
        delete myPolicy.GetPrototype();
        myPolicy.SetPrototype(pNewPrototype);
    }
};

template<class T>
struct NoChecking {
    static void Check(T *) {}
};

template<class T>
struct EnforceNotNull {
    class NullPointerException : public std::exception {
    };

    static void Check(T *ptr) {
        if (!ptr) throw NullPointerException();
    }

    EnforceNotNull(NoChecking<T> p) {}
};

template<class T>
struct EnsureNotNull {
    static void Check(T *ptr) {
        if (!ptr) ptr = GetDefaultValue();
    }

    static T *GetDefaultValue() {
        return 0;
    }
};

template<class T>
struct SimpleModel {
    struct Lock : T {
        Lock(T t) {

        }
    };

    Lock guard(T t) {
        return t;
    }
};

template<class T>
class DefaultSmartPtrStorage {
public:
    typedef T *PointerType;
    typedef T &ReferenceType;
protected:
    PointerType GetPointer() { return ptr_; }

    void SetPointer(PointerType ptr) { ptr_ = ptr; }

    PointerType ptr_;
};

template
        <class T, template<class> class CheckingPolicy>
class SmartPtr : public CheckingPolicy<T> {
public:
    SmartPtr(){}

    template<class T1, template<class> class CP1>
    SmartPtr(const SmartPtr<T1, CP1>& other) : pointee_(other.pointee_), CheckingPolicy<T>(other) {}

public:
    T *pointee_;
};

//typedef SmartPtr<Widget, NoChecking, SingleThreaded> WidgetPtr;
//typedef SmartPtr<Widget, EnforceNotNull, SingleThreaded> SafeWidgetPtr;

int usage() {
    SmartPtr<ExtendedWidget, NoChecking> smartPtr;
    SmartPtr<Widget, EnforceNotNull> smartPtr1(smartPtr);

    return 0;
}
#endif //GENERICPROGRAMMING_DECOMPOSING_H
