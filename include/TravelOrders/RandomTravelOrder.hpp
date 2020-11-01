// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_TRAVELORDERS_RANDOMTRAVELORDER_HPP_
#define INCLUDE_TRAVELORDERS_RANDOMTRAVELORDER_HPP_

/*!
 * @brief одна из стандартных реализаций интерфейса TravelOrder, реализующая
 * поведение произвольного обхода*/

#include <TravelOrders/TravelOrder.hpp>
#include <random>

class RandomTravelOrder : public TravelOrder {
 public:
  RandomTravelOrder();
  ~RandomTravelOrder() override = default;

  std::size_t GetNextIndex() override;
  void SetDefaultIndex() override;

 private:
  std::mt19937 randomizer;
};

#endif  // INCLUDE_TRAVELORDERS_RANDOMTRAVELORDER_HPP_
