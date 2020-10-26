// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef CACHE_REVERSETRAVELORDER_HPP
#define CACHE_REVERSETRAVELORDER_HPP

#include <TravelOrders/TravelOrder.hpp>

class ReverseTravelOrder : public TravelOrder {
 public:
  ReverseTravelOrder();
  ~ReverseTravelOrder() override = default;
  std::size_t GetNextIndex() override;
  void SetDefaultIndex() override;
  void SetBufferSize(std::size_t size) override;
};

#endif  // CACHE_REVERSETRAVELORDER_HPP
