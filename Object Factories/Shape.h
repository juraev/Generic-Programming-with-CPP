//
// Created by gitarist on 5/11/20.
//

#ifndef GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_SHAPE_H_
#define GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_SHAPE_H_

class Shape {
 public:
  virtual Shape* Clone() const = 0;
  virtual void Draw() const = 0;
  virtual void Rotate(double angle) = 0;
  virtual void Zoom(double zoomFactor) = 0;
};

class Line : public Shape
{
 public:
  virtual Line* Clone() const
  {
    return new Line(*this);
  }
};

#endif //GENERICPROGRAMMING_SRC_OBJECT_FACTORIES_SHAPE_H_
