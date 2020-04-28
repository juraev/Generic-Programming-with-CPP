//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_SRC_TECHNIQUES_WRAPPER_AROUND_TYPE_INFO_H_
#define GENERICPROGRAMMING_SRC_TECHNIQUES_WRAPPER_AROUND_TYPE_INFO_H_
#include <iostream>
#include <typeinfo>

struct Base{};
struct Derived : Base{};

void fun(Base* pObj){
  // Compare the two type_info objects corresponding // to the type of *pObj and Derived
  if (typeid(*pObj) == typeid(Derived))
  {
    //... aha, pObj actually points to a Derived object ...
  }
  std::cout << (typeid(*pObj)).name() << std :: endl;
}

class TypeInfo{
 public:
  TypeInfo();
  TypeInfo(const std :: type_info&);
  TypeInfo(const TypeInfo&);
  TypeInfo& operator = (const TypeInfo&);

  bool before(const TypeInfo&) const ;
  const char* name() const;
 private:
  const std :: type_info* info_;
};

bool operator==(const TypeInfo&, const TypeInfo&);
bool operator!=(const TypeInfo&, const TypeInfo&);
bool operator<(const TypeInfo&, const TypeInfo&);
bool operator>=(const TypeInfo&, const TypeInfo&);
bool operator>(const TypeInfo&, const TypeInfo&);
bool operator<=(const TypeInfo&, const TypeInfo&);

void fun_(Base* pObj){
  TypeInfo info = typeid(Derived);

  if(typeid(*pObj) == info){

  }
}


#endif //GENERICPROGRAMMING_SRC_TECHNIQUES_WRAPPER_AROUND_TYPE_INFO_H_
