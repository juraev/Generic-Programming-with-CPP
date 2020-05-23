//
// Created by gitarist on 5/15/20.
//

#ifndef GENERICPROGRAMMING_SRC_ABSTRACTFACTORY_ABSTRACTFACTORYUNIT_H_
#define GENERICPROGRAMMING_SRC_ABSTRACTFACTORY_ABSTRACTFACTORYUNIT_H_

#include "../Typelists/GenScatterHierarchy.h"
#include "AbstractFactoryUnit.h"
#include "../Typelists/hierarchies.h"
#include <iostream>


struct Soldier {
    Soldier()
    {
        std::cout << "Soldier is Created\n";
    }

    void pa(){
        std::cout << "PAAAA" << std::endl;
    }
};
struct Monster {
    Monster()
    {
        std::cout << "Monster is Created\n";
    }
};
struct SuperMonster {
    SuperMonster()
    {
        std::cout << "SuperMonster is Created\n";
    }
};


template<class TList,
        template<class> class Unit = AbstractFactoryUnit>
class AbstractFactory: public GenScatterHierarchy<TList, Unit> {
public:
    typedef TList ProductList;
    template<class T> T* Create()
    {
        Unit<T>& unit = *this;
        return unit.DoCreate(Type2Type<T>());
    }
};

template<class ConcreteProduct, class Base>
class OpNewFactoryUnit: public Base {
    typedef typename Base::ProductList BaseProductList;
protected:
    typedef typename BaseProductList::Tail ProductList;
public:
    typedef typename BaseProductList::Head AbstractProduct;
    ConcreteProduct* DoCreate(Type2Type<AbstractProduct>)
    {
        return new ConcreteProduct();
    }
};

template<class AbstractFact,
        template<class, class> class Creator = OpNewFactoryUnit,
        class TList = typename AbstractFact::ProductList>
class ConcreteFactory
        : public GenerateLinearHierarchy<typename TL::Reverse<TList>::Result, Creator, AbstractFact> {
public:
    typedef typename AbstractFact::ProductList ProductList;
    typedef TList ConcreteProductList;
};

void usage_abstract_fac()
{
    typedef AbstractFactory<TYPELIST_1(Soldier)> AbstractEnemyFactory;

    typedef ConcreteFactory<AbstractEnemyFactory, OpNewFactoryUnit, TYPELIST_1(Soldier)> EnemyFactory;

    EnemyFactory* enemy_factory = new EnemyFactory();

    auto* sold = enemy_factory->Create<Soldier>();
    sold->pa();
}

#endif //GENERICPROGRAMMING_SRC_ABSTRACTFACTORY_ABSTRACTFACTORYUNIT_H_
