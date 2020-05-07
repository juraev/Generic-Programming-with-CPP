//
// Created by gitarist on 4/29/20.
//
#include "Singleton.h"

Singleton::destroyed_ = false;

void Singleton::OnDeadReference() {
// Obtain the shell of the destroyed singleton
  Create();
// Now pInstance_ points to the "ashes" of the singleton // - the raw memory that the singleton was seated in.
// Create a new singleton at that address
  new(pInstance_) Singleton;
// Queue this new object's destruction
  atexit(KillPhoenixSingleton);
// Reset destroyed_ because we're back in business
  destroyed_ = false;
}
void Singleton::KillPhoenixSingleton() {
// Make all ashes again
// - call the destructor by hand.
// It will set pInstance_ to zero and destroyed_ to true
  pInstance_->~Singleton();
}

Singleton &Singleton::Instence() {
  if (!pInstance_) {

    if (destroyed_) {
      OnDeadReference();
    } else {
      //First call-initialize
      Create();
    }
  }
  return *pInstance_;
}
void Singleton::Create() {
  //Task: initialize pInstance_
  static Singleton theInstance;
  pInstance_ = &theInstance;
}
Singleton::~Singleton() {
  pInstance_ = nullptr;
  destroyed_ = true;
}

static void Private::AtExitFn() {
  assert(elements > 0 && pTrackerArray != 0);
// Pick the element at the top of the stack
  LifetimeTracker *pTop = pTrackerArray[elements - 1];
// Remove that object off the stack
// Don't check errors-realloc with less memory
// can't fail
  pTrackerArray = static_cast<TrackerArray>(std::realloc(
      pTrackerArray, sizeof(T) * --elements)); // Destroy the element
  delete pTop;

}
