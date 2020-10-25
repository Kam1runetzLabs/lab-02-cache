//
// Created by w1ckedente on 24.10.2020.
//

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
