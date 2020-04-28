//
// Created by gitarist on 3/31/20.
//

#ifndef GENERICPROGRAMMING_LOCAL_CLASSES_H
#define GENERICPROGRAMMING_LOCAL_CLASSES_H

void Fun() {
  class Local {
//        ... member variables ...
//        ... member function definitions ...
  };
//    ... code using Local ...
}

class Interface {
 public:
  virtual void Fun() = 0;
};

template<class T, class P>
Interface *MakeAdapter(const T &obj, const P &arg)
{
  class Local : public Interface{
   public:
    Local(const T& obj, const P& arg) : obj_(obj), arg_(arg){}
   private:
    T obj_;
    P arg_;
  };
  return new Local(obj, arg);
}

#endif //GENERICPROGRAMMING_LOCAL_CLASSES_H
