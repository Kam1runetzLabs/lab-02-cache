// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

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
