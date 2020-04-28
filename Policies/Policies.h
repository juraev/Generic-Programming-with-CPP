//
// Created by gitarist on 3/30/20.
//

#ifndef GENERICPROGRAMMING_POLICIES_H
#define GENERICPROGRAMMING_POLICIES_H

#include <iostream>

struct Widget {
};

template<class T>
struct OpNewCreator {
    static T *Create() {
        return new T;
    }

protected:
    ~OpNewCreator()= default;
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
    void SwitchPrototype(Widget* pNewPrototype){
        CreationPolicy<Widget>& myPolicy = *this;
        delete myPolicy.GetPrototype();
        myPolicy.SetPrototype(pNewPrototype);
    }
};



#endif //GENERICPROGRAMMING_POLICIES_H
