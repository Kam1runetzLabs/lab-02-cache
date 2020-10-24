//
// Created by w1ckedente on 24.10.2020.
//
#include <TravelOrders/RandomTravelOrder.hpp>
#include <config.hpp>
#include <random>

RandomTravelOrder::RandomTravelOrder(std::size_t bufferSize)
    : TravelOrder("random", bufferSize) {
  std::random_device rd;
  randomizer = std::mt19937_64(rd());
}

std::size_t RandomTravelOrder::GetNextIndex() {
  return ((randomizer() % currentBufferIndex) / CacheLineSize) * CacheLineSize;
}
