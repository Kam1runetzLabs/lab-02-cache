//
// Created by w1ckedente on 24.10.2020.
//

#include <TravelOrders/ReverseTravelOrder.hpp>
#include <config.hpp>

ReverseTravelOrder::ReverseTravelOrder(std::size_t bufferSize)
    : TravelOrder("reverse", bufferSize - 1) {}

std::size_t ReverseTravelOrder::GetNextIndex() {
  auto tmp = currentBufferIndex;
  currentBufferIndex -= CacheLineSize;
  return tmp;
}