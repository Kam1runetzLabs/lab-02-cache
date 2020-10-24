//
// Created by w1ckedente on 24.10.2020.
//

#include <TravelOrders/DirectTravelOrder.hpp>
#include <config.hpp>

DirectTravelOrder::DirectTravelOrder() : TravelOrder("direct", 0) {}

std::size_t DirectTravelOrder::GetNextIndex() {
  auto tmp = currentBufferIndex;
  currentBufferIndex += CacheLineSize;
  return tmp;
}