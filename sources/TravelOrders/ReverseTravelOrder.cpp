// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <TravelOrders/ReverseTravelOrder.hpp>
#include <config.hpp>


ReverseTravelOrder::ReverseTravelOrder() : TravelOrder("reverse", 0) {}

std::size_t ReverseTravelOrder::GetNextIndex() {
  auto tmp = currentBufferIndex;
  if (currentBufferIndex - CacheLineSize + 1 == 0)
    currentBufferIndex = 0;
  else
    currentBufferIndex -= CacheLineSize;
  return tmp;
}
void ReverseTravelOrder::SetDefaultIndex() {
  currentBufferIndex = bufferSize - 1;
}
void ReverseTravelOrder::SetBufferSize(std::size_t size) {
  currentBufferIndex = bufferSize - 1;
  bufferSize = size;
}
