//
// Created by w1ckedente on 24.10.2020.
//

#ifndef CACHE_DIRECTTRAVELORDER_HPP
#define CACHE_DIRECTTRAVELORDER_HPP

#include <TravelOrders/TravelOrder.hpp>

class DirectTravelOrder : public TravelOrder {
 public:
  DirectTravelOrder();
  std::size_t GetNextIndex() override;
};

#endif  // CACHE_DIRECTTRAVELORDER_HPP
