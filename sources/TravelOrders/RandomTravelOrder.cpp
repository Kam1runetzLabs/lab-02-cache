// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <TravelOrders/RandomTravelOrder.hpp>
#include <config.hpp>
#include <random>

RandomTravelOrder::RandomTravelOrder() : TravelOrder("random", 1) {
  std::random_device rd;
  randomizer = std::mt19937_64(rd());
}

std::size_t RandomTravelOrder::GetNextIndex() {
  return ((randomizer() % bufferSize) / CacheLineSize) * CacheLineSize;
}
void RandomTravelOrder::SetDefaultIndex() { currentBufferIndex = 1; }
