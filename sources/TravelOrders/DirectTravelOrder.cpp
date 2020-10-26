// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <TravelOrders/DirectTravelOrder.hpp>
#include <config.hpp>

DirectTravelOrder::DirectTravelOrder() : TravelOrder("direct", 0) {}

std::size_t DirectTravelOrder::GetNextIndex() {
  auto tmp = currentBufferIndex;
  currentBufferIndex += CacheLineSize;
  return tmp;
}
void DirectTravelOrder::SetDefaultIndex() {
  currentBufferIndex = 0;
}
