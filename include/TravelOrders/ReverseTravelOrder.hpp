//
// Created by w1ckedente on 24.10.2020.
//

#ifndef CACHE_REVERSETRAVELORDER_HPP
#define CACHE_REVERSETRAVELORDER_HPP

#include <TravelOrders/TravelOrder.hpp>

class ReverseTravelOrder : public TravelOrder {
 public:
  ReverseTravelOrder(std::size_t bufferSize);
  std::size_t GetNextIndex() override;
};

#endif  // CACHE_REVERSETRAVELORDER_HPP
