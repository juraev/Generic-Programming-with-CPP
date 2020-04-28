//
// Created by gitarist on 4/12/20.
//

#ifndef GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_SMALLOBJECT_H_
#define GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_SMALLOBJECT_H_

class SmallObject {
 public:
  static void* operator new(std::size_t size);
  static void operator delete(void* p, std::size_t size);
  virtual ~SmallObject(){};
};

#endif //GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_SMALLOBJECT_H_
