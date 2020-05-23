//
// Created by gitarist on 5/11/20.
//

#include "ShapeFactory.h"

Shape *ShapeFactory::CreateShape(int shapeId) {
  CallbackMap::const_iterator i = callbacks_.find(shapeId);
  if (i == callbacks_.end()) {
// not found
    throw std::runtime_error("Unknown Shape ID");
  }
  // Invoke the creation function
  return (i->second)();
}