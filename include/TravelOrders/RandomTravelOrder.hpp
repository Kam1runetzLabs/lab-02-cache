//
// Created by w1ckedente on 24.10.2020.
//

#ifndef CACHE_RANDOMTRAVELORDER_HPP
#define CACHE_RANDOMTRAVELORDER_HPP

#include <TravelOrders/TravelOrder.hpp>
#include <random>

class RandomTravelOrder : public TravelOrder {
 public:
  explicit RandomTravelOrder();
  ~RandomTravelOrder() override = default;

  std::size_t GetNextIndex() override;
  void SetDefaultIndex() override;
 private:
  std::mt19937_64 randomizer;
};

#endif  // CACHE_RANDOMTRAVELORDER_HPP
