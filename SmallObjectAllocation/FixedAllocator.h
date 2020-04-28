//
// Created by gitarist on 4/12/20.
//

#ifndef GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_FIXEDALLOCATOR_H_
#define GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_FIXEDALLOCATOR_H_

#include "Chunk.h"
#include <vector>

class FixedAllocator {

  void* Allocate();
  void Deallocate(void*);

 private:
  std::size_t blockSize_;
  unsigned char numBlocks_;
  typedef std::vector<Chunk> chunks_;
  Chunk* allocChunk_;
  Chunk* deallocChunk_;
};

void* FixedAllocator::Allocate(){
  if(allocChunk_ == 0 || allocChunk_ -> blocksAvailable_ == 0){
    Chunks::iterator i = chunks_.begin();
    for(;; i++){
      if(i == chunks_.end()){
        //All filled up-add a new chunk
        chunks_.reserve(chunks_.size()+1);
        Chunk newChunk;
        newChunk.Init(blockSize_, numBlocks_);
        chunks_.push_back(newChunk);
        allocChunk_ = &chunks_.back();
        deallocChunk_ = &chunks_.back();
        break;
      }
      if(i->blocksAvailable_ > 0){
        allocChunk_ = &*i;
        break;
      }
    }
  }
  assert(allocChunk_!= 0);
  assert(allocChunk_ -> blocksAvailable_ > 0);
  return allocChunk_ -> Allocate(blockSize_);
}

void FixedAllocator::Deallocate(void* p) {
  unsigned char *toRelease = static_cast<unsigned char *>(p);



}
#endif //GENERICPROGRAMMING_SRC_SMALLOBJECTALLOCATION_FIXEDALLOCATOR_H_
