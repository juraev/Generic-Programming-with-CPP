//
// Created by gitarist on 4/29/20.
//

#ifndef GENERICPROGRAMMING_SRC_SINGLETONS_SINGLETON_H_
#define GENERICPROGRAMMING_SRC_SINGLETONS_SINGLETON_H_

#include <iostream>
#include <cstdlib>
#include <algorithm>

class Singleton {
 public:
  Singleton &Instance();

 private:

  //Create new singleton
  //pointer to it in pInstance_
  static void Create();

  //Gets called if dead reference detected
  static void OnDeadReference();

  virtual ~Singleton();

  static Singleton *pInstance_;
  static bool destroyed_;

  Singleton();
  Singleton(const Singleton &);
  void operator=(const Singleton &);
  static void KillPhoenixSingleton(); // Added
};

namespace Private {
class LifetimeTracker {
 public:
  LifetimeTracker(unsigned int x) : longevity_{x} {}
  virtual ~LifetimeTracker() = 0;

  friend inline bool Compare(unsigned int longevity, const LifetimeTracker *p);
  unsigned int longevity_;
};

inline bool Compare(unsigned int longevity, const LifetimeTracker *p) {
  return p->longevity_ > longevity;
}

typedef LifetimeTracker **TrackerArray;
extern TrackerArray pTrackerArray;
extern unsigned int elements;

//Helper destroyer function
template<typename T>
struct Deleter {
  static void Delete(T *pObj) { delete pObj; }
};

// Concrete lifetime tracker for objects of type T
template<typename T, typename Destroyer>
class ConcreteLifetimeTracker : public LifetimeTracker {
 public:

  ConcreteLifetimeTracker(T *p, unsigned int longevity, Destroyer d)
      : LifetimeTracker(longevity), pTracked_(p), destroyer_(d) {}

  ~ConcreteLifetimeTracker() override {
    destroyer_(pTracked_);
  }
 private:
  T *pTracked_;
  Destroyer destroyer_;
};

void AtExitFn(); // Declaration needed below

template<typename T, typename Destroyer>

void SetLongevity(
    T *pDynObject,
    unsigned int longevity,
    Destroyer d = Private::Deleter<T>::Delete) {

  auto pNewArray = static_cast<TrackerArray>( std::realloc(pTrackerArray, sizeof(T) * (elements + 1)));

  if (!pNewArray) throw std::bad_alloc();

  pTrackerArray = pNewArray;

  LifetimeTracker *p = new ConcreteLifetimeTracker<T, Destroyer>(pDynObject, longevity, d);

  TrackerArray pos = std::upper_bound(pTrackerArray, pTrackerArray + elements, longevity, Compare);

  std::copy_backward(pos, pTrackerArray + elements, pTrackerArray + elements + 1);

  *pos = p;
  ++elements;
  std::atexit(AtExitFn);
}
}

class CreateUsingNew;
class DefaultLifetime;

template<class T>
class SingleThreaded {
//...
 public:
  typedef T VolatileType;
};

template<
    class T,
    template<class> class CreationPolicy = CreateUsingNew,
    template<class> class LifetimePolicy = DefaultLifetime,
    template<class> class ThreadingModel = SingleThreaded>
class SingletonHolder {
 public:
  static T &Instance();
 private:
// Helpers
  static void DestroySingleton();
// Protection
  SingletonHolder();
//  ...
// Data
  typedef typename ThreadingModel<T>::VolatileType InstanceType;
  static InstanceType *pInstance_;
  static bool destroyed_;
};

template<class T, class CreationPolicy, class LifetimePolicy, class ThreadingModel>
T &SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadingModel>::Instance() {
  if (!pInstance_) {
    typename ThreadingModel<T>::Lock guard;
    if (!pInstance_) {
      if (destroyed_) {
        LifetimePolicy<T>::OnDeadReference();
        destroyed_ = false;
      }
      pInstance_ = CreationPolicy<T>::Create();
      LifetimePolicy<T>::ScheduleCall(&DestroySingleton);
    }
  }
  return *pInstance_;
}
template<class T, class CreationPolicy, class LifetimePolicy, class ThreadingModel>
void SingletonHolder<T, CreationPolicy, LifetimePolicy, ThreadingModel>::DestroySingleton() {
  assert(!destroyed_);
  CreationPolicy<T>::Destroy(pInstance_);
  pInstance_ = 0;
  destroyed_ = true;
}
#endif //GENERICPROGRAMMING_SRC_SINGLETONS_SINGLETON_H_
