//
// Created by gitarist on 5/11/20.
//

#ifndef GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_SHAPEFACTORY_H_
#define GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_SHAPEFACTORY_H_

#include "Shape.h"

class ShapeFactory {
 public:
  typedef Shape* (*CreateShapeCallback())();
 private:
  typedef std::map<int, CreateShapeCallback> CallbackMap;

 public:
  bool RegisterShape(int ShapeId, CreateShapeCallback CreateFn);
  bool UnRegisterShape(int ShapeId);
  Shape* CreateShape(int ShapeId);
 private:
  CallbackMap callbacks_;
};

#endif //GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_SHAPEFACTORY_H_
