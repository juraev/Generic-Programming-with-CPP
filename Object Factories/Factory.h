//
// Created by gitarist on 5/11/20.
//

#ifndef GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_FACTORY_H_
#define GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_FACTORY_H_
#include "DefaultFactoryError.h"

template<
    class AbstractProduct,
    typename IdentifierType,
    typename ProductCreator = AbstractProduct* (*)(),
    template<typename, class> class FactoryErrorPolicy = DefaultFactoryError
    >
class Factory : public FactoryErrorPolicy<IdentifierType, AbstractProduct> {
 public:
  bool Register(const IdentifierType &id, ProductCreator creator) {
    return associations_.insert(AssocMap::value_type(id, creator)).second;
  }
  bool Unregister(const IdentifierType &id) {
    return associations_.erase(id) == 1;
  }
  AbstractProduct *CreateObject(const IdentifierType &id) {
    typename AssocMap::const_iterator i = associations_.find(id);
    if (i != associations_.end()) {
      return (i->second)();
    }
    return OnUnknownType(id);
  }
 private:
  typedef std::map <IdentifierType, AbstractProduct> AssocMap;
  AssocMap associations_;
};

#endif //GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_FACTORY_H_
