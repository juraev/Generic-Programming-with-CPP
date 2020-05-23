//
// Created by gitarist on 5/11/20.
//

#ifndef GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_DEFAULTFACTORYERROR_H_
#define GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_DEFAULTFACTORYERROR_H_

template<class IdentifierType, class ProductType>
class DefaultFactoryError {
 public:
  class Exception : public std::exception {
   public:
    Exception(const IdentifierType &unknownId) : unknownId_(unknownId) { }
    virtual const char *what() {
      return "Unknown object type passed to Factory.";
    }
    const IdentifierType GetId() {
      return unknownId_;
    };
   private:
    IdentifierType unknownId_;
  };
 protected:
  StaticProductType *OnUnknownType(const IdentifierType &id) {
    throw Exception(id);
  }
};

#endif //GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_DEFAULTFACTORYERROR_H_
