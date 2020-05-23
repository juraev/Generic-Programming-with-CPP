//
// Created by gitarist on 5/15/20.
//

#ifndef GENERICPROGRAMMING_SRC_ABSTRACTFACTORY_ABSTRACTFACTORYUIT_H_
#define GENERICPROGRAMMING_SRC_ABSTRACTFACTORY_ABSTRACTFACTORYUIT_H_

#include "../Techniques/type_to_type_mapping.h"

template<class T>
class AbstractFactoryUnit {
public:
    virtual T* DoCreate(Type2Type<T>) = 0;
    virtual ~AbstractFactoryUnit() { }
};

#endif //GENERICPROGRAMMING_SRC_ABSTRACTFACTORY_ABSTRACTFACTORYUIT_H_
