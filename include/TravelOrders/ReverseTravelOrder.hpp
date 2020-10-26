// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_TRAVELORDERS_REVERSETRAVELORDER_HPP_
#define INCLUDE_TRAVELORDERS_REVERSETRAVELORDER_HPP_

#include <TravelOrders/TravelOrder.hpp>

class ReverseTravelOrder : public TravelOrder {
 public:
  ReverseTravelOrder();
  ~ReverseTravelOrder() override = default;
  std::size_t GetNextIndex() override;
  void SetDefaultIndex() override;
  void SetBufferSize(std::size_t size) override;
};

#endif  // INCLUDE_TRAVELORDERS_REVERSETRAVELORDER_HPP_
