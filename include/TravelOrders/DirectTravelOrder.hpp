// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef CACHE_DIRECTTRAVELORDER_HPP_
#define CACHE_DIRECTTRAVELORDER_HPP_

#include <TravelOrders/TravelOrder.hpp>

class DirectTravelOrder : public TravelOrder {
 public:
  DirectTravelOrder();
  ~DirectTravelOrder() override = default;
  std::size_t GetNextIndex() override;
  void SetDefaultIndex() override;
};

#endif  // CACHE_DIRECTTRAVELORDER_HPP_
