//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_COMBINING_POLICIES_H
#define GENERICPROGRAMMING_COMBINING_POLICIES_H

#include <iostream>

struct Widget {
    void print(){
        std::cout << "Working" << std::endl;
    }
};

template <class T>
struct EnsureNotNull{
    static void Check(T* ptr){
        if(!ptr) ptr = GetDefaultValue();
    }

    static T* GetDefaultValue(){
        return nullptr;
    }
};

template <class T>
struct SimpleModel{
    struct Lock : T{
        Lock(T t){

        }
    };
    Lock guard(T t){
        return t;
    }
};

template <
        class T,
        template <class> class CheckingPolicy,
        template <class> class ThreadingModel
>
class SmartPtr : public CheckingPolicy<T>, public ThreadingModel<SmartPtr<T, CheckingPolicy, ThreadingModel>>{
public:
    T* operator->(){
        typename ThreadingModel<SmartPtr> :: Lock guard(*this);
        CheckingPolicy<T>::Check(pointee_);
        return pointee_;
    }

private:
    T* pointee_;
};

int usage() {
    SmartPtr<Widget, EnsureNotNull, SimpleModel> smartPtr{};
    smartPtr->print();
    return 0;
}

#endif //GENERICPROGRAMMING_COMBINING_POLICIES_H
