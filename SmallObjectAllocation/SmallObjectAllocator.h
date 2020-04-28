//
// Created by gitarist on 4/12/20.
//

#ifndef GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_
#define GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_

#include "FixedAllocator.h"

class SmallObjectAllocator {
 public:
  SmallObjectAllocator(
      std::size_t chunkSize,
      std::size_t maxObjectSize)
  void* Allocate(std::size_t numBytes);
  void Deallocate(void* p, std::size_t size);

 private:
  vector<FixedAllocator> pool_;
  FixedAllocator* pLastAlloc_;
  FixedAllocator* pLastDealloc_;

};

#endif //GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_SMALLOBJECTALLOCATOR_H_
